using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace canYouREMe
{
    static public class stager
    {
        public static byte[] encryptTheFlag(byte[] flag)
        {
            byte[] passwordBytes = Encoding.UTF8.GetBytes("BSidesPDXBSidesPDXBSidesPDXBSidesPDXBSidesPDX");
            byte[] encSC = crypto.AES_Encrypt(flag, passwordBytes);
            return encSC;
        }


        public static byte[] decryptTheFlag(byte[] flag)
        {
            byte[] passwordBytes = Encoding.UTF8.GetBytes("BSidesPDXBSidesPDXBSidesPDXBSidesPDXBSidesPDX");
            byte[] encSC = crypto.AES_Decrypt(flag, passwordBytes);
            return encSC;
        }

        // 2. Take the base64 encrypted flag and put it here. 
        public static string encryptedFlag = "m1emrQ4us7IyLTYZHL/VLgtF7oyjsFxkaGpqTJ5ZFbs=";
    }
}
