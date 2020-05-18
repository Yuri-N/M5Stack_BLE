// M5STACKでadvertinzing packetを受信する
// 2020/01/17 Programed by Yuri

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <M5Stack.h>

int scanTime = 10000; // スキャン完了までの秒数 (2 hours)

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    char uuid[60];
    String uuid_str;
    BLEAddress addr = advertisedDevice.getAddress();
    int rssi = advertisedDevice.getRSSI();
    std::string data = advertisedDevice.getManufacturerData();

//  FIND iBeacon
//   data[0]+data[1] :  Company Identifiers. 0x4c00=Apple,Inc
//   data[2]+data[3] :  Beacon type. 0x0215=iBeacon
//
     if(data.length() == 25)
    {
      if((data[0] == 0x4c) && (data[1] == 0x00) && (data[2] == 0x02) && (data[3] == 0x15)) {
        sprintf(uuid,"%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X"
          ,data[4],data[5],data[6],data[7],data[8],data[9],data[10],data[11],data[12],data[13]
          ,data[14],data[15],data[16],data[17],data[18],data[19]);
        int major = (int)(((data[20]&0xff) << 8) + (data[21] & 0xff));
        int minor = (int)(((data[22]&0xff) << 8) + (data[23] & 0xff));
        signed char power = (signed char)(data[24]&0xff);

//MAMORIO UUID=b9407f30-f5f8-466e-aff9-25556b57fe6e
        uuid_str = uuid;
        if (uuid_str.equalsIgnoreCase("b9407f30-f5f8-466e-aff9-25556b57fe6e")==true){
            Serial.printf("FOUND MAMORIO!!! major=0x%x,minor=0x%x,power=%d",major,minor,power);
            Serial.println("");
        }
        else {
          Serial.println("FOUND iBeacon!!!"); 
          Serial.printf("addr=%s rssi=%d uuid=%s,major=0x%x,minor=0x%x,power=%d",addr.toString().c_str(),rssi,uuid,major,minor,power);
          Serial.println("");
        }
      }
    }
  }
};

void setup() {
  M5.begin();

  Serial.begin(115200);
  M5.Lcd.fillScreen(0x000F); //NAVY
  M5.Lcd.setCursor(50, 50);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("START");
  M5.Lcd.setCursor(10, 40);
}


void loop() {
  M5.Lcd.fillScreen(0xFFE0);//Yellow
  M5.Lcd.setCursor(50, 50);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("Scan MAMORIO start!");

  Serial.println("Scan MAMORIO start!");
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(),true);   
  pBLEScan->setActiveScan(true);
  BLEScanResults foundDevices = pBLEScan->start(scanTime);
  Serial.println("Scan done!");
  
  M5.Lcd.fillScreen(0x000F); //NAVY
  M5.Lcd.setCursor(50, 50);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("Scan done!");
}
