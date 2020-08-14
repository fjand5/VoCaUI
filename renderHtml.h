#ifndef RENDER_HTML
#define RENDER_HTML
#define SIZE_HTML 50000
#include "html/sourceHtml.h"

#include "sysFunc.h"
#include <ESP8266WiFi.h>
#ifdef ETHERNET
#include <Ethernet2.h>
#endif
String responeBuf = "";
String listMenu = "";
/*new render
  giao diện do server dựng, không chạy offline được.
*/

void render_chart(String id, String label, float minX, float maxX,float minY,float maxY,String prams, onValueChange func = [](String val) {}) {
  setValue(id.c_str(), "", true);
  responeBuf += emptyString
                + "<div id='" + id + "'"+prams+" class='chart'"
                + "minX='" + minX + "'"
                + "maxX='" + maxX + "'"
                + "minY='" + minY + "'"
                + "maxY='" + maxY + "'"
        
                + "><label>" + label + "</label>"
                + "</div>";
  std::pair < String, onValueChange > tmpPair(id, func);
  std::pair < String, bool > tmpPair2(id, false);
  changeFlag.insert(tmpPair2);
  listFunc.insert(tmpPair);
}
/*old render*/
void render_range(String id, String label, int min, int max, int step,String prams, onValueChange func = [](String val) {}) {
  setValue(id.c_str(), "", true);
  responeBuf += emptyString
                + "<div id='" + id + "'"+prams+" class='rng'>"
                + "<label>" + label + "</label>"
                + "<label></label>"
                + "<input type='range'" +
                "min='" + min + "'" +
                "max='" + max + "'" +
                "step='" + step + "'" +
              
                "onchange=\"sdt('" + id + "',this.value); this.blur()\"" +
                "oninput=\"this.previousSibling.innerHTML=this.value\"" +
                ">"
                + "</div>";



  std::pair < String, onValueChange > tmpPair(id, func);
  std::pair < String, bool > tmpPair2(id, false);
  changeFlag.insert(tmpPair2);
  listFunc.insert(tmpPair);
}


void render_inputText(String id, String label,String prams, onValueChange func = [](String val) {}) {
  setValue(id.c_str(), "", true);
  responeBuf += emptyString
                + "<div id='" + id + "'" + prams +" class='inptxt'>"
                + "<label>" + label + "</label>"
                + "<input type='text'>"
                + "<button onclick=\"sdt('" + id + "',this.previousSibling.value)\">"
                + "OK</button>"
                + "</div>";
  std::pair < String, onValueChange > tmpPair(id, func);
  std::pair < String, bool > tmpPair2(id, false);
  changeFlag.insert(tmpPair2);
  listFunc.insert(tmpPair);
}
void render_textView(String id, String label,String prams) {
  setValue(id.c_str(), "", true);
  responeBuf += emptyString
                + "<div id='" + id + "'" +prams+ " class='txtvie'>"
                + "<label>" + label + "</label>"
                + "<input type='text' readonly>"
                + "</div>";

  std::pair < String, onValueChange > tmpPair(id, [](String val) {});
  std::pair < String, bool > tmpPair2(id, false);
  changeFlag.insert(tmpPair2);
  listFunc.insert(tmpPair);
}

