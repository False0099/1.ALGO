# 知识点
  ## [[双指针]]
# 题目
 
对于两个字符串 $s$ 和 $t$ ，若可以通过 **修改、删除或增加** $s$ 中的任意一个字符将 $s$ 变为 $t$ ，则认为这两个字符串的编辑距离为 1 。注意，只能选择一个操作，例如如果选择修改一个字符就不能再增加或删除字符了。  
  
给定两个由小写字母组成的**不同**的字符串 $s$ 与 $t$ ，请判断这两个字符串编辑距离是否为 1 。
# 思路
·要判断编辑距离，首先我们按照 s 和 t 的长度关系来分类
·如果 s 的长度是大于 t 的，那么我们就只考虑在不相等时删除依次看之后还会不会相等
·如果 s 的长度是等于 t 的，那么我们就只考虑在不相等的时候修改看之后还会不会不相等
·如果 s 的长度是小于 t 的，那么我们就只用考虑在相等的时候增加看之后还不会不会不相等。
# AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string a,b;cin >> a >> b;
    int al = a.length(),bl = b.length();
    if(al==bl)//判断长度相等的情况
    {
        int cnt = 0;
        for(int i = 0;i < al;i ++)
        {
            if(a[i]!=b[i]) cnt ++;
        }
        if(cnt==1) cout << "YES";
        else cout << "NO";
        return 0;
    }
    if(abs(al-bl)>1)//判断长度不同的情况 
    {
        cout << "NO";return 0;
    }
    if(al>bl)
    {
        int cnt = 0;
        for(int i = 0,j = 0;i<al,j < bl;)
        {
            if(a[i]!=b[j]) 
            {
                cnt ++;
                i ++;
            }
            else {i++;j++;}
        }
        if(cnt<=1) cout << "YES";
        else cout << "NO";
        return 0;
    }
    if(al<bl)
    {
        int cnt = 0;
        for(int i = 0,j = 0;i<bl,j < al;)
        {
            if(b[i]!=a[j]) 
            {
                cnt ++;
                i ++;
            }
            else {i++;j++;}
        }
        if(cnt<=1) cout << "YES";
        else cout << "NO";
        return 0;
    }
    return 0;
}
```
# 备注
