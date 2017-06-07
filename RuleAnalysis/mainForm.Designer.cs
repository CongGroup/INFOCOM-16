namespace RuleAnalysis
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtRuleFile = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.label2 = new System.Windows.Forms.Label();
            this.tbAllRules = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.tbTcpRules = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.tbCommonPair = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tbAllPair = new System.Windows.Forms.TextBox();
            this.tbOffDepPair = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.tbFieldPair = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.tbSavetoFile = new System.Windows.Forms.TextBox();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(457, 430);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.groupBox3);
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(449, 404);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Snort Rules";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.tbFieldPair);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.tbOffDepPair);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.tbAllPair);
            this.groupBox3.Controls.Add(this.tbCommonPair);
            this.groupBox3.Controls.Add(this.tbTcpRules);
            this.groupBox3.Controls.Add(this.tbAllRules);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Location = new System.Drawing.Point(18, 122);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(398, 261);
            this.groupBox3.TabIndex = 6;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Rule Info";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtRuleFile);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(18, 22);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(398, 85);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Rule File";
            // 
            // txtRuleFile
            // 
            this.txtRuleFile.Cursor = System.Windows.Forms.Cursors.Hand;
            this.txtRuleFile.Location = new System.Drawing.Point(89, 40);
            this.txtRuleFile.Name = "txtRuleFile";
            this.txtRuleFile.Size = new System.Drawing.Size(275, 21);
            this.txtRuleFile.TabIndex = 1;
            this.txtRuleFile.Click += new System.EventHandler(this.txtRuleFile_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 43);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "RuleFile";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.groupBox2);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(449, 404);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Put into Index";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(41, 44);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "All Rules";
            // 
            // tbAllRules
            // 
            this.tbAllRules.Location = new System.Drawing.Point(122, 41);
            this.tbAllRules.Name = "tbAllRules";
            this.tbAllRules.ReadOnly = true;
            this.tbAllRules.Size = new System.Drawing.Size(48, 21);
            this.tbAllRules.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(214, 44);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "TCP Rules";
            // 
            // tbTcpRules
            // 
            this.tbTcpRules.Location = new System.Drawing.Point(289, 41);
            this.tbTcpRules.Name = "tbTcpRules";
            this.tbTcpRules.ReadOnly = true;
            this.tbTcpRules.Size = new System.Drawing.Size(48, 21);
            this.tbTcpRules.TabIndex = 1;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(41, 90);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(119, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "Common content Pair";
            // 
            // tbCommonPair
            // 
            this.tbCommonPair.Location = new System.Drawing.Point(187, 87);
            this.tbCommonPair.Name = "tbCommonPair";
            this.tbCommonPair.ReadOnly = true;
            this.tbCommonPair.Size = new System.Drawing.Size(147, 21);
            this.tbCommonPair.TabIndex = 1;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(43, 209);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(119, 12);
            this.label5.TabIndex = 0;
            this.label5.Text = "Totally All KeyPair";
            // 
            // tbAllPair
            // 
            this.tbAllPair.Location = new System.Drawing.Point(189, 206);
            this.tbAllPair.Name = "tbAllPair";
            this.tbAllPair.ReadOnly = true;
            this.tbAllPair.Size = new System.Drawing.Size(147, 21);
            this.tbAllPair.TabIndex = 1;
            // 
            // tbOffDepPair
            // 
            this.tbOffDepPair.Location = new System.Drawing.Point(187, 126);
            this.tbOffDepPair.Name = "tbOffDepPair";
            this.tbOffDepPair.ReadOnly = true;
            this.tbOffDepPair.Size = new System.Drawing.Size(147, 21);
            this.tbOffDepPair.TabIndex = 3;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(41, 129);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(131, 12);
            this.label6.TabIndex = 2;
            this.label6.Text = "Offset And depth Pair";
            // 
            // tbFieldPair
            // 
            this.tbFieldPair.Location = new System.Drawing.Point(189, 165);
            this.tbFieldPair.Name = "tbFieldPair";
            this.tbFieldPair.ReadOnly = true;
            this.tbFieldPair.Size = new System.Drawing.Size(147, 21);
            this.tbFieldPair.TabIndex = 5;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(43, 168);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(119, 12);
            this.label7.TabIndex = 4;
            this.label7.Text = "Http Attribute Pair";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.tbSavetoFile);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Location = new System.Drawing.Point(11, 11);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(424, 107);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Output Snort Pairs";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(21, 51);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(77, 12);
            this.label8.TabIndex = 0;
            this.label8.Text = "Save to File";
            // 
            // tbSavetoFile
            // 
            this.tbSavetoFile.Cursor = System.Windows.Forms.Cursors.Hand;
            this.tbSavetoFile.Location = new System.Drawing.Point(122, 48);
            this.tbSavetoFile.Name = "tbSavetoFile";
            this.tbSavetoFile.Size = new System.Drawing.Size(269, 21);
            this.tbSavetoFile.TabIndex = 1;
            this.tbSavetoFile.Click += new System.EventHandler(this.tbSavetoFile_Click);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(457, 430);
            this.Controls.Add(this.tabControl1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "mainForm";
            this.Text = "RuleAnalysis";
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtRuleFile;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbAllRules;
        private System.Windows.Forms.TextBox tbAllPair;
        private System.Windows.Forms.TextBox tbCommonPair;
        private System.Windows.Forms.TextBox tbTcpRules;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbOffDepPair;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox tbFieldPair;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox tbSavetoFile;
    }
}

