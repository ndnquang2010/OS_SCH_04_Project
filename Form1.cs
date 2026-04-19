using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace WinFormsApp1
{

    public partial class Form1 : Form
    {
        List<Process> listInput = new List<Process>();

        public Form1()
        {
            InitializeComponent();
        }

        // 1. Nút Mở file CSV
        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog { Filter = "CSV Files|*.csv" };
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                lblFilePath.Text = ofd.FileName;
                listInput.Clear();
                try
                {
                    var lines = File.ReadAllLines(ofd.FileName);
                    foreach (var line in lines.Skip(1)) // Bỏ qua dòng tiêu đề
                    {
                        if (string.IsNullOrWhiteSpace(line)) continue;
                        var parts = line.Split(',');
                        listInput.Add(new Process
                        {
                            Name = parts[0].Trim(),
                            ArrivalTime = int.Parse(parts[1].Trim()),
                            BurstTime = int.Parse(parts[2].Trim())
                        });
                    }
                    dgvResult.DataSource = null;
                    dgvResult.DataSource = listInput.ToList();
                    MessageBox.Show("Đã nạp " + listInput.Count + " tiến trình.");
                }
                catch (Exception ex) { MessageBox.Show("Lỗi đọc file: " + ex.Message); }
            }
        }

        // 2. Nút Chạy & Vẽ
        private void btnRun_Click(object sender, EventArgs e)
        {
            if (listInput.Count == 0) { MessageBox.Show("Hãy mở file CSV trước!"); return; }

            // Kiểm tra xem đã chọn thuật toán trong ComboBox chưa
            if (cboAlgo.SelectedItem == null)
            {
                MessageBox.Show("Vui lòng chọn thuật toán (FCFS hoặc SJF)!");
                return;
            }

            List<Process> solved;
            string selectedAlgo = cboAlgo.SelectedItem.ToString();

            // Clone dữ liệu để tính toán
            var tempData = listInput.Select(p => new Process { Name = p.Name, ArrivalTime = p.ArrivalTime, BurstTime = p.BurstTime }).ToList();

            if (selectedAlgo.Contains("SJF"))
                solved = CalculateSJF(tempData);
            else
                solved = CalculateFCFS(tempData);

            // Hiển thị kết quả lên bảng
            dgvResult.DataSource = null;
            dgvResult.DataSource = solved;

            // Vẽ biểu đồ Gantt
            DrawGantt(solved);

            // Tự động xuất file kết quả
            ExportToCSV(solved);
        }

        private List<Process> CalculateFCFS(List<Process> input)
        {
            var sorted = input.OrderBy(p => p.ArrivalTime).ToList();
            int cur = 0;
            foreach (var p in sorted)
            {
                if (cur < p.ArrivalTime) cur = p.ArrivalTime;
                p.StartTime = cur;
                p.CompletionTime = p.StartTime + p.BurstTime;
                p.TurnaroundTime = p.CompletionTime - p.ArrivalTime;
                p.WaitingTime = p.TurnaroundTime - p.BurstTime;
                cur = p.CompletionTime;
            }
            return sorted;
        }

        private List<Process> CalculateSJF(List<Process> input)
        {
            List<Process> res = new List<Process>();
            int cur = 0;
            while (input.Count > 0)
            {
                var ready = input.Where(p => p.ArrivalTime <= cur).OrderBy(p => p.BurstTime).FirstOrDefault();
                if (ready == null) { cur = input.Min(p => p.ArrivalTime); continue; }
                ready.StartTime = cur;
                ready.CompletionTime = ready.StartTime + ready.BurstTime;
                ready.TurnaroundTime = ready.CompletionTime - ready.ArrivalTime;
                ready.WaitingTime = ready.TurnaroundTime - ready.BurstTime;
                cur = ready.CompletionTime;
                res.Add(ready);
                input.Remove(ready);
            }
            return res;
        }

        private void DrawGantt(List<Process> processes)
        {
            Graphics g = pnlGantt.CreateGraphics();
            g.Clear(Color.White);
            int x = 10, y = 20, scale = 30; // Tăng scale để hình to hơn
            Pen pen = new Pen(Color.Black, 2);
            Font f = new Font("Arial", 10, FontStyle.Bold);

            foreach (var p in processes)
            {
                int w = p.BurstTime * scale;
                // Tô màu xanh nhạt cho ô tiến trình
                g.FillRectangle(Brushes.LightBlue, x, y, w, 40);
                g.DrawRectangle(pen, x, y, w, 40);
                // Vẽ tên P1, P2...
                g.DrawString(p.Name, f, Brushes.Black, x + 2, y + 12);
                // Vẽ mốc thời gian bắt đầu
                g.DrawString(p.StartTime.ToString(), Font, Brushes.Red, x, y + 45);
                x += w;
            }
            // Vẽ mốc thời gian kết thúc cuối cùng
            if (processes.Count > 0)
                g.DrawString(processes.Last().CompletionTime.ToString(), Font, Brushes.Red, x - 10, y + 45);
        }

        private void ExportToCSV(List<Process> result)
        {
            try
            {
                string folder = Path.Combine(Application.StartupPath, "Output");
                if (!Directory.Exists(folder)) Directory.CreateDirectory(folder);
                string file = Path.Combine(folder, "Result.csv");
                using (StreamWriter sw = new StreamWriter(file))
                {
                    sw.WriteLine("Process,Arrival,Burst,Start,Finish,Waiting,Turnaround");
                    foreach (var p in result)
                        sw.WriteLine($"{p.Name},{p.ArrivalTime},{p.BurstTime},{p.StartTime},{p.CompletionTime},{p.WaitingTime},{p.TurnaroundTime}");
                }
                MessageBox.Show("Kết quả đã lưu tại: " + file);
            }
            catch { }
        }

        private void pnlGantt_Paint(object sender, PaintEventArgs e)
        {

        }

        private void dgvResult_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }

    public class Process
    {
        public string Name { get; set; } = "";
        public int ArrivalTime { get; set; }
        public int BurstTime { get; set; }
        public int StartTime { get; set; }
        public int CompletionTime { get; set; }
        public int WaitingTime { get; set; }
        public int TurnaroundTime { get; set; }
    }
}