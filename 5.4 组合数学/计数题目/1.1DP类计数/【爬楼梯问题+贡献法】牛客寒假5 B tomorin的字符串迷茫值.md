> Anon：不过，为了下次不失败努力不就好了  
> 
> Anon：就算失败一次，也要有重来的信心  
> Anon：不然人生这么长，怎么过得下去  
> 
> Anon：下次说不定会碰到奇迹，找到很棒的乐队成员啊
> 
> Anon：虽然那个人不一定是我，但我还挺想和你组乐队的
> 
> Tomori：那……能陪我组一辈子的乐队吗？
> 
> Anon：诶……一辈子？
> 
>   
> 
> BV 12 g 4 y 1 Q 7 kw
> 
> 不会做就去听听歌吧，虽然听了也不会做，但至少听了一首歌，血赚！

  

Tomorin 定义一个字符串的迷茫值为该字符串包含"mygo"连续子串的个数。例如"mygomygo"、"itsmygo"的迷茫值分别为 2，1，而"bangdream"的迷茫值为 0。

  
现在 tomorin 有一个字符串，她准备删除一些字符，但不能删除两个连续字符。  
  

Tomorin 想知道在所有删除方案中，字符串的迷茫值之和是多少？

  

由于答案可能很大，你需要将答案对 $10^9+7$ 取模。

## 输入：
一个仅包含小写字母的字符串，长度不超过 $2 \times 10^5$ 。

## 输出:
一个整数，代表迷茫值之和。由于答案可能很大，你只需要输出答案对 $10^9+7$ 取模的结果。

## 题解
我们本题的思路是计算每一种可能的构造方案对于我们答案的贡献，不难发现，如果我们想要构造出对应的 mygo 字符串，我们最多只有 8 种种可能的情况："mygo"，"m_ygo"，"my_go"，"myg_o"，"m_y_go"，"m_yg_o"，"my_g_o"，"m_y_g_o"这 8 种子串可以通过删除得到"mygo"子串。

我们分别计算**每一种情况对于我们的最终答案的贡献**，那么我们可以枚举上面这八种字串，然后计算他们对于我们答案的贡献值：

一个字串对于我们答案的贡献就是我们的左边任意删方案数乘以右边任意删方案数。而我们的两侧任意删的方案数，就可以通过我们的斐波那契数列处理得到。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int M = 1e9 + 7;

int main(){
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s + "BanG Dream! It's MyGO!!!!!";
    vector<int> f(n + 1, 1);
    f[1] = 2;
    for(int i = 2; i <= n; i++){
        f[i] = (f[i - 1] + f[i - 2]) % M;
    }
    vector<string> t = {"mygo", "m ygo", "my go", "myg o", "m y go", "m yg o", "my g o", "m y g o"};
    int ans = 0;
    for(int i = 1; i <= n; i++){
        for(auto &j : t){
            auto x = s.substr(i, j.size());
            auto check = [&](auto s, auto t){
                for(int i = 0; i < s.size(); i++){
                    if(t[i] == ' ') continue;
                    if(s[i] != t[i]) return 0;
                }
                return 1;
            };
            if(check(x, j)) ans = (ans + 1ll * f[i - 1] * f[n - (i + j.size() - 1)] % M) % M;
        }
    }
    cout << ans << endl;
}

```