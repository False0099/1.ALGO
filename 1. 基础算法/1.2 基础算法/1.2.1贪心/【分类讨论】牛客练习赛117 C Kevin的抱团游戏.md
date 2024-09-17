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

  
此时，氧气少年喊出一个数字 $k$，这个时候男生和女生需要尽快完成抱团，男生和女生们可以抱成多个团，但每个人最多处于一个抱团内，并且每个抱团的总钱数恰好为 $k$。而落单的人需要表演一个节目。  
  

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
我们直接求解我们的落单人数不方便，但我们可以计算出我们的**落单价值**，这个是相对来说简单的。然后我们就可以根据我们的落单价值，贪心的求出我们最少的落单人数是多少。
而要求出我们的落单价值，我们可以通过计算出我们的**抱团价值**是多少，而我们要求出我们的抱团价值是多少，我们就需要计算出我们的**抱团组数**是多少，但是我们要注意一个点，就是我们的可能构成的组数需要我们进行我们的**分类讨论**，
如果我们的价值是我们的偶数，那么我们就一定可以达到我们的理论最大值（总价值/k）。
如果我们的价值是我们的奇数，那么我们还需要判断，我们的男生的个数是否够，如果**男生的数量不够的话，那么我们的实际组数就是我们的男生数量**。

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
        //k%2==0时，我们一定可以达到我们的理论最大组数
        else if(k%2==0){
            long long gp=(n+2*m)%k;
            long long x=min(m,gp/2);//计算我们能用多少个女生落单，我们优先让女生落单
            cout<<gp-x<<endl;
        }
        //k%2！=0时，我们实际组数是我们的理论组数以及我们的男生数的一个最小值（因为要凑1）
        else {
            long long num=min(n,(n+2*m)/k);//统计我们的可能的组数？
            long long gp=n+2*m-num*k,x=min(m,gp/2);//我们优先让女生落单
            cout<<gp-x<<endl;
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