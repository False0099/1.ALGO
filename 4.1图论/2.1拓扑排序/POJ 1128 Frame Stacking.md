考虑以下5个图片帧放置在9×8阵列上。  

  
........ ........ ........ ........ .CCC....
  
EEEEEE.. ........ ........ ..BBBB.. .C.C....
  
E....E.. DDDDDD.. ........ ..B..B.. .C.C....
  
E....E.. D....D.. ........ ..B..B.. .CCC....
  
E....E.. D....D.. ....AAAA ..B..B.. ........
  
E....E.. D....D.. ....A..A ..BBBB.. ........
  
E....E.. DDDDDD.. ....A..A ........ ........
  
E....E.. ........ ....AAAA ........ ........
  
EEEEEE.. ........ ........ ........ ........
  
    1        2        3        4        5   

  
现在把它们放在一起，从底部的1开始，到顶部的5结束。如果一个框架的任何部分覆盖了另一个框架，那么它会将框架的该部分隐藏在下面。  
  
查看由5帧组成的堆栈，我们可以看到以下内容。  

  
.CCC....
  
ECBCBB..
  
DCBCDB..
  
DCCC.B..
  
D.B.ABAA
  
D.BBBB.A
  
DDDDAD.A
  
E...AAAA
  
EEEEEE..
  
  

  
  
  
框架从下到上的顺序是什么？The answer is EDABC.  
  
您的问题是，给定堆叠帧的图片，确定帧从下到上堆叠的顺序。以下是规则：  
  
1. 帧的宽度始终正好为1个字符，并且边的长度永远不小于3个字符。  
  
2. 可以看到一个框架的四个侧面的至少一个部分。一个角落显示出两面。  
  
3. 框架将使用大写字母书写，并且不会将两个框架指定为同一个字母。

Input

每个输入块包含第一行的高度h（h<=30）和第二行的宽度w（w<=30）。然后，堆叠帧的图片以h字符串的形式给出，每个字符串包含w个字符。 您的输入可能包含上述格式的多个块，中间没有任何空行。必须按顺序处理输入中的所有块。

Output

将解决方案写入标准输出。按照从下到上的顺序排列框架的字母。如果一个排序有多种可能性，请按字母顺序列出所有这些可能性，每一种都在单独的一行上。每个输入块始终至少有一个合法顺序。按顺序列出输入中所有块的输出，不带任何空行（甚至在块之间）。

Sample

|Inputcopy|Outputcopy|
|---|---|
|9<br>8<br>.CCC....<br>ECBCBB..<br>DCBCDB..<br>DCCC.B..<br>D.B.ABAA<br>D.BBBB.A<br>DDDDAD.A<br>E...AAAA<br>EEEEEE..|EDABC|


## 题解
我们这一题其实展现出了我们 1270 题的本质，我们这一题要求的是我们的覆盖问题，我们于是也可以按照我们 1270 题的想法去解决（但是，因为我们这一题**可能有很多的相框，所以我们不能靠枚举了**（悲））。
1. 对于每一个相框，我们可以遍历一遍找到它的上下左右四条边的位置，然后再搜索这几条边上是否有其他字母，有的话就添加一个类似于 $A<B$ 的关系。
2. 另外，因为我们这一题要输出字典序最小的一个，所以我们考虑用 dfs 来实现我们的拓扑排序。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <functional>
#include <vector>
#include <stack>
#include <set>
#include <bitset>
//#define int long long
using namespace std;
typedef long long ll;
const int maxn=2e5+50;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int HASH=131;

string s[40];
vector<int> v[30];
int degree[30]={0};
int vis[30]={0};
int h,w,n;
int cnt[30]={0};
void init()
{
    n=0;
    for(int i=0;i<=26;i++)
    {
        v[i].clear();
        degree[i]=0;
        vis[i]=0;
        cnt[i]=0;
    }
}

char ans[30];

void topsort(int tmp,int depth)
{
    ans[depth]=tmp+'A';

    if(depth==n-1)
    {
        cout<<ans<<endl;
        return;
    }
    cnt[tmp]++;
    for(int i=0;i<v[tmp].size();i++)
    {
        int t=v[tmp][i];
        --degree[t];
    }
    for(int i=0;i<26;i++)
        if(vis[i]&&degree[i]==0&&!cnt[i])
            topsort(i,depth+1);
    for(int i=0;i<v[tmp].size();i++)
    {
        int t=v[tmp][i];
        ++degree[t];
    }
    cnt[tmp]--;
}




int main()
{

    while(scanf("%d %d",&h,&w)!=EOF)
    {
        init();
        for(int i=0;i<h;i++)
            cin>>s[i];
        for(int num=0;num<26;num++)
        {
            char id=num+'A';
            int shang=100,xia=-1,zuo=100,you=-1;
            for(int i=0;i<h;i++)
            {
                for(int j=0;j<w;j++)
                {
                    if(s[i][j]==id)
                    {
                        shang=min(i,shang);
                        xia=max(i,xia);
                        zuo=min(j,zuo);
                        you=max(j,you);
                    }
                }
            }
            if(shang!=100) vis[num]=1;
            for(int i=zuo;i<=you;i++)
            {
                if(s[shang][i]!=id)
                {
                    int id1=id-'A';
                    int id2=s[shang][i]-'A';
                    v[id1].push_back(id2);
                    degree[id2]++;
                }
                if(s[xia][i]!=id)
                {
                    int id1=id-'A';
                    int id2=s[xia][i]-'A';
                    v[id1].push_back(id2);
                    degree[id2]++;
                }
            }
            for(int i=shang;i<=xia;i++)
            {
                if(s[i][zuo]!=id)
                {
                    int id1=id-'A';
                    int id2=s[i][zuo]-'A';
                    v[id1].push_back(id2);
                    degree[id2]++;
                }
                if(s[i][you]!=id)
                {
                    int id1=id-'A';
                    int id2=s[i][you]-'A';
                    v[id1].push_back(id2);
                    degree[id2]++;
                }
            }
        }//建图
        for(int i=0;i<26;i++)
            if(vis[i]) n++;
        ans[n]='\0';
        for(int i=0;i<26;i++)
        {
            if(vis[i]&&degree[i]==0)
            topsort(i,0);
        }
    }
    return 0;
}


```