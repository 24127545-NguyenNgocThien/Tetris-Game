# Tetris Game (OOP Final Project)

## 1. Giới thiệu
Đây là đồ án môn **Lập Trình Hướng Đối Tượng (OOP)**.  
Game được xây dựng bằng **C++** và thư viện **raylib**, áp dụng các nguyên lý OOP (`Encapsulation`, `Inheritance`, `Abstraction`, `Polymorphism `) và một số design pattern (`Prototype`, `Template Method`, `Facade`).

## 2. Yêu cầu hệ thống
- C++ compiler (g++/clang/MSVC).
- CMake >= 3.10.
- raylib (đã kèm `libraylib.a` trong thư mục `lib`).
- Hệ điều hành: Windows/Linux.

## 3. Cách build và chạy
### Trên Linux/Mac:
```bash
mkdir build
cd build
cmake ..
make
./Tetris
```
### Trên Windows (MSVC):
```bash
cmake -S . -B build "MinGW Makefiles"
cmake --build build
Để chạy, vào thư mục build/bin chạy tệp TetrisGame.exe
```

## 4. Điều khiển
- ← / → : Di chuyển trái / phải
- ↑ : Xoay khối 
- ↓ : Di chuyển xuống
- SHIFT-LEFT + ↓ : Thả khối
- Z : Giữ khối
- R : chơi lại khi thua (game over)

## 5. Cấu trúc đồ án
```css
include/  # header files
src/      # source code (.cpp)
lib/      # thư viện raylib
Sounds/ # âm thanh
Font/ # kiểu chữ 
CMakeLists.txt
```

## 6. Design Pattern 
- **Prototype** : nhân bản dữ liệu block từ mẫu sẵn.
- **Template Method** : định nghĩa khung xử lý vòng lặp game, cho phép các bước cụ thể override.
- **Facade** : lớp `Game` làm giao diện đơn giản, che giấu chi tiết `Grid`, `Block`, input, render.

## 7. Ghi chú 
- Lưới 20x10, mỗi ô 30px.
- Điểm số và tốc độ rơi tăng dần theo level, tối đa là level 5


