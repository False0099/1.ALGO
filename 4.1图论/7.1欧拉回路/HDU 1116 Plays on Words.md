Some of the secret doors contain a very interesting word puzzle. The team of archaeologists has to solve it to open that doors. Because there is no other way to open the doors, the puzzle is very important for us.  
  
There is a large number of magnetic plates on every door. Every plate has one word written on it. The plates must be arranged into a sequence in such a way that every word begins with the same letter as the previous word ends. For example, the word ``acm'' can be followed by the word ``motorola''. Your task is to write a computer program that will read the list of words and determine whether it is possible to arrange all of the plates in a sequence (according to the given rule) and consequently to open the door.  

Input

The input consists of T test cases. The number of them (T) is given on the first line of the input file. Each test case begins with a line containing a single integer number Nthat indicates the number of plates (1 <= N <= 100000). Then exactly Nlines follow, each containing a single word. Each word contains at least two and at most 1000 lowercase characters, that means only letters 'a' through 'z' will appear in the word. The same word may appear several times in the list.  

Output

Your program has to determine whether it is possible to arrange all the plates in a sequence such that the first letter of each word is equal to the last letter of the previous word. All the plates from the list must be used, each exactly once. The words mentioned several times must be used that number of times.  
If there exists such an ordering of plates, your program should print the sentence "Ordering is possible.". Otherwise, output the sentence "The door cannot be opened.".  

Sample

|Inputcopy|Outputcopy|
|---|---|
|3<br>2<br>acm<br>ibm<br>3<br>acm<br>malform<br>mouse<br>2<br>ok<br>ok|The door cannot be opened.<br>Ordering is possible.<br>The door cannot be opened|


## 题解
我们本题与我们洛谷上那一道判断字符串是否能连接的题一毛一样，我们甚至还不用输出我们的欧拉路径，因为我们拿到的是一个有向图，所以我们要判断每一个点的入度和出度是不是相等的，如果是的话，那么我们认为不能构造出欧拉回路。否则，我们就可以构造出一个欧拉回路。

对于**欧拉路径**，我们需要判断是否有一个点的入度和初读和差为 1，且只有一个点的入度和出度差为 1. 如果满足上述条件，那么我们就有一条欧拉路径。

```cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;
const int maxn=100010;
int in[maxn]={0};//
int out[maxn]={0};//
int vis[30];//
int e[30][30]={0};
void dfs(int tar)
{
	vis[tar]=1;
	for(int i=0;i<26;i++)
	{
		if(e[tar][i]&&!vis[i])
		{
			dfs(i);
		}
	}
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		memset(vis,0,sizeof(vis));
		memset(e,0,sizeof(e));
		memset(in,0,sizeof(in));
		memset(out,0,sizeof(out));
		int n;
		cin>>n;
		for(int i=0;i<n;i++)
		{
			string t;
			cin>>t;
			int a=t[0]-'a';
			int b=t[t.size()-1]-'a';
			out[a]++;
			in[b]++;
			if(a!=b) e[a][b]=e[b][a]=1;
		}
		int flag=0;
		int s=-1,e=-1;
		for(int i=0;i<26;i++)
		{
			if(out[i]-in[i]==1)
			{
				if(s==-1)
				{
					s=i;
				}
				else
				{
					flag=1;
					break;
				}
			}
			if(in[i]-out[i]==1)
			{
				if(e==-1)
				{
					e=i;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		if(flag==1)
		{
			cout<<"The door cannot be opened."<<endl;
			continue;
		}
		if(s==-1&&s==e)
		{
			int flag=0;
			for(int i=0;i<26;i++)
			{
				if(in[i]!=0)
				{
					s=i;
					break;
				}
			}
			dfs(s);
			for(int i=0;i<26;i++) 
			{
				if(in[i]!=out[i])
				{
					flag=1; 
					break;
				}
				if(in[i]!=0||out[i]!=0)
				{
					if(vis[i]==0)
					{
						flag=1;
						break;
					}
				}
			}
			
			if(flag) cout<<"The door cannot be opened."<<endl;
			else cout<<"Ordering is possible."<<endl;
			continue;
		}
		if(s==-1)
		{
			for(int i=0;i<26;i++)
			{
				if(in[i]+out[i]==3)
				{
					s=i;
					break;
				}
			}
		}
		dfs(s);
		int counter=0;
		for(int i=0;i<26;i++)
		{
			if(in[i]==out[i]&&in[i]==0)
			{
				continue;
			}
			else
			{
				if(vis[i]!=1)
				{
					flag=1;
					break;
				}
				if(in[i]!=out[i]&&fabs(in[i]-out[i])!=1)
				{
					flag=1;
					break;
				}
			}
		}
		if(flag) cout<<"The door cannot be opened."<<endl;
		else cout<<"Ordering is possible."<<endl;
		
	}
	return 0;
}

```