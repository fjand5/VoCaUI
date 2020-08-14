//#define ETHERNET //Dùng cho mạng có dây (giao tiếp bằng chân D4 và spi)
#include "vocaui.h"
#include "mail.h"

void setup() {

  Serial.begin(115200);

  // loadConfigFile(true); // Sử dụng trong khi phát triển (sẽ xóa dữ liệu động)
  loadConfigFile(false); // for using
  render_init("cafe vong cat"); // Khởi tạo trang web

  begin_menu("mngMail", "test giao diện", [](String val) {
    LOG(val + " -- test giao diện" );
  });
  render_inputText("mesg", "Nội Dung", "", [](String val) {
    LOG(val + " -- Nội Dung" );
  });
  render_range("testrange", "đây là range", 0, 100, 1, "", [](String val) {
    LOG(val + " -- đây là range" );
  });
  render_switch("testswitch", "đây là swicth", "", [](String val) {
    LOG(val + " -- đây là swicth" );
    setValue("teststate", val);
  });
  render_state("teststate", "đây là state","");
  render_TimePicker("TimePicker1", "TimePicker", "", [](String val) {

    uint32_t stamp = val.toInt();
    uint32_t _hour = stamp / 60;
    uint32_t _min  = stamp % 60;
    LOG(val + " -- TimePicker1  "  + _hour + " " + _min);


  });
  render_TimePicker("TimePicker2", "TimePicker", "", [](String val) {
    uint32_t stamp = val.toInt();
    uint32_t _hour = stamp / 60;
    uint32_t _min  = stamp % 60;
    LOG(val + " -- TimePicker2  "  + _hour + " " + _min);
  });
  render_textView("tview", "Nội Dung","");
  render_button("testMail", "Gửi Thử1", "", [](String val) {
    LOG("testMail");
    addMail("testMailtestMail");
  });
  render_button("testMail2", "Gửi Thử2", "", [](String val) {
    LOG("testMail2");
  });
  end_menu();

	// chức năng hẹn giờ, chạy 1 phút 1 lần.
  addTaskEvent(1, [](int dayW, int hour, int min) {

    uint32_t stamp = String(getValue("TimePicker1")).toInt();
    uint32_t _hour = stamp / 60;
    uint32_t _min  = stamp % 60;
    if (_hour == hour
        && _min == min) {
      LOG(String(" -- TimePicker1  chay: ")  + dayW + " " + hour + " " + min);
    }


  });

  addTaskEvent(2, [](int dayW, int hour, int min) {
    uint32_t stamp = String(getValue("TimePicker2")).toInt();
    uint32_t _hour = stamp / 60;
    uint32_t _min  = stamp % 60;
    if (_hour == hour
        && _min == min) {
      LOG(String(" -- TimePicker2  chay: ")  + dayW + " " + hour + " " + min);
    }


  });
  initVoCa();


}
void loop() {
  voCaHandle();


}