void render_updatetButton() {
  String id = "reset";
  responeBuf += String("<button type=\"button\" id=\"") + id + "\"" + " onclick=\"location.assign('/update')\"" +
                ">UPDATE</button>";
}
void render_resetButton() {
  String id = "reset";
  responeBuf += String("<button type=\"button\" id=\"") + id + "\"" + " onclick=\"sdt('rst','')\"" +
                ">RESET</button>";

}
void render_formatButton() {

  String id = "format";
  responeBuf += String("<button type=\"button\" id=\"") + id + "\"" + " onclick=\"sdt('fmt','')\"" +
                ">FORMAT</button>";

}
void render_button(String id, String label,String prams, onValueChange func = [](String val) {}) {
  setValue(id.c_str(), "", true);
  responeBuf += emptyString
                + "<div id='" + id + "'"+prams+" class='sglbtn'>"
                + "<button onclick=\"sdt('" + id + "','" + label + "')\">"
                + label
                + "</button>"
                + "</div>";
  std::pair < String, onValueChange > tmpPair(id, func);
  std::pair < String, bool > tmpPair2(id, false);
  changeFlag.insert(tmpPair2);
  listFunc.insert(tmpPair);

}
void render_switch(String id, String label, String prams, onValueChange func = [](String val) {}) {
  setValue(id.c_str(), "", true);
  responeBuf += emptyString
                + "<div id='" + id + "'" +prams+ " class='swch'>"
                + "<label>" + label + "</label>"
                + "<input id = '_" + id + "' type='checkbox' onclick=\"sdt('" + id + "',this.checked.toString())\">"
                + "<label for='_" + id + "'></label>"
                + "</div>";

  std::pair < String, onValueChange > tmpPair(id, func);
  std::pair < String, bool > tmpPair2(id, false);
  changeFlag.insert(tmpPair2);
  listFunc.insert(tmpPair);

}
void render_state(String id, String label, String prams) {
  setValue(id.c_str(), "", true);
  responeBuf += emptyString
                + "<div id='" + id + "'"+prams+" class='state'>"
                + "<label>" + label + "</label>"
                + "<input  id = '_" + id + "' type='checkbox' disabled='disabled' onclick='return false;'>"
                + "<label for='_" + id + "'></label>"
                + "</div>";

  std::pair < String, onValueChange > tmpPair(id, [](String val) {});
  std::pair < String, bool > tmpPair2(id, false);
  changeFlag.insert(tmpPair2);
  listFunc.insert(tmpPair);


}

void render_TimePicker(String id, String label, String prams, onValueChange func = [](String val) {}) {
  setValue(id.c_str(), "", true);

  responeBuf += emptyString
                + "<div id='" + id + "'"+prams+" class='tmpk'>"
                + "<label>" + label + "</label><br>"
                + "<label>Giờ: </label><select class='hLst'></select>"
                + "<label>Phút: </label><select class='mLst'></select>"
                + "<button onclick=\"var p=this.parentElement.children; var m = p[5];var h = p[3]; var v = parseInt(m.value) + h.value * 60; sdt('" + id + "',v)\">OK</button>"
                + "</div>";


  std::pair < String, onValueChange > tmpPair(id, func);
  std::pair < String, bool > tmpPair2(id, false);
  changeFlag.insert(tmpPair2);
  listFunc.insert(tmpPair);

}
void begin_menu(String id, String name, onValueChange func = [](String val) {}) {
  setValue(id.c_str(), "", true);
  listMenu += "<li onclick=\"oMnClk('" + id + "','')\"><a href=\"#\" >" + name + "</a></li>";
  responeBuf += "<div class='mnu' id=\"" + id + "\" style='display: none'>"
                + "<label>" + name + "</label><br>";
  std::pair < String, onValueChange > tmpPair(id, func);
  std::pair < String, bool > tmpPair2(id, false);
  changeFlag.insert(tmpPair2);
  listFunc.insert(tmpPair);
}
void end_menu() {
  responeBuf += "</div>";
}
const char * getPage() {
  static bool gotPage = false;
  if (gotPage)
    return responeBuf.c_str();
  responeBuf += "<div class='lmnu' style='display: none' onclick='hidelmnu();'><ul>";
  responeBuf += listMenu;
  responeBuf += "</ul></div>";
  responeBuf += last_part_page;
  gotPage = true;
  return responeBuf.c_str();
}
void render_init(String title) {
  responeBuf.reserve(SIZE_HTML);
  responeBuf += first_part_page + title + mid_part_page;
  begin_menu("setting", "setting");
  render_inputText("staid", "Tên Wifi","");
  render_inputText("stapass", "Mật Khẩu","");
  render_inputText("user", "T.Khoản VoCa","");
  render_inputText("pass", "Mật Khẩu VoCa","");
  render_resetButton();
  render_formatButton();
  render_updatetButton();
  end_menu();
  begin_menu("mail", "Quản Lý Mail");
   render_inputText("desMail", "Mail","");
  render_inputText("tknMail", "Token Mail","");
  render_textView("mailCnt", "Mail đang chờ gửi","");
  render_inputText("tknMail", "Token Mail","");
  end_menu();
  begin_menu("info", "Thông Tin", [](String val) {
#ifdef ETHERNET
    setValue("localIP", Ethernet.localIP().toString());

#else
    setValue("localIP", WiFi.localIP().toString());
#endif


    setValue("upTime", String(millis() / 1000));
  });
  render_inputText("deviceId", "id thiết bị: ","");
  render_textView("localIP", "Địa chỉ IP: ","");
  render_textView("upTime", "Up Time: ","");
  end_menu();
}
#endif
