// See https://aka.ms/new-console-template for more information

using DotNet90Console1;

var t = System.Environment.TickCount64;

// run
uint[] a = { 102, 10011, 1000017 }; // 必须各个元素差距比较大，maxQueueSize才会比较小
Console.WriteLine(string.Join(" ", a.OrderedSumOfList().Take(500)));
Console.WriteLine("Max Queue Size=" + Common.MaxSize);

t = System.Environment.TickCount64 - t;
Console.WriteLine("Done. time = {0} ms", t);
