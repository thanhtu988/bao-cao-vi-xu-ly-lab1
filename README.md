# Lab 1 – Điều khiển LED với STM32F103 (Vi xử lý – Vi điều khiển)

**Sinh viên:** Đào Ngọc Thanh Tú – 2413841
**Giảng viên:** Lê Trọng Nhân
**Nội dung:** 10 exercise của Lab 1, mỗi bài là một project STM32CubeIDE độc lập, mô phỏng trên Proteus.

Báo cáo: [`BaoCao/Bao-cao-vi-xu-ly-lab1.pdf`](BaoCao/Bao-cao-vi-xu-ly-lab1.pdf)

## Cách build và mô phỏng

1. STM32CubeIDE → `File > Open Projects from File System…` → chọn thư mục `Lab1_ExN` → `Ctrl+B`.
2. Proteus (mở bằng *Run as administrator*) → double-click MCU → `Program File` = `Lab1_ExN/Debug/Lab1_ExN.hex`, `Crystal Frequency` = 8MHz → Play.

## 1. Cấu trúc thư mục

```
Lab1/
├── Lab1_Ex1 … Lab1_Ex10/     10 project STM32CubeIDE (đã build, có Debug/Lab1_ExN.hex)
├── Proteus/
│   ├── Lab1_Ex1.pdsprj       project Proteus (trang trống, chưa vẽ)
│   ├── so_do/                hình sơ đồ nối dây tham chiếu cho từng bài
│   └── HUONG_DAN.txt
├── BaoCao/                   báo cáo PDF + ảnh mô phỏng (img/)
└── README.md
```

| Bài | Nội dung | Chân | File code chính |
|---|---|---|---|
| Ex1 | 2 LED đổi trạng thái mỗi 2 s | PA5 đỏ, PA6 vàng | `main.c` |
| Ex2 | Đèn giao thông 1 hướng: đỏ 5 s → xanh 3 s → vàng 2 s | + PA7 xanh | `main.c` |
| Ex3 | Ngã tư 12 LED | PA1…PA12 | `traffic.c/.h` |
| Ex4 | LED 7 đoạn, `display7SEG()` | + PB0…PB6 (a…g) | `seven_seg.c/.h` |
| Ex5 | Ngã tư + đếm ngược tuyến Bắc–Nam | như Ex4 | `traffic.c` + `seven_seg.c` |
| Ex6 | Test 12 LED đồng hồ | PA4…PA15 | `main.c` |
| Ex7–9 | `clearAllClock()`, `setNumberOnClock()`, `clearNumberOnClock()` | PA4…PA15 | `led_clock.c/.h` |
| Ex10 | Đồng hồ giờ/phút/giây bằng 3 LED | PA4…PA15 | `main.c` + `led_clock.c` |

Pin cụ thể của Ex3 (mỗi hướng: đỏ / vàng / xanh):
Bắc PA1/PA2/PA3 · Nam PA4/PA5/PA6 · Đông PA7/PA8/PA9 · Tây PA10/PA11/PA12.
Tuyến A = Bắc + Nam, tuyến B = Đông + Tây.

## 2. Nguyên tắc chung

- **LED active-low:** cathode nối chân MCU, anode nối +3.3V (đúng như PDF). Chân = 0 → LED sáng. Trong code: `LED_ON = GPIO_PIN_RESET`, `LED_OFF = GPIO_PIN_SET`.
- **PA13/PA14 (Ex6–Ex10)** là chân SWD. Các project này đặt *SYS → Debug = No Debug* để dùng làm GPIO. Proteus chạy bình thường; trên kit thật phải nạp bằng *Connect under reset*.
- **Đường dẫn không dấu, không khoảng trắng.** Proteus 8.10 và CubeMX sẽ lỗi với đường dẫn kiểu `vi xử lý -`. Thư mục cũ đã được đổi thành `D:\261\vixuly`. Project `LAB\test` cũ hỏng cũng vì lý do này.
- Code người dùng chỉ nằm trong vùng `USER CODE` hoặc trong file riêng, nên bấm *Generate Code* trong file `.ioc` sẽ không làm mất code.

## 3. Build trong STM32CubeIDE

10 project đã được import vào `workspace_1.7.0`. Nếu cần import lại: *File → Import → General → Existing Projects into Workspace*, chọn thư mục `D:\261\vixuly\LAB\Lab1` và **không** tick *Copy projects into workspace*.
Build: chọn project → `Ctrl+B`. File hex được tạo tại `Lab1_ExN\Debug\Lab1_ExN.hex`.

