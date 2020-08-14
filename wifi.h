#ifndef WIFI
#define WIFI
#define BOOT_FAST 0 // Set 1 để khởi động nhanh, không chờ setting.
#define DEFAULT_APID "VOCAUI"
#define DEFAULT_APPASS "12345678"
#define DEFAULT_STAID "Vong Cat-Hide"
#define DEFAULT_STAPASS "78787878"
#include "sysDefine.h"
#include "sysFunc.h"
#include "renderHtml.h"
#include "vocaui.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#ifdef ETHERNET
#include <SPI.h>
#include <Ethernet2.h>
#define CLIENT EthernetClient
#else
#define CLIENT WiFiClient
#endif
CLIENT vocaClient;
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
bool gotTime = false;
bool keepSetting = false;
uint32_t timerSettingMode = 0;
extern void handleChangeValueEvent();
void initWifi() {

  server.on("/", []() {
    keepSetting = true;
    server.send(200, "text/html", getPage());

  });
  server.on("/script.js", []() {
    server.send_P(200, "text/javascript", java_script);
  });
  server.on("/style.css", []() {


    server.send_P(200, "text/css", menu_css);
  });
  server.on("/recv", []() {

    for (int i = 0; i < server.args(); ++i)
    {
      String key = server.argName(i);
      String value = server.arg(i);

      if (key == "rst")
        ESP.reset();
      if (key == "fmt") {
        clearRoot();
        LittleFS.format();
      }
      if (key == "all") { // yeu cau gui du lieu
        setValue("", "");
      }
      setValue(key.c_str(), value.c_str());
    }
    saveConfigFile();


    server.send(200, "text/html", "");
  });
  server.on("/trans", []() { // server truyền dữ liệu




    String key = server.argName(0);
    String value = server.arg(0);
    uint32_t cToken = 0;
    if (key == "tokn") {
      cToken = value.toInt();
    }
    server.sendHeader("tokn", String(countSetValue));

    if (cToken == countSetValue) { // Chưa có dữ liệu mới
      server.send(504, "text/html", "");
      return;
    }
    String tmp = getRoot();

    server.send(200, "application/json", getRoot());
  });
  httpUpdater.setup(&server);
  server.begin();
  WiFi.disconnect(true);
  if (!BOOT_FAST || String(getValue("wfMode")) == "ST") // setting mode
  {
    pinMode(LED_BUILTIN, OUTPUT);
    ConfigContent["wfMode"] = "WK";// work mode
    saveConfigFile();
    WiFi.mode(WIFI_AP);
    if (checkKey("apid")
        && checkKey("appass")) {
      WiFi.softAP(getValue("apid"), getValue("appass"));
    } else {
      WiFi.softAP(String(DEFAULT_APID) + NAME_DEVICE + "_" + getValue("deviceId"), DEFAULT_APPASS);
    }
    /*
    Trong vòng 40s mà chưa vào trang setting 
    thì tiếp tục chương trình
    */
    while (keepSetting
           || millis() < 40000) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      server.handleClient();
      handleChangeValueEvent();
      delay(50);
    }
  }
  server.stop();

#ifndef ETHERNET
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(String(NAME_DEVICE) + "_" + getValue("deviceId"));
  //    WiFi.macAddress(macAddr);
  if (checkKey("staid")
      && checkKey("stapass")) {
    WiFi.begin(getValue("staid"), getValue("stapass"));
  } else {
    WiFi.begin(DEFAULT_STAID, DEFAULT_STAPASS);
  }
#else
  SPI.begin();
  Ethernet.init(D4);
  Ethernet.begin(macAddr);
  Serial.print("  DHCP assigned IP ");
  Serial.println(Ethernet.localIP());
#endif

}
uint32_t getEpochTime() {
  vocaClient.stop();
  if (vocaClient.connect("www.ngoinhaiot.com", 80)) {

    vocaClient.println("GET /user/sysTime HTTP/1.1");

    vocaClient.println(String("Name: ") + getValue("user"));
    vocaClient.println(String("Password: ") + getValue("pass"));
    vocaClient.println();
    vocaClient.flush();
  }
  else {
    return 0;
  }
  delay(1000);
  String response = vocaClient.readString();
  uint32_t resLen = response.length();
  uint32_t idxCL = response.indexOf("Content-Length: ") + 16;
  uint32_t contentLength = response.substring(idxCL, response.indexOf("\n", idxCL)).toInt();
  String data = response.substring(resLen - contentLength);
  vocaClient.stop();
  return data.toInt();

}
uint32_t calcEpochTime() {

  // int32_t delta = (millis() - epochTimeTmp);
  // if(!gotTime)
  //   return 0;
  // if(delta<0){
  //   epochTime+=(4294967295-epochTimeTmp+millis())/1000;
  // }else{
  //     epochTime+=delta/1000;
  //   }
  // epochTimeTmp=millis();
  // epochTime = (millis() - epochTimeTmp)/1000;
  return epochTime +  (millis() - epochTimeTmp) / 1000 + 3600 * 7;
}
void wifiHandle() {
  if (millis() - timerSettingMode > 1000) {
    timerSettingMode = millis();
    if(gotTime){
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      }
    if (String(getValue("wfMode")) == "ST"
        && digitalRead(D3) == HIGH) {
      ESP.reset();
    }
    if (digitalRead(D3) == LOW) { // nếu nút flash được nhấn.
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
      ConfigContent["wfMode"] = "ST";
      saveConfigFile();
    }
  }
  /*
  Nếu chạy được 60s mà chưa vào được internet thì
  khởi động lại và vào chế độ setting
  */
  if (!gotTime && millis() > 60000) { 
    ConfigContent["wfMode"] = "ST";
    saveConfigFile();
    ESP.reset();
  }
  if (WiFi.status() == WL_CONNECTED
      && !gotTime) {
    epochTime = getEpochTime();
    if (epochTime > 0) {
      gotTime = true;

      epochTimeTmp = millis();
    }
  }else{
    delay(500);
    }

}

#endif
