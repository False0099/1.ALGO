Argestes has a lot of hobbies and likes solving query problems especially. One day Argestes came up with such a problem. You are given a sequence a consisting of N nonnegative integers, $a[1],a[2],...,a[n]$.Then there are M operation on the sequence.An operation can be one of the following:  
S X Y: you should set the value of $a[x]$ to y(in other words perform an assignment $a[x]=y$).  
Q L R D P: among $[L, R]$, L and R are the index of the sequence, how many numbers that the Dth digit of the numbers is P.  
Note: The 1st digit of a number is the least significant digit.

有一个长度为n个序列，有m个操作。每个操作如下：  
S X Y；表示$a[X]=y$  
Q L R D P:表示询问，下标在$[L,R]$范围内的数，有多少个数的第D位是P  
个位为第1位。  

Input

In the first line there is an integer T , indicates the number of test cases.  
For each case, the first line contains two numbers N and M.The second line contains N integers, separated by space: a[1],a[2],...,a[n]—initial value of array elements.  
Each of the next M lines begins with a character type.  
If type=S,there will be two integers more in the line: X,Y.  
If type=Q,there will be four integers more in the line: L R D P.  
  
[Technical Specification]  
1<=T<= 50  
1<=N, M<=100000  
0<=a[i]<=2^{31} - 1  
1<=X<=N  
0<=Y<=2^{31} - 1  
1<=L<=R<=N  
1<=D<=10  
0<=P<=9  
第一行一个整数T，表示测试数据组数。  
每组测试数据第一行两个整数N和M  
第二行为N个元素  
接下来为M个操作  

Output

For each operation Q, output a line contains the answer.  
对于每个操作，输出相应的结果。

Sample Input

1
5 7
10 11 12 13 14
Q 1 5 2 1
Q 1 5 1 0
Q 1 5 1 1
Q 1 5 3 0
Q 1 5 3 1
S 1 100
Q 1 5 3 1

Sample Output

5
1
1
5
0
1

## 题解
我们对于给定的所有，我们需要采用分块操作，

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;
#define maxn 100010
int a[maxn],belong[maxn],L[maxn],R[maxn],block[400][12][12],n,m;

//block[i][j][k]表示第i块中第j位上是k的数有多少个
int ten[11]={0,1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

void build(){
    int t=sqrt(n);
    int num=n/t;
    if(n%t)  num++;
    for(int i=1;i<=num;i++){
        L[i]=(i-1)*t+1;//每块的左右 
        R[i]=i*t;
    }
    R[num]=n;
    for(int i=1;i<=n;i++)
		belong[i]=(i-1)/t+1;//所属块 
    for(int i=1;i<=n;i++){
        int temp=a[i];
        for(int j=1;j<=10;j++){//位数最多有10位1<=D<=10
            block[belong[i]][j][temp%10]++;//块，位，位上的数 
            temp/=10;
        }
    }
}

int query(int l,int r,int d,int p){
    int ans=0;
    if(belong[l]==belong[r]){//属于同一块
        for(int i=l;i<=r;i++)//暴力统计 
            if((a[i]/ten[d])%10==p)
				ans++;
        return ans;
    }
    for(int i=belong[l]+1;i<belong[r];i++)//累加中间块 
		ans+=block[i][d][p];
    for(int i=l;i<=R[belong[l]];i++){//左端暴力累加 
        if((a[i]/ten[d])%10==p)
			ans++;
    }
    for(int i=L[belong[r]];i<=r;i++){//右端暴力累加
        if((a[i]/ten[d])%10==p)
			ans++;
    }
    return ans;
}

void update(int x,int y){
    for(int i=1;i<=10;i++){//原来的统计数减少 
        block[belong[x]][i][a[x]%10]--;
        a[x]/=10;
    }
    a[x]=y;
    for(int i=1;i<=10;i++){//新的统计数增加 
        block[belong[x]][i][y%10]++;
        y/=10;
    }
}

int main(){
	
    int T;
    scanf("%d",&T);
    while(T--){
        memset(block,0,sizeof(block));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
        build();//划分块 
        char s[5];
        while(m--){
            scanf("%s",s);
            if(s[0]=='S'){
                int x,y;
                scanf("%d%d",&x,&y);
                update(x,y);
            }
            else{
                int l,r,d,p;
                scanf("%d%d%d%d",&l,&r,&d,&p);
                printf("%d\n",query(l,r,d,p));
            }
        }
    }
	
    return 0;
}


```