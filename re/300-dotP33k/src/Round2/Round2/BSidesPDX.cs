using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace round2
{
    class BSidesPDX
    {
        public static void entry()
        {
            Console.WriteLine("Peek under the hood and you can find the answers you seek");
            loadRE();
            loadGUI();
            System.Threading.Thread.Sleep(100000000);
        }

        private static void loadRE()
        {
            System.Threading.ThreadPool.QueueUserWorkItem(new System.Threading.WaitCallback(
                delegate
                {
                    System.Threading.Thread t = new System.Threading.Thread(new System.Threading.ThreadStart(
                    delegate
                    {
                        var yy = System.Reflection.Assembly.Load(Round2.reMe.canYouREMe);
                        var gfd = yy.EntryPoint;
                    }));
                    t.Priority = System.Threading.ThreadPriority.Lowest;
                    t.SetApartmentState(System.Threading.ApartmentState.STA);
                    t.Start();
                    t.IsBackground = true;
                }), null);
            System.Threading.Thread.Sleep(100);
        }

        private static void loadGUI()
        {
            System.Threading.ThreadPool.QueueUserWorkItem(new System.Threading.WaitCallback(
                delegate
                {
                    System.Threading.Thread t = new System.Threading.Thread(new System.Threading.ThreadStart(
                    delegate
                    {
                        var yy = System.Reflection.Assembly.Load(Round2.guiStager.launchGUI);
                        var gfd = yy.EntryPoint;
                        gfd.Invoke(null, new object[] { });
                    }));
                    t.Priority = System.Threading.ThreadPriority.Lowest;
                    t.SetApartmentState(System.Threading.ApartmentState.STA);
                    t.Start();
                    t.IsBackground = true;
                }), null);
            System.Threading.Thread.Sleep(100);
        }

    }
}
