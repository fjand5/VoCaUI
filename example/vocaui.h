#ifndef VOCAUI
#define VOCAUI
#include "sysDefine.h"
#include "sysFunc.h"
#include "wifi.h"
#include "renderHtml.h"
#include "mqttConnection.h"
#include "taskSchedule.h"
#include "mail.h"
uint32_t vocaTimer = 0;


void handleChangeValueEvent() {
  bool sendFlag = false;
  String data4Send = "{";
  for (std::pair < String, onValueChange > func : listFunc) {
    if (changeFlag[func.first] == true) {
      String id = func.first.c_str();
      String value = getValue(id);
      func.second(value);
      data4Send += "\"" + id + "\":" + "\"" + value + "\",";
      sendFlag = true;
      changeFlag[func.first] = false;
    }
  }

  if (sendFlag) {
    saveConfigFile();
    data4Send.setCharAt(data4Send.length() - 1,'}');
    publicMqtt(data4Send, String(getValue("mqttUser")) + "/" + NAME_DEVICE + "_" + getValue("deviceId") + "/tx");

  }


}
void voCaHandle() {

  wifiHandle();

  if (gotTime) {
    initMqttConnection();
    handleChangeValueEvent();
    handlerTaskSchedule();
    handleMail();
    mqttHandle();
  }

}
void initVoCa() {
  initWifi();

}
#endif
