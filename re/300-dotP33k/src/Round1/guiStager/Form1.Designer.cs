namespace guiStager
{
    partial class Form1
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
            this.encryptedencryptedFlag = new System.Windows.Forms.TextBox();
            this.encrypt = new System.Windows.Forms.Button();
            this.decrypt = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // encryptedSC
            // 
            this.encryptedencryptedFlag.Location = new System.Drawing.Point(34, 12);
            this.encryptedencryptedFlag.Multiline = true;
            this.encryptedencryptedFlag.Name = "encryptedencryptedFlag";
            this.encryptedencryptedFlag.Size = new System.Drawing.Size(170, 145);
            this.encryptedencryptedFlag.TabIndex = 1;
            // 
            // encrypt
            // 
            this.encrypt.Location = new System.Drawing.Point(34, 192);
            this.encrypt.Name = "encrypt";
            this.encrypt.Size = new System.Drawing.Size(170, 23);
            this.encrypt.TabIndex = 2;
            this.encrypt.Text = "encrypt";
            this.encrypt.UseVisualStyleBackColor = true;
            this.encrypt.Click += new System.EventHandler(this.encrypt_Click);
            // 
            // decrypt
            // 
            this.decrypt.Location = new System.Drawing.Point(34, 163);
            this.decrypt.Name = "decrypt";
            this.decrypt.Size = new System.Drawing.Size(170, 23);
            this.decrypt.TabIndex = 3;
            this.decrypt.Text = "decrypt";
            this.decrypt.UseVisualStyleBackColor = true;
            this.decrypt.Click += new System.EventHandler(this.decrypt_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(230, 240);
            this.Controls.Add(this.decrypt);
            this.Controls.Add(this.encrypt);
            this.Controls.Add(this.encryptedencryptedFlag);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox encryptedencryptedFlag;
        private System.Windows.Forms.Button encrypt;
        private System.Windows.Forms.Button decrypt;
    }
}

