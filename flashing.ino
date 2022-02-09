
/*
  boot_app0.bin
  bootloader_qio_80m.bin
  trigBoardV8_BaseFirmware.ino.bin
  trigBoardV8_BaseFirmware.ino.partitions.bin
*/

bool startFlashing() {
  digitalWrite(En3VPin, HIGH);
  ESPFlasherInit(true, &Serial);//sets up Serial communication to wifi module, with debug messages, to Print Class of your choice
  if (ESPFlasherConnect()) {       //connects to wifi module
    if (ESPFlashBin(bootName, 0xe000)) { //bootapp
      ESPFlasherInit(true, &Serial);
      if (ESPFlasherConnect()) {
        if (ESPFlashBin(bootloaderName, 0x1000)) { //bootloader
          ESPFlasherInit(true, &Serial);
          if (ESPFlasherConnect()) {
            if (ESPFlashBin(firmwareName, 0x10000)) { //firmware
              ESPFlasherInit(true, &Serial);
              if (ESPFlasherConnect())
                if (ESPFlashBin(partitionsName, 0x8000)) { //partitions
                  Serial.println("!!!EVERYTHING IS FLASHED AND COMPLETE!!!");
                  return true;
                }
            }
          }
        }
      }
    }
  }
  return false;
}
