Laura is a girl who does not like combinatorics. Nemanja will try to convince her otherwise.

Nemanja wrote some digits on the board. All of them are either $1$, $2$, or $3$. The number of digits $1$ is $a$. The number of digits $2$ is $b$ and the number of digits $3$ is $c$. He told Laura that in one operation she can do the following:

-   Select two different digits and erase them from the board. After that, write the digit ($1$, $2$, or $3$) different from both erased digits.

For example, let the digits be $1$, $1$, $1$, $2$, $3$, $3$. She can choose digits $1$ and $3$ and erase them. Then the board will look like this $1$, $1$, $2$, $3$. After that, she has to write another digit $2$, so at the end of the operation, the board will look like $1$, $1$, $2$, $3$, $2$.

Nemanja asked her whether it was possible for only digits of one type to remain written on the board after some operations. If so, which digits can they be?

Laura was unable to solve this problem and asked you for help. As an award for helping her, she will convince Nemanja to give you some points.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first and only line of each test case contains three integers $a$, $b$, $c$ ($1 \le a, b, c \le 100$) — the number of ones, number of twos, and number of threes, respectively.

**Output**

For each test case, output one line containing $3$ integers.

The first one should be $1$ if it is possible that after some operations only digits $1$ remain on the board, and $0$ otherwise.

Similarly, the second one should be $1$ if it is possible that after some operations only digits $2$ remain on the board, and $0$ otherwise.

Similarly, the third one should be $1$ if it is possible that after some operations only digits $3$ remain on the board, and $0$ otherwise.

## 题解
我们本题的关键是找到我们的性质：可以证明，如果两个数字数量的奇偶性相同，那么我们就全部变成第三个数字，这一点我们可以先把我们的最小全部转移到我们的另一个元素中，再对半分我们的剩余元素。最后我们再进行一次操作即可。
```cpp
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
using LL = long long;

int main(){

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while(T--){
        int a[3];
        cin >> a[0] >> a[1] >> a[2];
        for(int i = 0; i < 3; i++) a[i] %= 2;
        for(int i = 0; i < 3; i++){
            if (a[(i + 1) % 3] == a[(i + 2) % 3]){
                cout << 1 << ' ';
            }
            else{
                cout << 0 << ' ';
            }
        }
        cout << '\n';
    }

}
```