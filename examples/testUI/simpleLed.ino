//#define ETHERNET //Dùng cho mạng có dây (giao tiếp bằng chân D4 và spi)
#define NAME_DEVICE "SIMPLE" // đặt tên cho thiết bị
#define BOOT_FAST 1 // bật chế độ khởi động nhanh (bỏ qua chế độ thiết lập mềm)
#include "vocaui.h"
#include "mail.h"
#define LED D1
void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  // loadConfigFile(true); // Sử dụng trong khi phát triển (sẽ xóa dữ liệu động)
  loadConfigFile(false); // for using

  //==== che 4 dòng này nếu thiết lập mềm qua 192.168.4.1
  setValue("staid","********"); // tên wifi
  setValue("stapass","********"); // mật khẩu wifi
  setValue("user","********");
  setValue("pass","********");
  //================================================
  render_init("Bật Tắt Led"); // Khởi tạo trang web

  begin_menu("panel", "Điều khiển đèn", [](String val) {
  });
  render_switch("onoffLed", "Bật Tắt", "", [](String val) {
    if (val == "true") {
      LOG("Nhận lệnh bật LED" );
      digitalWrite(LED, HIGH);
    }
    if (val == "false") {
      LOG("Nhận lệnh tắt LED" );
      digitalWrite(LED, LOW);
    }
  });
  render_state("stateLed", "Trạng thái led", "");
  end_menu();
  initVoCa();
  setValue("stateLed",digitalRead(LED)?"true":"false");
}
bool lastStateLed = digitalRead(LED);
void loop() {
  voCaHandle();
  if(digitalRead(LED)!=lastStateLed){
    lastStateLed = digitalRead(LED);
    setValue("stateLed",lastStateLed?"true":"false");
    }
}
