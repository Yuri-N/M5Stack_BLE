// M5STACK(ESP32)でadvertinzing packetを受信してシリアルターミナルに表示する
// 2020/05/15 Programed by Yuri

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <M5Stack.h>

int scanTime = 10000; // スキャン完了までの秒数 (2 hours)

//********Call back: アドバタイジングパケット受信時に呼ばれる関数***// 
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    char uuid[60];
    BLEAddress addr = advertisedDevice.getAddress();
    int rssi = advertisedDevice.getRSSI();
    std::string data = advertisedDevice.getManufacturerData();

//  FIND iBeacon
    if(data.length() == 25)
    {
      if((data[0] == 0x4c) && (data[1] == 0x00) && (data[2] == 0x02) && (data[3] == 0x15)) {
        Serial.println("FOUND iBeacon!!!");
        sprintf(uuid,"%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X"
          ,data[4],data[5],data[6],data[7],data[8],data[9],data[10],data[11],data[12],data[13]
          ,data[14],data[15],data[16],data[17],data[18],data[19]);
        int major = (int)(((data[20]&0xff) << 8) + (data[21] & 0xff));
        int minor = (int)(((data[22]&0xff) << 8) + (data[23] & 0xff));
        signed char power = (signed char)(data[24]&0xff);

        Serial.printf("Device Name=%s addr=%s rssi=%d uuid=%s,major=%d,minor=%d,power=%d",advertisedDevice.getName().c_str(), addr.toString().c_str(),rssi,uuid,major,minor,power);
        Serial.println("");
      }
    }
//  FIND other Advertinzing packet
    else{
      Serial.printf("Device Name=%s ",advertisedDevice.getName().c_str());
      Serial.printf("addr=%s rssi=%d",addr.toString().c_str(),rssi);
      Serial.println("");
      Serial.printf("ManufacturerData=");
      for(int i=0; i<data.length(); i++){
        Serial.printf("%02X", data[i]);
      }
      Serial.println("");
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
  M5.Lcd.printf("Scan start!");

  Serial.println("Scan start!");
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
