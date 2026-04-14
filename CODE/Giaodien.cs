using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace CPUSchedulingAlgorithm
{
    public partial class Giaodien : Form
    {
        List<Process> processes = new List<Process>();

        public Giaodien()
        {
            InitializeComponent();
        }

    // lỗi file 
        private void Form1_Load(object sender, EventArgs e)
        {
            dataGridView1.BackgroundColor = Color.White;
            dataGridView1.BorderStyle = BorderStyle.None;

            dataGridView1.EnableHeadersVisualStyles = false;
            dataGridView1.ColumnHeadersDefaultCellStyle.BackColor = Color.FromArgb(30, 144, 255);
            dataGridView1.ColumnHeadersDefaultCellStyle.ForeColor = Color.White;
            dataGridView1.ColumnHeadersDefaultCellStyle.Font = new Font("Segoe UI", 11, FontStyle.Bold);

            dataGridView1.DefaultCellStyle.Font = new Font("Segoe UI", 10);
            dataGridView1.AlternatingRowsDefaultCellStyle.BackColor = Color.FromArgb(245, 245, 245);

            dataGridView1.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridView1.RowHeadersVisible = false;
        }

        // sửa lỗi  DATAGRID CLICK
        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
        }

        // ================= LOAD CSV =================
        private void btnLoad_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "CSV files (*.csv)|*.csv";

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                processes.Clear();
                dataGridView1.Rows.Clear();

                var lines = File.ReadAllLines(ofd.FileName);

                for (int i = 1; i < lines.Length; i++)
                {
                    var p = lines[i].Split(',');

                    Process pr = new Process
                    {
                        Name = p[0],
                        Arrival = int.Parse(p[1]),
                        Burst = int.Parse(p[2]),
                        Priority = int.Parse(p[3])
                    };

                    processes.Add(pr);

                    dataGridView1.Rows.Add(
                        pr.Name, pr.Arrival, pr.Burst, pr.Priority,
                        "", "", "", ""
                    );
                }

                MessageBox.Show("Load thành công!");
            }
        }

        // FCFS 
        private void btnFCFS_Click(object sender, EventArgs e)
        {
            var list = processes.OrderBy(p => p.Arrival).ToList();
            int time = 0;

            foreach (var p in list)
            {
                if (time < p.Arrival) time = p.Arrival;

                p.Start = time;
                p.Finish = time + p.Burst;
                p.Waiting = p.Start - p.Arrival;
                p.Turnaround = p.Finish - p.Arrival;

                time = p.Finish;
            }

            ShowData(list);
        }

        //  SJF 
        private void btnSJF_Click(object sender, EventArgs e)
        {
            var temp = processes.OrderBy(p => p.Arrival).ToList();
            List<Process> result = new List<Process>();
            int time = 0;

            while (temp.Count > 0)
            {
                var ready = temp.Where(p => p.Arrival <= time).ToList();

                if (ready.Count == 0)
                {
                    time++;
                    continue;
                }

                var p = ready.OrderBy(x => x.Burst).First();

                p.Start = time;
                p.Finish = time + p.Burst;
                p.Waiting = p.Start - p.Arrival;
                p.Turnaround = p.Finish - p.Arrival;

                result.Add(p);
                time = p.Finish;
                temp.Remove(p);
            }

            ShowData(result);
        }

        //  PRIORITY 
        private void btnPriority_Click(object sender, EventArgs e)
        {
            var list = processes.Select(p => new Process
            {
                Name = p.Name,
                Arrival = p.Arrival,
                Burst = p.Burst,
                Priority = p.Priority,
                Completed = false
            }).ToList();

            int time = 0;
            int completed = 0;
            int n = list.Count;

            List<Process> result = new List<Process>();

            while (completed < n)
            {
                Process selected = null;

                foreach (var p in list)
                {
                    if (!p.Completed && p.Arrival <= time)
                    {
                        if (selected == null ||
                            p.Priority < selected.Priority ||
                            (p.Priority == selected.Priority && p.Arrival < selected.Arrival))
                        {
                            selected = p;
                        }
                    }
                }

                if (selected == null)
                {
                    time++;
                    continue;
                }

                selected.Start = time;
                selected.Finish = time + selected.Burst;
                selected.Waiting = selected.Start - selected.Arrival;
                selected.Turnaround = selected.Finish - selected.Arrival;

                time = selected.Finish;
                selected.Completed = true;
                completed++;

                result.Add(selected);
            }

            ShowData(result);
        }

        // HIỂN THỊ 
        private void ShowData(List<Process> list)
        {
            dataGridView1.Rows.Clear();

            foreach (var p in list)
            {
                dataGridView1.Rows.Add(
                    p.Name, p.Arrival, p.Burst, p.Priority,
                    p.Start, p.Finish, p.Waiting, p.Turnaround
                );
            }
        }
    }

    public class Process
    {
        public string Name { get; set; }
        public int Arrival { get; set; }
        public int Burst { get; set; }
        public int Priority { get; set; }

        public int Start { get; set; }
        public int Finish { get; set; }
        public int Waiting { get; set; }
        public int Turnaround { get; set; }

        public bool Completed { get; set; }
    }
}
