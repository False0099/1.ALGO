Problem Description

Yellowstar is writing an article that contains N words and 1 picture, and the i-th word contains ai characters.  
The page width is fixed to W characters. In order to make the article look more beautiful, Yellowstar has made some rules:  
  
1. The fixed width of the picture is pw. The distance from the left side of the page to the left side of the photo fixed to dw, in other words, the left margin is dw, and the right margin is W - pw - dw.  
2. The photo and words can't overlap, but can exist in same line.  
3. The relative order of words cannot be changed.  
4. Individual words need to be placed in a line.  
5. If two words are placed in a continuous position on the same line, then there is a space between them.  
6. Minimize the number of rows occupied by the article according to the location and height of the image.  
  
However, Yellowstar has not yet determined the location of the picture and the height of the picture, he would like to try Q different locations and different heights to get the best look. Yellowstar tries too many times, he wants to quickly know the number of rows each time, so he asked for your help. It should be noted that when a row contains characters or pictures, the line was considered to be occupied.  

![](http://acm.hdu.edu.cn/data/images/C764-1012-1.jpg)

  

Input

The first line of the input gives the number of test cases T; T test cases follow.  
Each case begins with one line with four integers N, W, pw, dw : the number of words, page width, picture width and left margin.  
The next line contains N integers ai, indicates i-th word consists of ai characters.  
The third line contains one integer Q.  
Then Q lines follow, each line contains the values of xi and hi, indicates the starting line and the image height of the image.  
  
Limits  
T≤10  
1≤N,W,Q≤105  
1≤pw,ai≤W  
0≤dw≤W−pw

  

Output

For each query, output one integer denotes the minimum number of rows.  

  

Sample Input

2
2 7 4 3
1 3
3
1 2
2 2
5 2
3 8 2 3
1 1 3
1
1 1

  

Sample Output

2
3
3
1

## 题解

```cpp
#include<bits/stdc++.h>
using namespace std;
const int  MAXN=200005;
int T;
int n,w,pw,lw;//单词数，页面宽度，图片宽度，页左边距
int a[MAXN];
int Q;//查询次数
int xi,hi;
int mx;
int f1[MAXN][30];//f1[i][j]表示从第i个单词开头，占据2^j行能放置的最大单词数
int f2[MAXN][30];//f1[i][j]表示有图片的情况下从第i个单词开头，占据2^j行能放置的最大单词数
void Init_ST()
{
    memset(f1,0,sizeof(f1));
    memset(f2,0,sizeof(f2))
    a[n+1]=w+1;//在最后添加一个虚拟的单词长度超过页面宽度
    for(int i=1;i<=n;i++)//求出f1[i][1]
    {
        int tw=a[i];//宽度
        int j=i+1;
        while(tw+a[j]+1<=w){tw+=a[j]+1;j++;}
        f1[i][0]=j-i;
    }
    for(int k=1;(1<<k)<=mx;k++)
    {
        for(int i=1;i<=n;i++)
        {
            int t=f1[i][k-1];
            f1[i][k]=t+f1[i+t][k-1];
        }
    }
    for(int i=1;i<=n;i++)
    {
        int j=i;
        int tw=0;
        if(tw+a[j]<=lw){tw+=a[j];j++;}
        while(tw+a[j]+1<=lw) {tw+=a[j]+1;j++;}
        tw=0;
        int rw=w-pw-lw;
        if(tw+a[j]<=rw){tw+=a[j];j++;}
        while(tw+a[j]+1<=rw){ tw+=a[j]=1;j++;}
        f2[i][0]=j-i;
    }
    for(int k=1;(1<<k)<=mx;k++)
    {
        for(int i=1;i<=n;i++)
        {
            int t=f2[i][k-1];
            f2[i][k]=t+f2[i+t][k-1];
        }
    }
}
int RMQ1(int i,int x)//不含图片，以i开头长度为x的段落之后的单词标号
{
    if(x==0)return i;
    while(x!=0 && i<=n)
    {
         int j=0;
         while((1<<(j+1))<=x)j++;
         i+=f1[i][j];
         x-=(1<<j);
    }
    return i;
}
int RMQ2(int i,int x)//含图片，以i开头长度为x的段落之后的单词标号
{
    if(x==0)return i;
    while(x!=0 && i<=n)
    {
         int j=0;
         while((1<<(j+1))<=x)j++;
         i+=f2[i][j];
         x-=(1<<j);
    }
    return i;
}
int RMQ3(int i)//不含图片，以i开头到末尾的行数
{
    int ans=0;
    while(i<=n)
    {
        int j=0;
        while(i+f1[i][j+1]<=n)j++;
        i+=f1[i][j];
        ans+=(1<<j);
    }
    return ans;
}
int  Work(int x,int h)
{
    int temp=RMQ3(1);
    if(temp<=x-1)return temp+h;
    int ans=x+h-1;
    int i=0;
    i=RMQ1(1,x-1);
    i=RMQ2(i,h);
    if(i<=n)ans+=RMQ3(i);
    return ans;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        mx=1000000;//设置一个最大的长度
        scanf("%d%d%d%d",&n,&w,&pw,&lw);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        Init_ST();
        scanf("%d",&Q);
        for(int i=1;i<=Q;i++)
        {
            scanf("%d%d",&xi,&hi);
            printf("%d\n",Work(xi,hi));
        }
    }
}

```