using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using VineCopulaWrapper;

namespace VineCopulaTest
{
    class Program
    {


        // [DllImport("VinCopulaDll.dll")] public static extern double getAverage(double[] val, int size);
        [DllImport("VinCopulaDll.dll")] public static extern double Hinv1(int family, int nsize, double[] x, double[] y, double theta, double nu, double[] output);


        // void Hinv(int* family, int* n, double* u, double* v, double* theta, double* nu, double* out)
        static void Main(string[] args)
        {
            const int nsize = 3000;
            Random randObj = new Random();
            double[] x = new double[nsize];
            double[] y = new double[nsize];
            double[] output = new double[nsize];

            double[] results = new double[nsize];

            // Generate random integers and doubles, and then count
            // them by group.
            for (int i = 0; i < nsize; i++)
            {
                x[i] = (double)randObj.Next(0, 1);
                y[i] = (double)randObj.Next(0, 1);
            }


            VineCopulaBridge bridge = new VineCopulaBridge();
            results = bridge.Hinv1(134, nsize, x, y, -2.55, 0.36, output);


            string resultsPath = @"C:\VN\results.txt";


            using (StreamWriter sw = new StreamWriter(resultsPath, true))
            {
                for (int i = 0; i < nsize; i++)
                {
                    sw.WriteLine($"Value at index {i} is {results[i]}");

                }

            }

          
        }
    }
}
