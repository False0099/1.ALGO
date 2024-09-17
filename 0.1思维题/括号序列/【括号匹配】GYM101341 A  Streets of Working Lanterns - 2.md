## 题意：
给定你 n 个括号序列，问你这 n 个括号序列能否拼接成一个完整的括号序列。

Policeman Anatoliy again monitors a lair of unorganized criminal group spreading prohibited Asian drawings. Presently the criminals are also sharing wireless Internet which can be used anonymously by whoever wants to. The lair still has only one entrance, which is also an exit. When someone enters into the lair, Anatoliy writes an opening round bracket in his notepad, and when someone comes out, he writes a closing round bracket.

Anatoliy decided to refrain from eating donuts in order not to spoil the records just like the previous time, but nevertheless, when he tore a sheet out of a notepad to file it to a criminal case, accidentally tore it into pieces. He doesn't want his boss to shout on him, so he must restore his records by connecting pieces in the right order. It's good for him that the layout of notepad sheets allows to determine where top and bottom sides of these pieces are. Anatoliy ensured that the lair of criminals was empty before he started the surveillance and after he ended it.

### Input

The first line contains a single integer _n_ ($1 ≤ n ≤ 2·10^5$) — the number of pieces of paper with opening and closing round brackets written on them.

The next _n_ lines contain only characters «(» and «)» — these are the strings written on pieces. The total number of brackets does not exc

## 题解
本题我们考虑**贪心**，我们首先，需要对我们的原来的括号序列进行处理，我们首先有：我们的原括号序列内的已经配对的括号序列对我们的答案没有影响，可以删除，这个时候，我们就的字符串就都形如：`)*n(*t`，于是，这个时候，我们考虑怎么对上述的元素匹配。

**首先，我们需要以左括号开头，以右括号结尾**，所以，我们需要**首先按照左右括号**来进行潘旭，然后，我们可以将我们的原先的字符串先按照我们的最终的差值排序，按照我们的差值进行升序排序，差值相同的情况下，我们优先让我们的右括号在我们的同一侧即可。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
const int N=200005;
struct pos
{
	int l,r;
	int p;
}a[N],b[N];
//必须保证我们的起始位置为(,结尾位置为),然后再去根据我们的dx去贪心，如果按dx贪心
//可能会出现没法开头的情况：形如：)))((((((((,(((,)))))),就是先放左括号，再放其他的 
//因此，我们需要去先判断我们是否存在右括号 
bool cmp(pos a,pos b)
{
	if(a.r==0&&b.r==0)return a.l>b.l;//都没有右括号，优先安置左括号多的 
	if(a.r>0&&b.r>0) //都有右括号 
	{
		if(a.l>a.r&&b.l>b.r)
			return a.r<b.r;//如果我们都是左括号比右括号多 ，把右括号少的先放
		//如果我们的一个是左括号比右括号整体要多，先放着一个
		if(a.l>a.r)return 1;
		if(b.l>b.r)return 0; 
		return a.l>b.l;//这俩都是右括号多 谁左括号多先放谁
	}
	if(a.r==0)return 1;//否则谁有右括号先安排谁 
	return 0;//否则谁有右括号先安排谁 
}
string s[N];
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		int len=s[i].length();
		int now=0,ret=0x3f3f3f3f;
		for(int j=0;j<len;j++)
		{
			if(s[i][j]=='(')a[i].l++;
			else
			{
				if(a[i].l>0)a[i].l--;//统计有效的最终左括号数 
				else a[i].r++;//统计有效的右括号数 
			}
		}
		//cout<<a[i].l<<" "<<a[i].r<<endl;
		a[i].p=i;
	}
	sort(a+1,a+n+1,cmp);
//	for(int i=1;i<=c1;i++)cout<<a[i].m<<" "<<a[i].now<<endl;
//	for(int i=1;i<=c2;i++)cout<<b[i].m<<" "<<b[i].now<<endl;
	int ans=0;
	for(int i=1;i<=n;i++){
		cout<<a[i].l<<" "<<a[i].r<<" ";
		printf("%d ",a[i].p);
		puts("");
	}
	for(int i=1;i<=n;i++)
	{
		int len=s[a[i].p].length();
		for(int j=0;j<len;j++)
		{
			if(s[a[i].p][j]=='(')ans++;
			else ans--;
			if(ans<0)
			{
				puts("NO");
				return 0;
			}
		}
	}
	if(ans!=0){puts("NO");return 0;}
	puts("YES");
	for(int i=1;i<=n;i++){
		cout<<a[i].l<<" "<<a[i].r<<endl;
		printf("%d ",a[i].p);
	}
		
	return 0;
}
```