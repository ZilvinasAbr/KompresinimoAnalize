using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ArithmeticCoder;

namespace ArithmeticCompression
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //One 'alphabet' that encodes BILL GATES
            List<coder.symbol> billgates =
            new List<coder.symbol>
            {
                new coder.symbol(' ',0,1),//1
                new coder.symbol('A',1,2),//2
                new coder.symbol('B',2,3),//3
                new coder.symbol('E',3,4),//4
                new coder.symbol('G',4,5),//5
                new coder.symbol('I',5,6),//6
                new coder.symbol('L',6,8),//7
                new coder.symbol('S',8,9),//8
                new coder.symbol('T',9,10)//9                
            };

            //Another 'alphabet' that encodes hexadecimal digits/numbers
            List<coder.symbol> hexcodes =
            new List<coder.symbol>
            {
                new coder.symbol('0',0,1),//0x00
                new coder.symbol('1',1,2),//0x01
                new coder.symbol('2',2,3),//0x02
                new coder.symbol('3',3,4),//0x03
                new coder.symbol('4',4,5),//0x04
                new coder.symbol('5',5,6),//0x05
                new coder.symbol('6',6,7),//0x06
                new coder.symbol('7',7,8),//0x07
                new coder.symbol('8',8,9),//0x08
                new coder.symbol('9',9,10),//0x09
                new coder.symbol('A',10,11),//0x10
                new coder.symbol('B',11,12),//0x11
                new coder.symbol('C',12,13),//0x12
                new coder.symbol('D',13,14),//0x13
                new coder.symbol('E',14,15),//0x14
                new coder.symbol('F',15,16)//0x15                
            };




            string test, expand_test, compressed = "";
            
            System.IO.MemoryStream mem_test = new System.IO.MemoryStream();

            coder c;

            //Test 1
            test = "BILL GATES";

            c = new coder(billgates);

            c.Scale = 11;//Very important

            mem_test = c.compress(test);

            foreach (byte b in mem_test.ToArray())
                compressed += b.ToString();

            expand_test = c.expand(mem_test, test.Length);

            MessageBox.Show(" Before Compression :" + test);
            MessageBox.Show(" Compressed (" + mem_test.Length + " bytes) :\n" + compressed);
            MessageBox.Show(" Expanded :" + expand_test);

            //Test 2
            
            test = "FEDCBA9876543210";

            c = new coder(hexcodes);

            c.Scale = 16;

            mem_test = c.compress(test);

            foreach (byte b in mem_test.ToArray())
                compressed += b.ToString();

            expand_test = c.expand(mem_test, test.Length);

            MessageBox.Show(" Before Compression :" + test);
            MessageBox.Show(" Compressed (" + mem_test.Length + " bytes) :\n" + compressed);
            MessageBox.Show(" Expanded :" + expand_test);
        }
    }
}
