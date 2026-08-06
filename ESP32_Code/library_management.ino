// ESP32 RFID Library Management Code
/*
=========================================================
RFID-Based Library Management System

Author: Akanksha Magdum

Description:
An ESP32-based RFID Library Management System that
automates book issue and return operations using
MFRC522 RFID Reader, DS3231 RTC, PHP, and MySQL.

Hardware:
- ESP32 Dev Board
- MFRC522 RFID Reader
- DS3231 RTC Module
- RFID Tags

Software:
- Arduino IDE
- PHP
- MySQL
=========================================================
*/


#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <RTClib.h>

#define SS_PIN 5
#define RST_PIN 4

MFRC522 rfid(SS_PIN, RST_PIN);
RTC_DS3231 rtc;

const char* ssid="YOUR_WIFI_SSID";
const char* password="YOUR_WIFI_PASSWORD";
const char* serverName="http://YOUR_SERVER_IP/rfid_library/insert_data.php";

String studentID="", bookID="";

String getUID(){
  String uid="";
  for(byte i=0;i<rfid.uid.size;i++){
    if(rfid.uid.uidByte[i]<0x10) uid+="0";
    uid+=String(rfid.uid.uidByte[i],HEX);
  }
  uid.toLowerCase();
  return uid;
}

String resolveUID(String uid){
  if(uid=="302f8a3f") return "21ST116331023";
  if(uid=="c31124e4") return "EMBEDDED SYSTEMS";
  return "UNKNOWN";
}

void sendToServer(String sid,String bid,String scan,String issue){
  if(WiFi.status()!=WL_CONNECTED) return;
  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type","application/x-www-form-urlencoded");
  String post="student_id="+sid+"&book_id="+bid+"&scan_time="+scan+
              "&issue_date="+issue+"&status=Issued";
  int code=http.POST(post);
  Serial.print("HTTP: ");Serial.println(code);
  Serial.println(http.getString());
  http.end();
}

void setup(){
  Serial.begin(115200);
  SPI.begin();
  Wire.begin();
  rfid.PCD_Init();
  rtc.begin();
  if(rtc.lostPower()) rtc.adjust(DateTime(__DATE__,__TIME__));
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){delay(500);Serial.print(".");}
  Serial.println("\nReady...");
}

void loop(){
  if(!rfid.PICC_IsNewCardPresent()||!rfid.PICC_ReadCardSerial()) return;
  String uid=getUID();
  String val=resolveUID(uid);

  if(val.startsWith("21")){
    studentID=val;
    Serial.println("Student: "+studentID);
  }else if(val!="UNKNOWN"){
    bookID=val;
    Serial.println("Book: "+bookID);
  }

  if(studentID!="" && bookID!=""){
    DateTime now=rtc.now();
    char dt[20], d[11];
    sprintf(dt,"%04d-%02d-%02d %02d:%02d:%02d",now.year(),now.month(),now.day(),now.hour(),now.minute(),now.second());
    sprintf(d,"%04d-%02d-%02d",now.year(),now.month(),now.day());
    sendToServer(studentID,bookID,String(dt),String(d));
    studentID="";
    bookID="";
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000);
}

