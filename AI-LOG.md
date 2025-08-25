# AI Collaboration Log (AI_LOG.md)

> Ngày cập nhật: 25/08/2025

Nhật ký này ghi lại các lần tương tác quan trọng với AI trong quá trình làm đồ án.

---

## 1) Mở đầu
**SV:** "Nhóm tôi đang làm 1 project code game sử dụng phương pháp lập trình hướng đối tương về game, và game tôi chọn là tetris thì đầu tiên
tôi nên làm những gì?"<br>
**AI(tóm tắt):**
- Đầu tiên nên tạo 1 class là `Grid`(lớp), lớp này sẽ tạo ra những ô vuông(lưới).
- Và sau đó in ra màn hình check render nếu thành công thì sang bước tạo class `Block`.
- Các block sẽ được tô màu riêng biệt theo dạng block đó (Z S T... sẽ có màu khác nhau).<br>

**Quyết định:** *Chấp nhận*.

---

## 2) Tạo grid 
**SV:** "Mình muốn tạo lưới 20x10 đế chứa các block thì nên cái đặt thế nào?"<br>
**AI(tóm tắt):** Dùng mảng 2 chiều `int grid[20][10]` hoặc vector. Thêm hàm `IsCellEmpty(row, col)` và `ClearFullRow()`.<br>
**Quyết định:** *Chấp nhận*. Dùng int grid[20][10] vì đơn giản.

---

## 3) Tạo Block
**SV:** "Bây giờ chỉ cách tạo class `Block` đi"<br>
**AI(tóm tắt):** Đóng gói dữ liệu (tọa độ, state xoay) và hành vi (`Rotate`, `MoveLeft`, `MoveRight`, `Draw`).<br>
**Quyết định:** *Chấp nhận*. Tạo base class Block và kế thừa cho 7 loại block theo sự chỉ dẫn của AI. 

---

## 4) Sinh Random Block
**SV:** "Làm sao để sinh khối ngẫu nhiên trong 7 block"<br> 
**AI(tóm tắt):** Tạo vector `KhoBlock` chứa pointer trỏ tới từng loại. Dùng `rand() %7 ` để chọn.<br>
**Quyết định:** *Chấp nhận*. Tạo hàm GetRandomBlock() theo chỉ dẫn.

---

## 5) Rotate Block
**SV:** "Cách xử lý xoay khối"<br>
**AI(tóm tắt):** Mỗi block lưu trạng thái trong mảng. Biến `state` chạy từ 0 - 3, Rotate thì `(state + 1) % 4`<br>
**Quyết định:** *Chấp nhận*. Thực thi như hướng dẫn.

---

## 6) Thiết kế class Game
**SV:** "Nhóm tôi muốn thiết kế 1 class `Game` thì class này thiết kế như nào?"<br>
**AI(tóm tắt):** `Game` nên làm `Facade Pattern`: quản lý vòng lặp chính, chứa `Grid`, khối hiện tại, khối kế tiếp, điểm số, level, 
âm thanh. Nó cũng xử lý input và gọi hàm vẽ. `main.cpp` chỉ cần khởi tạo `Game` rồi gọi `Run()`.<br> 
**Quyết định:** *Chấp nhận*. Tạo `Game` để gom toàn bộ logic, giúp `main.cpp` gọn hơn.

---

## 7) Cách chia file .h và .cpp
**SV:** "Nhóm tôi đã chia file ra `.h` và `.cpp` theo OOP rồi nhưng vẫn thấy rối và khó quản lý"<br>
**AI(tóm tắt):** Nên tạo 1 thứ mục tên `include` và bỏ các file `.h` và thư mục `src` chứa các file `.cpp` để dễ quản lý hơn.<br>
**Quyết định:** *Chấp nhận*. 

---

## 8) Kiếm tra va chạm
**SV:** "Khi block rơi xuống thì cách nào kiểm tra bóng chạm vào biên của lưới ra sao?"<br>
**AI(tóm tắt):** Trước khi di chuyển, kiểm tra từng ô của block: nếu ra ngoài lưới hoặc ô grid đã có giá trị khác 0 thì va chạm.<br>
**Quyết định:** *Chấp nhận*. Thêm `IsBlockOutsie()` và `IsBlockColliding()`.

---

