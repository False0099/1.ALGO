# 知识点
  ## [[推公式]]
# 题目
 
  
  
        答案是诺艾尔，因为**赛|诺—艾尔|海森**。  
  
        是不是非常有趣？（感觉不用开空调了呢）须弥的**大风纪官**赛诺最喜欢冷笑话了，他觉得蒙德城里的大型风车非常亲切，因为风车也是一种**「大风机关 」**。  
  
        世界名画——《大风机关》（赛诺）（图片加载失败）  
  
        小沙觉得这场比赛太简单了，所以想加一个画图题毒瘤一下参赛选手，嘤嘤拦不住他，所以只能让大家画一画风车了。(冤有头，债有主)  
  
![[Pasted image 20230414220332.png]]

 ``如图，第一个风车如 n=1 所示，由四个等腰直角三角形组成，n>1 时，第 n 个风车将在第 n−1 个风车的基础上，增加四个底和高都大一倍的等腰直角三角形。

# 思路
·纯粹的麻烦的不要害怕的找规律的。
·恶心的，放弃的
·从每一行从上往下依次推导即可
# AC 代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
const int N = 5005;
char mp[N][N];
int len[] = {0, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097};
void draw(int d, int cnt)
{
	
//	cout << d << endl;
//    for(int i=0; i<d; i++) mp[i][d/2] = '*';
//    for(int i=0; i<d; i++) mp[d/2][i] = '*';
    int x = d/2, y = d/2;
    int k = pow(2, cnt);
    if(cnt&1)
    {
        for(int i=0; i<k; i++) mp[-- x][++ y] = '*';
        for(int i=0; i<k; i++) mp[-- x][-- y] = '*';
        x = d/2, y = d/2;
        for(int i=0; i<k; i++) mp[++ x][-- y] = '*';
        for(int i=0; i<k; i++) mp[++ x][++ y] = '*';
        x = d/2, y = d/2;
        for(int i=0; i<k; i++) mp[-- x][-- y] = '*';
        for(int i=0; i<k; i++) mp[++ x][-- y] = '*';
        x = d/2, y = d/2;
        for(int i=0; i<k; i++) mp[++ x][++ y] = '*';
        for(int i=0; i<k; i++) mp[-- x][++ y] = '*';
    }
    else
    {
        for(int i=0; i<k; i++) mp[-- x][-- y] = '*';
        for(int i=0; i<k; i++) mp[-- x][++ y] = '*';
        x = d/2, y = d/2;
        for(int i=0; i<k; i++) mp[++ x][++ y] = '*';
        for(int i=0; i<k; i++) mp[++ x][-- y] = '*';
        x = d/2, y = d/2;
        for(int i=0; i<k; i++) mp[++ x][-- y] = '*';
        for(int i=0; i<k; i++) mp[-- x][-- y] = '*';
        x = d/2, y = d/2;
        for(int i=0; i<k; i++) mp[-- x][++ y] = '*';
        for(int i=0; i<k; i++) mp[++ x][++ y] = '*';
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, d = 9;
    cin >> n;
    
    for(int i=0; i<len[n]; i++)
    	for(int j=0; j<len[n]; j++)
    		mp[i][j] = ' '; 
    for(int i=0; i<len[n]; i++) mp[i][len[n]/2] = '*';
    for(int i=0; i<len[n]; i++) mp[len[n]/2][i] = '*';
    for(int i=1; i<=n; i++)
    {
//     	cout << d << endl;
        draw(len[n], i);
//        d = d * 2 - 1;
    }
    for(int i=0; i<len[n]; i++) cout << mp[i] << endl;
    return 0;
}
```
# 备注






 