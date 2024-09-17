> $\sf I'm\ making\ more,\ just\ a\ little\ bit$
> 
>   
> 
> $\sf Spend\ a\ little\ more\ to\ get\ rid\ of\ it$  
> 
>   
> 
> $\sf Smile\ a\ little\ more\ and\ I'm\ into\ it$
> 
>   
> 
>        —— $Sunshine,\ \text{OneRepublic}$

有 $n$ 个男生和 $m$ 个女生聚在一起。$1$ 个男生代表 $1$ 块钱，$1$ 个女生代表 $2$ 块钱。

  
此时，_氧气少年_喊出一个数字 $k$，这个时候男生和女生需要尽快完成抱团，男生和女生们可以抱成多个团，但每个人最多处于一个抱团内，并且每个抱团的总钱数恰好为 $k$。而落单的人需要表演一个节目。  
  

例如，如果_氧气少年_喊出了数字 $5$，那么抱团可以是下面的形式：

-   $5$ 个男生
-   $1$ 个女生和 $3$ 个男生
-   $2$ 个女生和 $1$ 个男生

  
阅读样例解释可以帮助理解上述过程。  
  
你当然不希望更多的人落单，请你安排一种抱团方式，以最小化落单人数。  
  
请求出最小的落单人数。

## 输入描述

第一行包含一个整数 $T(1\leq T\leq 2\cdot 10^5)$，表示测试用例的组数。  
  
对于每组测试用例：  
  
仅输入一行，包含三个整数 $n(1\leq n\leq 10^9),m(1\leq m\leq 10^9),k(1\leq k\leq 10^9)$。

## 输出描述
对于每组测试用例：  
仅输出一行，包含一个整数，表示答案。


## 题解
我们这一题的思路就是二分，我们考虑二分我们抱团的数量，当我们的抱团数量最多时，我们落单的人数最少，关于我们抱团怎么计算，我们就优先考虑把女生放进去，然后再把我们的男生放进去。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        long long n,m,k;
        cin>>n>>m>>k;
        if(k==1) cout<<m<<endl;
        else if(k%2==0){
            long long gp=(n+2*m)%k;
            long long x=min(m,gp/2);//x统计我们分组中有多少个2
            cout<<gp-x<<endl;
        }
        else {
            long long num=min(n,(n+2*m)/k);//统计我们的可能的组数？
            long long gp=n+2*m-num*k,x=min(m,gp/2);
            //gp-2x就是我们1的升序个数
            //x是我们剩余的2的个数
            cout<<x+gp-2*x<<endl;
        }
    }
    return 0;
}
```


```
#include<bits/stdc++.h>
using namespace std;
int n,a[200005];
void solve()
{
	int n,m,k;
	cin>>n>>m>>k;
	if(k==1)
	{
		cout<<m<<endl;
		return;
	}
	if(k%2==0)
	{
		int left = (n + 2ll * m) % k, ret = 0;
		if(left % 2) {
			ret ++;
			left --;
		}
		ret += min(left / 2, m) + max(0, left - 2 * m);//表示剩下的最大的人，
		cout<<ret<<endl;
	}
	else
	{
		int x = min(n, int((n + 2ll * m) / k));
		int left = (n + 2ll * m) - x * k;
		n -= x;
		int ret = 0;
		if(left % 2) {
			ret ++;
			left --;
		}
		ret += min(left / 2, m) + max(0, left - 2 * m);
		cout<<ret<<endl;
	}
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
		solve();
}
```