## 9) Xử lý xóa hàng
**SV:** "Khi 1 hàng đầy thì muốn xóa và các hàng trên nó dịch chuyển xuống thì làm sao?"<br>
**AI(tóm tắt):** Duyệt từng hàng, nếu tất cả các ô khác 0 thì xóa hàng, dồn các hàng trên xuống.<br>
**Quyết định:** *Chấp nhận*. Viết `ClearFullRow()`, xử lý theo hướng dẫn của AI và update score.

---

## 10) Add Sound
**SV:** "Làm sao để thêm âm thanh ví dụ như khi xóa hạng hoặc khi game over?"<br>
**AI(tóm tắt):** Tạo thư mục `resource` chứa các file .wav. Trong class `Game` load bằng:
``` bash
Example:
Sound clearSound = LoadSound("resource/clear.wav");
Sound overSound  = LoadSound("resource/gameover.wav");
```
Sau đó trong `ClearFullRows()` gọi `PlaySound(clearSound)` và trong xử lý Game Over gọi `PlaySound(overSound)`. Đừng quên gọi `InitAudioDevice()` lúc khởi tạo và `CloseAudioDevice()` khi thoát game.”<br>
**Quyết định:** *Chấp nhận*. Tạo thư mục `resource` và thêm hàm gọi âm thanh vào class `Game`.

---

## 11) Chọn & lý giải Design Patterns
**SV:** "Game Tetris của nhóm mình đang có các lớp `Game`, `Grid`, `Block` và 7 khối kế thừa. Gợi ý 3 design pattern phù hợp và chỉ ra vị trí áp dụng trong code?"<br>  
**AI(tóm tắt):**
- Dùng **State** cho trạng thái xoay của khối (`Block::state` 0..3; `GetTilesPosition`, `Rotate`, `UndoRotate` phụ thuộc `state`).
- Dùng **Factory Method / Simple Factory** để tạo khối ngẫu nhiên (`Game::KhoBlock`, `Game::GetRandomBlock`).
- Dùng **Facade**: `Game` che giấu chi tiết `Grid`, `Block`, input, render, âm thanh và phơi bày API mức cao cho `main`.<br>

**Quyết định:** *Chấp nhận*. Ba pattern này khớp kiến trúc hiện có, không cần viết lại lớn.

---

## 12) Hệ thống build bằng CMake trên Windows
**SV:** "Viết hướng dẫn build nhanh bằng CMake cho Windows (MSVC/MinGW), dùng `libraylib.a` có sẵn"<br>
**AI(tóm tắt):** Thêm mục “Yêu cầu hệ thống”, 2 quy trình build (CLI và CMake GUI), chỉ rõ output ở `bin/`.<br>
**Quyết định:** *Chấp nhận*. CMakeLists hiện liên kết `opengl32 gdi32 winmm`, nên ưu tiên Windows; các HĐH khác cần tự chỉnh `target_link_libraries`.

---

## 13) Điều khiển bàn phím & UI Game Over
**SV:** "Tự động dò phím trong source và tạo bảng điều khiển người chơi"<br>
**AI(tóm tắt):** Liệt kê `KEY_LEFT/RIGHT/UP/DOWN/R` với ý nghĩa; thêm hướng dẫn “R để Restart khi Game Over”.  <br>
**Quyết định:** *Chấp nhận*. Trùng khớp với xử lý phím trong `Game::XuLyBanPhim()`.

---

## 14) Đề xuất mở rộng (không bắt buộc)
**SV:** "Gợi ý mở rộng tính năng mà không sửa nhiều kiến trúc"<br>
**AI(tóm tắt):**
- Thêm **Command** cho input (dễ bind phím khác/hard-drop).
- Bảng xếp hạng cục bộ (ghi file), tuỳ chọn âm lượng, hiệu ứng hard drop.<br>

**Quyết định:** *Tạm hoãn*. Để sau khi nộp bản cơ bản.

---

## 15) Đóng gói tài liệu nộp
**SV:** "Nhắc lại các deliverable theo đề bài và tạo README + AI_LOG chuẩn hoá." <br>
**AI(tóm tắt):** Tạo `README.md` (build/run, controls, kiến trúc, pattern), `AI_LOG.md` (nhật ký tương tác chính).<br>
**Quyết định:** *Chấp nhận*. Sẽ đặt file vào thư mục `group/report/` theo cấu trúc nộp.