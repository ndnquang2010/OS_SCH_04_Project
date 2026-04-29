# OS_SCH_04_Project

## 📌 Giới thiệu
Đây là đồ án môn **Hệ điều hành**, tập trung vào việc mô phỏng các **thuật toán lập lịch CPU (CPU Scheduling)**.  
Mục tiêu của dự án là giúp hiểu rõ cách hệ điều hành quản lý tiến trình trong **hàng đợi sẵn sàng (ready queue)** và phân phối thời gian CPU một cách hiệu quả.

Dự án hỗ trợ mô phỏng và phân tích:
- Quản lý tiến trình
- Hàng đợi sẵn sàng
- Thời gian chờ
- Thời gian hoàn thành
- So sánh hiệu suất các thuật toán

---

## 🎯 Mục tiêu
- Hiểu nguyên lý hoạt động của các thuật toán lập lịch CPU
- Mô phỏng các thuật toán phổ biến trong môn Hệ điều hành
- Đánh giá hiệu suất thông qua các chỉ số
- So sánh ưu và nhược điểm của từng thuật toán

---

## ⚙️ Các thuật toán được cài đặt
Dự án bao gồm các thuật toán sau:

### 1. FCFS (First Come First Serve)
Tiến trình đến trước sẽ được xử lý trước.

### 2. SJF (Shortest Job First)
Tiến trình có thời gian xử lý ngắn nhất sẽ được ưu tiên.

### 3. Priority Scheduling
Lập lịch theo độ ưu tiên của tiến trình.

### 4. Round Robin (RR)
Mỗi tiến trình được cấp một khoảng thời gian CPU cố định theo vòng lặp.

### 5. Multi-Level Queue (MLQ)
Các tiến trình được chia thành nhiều hàng đợi theo mức ưu tiên.

---

## 🛠 Công nghệ sử dụng
- **Ngôn ngữ:** C
- **Compiler:** GCC
- **Nền tảng:** Linux / Ubuntu
- **Công cụ:** Terminal, Makefile

---

## 📂 Cấu trúc thư mục
```bash
OS_SCH_04_Project/
│── src/
│   ├── scheduler.c
│   ├── queue.c
│   ├── process.c
│── include/
│   ├── scheduler.h
│   ├── queue.h
│── input/
│   ├── processes.txt
│── output/
│   ├── result.txt
│── README.md
```

---

## ▶️ Cách chạy chương trình

### Biên dịch
```bash
gcc *.c -o scheduler
```

### Chạy chương trình
```bash
./scheduler
```

---

## 📊 Các chỉ số đánh giá
Dự án sử dụng các chỉ số sau để đánh giá hiệu suất:

- **Waiting Time (Thời gian chờ)**
- **Turnaround Time (Thời gian hoàn thành)**
- **Response Time (Thời gian phản hồi)**
- **CPU Utilization (Mức sử dụng CPU)**

---

## 📈 Ví dụ kết quả
```text
Tiến trình   Đến   Xử lý   Chờ   Hoàn thành
P1           0     5       0     5
P2           1     3       4     7
P3           2     2       6     8
```

Thời gian chờ trung bình = 3.33  
Thời gian hoàn thành trung bình = 6.67  

---

## 👨‍💻 Tác giả
**Nguyễn Đình Quang**  
Đồ án môn Hệ điều hành

---

## 📚 Tài liệu tham khảo
- Giáo trình Hệ điều hành
- Operating System Concepts
- Tài liệu bài giảng và bài lab
