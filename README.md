# Tetris Game (OOP Final Project)

## 1. Giới thiệu
Đây là đồ án môn **Lập Trình Hướng Đối Tượng (OOP)**.  
Game được xây dựng bằng **C++** và thư viện **raylib**, áp dụng các nguyên lý OOP (`Encapsulation`, `Inheritance`, `Polymorphism`, `Abstraction`) và một số design pattern (`Prototype`, `Template Method`, `Facade`).

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
cmake -S . -B build
cmake --build build --config Release
./bin/Tetris_Game.exe
```

## 4. Điều khiển
- ↑ : Xoay khối 
- ↓ : Thả nhanh (soft drop)
- ← / → : Di chuyển trái / phải
- R : chơi lại khi thua (game over)

## 5. Cấu trúc đồ án
```css
include/  # header files
src/      # source code (.cpp)
lib/      # thư viện raylib
resource/ # âm thanh, font
CMakeLists.txt
```

## 6. Design Pattern 
- **Prototype** : nhân bản dữ liệu block từ mẫu sẵn.
- **Template Method** : định nghĩa khung xử lý vòng lặp game, cho phép các bước cụ thể override.
- **Facade** : lớp `Game` làm giao diện đơn giản, che giấu chi tiết `Grid`, `Block`, input, render.

## 7. Ghi chú 
- Lưới 20x10, mỗi ô 50px.
- Điểm số và tốc độ rơi tăng dần theo level.
- Âm thanh và font load từ thư mục `resource`.