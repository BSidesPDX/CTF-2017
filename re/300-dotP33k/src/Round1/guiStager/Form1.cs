using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace guiStager
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void encrypt_Click(object sender, EventArgs e)
        {
            AppDomain myDomain = AppDomain.CurrentDomain;
            Assembly[] allAssemblies = myDomain.GetAssemblies();
            Assembly canYouReMe = null;
            Type encrypt = null;
            byte[] resultType = null;

            foreach (Assembly asm in allAssemblies)
            {
                string assemblyName = asm.FullName.ToString();
                if (assemblyName.Contains("canYouREMe"))
                {
                    canYouReMe = asm;
                    break;
                }
                return; 
            }

            encrypt = canYouReMe.GetTypes().First(t => t.Name == "stager");
            var methodInfo = encrypt.GetMethod("encryptTheFlag", BindingFlags.Static | BindingFlags.Instance | BindingFlags.Public);

            // 1.Put flag here
            var result = methodInfo.Invoke(encrypt, new object[] { Encoding.UTF8.GetBytes("FLAG") });
            resultType = (byte[])result;
            encryptedencryptedFlag.Text = Convert.ToBase64String(resultType);
        }

        private void decrypt_Click(object sender, EventArgs e)
        {
            // DEBUG macro. This is one of the "RE" parts of the challenge. 
#if DEBUG
            byte[] decryptedFlag = canYouREMe.stager.decryptTheFlag(Convert.FromBase64String(canYouREMe.stager.encryptedFlag));
            encryptedencryptedFlag.Text = Encoding.UTF8.GetString(decryptedFlag);
#endif
        }
    }
}
