#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>

#define scanTime 5

class AdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    
    Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());   // Print the device's address / name

    if (advertisedDevice.haveManufacturerData()) {
      String manufacturerData = advertisedDevice.getManufacturerData();
      Serial.print("Received Message: ");
      const char* data = manufacturerData.c_str();
      for (size_t i = 2; i < manufacturerData.length(); i++) { Serial.printf("%c", (char)data[i]);  }  // Print the manufacture data ( message ) 
      Serial.println();
    }
  }
};

void setup() {
  Serial.begin(115200);

  // Initialize BLE
  BLEDevice::init("");
  
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());

  // Set the scan interval and window
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);

  // Start the scan
  pBLEScan->setActiveScan(true);     // Active scan uses more power but returns more data
  pBLEScan->start(scanTime, false);  // The second argument is to not continue scanning after the timeout
}

void loop() {
  // Start scanning again after previous scan ends
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->start(scanTime, false);
}
