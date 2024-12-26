using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DotNet90Console1;

internal static class Common
{
    public static int MaxSize { get; private set; } = 0;

    public static IEnumerable<ulong> OrderedSumOfList(this IList<uint> a)
    {
        if (a.Count == 0 || a.Any(t => t == 0))
            throw new ArgumentException("list empty or list contains 0");

        Span<uint> st = stackalloc uint[a.Count];
        foreach (var item in a.OrderBy(t => t).Zip(Enumerable.Range(0, a.Count)))
            st[item.Second] = item.First;

        yield return 0UL; 

        PriorityQueue<(ulong, int, int), ulong> pq = new();
        pq.Enqueue((a[0], 0, a.Count - 1), a[0]);
        while (pq.Count > 0)
        {
            (ulong sm, int i, int limit) = pq.Peek(); // pq.Dequeue(); // 放到后面一起调DequeueEnqueue，提高效率
            yield return sm;

            // op1: add a[0]
            ulong nx = sm + a[0];
            pq.DequeueEnqueue((nx, 0, i), nx);


            // op2: move a[i] to a[i + 1] (limit: a[i] only taken 1)
            if (i + 1 <= limit)
            {
                nx = sm - a[i] + a[i + 1];
                pq.Enqueue((nx, i + 1, limit), nx);
            }

            MaxSize = Math.Max(MaxSize, pq.Count);
        }
    }

    /* 用乘法的版本
    public static IEnumerable<ulong> OrderedSumOfList(this IList<uint> a)
    {
        if (a.Count == 0 || a.Any(t => t == 0))
            throw new ArgumentException("list empty or list contains 0");

        //Span<uint> st = stackalloc uint[a.Count];

        yield return 1UL; // 0UL

        PriorityQueue<(ulong, int, int), ulong> pq = new();
        pq.Enqueue((a[0], 0, a.Count - 1), a[0]);
        while (pq.Count > 0)
        {
            (ulong sm, int i, int limit) = pq.Dequeue();
            yield return sm;

            // op1: add a[0]
            ulong nx = sm * a[0];
            pq.Enqueue((nx, 0, i), nx);


            // op2: move a[i] to a[i + 1] (limit: a[i] only taken 1)
            if (i + 1 <= limit)
            {
                nx = sm / a[i] * a[i + 1];
                pq.Enqueue((nx, i + 1, limit), nx);
            }
        }
    }
     * */
}
