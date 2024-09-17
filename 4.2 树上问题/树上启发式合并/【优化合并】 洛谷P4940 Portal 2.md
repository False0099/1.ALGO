# Portal 2

## 题目背景

某地 `ENLIGHTENED` 的 `XM` 研究所正在研究 `Portal` 的处理法则，想要揭示 `XM能量` 的来源以及应用 `XM能量`。`ENLIGHTENED` 的首席科学家 `Jacks` 发现其能量的运算法则以及运算方法，但是方法十分复杂，仅靠人手工计算是很难算出答案的，所以它需要你协助他完成计算。

## 题目描述

`Portal` 计算 `XM能量` 是通过个 $2$ 个栈（$0$ 号栈，$1$ 号栈）实现的，它把对 `XM` 能量的操作如下

$PUSH$ $X$ $NUM$

把 $NUM$ 加入到 X 号栈的栈顶。 

$POP$ $X$

把 $X$ 号栈的栈顶元素**删除**。

$ADD$ $X$

**取出**$0$ 号栈和 $1$ 号栈的元素各一个，并且把它的和放入 $X$ 号栈。

$SUB$ $X$

**取出**$0$ 号栈和 $1$ 号栈的元素各一个，并且把它的差的绝对值放入 $X$ 号栈。
 
$DEL$ $X$

**清空**$X$ 号栈中所有元素不管栈是否为空。 

$MOVE$ $X$ $Y$ 

循环操直到 $Y$ 号栈为空，把 $Y$ 号栈的栈顶元素加入到 $X$ 号栈，删除 $Y$ 号栈的栈顶元素。 

**数据保证 X 和 Y 不相同**

$SWAP$

将两个栈的所有元素调换。

$END$

代表命令结束，并且分两行分别输出 0 号栈和 1 号栈由栈顶到栈底的元素的值，若栈内无元素，输出 `NONE`。数据保证指令以 `END` 结束且仅有一个 `END`，并且也需要输出 `SUCCESS`。

~~$AKNOI$~~

~~等为无效操作，**无效操作后不接数字**。~~

**更正不会有类似无效操作**

对于每一行指令，若当前指令成功执行输出 `SUCCESS`，若**取出**或**删除**元素时栈内为空或者没有对应指令输出 `UNSUCCESS` 并且不执行该行指令。

## 输入格式

输入若干行指令，以 `END` 指令结束

## 输出格式

对于每一次操作，都要对应输出 `SUCCESS` 或者 `UNSUCCESS`，对于 `END` 根据指令描述输出栈内元素。

## 样例 #1

### 样例输入 #1

```
PUSH 0 10
PUSH 0 20
PUSH 0 30
PUSH 0 40
PUSH 1 50
PUSH 1 60
ADD 0
ADD 0
ADD 0
END
```

### 样例输出 #1

```
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
UNSUCCESS
SUCCESS
150 30 20 10
NONE
```

## 样例 #2

### 样例输入 #2

```
PUSH 0 10
PUSH 0 20
PUSH 0 30
PUSH 0 40
PUSH 1 50
PUSH 1 60
MOVE 0 1
END
```

### 样例输出 #2

```
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
50 60 40 30 20 10
NONE
```

## 提示

对于 $20\%$ 的数据数据保证不会出现 `MOVE/SWAP` 操作，$命令总数 \leq 100$

对于 $40\%$ 的数据 $命令总数 \leq 1000$

对于 $60\%$ 的数据数据保证 `MOVE/SWAP` 的操作次数不会超过 $10000$ 次，$命令总数 \leq 10^5$

对于 $100\%$ 的数据 $0 \leq X,Y \leq 1,命令总数 \leq 10^6$ 

**数据保证无论任何情况，栈中元素的值 $X$ 满足 $0 \leq x \leq 2^{63}-1​$**

