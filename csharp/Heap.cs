using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DotNet90Console1;
public class Heap<T>
{
    Func<T, T, bool> comp;
    public Heap(Func<T, T, bool> comp) => this.comp = comp;
    bool Compare(int i, int j) => comp(GetAt(i), GetAt(j));
    List<T> _list = new List<T>();
    T GetAt(int index) => _list[index - 1];
    public bool Any() => _list.Any();
    public int Count => _list.Count;
    public T Head => _list[0];
    void Swap(int i, int j) => (_list[i - 1], _list[j - 1]) = (_list[j - 1], _list[i - 1]);
    public void Push(T n)
    {
        _list.Add(n);
        int i = Count;
        int inext = i >> 1;
        while (inext > 0 && Compare(i, inext))
        {
            Swap(i, inext);
            i = inext; inext = i >> 1;
        }
    }
    public bool PushPop(T val)
    {
        if (comp(Head, val))
        {
            _list[0] = val;
            SwapDown(1);
            return true;
        }
        return false;
    }
    public T Pop()
    {
        T val = _list.Last();
        _list.RemoveAt(_list.Count - 1);
        return PopPush(val);
    }
    public T PopPush(T val)
    {
        T ans = _list[0];
        _list[0] = val;
        SwapDown(1);
        return ans;
    }
    void SwapDown(int i)
    {
        int inext = i << 1;
        if (inext <= Count)
        {
            if (inext < Count && Compare(inext + 1, inext)) ++inext;
            if (Compare(inext, i))
            {
                Swap(i, inext);
                SwapDown(inext);
            }
        }
    }
    public T[] ToArray() => _list.ToArray();
}
