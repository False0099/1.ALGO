# 知识点
  ## [[DFS]]
# 题目
 已知有两个字串 A, B 及一组字串变换的规则（至多 6 个规则）:

A 1→B 1
A 2→B 2
…

规则的含义为：在 A 中的子串 A 1 可以变换为 B 1、A 2 可以变换为 B 2…
。

例如：A＝abcd B＝xyz

变换规则为：

Abc → Xu
ud → Y 
y → Yz

则此时，A 可以经过一系列的变换变为 B，其变换的过程为：

Abcd → Xud → Xy → Xyz

共进行了三次变换，使得 A 变换为 B
。

注意，一次变换只能变换一个子串，例如 A＝aa B＝bb

变换规则为：

A → B

此时，不能将两个 a 在一步中全部转换为 b，而应当分两步完成。

## 输入格式
输入格式如下：

A B

A 1 B 1

A 2 B 2

… …

第一行是两个给定的字符串 A 和 B
。

接下来若干行，每行描述一组字串变换的规则。

所有字符串长度的上限为 20
。

## 输出格式
若在 10 步（包含 10 步）以内能将 A 变换为 B ，则输出最少的变换步数；否则输出 NO ANSWER!。

## 输入样例 ：
Abcd xyz
Abc xu
Ud y
Y yz
## 输出样例 ：
3

# 思路
·
·
·
# AC 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

const int N = 6;

int n;
string A, B;//起点、终点
string a[N], b[N];//规则
//da表示正序规则得到的，db表示按照逆序规则得到的。
int extend(queue<string>& q, unordered_map<string, int>&da, unordered_map<string, int>& db, 
    string a[N], string b[N])
{
    int d = da[q.front()];
    while (q.size() && da[q.front()] == d)
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < n; i ++ )
            for (int j = 0; j < t.size(); j ++ )
                if (t.substr(j, a[i].size()) == a[i])
                {
                    string r = t.substr(0, j) + b[i] + t.substr(j + a[i].size());//进行字符串的变换。
                    if (db.count(r)) return da[t] + db[r] + 1;//在b中出现过r
                    if (da.count(r)) continue;
                    da[r] = da[t] + 1;
                    q.push(r);
                }
    }

    return 11;//没找到前统一回复做不到
}

int bfs()
{
    if (A == B) return 0;
    queue<string> qa, qb;
    unordered_map<string, int> da, db;//每个bfs的距离数组

    qa.push(A), qb.push(B);
    da[A] = db[B] = 0;

    int step = 0;
    while (qa.size() && qb.size())
    {
        int t;
        if (qa.size() < qb.size()) t = extend(qa, da, db, a, b);//先扩展qa，正着写规则
        else t = extend(qb, db, da, b, a);//先扩展qb，规则数组反过来

        if (t <= 10) return t;
        if ( ++ step == 10) return -1;
    }

    return -1;
}

int main()
{
    cin >> A >> B;
    while (cin >> a[n] >> b[n]) n ++ ;

    int t = bfs();
    if (t == -1) puts("NO ANSWER!");
    else cout << t << endl;

    return 0;
}
```
# 备注
