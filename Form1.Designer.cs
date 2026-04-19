namespace WinFormsApp1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            btnOpenFile = new Button();
            btnRun = new Button();
            lblFilePath = new Label();
            cboAlgo = new ComboBox();
            dgvResult = new DataGridView();
            pnlGantt = new Panel();
            ((System.ComponentModel.ISupportInitialize)dgvResult).BeginInit();
            SuspendLayout();
            // 
            // btnOpenFile
            // 
            btnOpenFile.BackgroundImageLayout = ImageLayout.Center;
            btnOpenFile.ForeColor = SystemColors.MenuText;
            btnOpenFile.Location = new Point(12, 39);
            btnOpenFile.Name = "btnOpenFile";
            btnOpenFile.Size = new Size(177, 65);
            btnOpenFile.TabIndex = 0;
            btnOpenFile.Text = "Mở file CSV";
            btnOpenFile.UseVisualStyleBackColor = true;
            btnOpenFile.Click += btnOpenFile_Click;
            // 
            // btnRun
            // 
            btnRun.Location = new Point(12, 114);
            btnRun.Name = "btnRun";
            btnRun.Size = new Size(175, 78);
            btnRun.TabIndex = 1;
            btnRun.Text = "Chạy và Vẽ";
            btnRun.UseVisualStyleBackColor = true;
            btnRun.Click += btnRun_Click;
            // 
            // lblFilePath
            // 
            lblFilePath.AutoSize = true;
            lblFilePath.Location = new Point(230, 103);
            lblFilePath.Margin = new Padding(2);
            lblFilePath.Name = "lblFilePath";
            lblFilePath.Size = new Size(93, 15);
            lblFilePath.TabIndex = 2;
            lblFilePath.Text = "Chưa chọn file...";
            // 
            // cboAlgo
            // 
            cboAlgo.ForeColor = SystemColors.MenuHighlight;
            cboAlgo.FormattingEnabled = true;
            cboAlgo.Items.AddRange(new object[] { "FCFS", "SJF" });
            cboAlgo.Location = new Point(554, 100);
            cboAlgo.Name = "cboAlgo";
            cboAlgo.Size = new Size(188, 23);
            cboAlgo.TabIndex = 3;
            // 
            // dgvResult
            // 
            dgvResult.BackgroundColor = SystemColors.Info;
            dgvResult.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvResult.Location = new Point(193, 184);
            dgvResult.Name = "dgvResult";
            dgvResult.Size = new Size(783, 184);
            dgvResult.TabIndex = 4;
            dgvResult.CellContentClick += dgvResult_CellContentClick;
            // 
            // pnlGantt
            // 
            pnlGantt.BackColor = SystemColors.ControlLight;
            pnlGantt.Location = new Point(193, 386);
            pnlGantt.Name = "pnlGantt";
            pnlGantt.Size = new Size(783, 213);
            pnlGantt.TabIndex = 5;
            pnlGantt.Paint += pnlGantt_Paint;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1510, 638);
            Controls.Add(pnlGantt);
            Controls.Add(dgvResult);
            Controls.Add(cboAlgo);
            Controls.Add(lblFilePath);
            Controls.Add(btnRun);
            Controls.Add(btnOpenFile);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)dgvResult).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnOpenFile;
        private Button btnRun;
        private Label lblFilePath;
        private ComboBox cboAlgo;
        private DataGridView dgvResult;
        private Panel pnlGantt;
    }
}
