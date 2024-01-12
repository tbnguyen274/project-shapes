# Project Shapes

1. Danh sách thành viên thực hiện đồ án
   - Họ và tên: Nguyễn Thái Bảo, MSSV: 23120023
   - Họ và tên: Lê Minh Hải, MSSV: 23120041

2. Các chức năng đã thực hiện
   - Đọc nội dung tập tin input.txt.
   - In ra màn hình thông tin các hình vừa đọc, đồng thời in ra chu vi, diện tích mỗi hình.
   - In ra màn hình thông tin hình có chu vi lớn nhất, hình có diện tích lớn nhất.
   - In ra màn hình thông tin hình có chu vi nhỏ nhất, hình có diện tích nhỏ nhất.
   - In ra màn hình thống kê số lượng các loại hình đã đọc.
   - Ghi nội dung tập tin vào tập tin output.txt gồm:
      + Chu vi lớn nhất.
      + Diện tích lớn nhất.
      + Chu vi nhỏ nhất.
      + Diện tích nhỏ nhất.
      + Thông kế số lượng các loại hình đã đọc.

3. Các chức năng chưa thực hiện
   Không có

4. Các nội dung/ chức năng đã tìm hiểu thêm/ bỏ công tìm hiểu sâu và giáo viên nên cân nhắc cộng điểm nếu có
   - Ghi các nội dung quan trọng vào tập tin output.txt
   - Sản phẩm nộp gồm 2 thư mục main và enhancement:
      + Thư mục main là thư mục chứa mã nguồn chính cho đồ án, nội dung có sử dụng mảng bất chấp kiểu dữ liệu
      (void*) và các hàm có lưu kiểu theo hướng dẫn.

      + Thư mục enhancement là thư mục chứa mã nguồn tối ưu hơn so với thư mục main. Lí do là việc sử dụng mảng
      bất chấp dữ liệu có thể mang lại nhiều bất lợi như: khó quản lý và duy trì, không an toàn về kiểu, dễ gây
      lỗi, không linh hoạt. Do đó ở đây, nhóm tạo thêm 1 struct Shape lưu trữ các thông tin chung về hình học
      như loại hình, chu vi, diện tích và các con trỏ đến 3 loại hình cụ thể. Từ đó, việc truy xuất, xử lý và
      tính toán có thể được thực hiện dễ dàng hơn thông qua đối tượng Shape và mã nguồn được cô đọng, dễ kiểm
      soát hơn.

5. Điểm tự đánh giá từng thành viên trên thang 10.
   - Nguyễn Thái Bảo: 10
   - Lê Minh Hải: 10