# Hệ Thống Quản Lý Nhân Viên và Khách Hàng

Đây là một dự án quản lý dữ liệu cho **nhân viên** và **khách hàng** được viết bằng C++ với giao diện console. Hệ thống hỗ trợ các thao tác **CRUD** (Tạo, Đọc, Cập nhật, Xóa) cho cả nhân viên và khách hàng, đồng thời cung cấp các chức năng **thống kê** (tính tổng số tiền giảm giá, tổng số tiền hàng chưa giảm giá, doanh thu sau giảm giá). Dữ liệu được lưu trữ dưới dạng file văn bản, với tên file phụ thuộc vào ngày (định dạng `dd_mm_yyyy`).

---

## Các Tính Năng Chính

- **Đăng Nhập Admin:**  
  Hệ thống yêu cầu đăng nhập với tài khoản cố định để đảm bảo an toàn cho dữ liệu.

- **Quản Lý Nhân Viên:**  
  Cho phép thêm, xem, cập nhật và xóa thông tin nhân viên. Mỗi nhân viên được gán mã ngẫu nhiên có tiền tố `EMP_`.

- **Quản Lý Khách Hàng:**  
  Cho phép thêm, xem, cập nhật và xóa thông tin khách hàng. Mỗi khách hàng được gán mã ngẫu nhiên có tiền tố `CUS_`.

- **Thống Kê Dữ Liệu:**  
  - Tính tổng số tiền giảm giá được áp dụng cho khách hàng.
  - Tính tổng số tiền hàng (chưa giảm giá).
  - Tính doanh thu (sau khi trừ giảm giá).

- **Lưu Trữ Theo Ngày:**  
  Dữ liệu của mỗi ngày được lưu riêng biệt (ví dụ: `data/staff_dd_mm_yyyy.txt` và `data/client_dd_mm_yyyy.txt`), giúp quản lý và tra cứu dữ liệu theo từng ngày cụ thể.

---

## Các Điểm Mới Của Dự Án

- **Hiển thị được tiếng việt trên termial:**  
   Hiển thị tiếng việt trong console: Để hiện thị tiếng việt trong console em đã sử dụng “SetConsoleOutputCP(65001);” của thư viện<Windows.h>. Nó cung cấp cho trình biến dịch các ký tự đặc biệt trong bảng mã utf-8 giúp có thể xuất ra màn hình văn bản có dấu.

- **Bổ Sung Inline Comment Chi Tiết:**  
  Mỗi dòng code đã được thêm comment chi tiết, giúp cho người đọc dễ hiểu được logic của từng phần trong dự án.
---