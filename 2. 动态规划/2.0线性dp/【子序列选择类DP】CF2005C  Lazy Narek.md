Narek is too lazy to create the third problem of this contest. His friend Artur suggests that he should use ChatGPT. ChatGPT creates $n$ problems, each consisting of $m$ letters, so Narek has $n$ strings. To make the problem harder, he combines the problems by selecting some of the $n$ strings **possibly none** and concatenating them **without altering their order**. His chance of solving the problem is defined as $score_n - score_c$, where $score_n$ is Narek's score and $score_c$ is ChatGPT's score.

Narek calculates $score_n$ by examining the selected string (he moves from left to right). He initially searches for the letter $\texttt{"n"}$, followed by $\texttt{"a"}$, $\texttt{"r"}$, $\texttt{"e"}$, and $\texttt{"k"}$. Upon finding all occurrences of these letters, he increments $score_n$ by $5$ and resumes searching for $\texttt{"n"}$ again (he doesn't go back, and he just continues from where he left off).

After Narek finishes, ChatGPT scans through the array and increments $score_c$ by $1$ for each letter $\texttt{"n"}$, $\texttt{"a"}$, $\texttt{"r"}$, $\texttt{"e"}$, or $\texttt{"k"}$ that Narek fails to utilize (note that if Narek fails to complete the last occurrence by finding all of the $5$ letters, then all of the letters he used are counted in ChatGPT's score $score_c$, and Narek doesn't get any points if he doesn't finish finding all the 5 letters).

Narek aims to maximize the value of $score_n - score_c$ by selecting the most optimal subset of the initial strings.

**Input**

In the first line of the input, you're given a single integer $t$ ($1 \le t \le 10^5$), the number of test cases. Then the description of each test case follows.

In the first line of each test case, you're given two integers $n, m$ ($1 \le n, m \le 10^3$), the number of strings and the length of each string.

In the next $n$ lines, you're given $n$ strings, each having a length of $m$. The strings only contain lowercase letters of the English alphabet.

The sum of values of $n \cdot m$ over all test cases does not exceed $10^6$.

**Output**

For each test case, output a single integer: the maximal possible value of $score_n - score_c$.

## 题解
我们本题，因为我们的 $n,m$ 给定的范围较小，于是我们可以考虑我们的 $o(n*m)$ 的做法，于是，我们考虑按照下面的方法先预处理出我们的每一个字符，

或者其实我们就考虑 $dp[n][S]$ 表示我们在前 n 个中任意选，当前状态为 S 的情况下，我们的最终结果最大是多少。我们显然，我们有：$dp[n][S]+calcval(S)\to dp[n+1][calc(S)]$

这样，我们就可以完成我们的本题，时间复杂度也够：
```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=1010;
int dp[N][5];
string s[N];
string a="narek";
void solve(){
    int n,m;
    cin>>n>>m;
    auto calc=[&](string s,int j){
        int idx=j;
        int add=0;
        int del=0;
        for(int i=0;s[i];i++){
            if(s[i]=='n'||s[i]=='a'||s[i]=='r'||s[i]=='k'||s[i]=='e'){
                del++;
            }
            if(s[i]==a[idx]){
                idx=(idx+1)%5;
                if(idx==0){
//                    cerr<<idx<<" "<<endl;
                    add+=5;
                    del-=5;
                }
            }
        }
        //cerr<<add<<" "<<del<<endl;
        return make_pair(idx,add-del);
    };
    //auto [u,v]=calc("narek",1);
    //cerr<<u<<" "<<v<<endl;
    //exit(0);
    for(int i=0;i<=n;i++){
        for(int j=0;j<5;j++){
            dp[i][j]=-INF;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(int j=0;j<5;j++){
            
            auto [states,val]=calc(s,j);
         //   cerr<<states<<" "<<val<<endl;
            dp[i][states]=max(dp[i][states],dp[i-1][states]);
            dp[i][states]=max(dp[i][states],dp[i-1][j]+val);
            dp[i][states]=max(dp[i][states],dp[i-1][states]);
        }
        for(int j=0;j<5;j++){
            dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<5;j++){
            ans=max(ans,dp[i][j]);
        }
    }
    cout<<ans<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```