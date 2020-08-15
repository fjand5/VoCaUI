## Lưu ý
Các bạn nên cài thư viện **PubSubClient** bản mới nhất để hệ thống được chạy ngon lành.
## Đăng ký tài khoản tại [Ngôi Nhà IoT](https://ngoinhaiot.com) để được kết nối.
VoCaUI được tích hợp trên **[Ngôi Nhà IoT](https://ngoinhaiot.com)**.\
Giao diện được cập nhật theo code trên arduino.\
Bạn chỉ lập trình giao diện trên arduino.\
Giám sát toàn bộ thiết bị trên **[Ngôi Nhà IoT](https://ngoinhaiot.com)**.
## Hướng dẫn config cho hệ thống.
1. Khi hệ thống bắt đầu khởi động, đèn trên board sẽ nháy nhanh trong 40s (bạn có 40s để làm bước 3).\
2. Bạn kết nối vào wifi do hệ thống phát ra ("VoCaUI-xxx") với mật khẩu là 12345678.\
3. Vào địa chỉ 192.168.4.1 bằng trình duyệt (nhớ tắt hết 3G, 4G nếu sử dụng điện thoại), khi đã vào được trang web thì không còn giới hạn 40s nữa, bạn có thể từ từ thao tác cũng được.\
4. Vào menu/setting để thiết lập các thông số: tên wifi, passwifi; tên tài khoản và mật khẩu VoCa (trùng với tài khoản và mật khẩu trên **[Ngôi Nhà IoT](https://ngoinhaiot.com)**).

## Chức năng các hàm trong hệ thống.
### * loadConfigFile(del)
> Nạp toàn bộ thông tin để hệ thống hoạt động, **phải được chạy đầu tiên**. 
1. del (bool): true - xóa dữ liệu động (dùng trong quá trình lập trình), false - không xóa dữ liệu động (dùng cho sản phẩm hoàn thiện)

### * render_init(title)
> Khởi tạo quá trình dựng giao diện. 
1. title (String): tiêu đề của ứng dụng.


### * begin_menu(id, label, onRecive)
> Bắt đầu tạo một menu (mọi phần tử sẽ được tạo trong menu này cho tới khi gặp end_menu). 
1. id (String): id của menu.
2. label (String): nhãn của menu.
3. onRecive ([](String val){}): hàm được gọi khi menu này được chọn trên giao diện.
### * end_menu()
> Kết thúc một menu. 
### * render_inputText(id, label, params, onRecive)
> Bắt đầu tạo một vùng nhập liệu (phần tử phải được đặt trong menu - sau begin_menu và trước end_menu). 
1. id (String): id của phần tử.
2. label (String): nhãn của phần tử.
3. params (String): tham số thêm (chức năng đang được phát triển, tạm thời truyền vào "").
4. onRecive ([](String val){}): hàm được gọi khi phần tử được thay đổi giá trị trên giao diện.
### * render_range(id, label, params, min, max, step, onRecive)
> Bắt đầu tạo một thanh trượt (phần tử phải được đặt trong menu - sau begin_menu và trước end_menu). 
1. id (String): id của phần tử.
2. label (String): nhãn của phần tử.
3. params (String): tham số thêm (chức năng đang được phát triển, tạm thời truyền vào "").
4. min (int): giá trị tối thiểu có thê nhập.
5. max (int): giá trị tối đa có thê nhập.
6. step (int): độ chia nhỏ nhất của thanh trượt.
7. onRecive ([](String val){}): hàm được gọi khi phần tử được thay đổi giá trị trên giao diện.
### * render_switch(id, label, params, onRecive)
> Bắt đầu tạo một nút gạt (phần tử phải được đặt trong menu - sau begin_menu và trước end_menu). 
1. id (String): id của phần tử.
2. label (String): nhãn của phần tử.
3. params (String): tham số thêm (chức năng đang được phát triển, tạm thời truyền vào "").
4. onRecive ([](String val){}): hàm được gọi khi phần tử được thay đổi giá trị trên giao diện - val nhận giá trị "true"|"flase".
### * render_state(id, label, params)
> Bắt đầu tạo một phần tử thể hiện trạng thái nhị phân(phần tử phải được đặt trong menu - sau begin_menu và trước end_menu). 
1. id (String): id của phần tử.
2. label (String): nhãn của phần tử.
3. params (String): tham số thêm (chức năng đang được phát triển, tạm thời truyền vào "").
### * render_TimePicker(id, label, params, onRecive)
> Bắt đầu tạo một nút gạt (phần tử phải được đặt trong menu - sau begin_menu và trước end_menu). 
1. id (String): id của phần tử.
2. label (String): nhãn của phần tử.
3. params (String): tham số thêm (chức năng đang được phát triển, tạm thời truyền vào "").
4. onRecive ([](String val){}): hàm được gọi khi phần tử được thay đổi giá trị trên giao diện - val nhận giá trị là số phút kể từ lúc 00h00 dưới dạng chuỗi được chọn trên giao diện.
### * render_textView(id, label, params)
> Bắt đầu tạo một phần tử thể hiện một giá trị nào đó(phần tử phải được đặt trong menu - sau begin_menu và trước end_menu). 
1. id (String): id của phần tử.
2. label (String): nhãn của phần tử.
3. params (String): tham số thêm (chức năng đang được phát triển, tạm thời truyền vào "").
### * render_button(id, label, params, onRecive)
> Bắt đầu tạo một nút nhấn (phần tử phải được đặt trong menu - sau begin_menu và trước end_menu). 
1. id (String): id của phần tử.
2. label (String): nhãn của phần tử.
3. params (String): tham số thêm (chức năng đang được phát triển, tạm thời truyền vào "").
4. onRecive ([](String val){}): hàm được gọi khi nút được nhấn trên giao diện.
### * addTaskEvent(id, onMin)
> Bắt đầu tạo một tác vụ. 
1. id (int): id của phần tử.
2. onMin ([](int dayW, int hour, int min) {}): hàm được gọi mỗi phút.
### * getValue(id)
> Lấy giá trị từ bộ nhớ với id là id của các phần tử. 
1. id (String): id của phần tử.
> Trả về chuỗi String. 

### * setValue(id,value)
> Nạp giá trị vào bộ nhớ với id là id của các phần tử. 
1. id (int): id của phần tử.
2. value (String): giá trị cần nạp.

## Ví dụ.
```
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
```



