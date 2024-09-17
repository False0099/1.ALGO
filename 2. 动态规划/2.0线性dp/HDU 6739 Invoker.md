Problem Description

In dota2, there is a hero named Invoker. He has 3 basic skills in the game, which are Quas, Wex and Exort. Once he launches a basic skill, he will gain the corresponding element, where Quas gives "Q", Wex gives "W" and Exort gives "E".  
Invoker can't have more than 3 elements simultaneously. If he launches a basic skill when he already owns 3 elements, he will get the corresponding element and lose the element he gained the earliest.  
As can be seen, there are 10 unordered combinations of 3 elements in 3 types, each represents a special skill, which are as follows:  
 

- Cold Snap: unordered element combination "QQQ", denoted by "Y"  
    
- Ghost Walk: unordered element combination "QQW", denoted by "V"  
    
- Ice Wall: unordered element combination "QQE", denoted by "G"  
    
- EMP: unordered element combination "WWW", denoted by "C"  
    
- Tornado: unordered element combination "QWW", denoted by "X"  
    
- Alacrity: unordered element combination "WWE", denoted by "Z"  
    
- Sun Strike: unordered element combination "EEE", denoted by "T"  
    
- Forge Spirit: unordered element combination "QEE", denoted by "F"  
    
- Chaos Meteor: unordered element combination "WEE", denoted by "D"
- Deafening Blast: unordered element combination "QWE", denoted by "B"  
    
- When Invoker owns 3 elements, he can launch the invoking skill, denoted by "R", to gain the special skill according to the elements he currently owns. After invoking, the elements won't disappear, and the chronological order of the 3 elements won't change.  
    Now given a sequence of special skills, you want to invoke them one by one with using the minimum number of basic skills(Q,W,E) and invoking skill(R). Print the minimum number in a single line.  
    At the beginning, Invoker owns no elements. And you should re-invoke the special skills even if you have already invoked the same skills just now.

Input

Input a single line containing a string s (1 ≤ |s| ≤ 100 000) that only contains uppercase letters in {B, C, D, F, G, T, V, X, Y, Z}, denoting the sequence of special skills.

Output

Output a single line containing a positive integer, denoting the minimum number of skills to launch.

Sample Input

XDTBVV

Sample Output

15

_Hint_

One possible scheme is QWWREERERWQRQRR.

## 题意：
一个英雄每次按 Q,W,E 键就会出现一个相应的魔法球,三个魔法球会组合成技能,按 R 键释放,释放技能后魔法球不会消失,魔法球最多存在3个,召唤新的魔法球后,最先出现的魔法球会消失,

## 题解
我们本题的决策在于我们用什么顺序去构成我们的对应的魔法球，而因为我们这一题一种球只有 6 种情况，而因此，我们完全可以枚举我们的情况是什么，然后再去考虑我们的转移。

我们设 $dp[i][j]$ 表示我们用第 j 种方式释放我们的 i 技能的最小花费是多少，于是我们就可以大力分类讨论后再转移即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int inf = 0x3f3f3f3f;
int dp[N][7];
map<char, string>mp;
int dir[6][3] = {0, 1, 2, 0, 2, 1, 1, 0, 2, 1, 2, 0, 2, 0, 1, 2, 1, 0};
 
void solve(int id, string a, string b) {
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6; ++j) {
            if(a[dir[i][0]] == b[dir[j][0]] && a[dir[i][1]] == b[dir[j][1]] && a[dir[i][2]] == b[dir[j][2]])
                dp[id][j] = min(dp[id - 1][i], dp[id][j]);
            else if(a[dir[i][1]] == b[dir[j][0]] && a[dir[i][2]] == b[dir[j][1]])
                dp[id][j] = min(dp[id - 1][i] + 1, dp[id][j]);
            else if(a[dir[i][2]] == b[dir[j][0]])
                dp[id][j] = min(dp[id - 1][i] + 2, dp[id][j]);
            else
                dp[id][j] = min(dp[id - 1][i] + 3, dp[id][j]);
        }
    }
}
 
int main() {
    mp['Y'] = "QQQ", mp['V'] = "QQW", mp['G'] = "QQE", mp['C'] = "WWW", mp['X'] = "QWW";
    mp['Z'] = "WWE", mp['T'] = "EEE", mp['F'] = "QEE", mp['D'] = "WEE", mp['B'] = "QWE";
    string s;
    while(cin >> s) {
        int len = s.size();
        memset(dp, inf, sizeof(dp));
        for(int i = 0; i < 6; ++i) dp[0][i] = 3;
        for(int i = 1; i < len; ++i) {
            solve(i, mp[s[i - 1]], mp[s[i]]);
        }
        int minn = inf;
        for(int i = 0; i < 6; ++i)
            minn = min(minn, dp[len - 1][i]);
        printf("%d\n", minn + len);
    }
    return 0;
}
```