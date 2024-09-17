A palindrome is a symmetrical string, that is, a string read identically from left to right as well as from right to left. You are to write a program which, given a string, determines the minimal number of characters to be inserted into the string in order to obtain a palindrome.  
  
As an example, by inserting 2 characters, the string "Ab3bd" can be transformed into a palindrome ("dAb3bAd" or "Adb3bdA"). However, inserting fewer than 2 characters does not produce a palindrome.  

Input

Your program is to read from standard input. The first line contains one integer: the length of the input string N, 3 <= N <= 5000. The second line contains one string with length N. The string is formed from uppercase letters from 'A' to 'Z', lowercase letters from 'a' to 'z' and digits from '0' to '9'. Uppercase and lowercase letters are to be considered distinct.

Output

Your program is to write to standard output. The first line contains one integer, which is the desired minimal number.

Sample

|Inputcopy|Outputcopy|
|---|---|
|5<br>Ab3bd|2|

## 题解
本题问我们最少插入多少个字母，让我们的字符变成我们的回文串。这里我们可以用我们的**顺序和逆序的最大公共子序列**。然后我们的**总长度减去我们的公共长度就是我们的答案。**

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int dp[2][5005];
int main()
{
    int n;
    while(cin>>n)
    {
        memset(dp,0,sizeof(dp));
        char s[5005],ss[5005];
        cin>>s;
        for(int i=n-1;i>=0;i--)
        {
            ss[n-i]=s[i];
            s[i+1]=s[i];
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(s[i]==ss[j])
                {
                    dp[1][j]=dp[0][j-1]+1;
                }
                else
                {
                    dp[1][j]=max(dp[0][j],dp[1][j-1]);
                }
            }
            for(int j=1;j<=n;j++)
            {
                dp[0][j]=dp[1][j];
            }
        }
        cout<<n-dp[1][n]<<endl;
    }
    return 0;
}
```