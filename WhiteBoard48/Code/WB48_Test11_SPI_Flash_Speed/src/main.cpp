#include <Arduino.h>
// The MIT License (MIT)
// Copyright (c) 2019 Ha Thach for Adafruit Industries

#include <SPI.h>
#include <SdFat.h>

#include "Adafruit_SPIFlash.h"
HardwareSerial uart2(PA3, PA2);
// for flashTransport definition
#include "flash_config.h"

Adafruit_SPIFlash flash(&flashTransport);
bool write_and_compare(uint8_t pattern);

#ifdef __AVR__
#define BUFSIZE 512
#else
#define BUFSIZE 4096
#endif

#define TEST_WHOLE_CHIP 1

#ifdef LED_BUILTIN
uint8_t led_pin = PA15;
#else
uint8_t led_pin = 0;
#endif

// 4 byte aligned buffer has best result with nRF QSPI
uint8_t bufwrite[BUFSIZE] __attribute__((aligned(4)));
uint8_t bufread[BUFSIZE] __attribute__((aligned(4)));

// the setup function runs once when you press reset or power the board
void setup() {
  uart2.begin(115200);
  while (!Serial) {
    delay(100); // wait for native usb
  }
  flash.begin();

  pinMode(led_pin, OUTPUT);
  flash.setIndicator(led_pin, true);

  uart2.println("Adafruit Serial Flash Speed Test example");
  uart2.print("JEDEC ID: ");
  uart2.println(flash.getJEDECID(), HEX);
  uart2.print("Flash size: ");
  uart2.println(flash.size());
  uart2.flush();

  write_and_compare(0xAA);
  write_and_compare(0x55);

  uart2.println("Speed test is completed.");
  uart2.flush();
}

void print_speed(const char *text, uint32_t count, uint32_t ms) {
  uart2.print(text);
  uart2.print(count);
  uart2.print(" bytes in ");
  uart2.print(ms / 1000.0F, 2);
  uart2.println(" seconds.");

  uart2.print("Speed: ");
  uart2.print((count / 1000.0F) / (ms / 1000.0F), 2);
  uart2.println(" KB/s.\r\n");
}

bool write_and_compare(uint8_t pattern) {
  uint32_t ms;

  uart2.println("Erase chip");
  uart2.flush();

#if TEST_WHOLE_CHIP
  uint32_t const flash_sz = flash.size();
  flash.eraseChip();
#else
  uint32_t const flash_sz = 4096;
  flash.eraseSector(0);
#endif

  flash.waitUntilReady();

  // write all
  memset(bufwrite, (int)pattern, sizeof(bufwrite));
  uart2.print("Write flash with 0x");
  uart2.println(pattern, HEX);
  uart2.flush();
  ms = millis();

  for (uint32_t addr = 0; addr < flash_sz; addr += sizeof(bufwrite)) {
    flash.writeBuffer(addr, bufwrite, sizeof(bufwrite));
  }

  uint32_t ms_write = millis() - ms;
  print_speed("Write ", flash_sz, ms_write);
  uart2.flush();

  // read and compare
  uart2.println("Read flash and compare");
  uart2.flush();
  uint32_t ms_read = 0;
  for (uint32_t addr = 0; addr < flash_sz; addr += sizeof(bufread)) {
    memset(bufread, 0, sizeof(bufread));

    ms = millis();
    flash.readBuffer(addr, bufread, sizeof(bufread));
    ms_read += millis() - ms;

    if (memcmp(bufwrite, bufread, BUFSIZE)) {
      uart2.print("Error: flash contents mismatched at address 0x");
      uart2.println(addr, HEX);
      for (uint32_t i = 0; i < sizeof(bufread); i++) {
        if (i != 0)
          uart2.print(' ');
        if ((i % 16 == 0)) {
          uart2.println();
          if (i < 0x100)
            uart2.print('0');
          if (i < 0x010)
            uart2.print('0');
          uart2.print(i, HEX);
          uart2.print(": ");
        }

        if (bufread[i] < 0x10)
          uart2.print('0');
        uart2.print(bufread[i], HEX);
      }

      uart2.println();
      return false;
    }
  }

  print_speed("Read  ", flash_sz, ms_read);
  uart2.flush();

  return true;
}

void loop() {
  // nothing to do
}