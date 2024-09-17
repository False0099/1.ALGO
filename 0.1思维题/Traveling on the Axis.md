BaoBao is taking a walk in the interval [0, n] on the number [axis](https://so.csdn.net/so/search?q=axis&spm=1001.2101.3001.7020), but he is not free to move, as at every point (i-0.5) for all i ∈ [1, n], where i is an integer, stands a traffic light of type ti (ti ∈{ 0, 1} ).  
BaoBao decides to begin his walk from point p and end his walk at point q (both p and q are integers,and p < q). During each unit of time, the following events will happen in order:

1. Let’s say BaoBao is currently at point x, he will then check the traffic light at point (x + 0.5). If the traffic light is green, BaoBao will move to point (x + 1); If the traffic light is red, BaoBao will remain at point x.
2. All the traffic lights change their colors. If a traffic light is currently red, it will change to green; If a traffic light is currently green, it will change to red.  
    A traffic light of type 0 is initially red, and a traffic light of type 1 is initially green.  
    Denote t(p, q) as the total units of time BaoBao needs to move from point p to point q. For some reason,BaoBao wants you to help him calculate  
    ![在这里插入图片描述](https://img-blog.csdnimg.cn/20190507201802647.png)  
    where both p and q are integers. Can you help him?

## 输入  
There are multiple test cases. The first line of the input contains an integer T, indicating the number of test cases. For each test case:  
The first and only line contains a string s (1≤|s|≤105, |s| = n, si ∈{‘0’, ‘1’} for all 1≤i≤|s| ),indicating the types of the traffic lights. If si = ‘0’, the traffic light at point (i-0.5) is of type 0 and is initially red; If si = ‘1’, the traffic light at point (i≤0.5) is of type 1 and is initially green.  
It’s guaranteed that the sum of |s| of all test cases will not exceed 106.

## 输出  
For each test case output one line containing one integer, indicating the answer.

## 样例输入  
3  
101  
011  
11010  
## 样例输出  
12  
15  
43

## 提示  
For the first sample test case, it’s easy to calculate that t(0, 1) = 1, t(0, 2) = 2, t(0, 3) = 3, t(1, 2) = 2,  
t(1, 3) = 3 and t(2, 3) = 1, so the answer is 1 + 2 + 3 + 2 + 3 + 1 = 12.  
For the second sample test case, it’s easy to calculate that t(0, 1) = 2, t(0, 2) = 3, t(0, 3) = 5, t(1, 2) = 1,  
t(1, 3) = 3 and t(2, 3) = 1, so the answer is 2 + 3 + 5 + 1 + 3 + 1 = 15.


## 题解
**怎么一股 CF 味**
我们将贡献分为两部分，一部分是假设完全都是顺风，我们这一块对于我们答案的贡献。这一部分我们可以通过公式来简单的计算出来，另外一个部分是**由于红绿灯造成的额外等待时间**，这一部分可以等价于计算这一个灯在所有 $t(p,q)$ 种**出现的次数**。



```cpp
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#define maxlen_s 100009
#define ll long long

using namespace std;

int sum_sum[maxlen_s]; //前n项和的前n项和
int wait_qian[maxlen_s]; //第二种情况
int wait_self[maxlen_s]; //第三种情况
int arr[maxlen_s];//路灯的初始状态
string ss;

void setsum_sum() {
    sum_sum[1] = 1;
    for (int i = 2; i <= 100002; i++) {
        sum_sum[i] = ((i*(i + 1)) >> 1) + sum_sum[i - 1];
    }
}
void setwait(int len) {
    arr[0] = 0;
    for (int i = 1; i <= len; i++) {
        if (arr[i] == 0) wait_self[i] = 1;
        if (arr[i - 1] == arr[i]) wait_qian[i] = 1;
    }
    wait_qian[1] = 0;
}

int main() {
    setsum_sum();

    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        cin >> ss;

        for (int i = 0; i<ss.length(); i++) {
            if (ss[i] == '1') arr[i + 1] = 1;
            else arr[i + 1] = 0;
        }
        setwait(ss.length());

        ll ans = sum_sum[ss.length()];
        for (int i = 1; i <= ss.length(); i++) {
            if (wait_qian[i]) {  //此处i>=2
                ans += (ss.length() - i + 1) + (i - 2);
            }
            if (wait_self[i]) {
                ans += ss.length() - i + 1;
            }
        }
        printf("%lld\n", ans);

        memset(wait_qian, 0, sizeof wait_qian);
        memset(wait_self, 0, sizeof wait_self);
    }
    return 0;
}
```