Họ và tên: Đỗ Tiến Đạt
MSSV	 : 23120119
Lớp 	 : 23CTT2
                                             MÔ TẢ ĐỒ ÁN 2048

I. Tổng quan
- Cách build:
  + Tải resource về máy, sau đó mở terminal và gõ dòng lệnh g++ *.cpp -o game2048
  + Chạy file thực thi: .\game2048.exe
- Một số lưu ý:
  + Người dùng phải cài sẵn môi trường để compile (g++, gcc, ...)
  + Nên chuyển sang bàn phím tiếng Anh (tắt Unikey)

II. Kiểm tra tính đúng đắn
Video: https://drive.google.com/drive/folders/1O5Sv1L6XlaHxhziBxe3-sAkOXwhdoccO

III. Tự Đánh giá
- Hiển thị được giao diện kèm chức năng của hai màn hình chính: 0.1 (thể hiện được Menu và bàn cờ)
- Thực hiện được chức năng nhập tên và kiểm tra tính trùng lắp: 0.1 (có thể kiểm tra được tính trùng lắp trong top 20)
- Thực hiện được chức năng cài đặt độ lớn của bàn cờ: 0.1 (có thể cài đặt độ lớn bàn cờ tùy ý)
- Thực hiện được việc lưu trữ thông tin người chơi: 0.1 (Lưu trữ thông tin người chơi bằng file nhị phân)
- Thực hiện được chức năng Resume: 0.2 (thực hiện Resume cho 5 tài khoản)
- Thực hiện được chức năng Exit: 0.1 (người dùng có thể dùng có thể thoát ra dựa vào hướng dẫn trong game)
- Thực hiện được logic trong trò chơi như phát sinh ngẫu nhiên, di chuyển, hiển thị trò chơi, hiển thị điểm,...: 1 (thực hiện được)
- Thực hiện được chức năng undo, undo và redo: 0.2 (có thể undo, redo nhiều lần)
- Hiển thị các thông báo và nội dung tương ứng: 0.1 (hiện thị rõ ràng các thông mỗi khi thực hiện chức năng) 
- Tổ chức thành các file rõ ràng: 0.2 (các file được tổ chức rõ ràng, dễ quản lí)
- Có sử dụng phương thức đồ hoạ kèm giao diện thân thiện: 0.1 (đồ họa còn khá thô sơ)
- Cài đặt được cách thức mã hoá tệp tin: 0.1 (bằng cách cộng một hằng số bất kì)
- Cài đặt được chức năng Resume cho năm tài khoản: 0.4 (có thể chọn 1 tài khoản bất kì để thay thế)

--> Tổng kết: 2.8

IV. Cách chơi
Mục tiêu của trò chơi là kết hợp các ô số để đạt được ô có giá trị 2048 hoặc hơn.

Luật chơi:
- Bắt đầu từ Menu với 6 lựa chọn: New game, Resume, Setting, Statistics, Rules of 2048, Exit. Sử dụng các phím mũi lên/xuống để di chuyển và Enter để lựa chọn.
- New game yêu cầu đăng nhập tài khoản trước khi vào bàn cờ.
- Sử dụng phím mũi tên hoặc W, A, S, D để di chuyển các ô trên bảng.
- Các ô có cùng giá trị sẽ hợp nhất thành một ô với giá trị gấp đôi.
- Trò chơi tiếp tục cho đến khi đạt ô có giá trị 2048 hoặc hết nước đi.
- Người chơi có thể tiếp tục chơi, undo/redo với phím U/R, và chỉnh sửa độ lớn bàn cờ.
- Người chơi có thể thoát ra và lưu lại tài khoản.

Các phím điều khiển (trong bàn cờ):
- Lên/W: Di chuyển lên.
- Xuống/S: Di chuyển xuống.
- Trái/A: Di chuyển sang trái.
- Phải/D: Di chuyển sang phải.
- U: Quay lại bàn cờ trước đó.
- R: Trở về bàn cờ khi undo.
- E: Thoát khỏi trò chơi.

Chiến lược chơi:
- Giữ các ô có giá trị cao ở góc bàn.
- Lập kế hoạch trước và xem xét các nước đi tiếp theo.
- Sử dụng chức năng Undo/Redo để thử các chiến lược khác nhau.

V.Các nguồn tài liệu đã tham khảo:

1. Đọc, ghi, mã hóa file binary
https://stackoverflow.com/questions/23399931/c-reading-string-from-binary-file-using-fstream
https://siliz4.github.io/guides/tutorials/2020/05/21/guide-on-binary-files-cpp.html
https://cplusplus.com/reference/fstream/fstream/
https://stackoverflow.com/questions/63248497/c-convert-the-binary-data-read-from-a-file-to-a-char-pointer

2. Thời gian
https://www.geeksforgeeks.org/chrono-in-c/

3. Random
https://github.com/ilqvya/random

4. Các thư viện đồ họa
https://cplusplus.com/forum/beginner/241912/#google_vignette
https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

5. Một số kiến thức khác
https://stackoverflow.com/questions/10076285/assignment-operator-overloading-in-c
https://roadmap.sh/cpp