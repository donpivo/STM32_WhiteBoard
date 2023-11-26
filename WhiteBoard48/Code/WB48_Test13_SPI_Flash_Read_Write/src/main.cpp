/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>

#include "SdFat.h"

#include "Adafruit_SPIFlash.h"

// for flashTransport definition
#include "flash_config.h"

Adafruit_SPIFlash flash(&flashTransport);
HardwareSerial uart2(PA3, PA2);

// file system object from SdFat
FatVolume fatfs;
File32 myFile;

void setup() {
  // Open serial communications and wait for port to open:
  uart2.begin(115200);
  while (!Serial) {
    delay(
        10); // wait for serial port to connect. Needed for native USB port only
  }

  uart2.println("Initializing Filesystem on external flash...");

  // Init external flash
  flash.begin();

  // Open file system on the flash
  if (!fatfs.begin(&flash)) {
    uart2.println("Error: filesystem is not existed. Please try SdFat_format "
                   "example to make one.");
    while (1) {
      yield();
      delay(1);
    }
  }

  uart2.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = fatfs.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    uart2.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    uart2.println("done.");
  } else {
    // if the file didn't open, print an error:
    uart2.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = fatfs.open("test.txt");
  if (myFile) {
    uart2.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      uart2.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    uart2.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}
