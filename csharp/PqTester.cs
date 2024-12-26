using System;
using System.Collections.Generic;
using System.Diagnostics.Metrics;
using System.Linq;
using System.Numerics;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace DotNet90Console1;

class MyComp : IComparer<int>
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
internal class PqTester
{
    internal static void Run()
    {
        PriorityQueue<int, int> pq = new(new MyComp());
        int rep = 1000000;
        int x = 1;
        while (rep-- > 0)
        {
            x = (x << 1) % 1000000007;
            if (pq.Count == 100000)
            {
                pq.EnqueueDequeue(x, x);
                //++MyComp.counter;
                //if (x > pq.Peek())
                //{
                //    pq.Dequeue();
                //    if (MyComp.count_pushpop == 1)
                //        Console.WriteLine("pq.pop done. now emplace {0}", x);

                //    pq.Enqueue(x, x);
                //    ++MyComp.count_pushpop;
                //}
            }
            else pq.Enqueue(x, x);
        }
        Console.WriteLine("ans={0}", pq.Peek());
        Console.WriteLine("count={0}", MyComp.counter);
        Console.WriteLine("pushpop={0}", MyComp.count_pushpop);
        Console.WriteLine("pq size={0}", pq.Count);
    }
}
