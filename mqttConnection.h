#ifndef MQTT_CONNECTION
#define MQTT_CONNECTION
#include <PubSubClient.h>
#include "html/sourceHtml.h"
#include "sysFunc.h"
#include "wifi.h"
CLIENT cMQTT;
PubSubClient mqttClient(cMQTT);
std::map < String, String > inComeData;
void json2MapInComeData(String json);
bool isPubDasboard = false;
void publicMqtt(String data, String topic, bool retain = false) {
  mqttClient.beginPublish(topic.c_str(), data.length(), retain);
  mqttClient.write((const uint8_t*)data.c_str(), data.length());
  mqttClient.endPublish();






}
//void publicMqtt(String data, String topic, bool retain = false) {
//  mqttClient.publish(topic.c_str(), data.c_str(),retain);
//
//}
void initMqttConnection() {
  static bool isInit = false;
  if (isInit)
    return;
  isInit = true;

    vocaClient.stop();
    if (vocaClient.connect("www.ngoinhaiot.com", 80)) {

      vocaClient.println("GET /user/mqttInfo HTTP/1.1");

      vocaClient.println(String("Name: ") + getValue("user"));
      vocaClient.println(String("Password: ") + getValue("pass"));
      vocaClient.println();
      vocaClient.flush();
    }
    else {

    }
    delay(1000);
    String response = vocaClient.readString();

    String mqttPass = response.substring(response.indexOf("mqttpass\":\"") + 11, response.indexOf("\"", response.indexOf("mqttpass\":\"") + 11));
    String mqttUser = response.substring(response.indexOf("name\":\"") + 7, response.indexOf("\"", response.indexOf("name\":\"") + 7));

    setValue("mqttUser", mqttUser);
    setValue("mqttPass", mqttPass);
    setValue("mqttAddr", "mqtt.ngoinhaiot.com");
    setValue("mqttPort", "1111");
    vocaClient.stop();
  



  mqttClient.setBufferSize(1024);
  mqttClient.setServer(getValue("mqttAddr"), String(getValue("mqttPort")).toInt());
  mqttClient.setCallback([](char* topic, byte * payload, unsigned int length) {
    String tmp;
    for (int i = 0; i < length; i++) {
      tmp += (char)payload[i];
    }
    json2MapInComeData(tmp);
    setValue(inComeData["id"], inComeData["value"]);
    if (inComeData["id"] == "all") {
      publicMqtt(String(getRoot()), String(getValue("mqttUser")) + "/" + NAME_DEVICE + "_" + getValue("deviceId") + "/tx");

    } else if (inComeData["id"] == "ui") {
      publicMqtt(String(getPage()), String(getValue("mqttUser")) + "/" + NAME_DEVICE + "_" + getValue("deviceId") + "/dashboard", true);


    }

  });
  String clientId = NAME_DEVICE;
  clientId += String(random(0xffff), HEX);
  mqttClient.connect(clientId.c_str(), getValue("mqttUser"), getValue("mqttPass"));
  mqttClient.subscribe((String(getValue("mqttUser")) + "/" + NAME_DEVICE + "_" + getValue("deviceId") + "/rx/#").c_str(), 1);


  isPubDasboard = false;


}

void mqttHandle() {
  if (!mqttClient.connected()) {
    initMqttConnection();
    return;
  }
  if (!isPubDasboard) {
    publicMqtt(String(getPage()), String(getValue("mqttUser")) + "/" + NAME_DEVICE + "_" + getValue("deviceId") + "/dashboard", true);
    isPubDasboard = true;
  }

  mqttClient.loop();
}
void json2MapInComeData(String json) {
  inComeData.clear();
  if (json.startsWith("{")
      && json.endsWith("}")) {
    json.replace("{", "");
    json.replace("}", "");
    while (json.length() > 0) {
      String key;
      String value;
      int32_t idx = json.lastIndexOf(",");
      String sub ;
      if (idx >= 0) {
        sub = json.substring(idx + 1, json.length());
        json.remove(idx, json.length());


      } else {
        sub = json;

        json.remove(0, json.length());
      }
      sub.replace("\"", "");
      key = sub.substring(0, sub.indexOf(":"));
      value = sub.substring(sub.indexOf(":") + 1, sub.length());
      inComeData[key] = value;
    }
  }
}

#endif