## 4. Vẽ schematic trên Proteus (chạy Proteus bằng *Run as administrator*)

> Nếu không chạy bằng quyền admin, Proteus 8.10 sẽ báo *No Libraries Found!*.

### 4.1 Thao tác cơ bản

1. Mở `Proteus\Lab1_Ex1.pdsprj`, vào tab *Schematic Capture*.
2. **Lấy linh kiện:** bấm nút **P** ở khung DEVICES rồi tìm lần lượt `STM32F103C6`, `LED-RED`, `LED-YELLOW`, `LED-GREEN` (Ex4 thêm `7SEG-COM-ANODE`). Double-click vào kết quả để thêm vào danh sách.
3. **Đặt linh kiện:** chọn tên trong DEVICES rồi click lên trang vẽ. Xoay bằng các nút xoay ở thanh bên trái (hoặc phím `+`/`-` trên numpad).
4. **Nguồn/đất:** chọn *Terminals Mode* → `POWER` hoặc `GROUND` → đặt lên trang → double-click → đặt String = `+3.3V`.
5. **VDDA/VSSA** (PDF bước 8): kéo một đoạn dây ngắn từ `+3.3V` và từ `GROUND` → chuột phải lên dây → *Place Wire Label* → đặt `VDDA` và `VSSA`.
6. **Nối dây:** click đầu chân này rồi click đầu chân kia.
7. **Gán file hex:** double-click STM32 → *Program File* → chọn `..\Lab1_ExN\Debug\Lab1_ExN.hex` → OK.
8. **Chạy mô phỏng:** bấm ▶ ở góc dưới bên trái. Trước khi sửa code hay build lại, bấm ■ để dừng.

### 4.2 Mẹo cho bài có 12 LED: dùng nhãn thay vì kéo dây dài

- Các **DEFAULT terminal** (trong *Terminals Mode*) có **cùng tên** thì được nối điện với nhau.
- Ở mỗi chân PA1…PA12 của MCU, kéo một đoạn dây ngắn tới một DEFAULT terminal.
- Ở cathode của mỗi LED, cũng đặt một DEFAULT terminal.
- **Đặt tên nhanh:** dùng *Property Assignment Tool* (phím `A`).
  - String = `NET=PA#`, Count = 1, Increment = 1.
  - Chọn *On Click*, rồi click lần lượt vào các terminal theo thứ tự.
  - Làm lần 1 cho các terminal ở MCU và lần 2 cho các terminal ở LED, theo đúng bảng chân.
- Anode của mọi LED nối vào `+3.3V`. Có thể đặt một POWER terminal cho mỗi cụm LED.

Hình tham chiếu trong `Proteus\so_do\`:

| Bài | Hình |
|---|---|
| Ex1, Ex2 | `Ex1_so_do.png`, `Ex2_so_do.png` |
| Ex3 | `Ex3_so_do.png` |
| Ex4, Ex5 | `Ex4_so_do.png` (7SEG: COM → +3.3V, A…G → PB0…PB6, DP bỏ trống) |
| Ex6–Ex10 | `Ex6_10_so_do.png` (LED vị trí k giờ → PA(4+k), vị trí 0 là 12 giờ) |

### 4.3 Tạo nhanh các file Proteus còn lại bằng *File → Save Project As*

| Từ | Lưu thành | Việc cần làm thêm |
|---|---|---|
| Ex1 | `Lab1_Ex2.pdsprj` | thêm LED-GREEN vào PA7, đổi Program File |
| (mới) | `Lab1_Ex3.pdsprj` | vẽ 12 LED |
| Ex3 | `Lab1_Ex4.pdsprj` | thêm 7SEG-COM-ANODE, đổi Program File |
| Ex4 | `Lab1_Ex5.pdsprj` | chỉ đổi Program File |
| (mới) | `Lab1_Ex6.pdsprj` | vẽ đồng hồ 12 LED |
| Ex6 | `Lab1_Ex7…Ex10.pdsprj` | chỉ đổi Program File |

Ex10 chạy theo giây thật, bắt đầu lúc 10:10:00. Muốn xem nhanh thì giảm `SECOND_MS` trong `main.c` (ví dụ 10) rồi build lại.

## 5. Báo cáo
