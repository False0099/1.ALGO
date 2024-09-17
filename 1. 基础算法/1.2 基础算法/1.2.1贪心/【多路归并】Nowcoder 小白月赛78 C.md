
## 题目描述

“O.o?”

  

集合中一开始拥有两个数字 aaa 和 bbb，如果 aaa 与 bbb 相同，那么仅有一个数字。

小沙每次可以选择集合中的两个数（可以相同）,将他们的和放入集合中，请问所有可能的集合中，第 K 小的值最小为多少？  
  
注：集合中相同元素只能有一个。

## 输入描述:

第一行，输入三个整数 k，a，b 。

  

保证有 $1 \le k \le 10^6$

## 输出描述:

输出一个数字代表答案。

示例1

## 输入

 3 2 3



## 输出

 4

## 题解
首先，本题**不能够采用我们的康托展开法，因为我们集合中的元素是未知的**，

我们本题的正解是因该直接用我们的优先队列来模拟我们的所有操作。每一次取出堆中最小的数，把它和我们的 a，b 加和的结果放入到我们的答案当中。最后当我们出现了 k 个**本质不同**的数时，我们就输出我们的结果。因此，我们还需要有一个 set 来帮助我们判重。

```cpp
#include <bits/stdc++.h>
using namespace std;
set<int> s;
typedef long long ll;
int main(){
    int a,b,k;
    cin>>k>>a>>b;
    priority_queue<ll,vector<ll>,greater<ll>> heap;
    heap.push(a);
    heap.push(b);
    int cnt=0;
    ll last=-1;
    while(heap.size()){
        if(s.count(heap.top())){
            heap.pop();
            continue;
        }else{
            s.insert(heap.top());
            ll u=heap.top();
            last=u;
            cnt++;
            heap.push((1ll)*(u+a));
            heap.push((1ll)*(u+b));
            heap.pop();
        }
        if(cnt==k){
            break;
        }   
    }
    cout<<last<<endl;
}
```