[题目创意来源OIERBBS](https://www.oierbbs.cn)

## 翻译：
给你两个栈，以及下面的 Q 种操作，每一次需要进行下面的一个操作：
操作 1：把一个数加入到某个栈顶
操作 2：删除栈顶
操作 3：取出栈顶，相加放到另一个
操作 4：取出栈顶，相减放到另一个
操作 5：清空
操作 6：循环把元素移动到另一个栈。

## 题解
我们发现，对于本题来说，我们的瓶颈在于我们的操作 6，我们操作 6 的时间复杂度最坏能来到我们的 $o(n^2)$,
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	stack<int> stk[2];
	//stk[0].clear(),stk[1].clear();
	while(true){
		string op;
		cin>>op;
		if(op=="END"){
			cout<<"SUCCESS"<<endl;
			if(stk[0].size()!=0){
				while(stk[0].size()){
					cout<<stk[0].top()<<" ";
					stk[0].pop();
				}
				puts("");
			}else{
				cout<<"NONE"<<endl;
			}
			if(stk[1].size()!=0){
				while(stk[1].size()){
					cout<<stk[1].top()<<" ";
					stk[1].pop();
				}
				puts("");
			}else{
				cout<<"NONE"<<endl;
			}
			break;
		}
		if(op=="PUSH"){
			int x,num;
			cin>>x>>num;
			stk[x].push(num);
			cout<<"SUCCESS"<<endl;
		}
		if(op=="POP"){
			int x;
			cin>>x;
			if(stk[x].size()==0){
				cout<<"UNSUCCESS"<<endl;
				continue;
			}else{
				cout<<"SUCCESS"<<endl;
				stk[x].pop();
			}
			
		}
		if(op=="ADD"){
			int x;
			cin>>x;
			if(stk[0].size()==0||stk[1].size()==0){
				cout<<"UNSUCCESS"<<endl;
				continue;
			}
			cout<<"SUCCESS"<<endl;
			int a=stk[0].top();
			stk[0].pop();
			int b=stk[1].top();
			stk[1].pop();
			stk[x].push(a+b);
		}
		if(op=="SUB"){
			int x;
			cin>>x;
			if(stk[0].size()==0||stk[1].size()==0){
				cout<<"UNSUCCESS"<<endl;
				continue;
			}
			cout<<"SUCCESS"<<endl;
			int a=stk[0].top();
			stk[0].pop();
			int b=stk[1].top();
			stk[1].pop();
			stk[x].push(abs(a-b));
		}
		if(op=="DEL"){
			int x;
			cin>>x;
			stack<int> clear_stack;
			stk[x]=clear_stack;
			cout<<"SUCCESS"<<endl;
		}
		if(op=="SWAP"){
			cout<<"SUCCESS"<<endl;
			swap(stk[0],stk[1]);
		}
		if(op=="MOVE"){
			int x;
			int y;
			cin>>x>>y;
			cout<<"SUCCESS"<<endl;
			if(stk[x].size()<stk[y].size()){
				
			}else{
				
			}
			while(stk[y].size()){
				stk[x].push(stk[y].top());
				stk[y].pop();
			}
		}
	}
}
```

于是我们需要我们的优化。首先，我们考虑启发式合并，启发式合并能把我们合并两个栈的操作的复杂度降低到 $o(n\log n)$,可以满足题目的要求。

而本题中，我们的启发式合并需要我们翻转我们的两个序列，而如果我们采用我们的启发式合并，那么我们就可能会出现的问题是：我们交换两个之后，我们的顺序也变了，这下该怎么办捏？

我们不妨逆向思维，如果我们原本是要从 $Y\to x$,当 $Y$ 栈大于 $X$ 栈我们借助 $Tag_0$ 和 $Tag_1$ 表示这个队列是否反转，即队头变队尾，队尾变队头，初始化都为零，表示没有反转我们将 $X$ 栈里的元素按照出栈顺序一一移动到 $Y$ 栈,然后再将 $Tag_YXOR$ 1, 因为两次反转则等于没有反转,最后 $SWAP(f_x,f_y)$

为什么这样是对的，因为将 $Y$ 栈移动到 $X$ 栈正好是将 $X$ 栈移动到 $Y$ 栈的反转序列，自己画个图就知道了

如果我们的 y 是更大的，我们就直接暴力操作即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
deque<ll>q[2];
int f[2]={0,1};
int tag[2]={0,0};
int main()
{
    char k[10];int x,y;ll X,Y;
    while(true){
        scanf("%s",k);
        if(k[0]=='P'&&k[1]=='O'){
            scanf("%d",&x);
            if(!q[f[x]].size()){
                puts("UNSUCCESS");
            }
            else{
                puts("SUCCESS");
                if(tag[f[x]]){
                    q[f[x]].pop_front();
                }
                else q[f[x]].pop_back();
            }
        }
        else if(k[0]=='P'&&k[1]=='U'){
            scanf("%d%lld",&x,&Y);
            puts("SUCCESS");
            if(tag[f[x]]){
                q[f[x]].push_front(Y);
            }
            else q[f[x]].push_back(Y);
        }
        else if(k[0]=='A'&&k[1]=='D'){
            scanf("%d",&x);
            if(!q[0].size()||!q[1].size()){
                puts("UNSUCCESS");
            }
            else{
                puts("SUCCESS");
                ll a,b;
                if(tag[0])a=q[0].front(),q[0].pop_front();
                else a=q[0].back(),q[0].pop_back();
                if(tag[1])b=q[1].front(),q[1].pop_front();
                else b=q[1].back(),q[1].pop_back();
                if(tag[f[x]]){
                    q[f[x]].push_front(a+b);
                }
                else{
                    q[f[x]].push_back(a+b);
                }
            }
        }
        else if(k[0]=='S'&&k[1]=='U'){
            scanf("%d",&x);
            if(!q[0].size()||!q[1].size()){
                puts("UNSUCCESS");
            }
            else{
                puts("SUCCESS");
                ll a,b;
                if(tag[0])a=q[0].front(),q[0].pop_front();
                else a=q[0].back(),q[0].pop_back();
                if(tag[1])b=q[1].front(),q[1].pop_front();
                else b=q[1].back(),q[1].pop_back();
                if(tag[f[x]]){
                    q[f[x]].push_front(abs(a-b));
                }
                else{
                    q[f[x]].push_back(abs(a-b));
                }
            }
        }
        else if(k[0]=='D'&&k[1]=='E'){
            scanf("%d",&x);
            puts("SUCCESS");
            tag[f[x]]=0;
            while(q[f[x]].size())q[f[x]].pop_back();
        }
        else if(k[0]=='M'&&k[1]=='O'){
            scanf("%d%d",&x,&y);
            puts("SUCCESS");
            if(q[f[x]].size()<q[f[y]].size()){
                while(q[f[x]].size()){
                    ll a;
                    if(tag[f[x]])a=q[f[x]].front(),q[f[x]].pop_front();
                    else a=q[f[x]].back(),q[f[x]].pop_back();
                    if(tag[f[y]])q[f[y]].push_front(a);
                    else q[f[y]].push_back(a);
                }
                tag[f[y]]^=1;
                swap(f[0],f[1]);
            }
            else{
                while(q[f[y]].size()){
                    ll a;
                    if(tag[f[y]])a=q[f[y]].front(),q[f[y]].pop_front();
                    else a=q[f[y]].back(),q[f[y]].pop_back();
                    if(tag[f[x]])q[f[x]].push_front(a);
                    else q[f[x]].push_back(a);
                }
            }
        }
        else if(k[0]=='S'&&k[1]=='W'){
            swap(f[0],f[1]);puts("SUCCESS");
        }
        else if(k[0]=='E'&&k[1]=='N'){
        	puts("SUCCESS");
            if(!q[f[0]].size())puts("NONE");
            else {
                if(tag[f[0]]){
                    while(q[f[0]].size())
                      printf("%lld ",q[f[0]].front()),q[f[0]].pop_front();
                }
                else{
                    while(q[f[0]].size())
                      printf("%lld ",q[f[0]].back()),q[f[0]].pop_back();
                }
                puts("");
            }
            if(!q[f[1]].size())puts("NONE");
            else {
                if(tag[f[1]]){
                    while(q[f[1]].size())
                      printf("%lld ",q[f[1]].front()),q[f[1]].pop_front();
                }
                else{
                    while(q[f[1]].size())
                      printf("%lld ",q[f[1]].back()),q[f[1]].pop_back();
                }
                puts("");
            }
            break;
        }
    }
    return 0;
}
```