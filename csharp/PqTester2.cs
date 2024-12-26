using System;
using System.Collections.Generic;
using System.Diagnostics.Metrics;
using System.Linq;
using System.Numerics;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace DotNet90Console1;

class MyComp2 : IComparer<int>
{
    internal static uint counter = 0;
    internal static uint count_pushpop = 0;
    public int Compare(int x, int y)
    {
        ++counter;
        if (count_pushpop == 1)
        {
            Console.WriteLine("comp {0} {1}", x, y);
        }
        return x.CompareTo(y);
    }
}
internal class PqTester2
{
    internal static void Run()
    {
        var mycomp = new MyComp2();
        var pq = new Heap<int>((a, b) => mycomp.Compare(a, b) < 0);
        int rep = 1000000;
        int x = 1;
        while (rep-- > 0)
        {
            x = (x << 1) % 1000000007;
            if (pq.Count == 100000)
            {
                pq.PushPop(x);
                //++MyComp2.counter;
                //if (x > pq.Head)
                //{
                //    pq.Pop();
                //    if (MyComp2.count_pushpop == 1)
                //        Console.WriteLine("pq.pop done. now emplace {0}", x);

                //    pq.Push(x);
                //    ++MyComp2.count_pushpop;
                //}
            }
            else pq.Push(x); 
        }
        Console.WriteLine("ans={0}", pq.Head); 
        Console.WriteLine("count={0}", MyComp2.counter);
        Console.WriteLine("pushpop={0}", MyComp2.count_pushpop);
        Console.WriteLine("pq size={0}", pq.Count);
    }
}
