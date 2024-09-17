It is well known that a human gene can be considered as a sequence, consisting of four nucleotides, which are simply denoted by four letters, A, C, G, and T. Biologists have been interested in identifying human genes and determining their functions, because these can be used to diagnose human diseases and to design new drugs for them.  
  
A human gene can be identified through a series of time-consuming biological experiments, often with the help of computer programs. Once a sequence of a gene is obtained, the next job is to determine its function.  
One of the methods for biologists to use in determining the function of a new gene sequence that they have just identified is to search a database with the new gene as a query. The database to be searched stores many gene sequences and their functions – many researchers have been submitting their genes and functions to the database and the database is freely accessible through the Internet.  
  
A database search will return a list of gene sequences from the database that are similar to the query gene.  
Biologists assume that sequence similarity often implies functional similarity. So, the function of the new gene might be one of the functions that the genes from the list have. To exactly determine which one is the right one another series of biological experiments will be needed.  
  
Your job is to make a program that compares two genes and determines their similarity as explained below. Your program may be used as a part of the database search if you can provide an efficient one.  
Given two genes AGTGATG and GTTAG, how similar are they? One of the methods to measure the similarity  
of two genes is called alignment. In an alignment, spaces are inserted, if necessary, in appropriate positions of  
the genes to make them equally long and score the resulting genes according to a scoring matrix.  
  
For example, one space is inserted into AGTGATG to result in AGTGAT-G, and three spaces are inserted into GTTAG to result in –GT--TAG. A space is denoted by a minus sign (-). The two genes are now of equal  
length. These two strings are aligned:  
  
AGTGAT-G  
-GT--TAG  
  
In this alignment, there are four matches, namely, G in the second position, T in the third, T in the sixth, and G in the eighth. Each pair of aligned characters is assigned a score according to the following scoring matrix.  

![](https://vj.csgrandeur.cn/fcf3938cf314f4598e568b157e91a600?v=1697650536)

  
denotes that a space-space match is not allowed. The score of the alignment above is (-3)+5+5+(-2)+(-3)+5+(-3)+5=9.  
  
Of course, many other alignments are possible. One is shown below (a different number of spaces are inserted into different positions):  
  
AGTGATG  
-GTTA-G  
  
This alignment gives a score of (-3)+5+5+(-2)+5+(-1) +5=14. So, this one is better than the previous one. As a matter of fact, this one is optimal since no other alignment can have a higher score. So, it is said that the  
similarity of the two genes is 14.

Input

The input consists of T test cases. The number of test cases ) (T is given in the first line of the input file. Each test case consists of two lines: each line contains an integer, the length of a gene, followed by a gene sequence. The length of each gene sequence is at least one and does not exceed 100.

Output

The output should print the similarity of each test case, one per line.

Sample

|Inputcopy|Outputcopy|
|---|---|
|2 <br>7 AGTGATG <br>5 GTTAG <br>7 AGCTATT <br>9 AGCTTTAAA|14<br>21|

## 题解
我们本题就是我们 LCS 的变形，我们增加了权值，我们需要先 hash 下方便处理

```cpp
/*
ID: LinKArftc
PROG: 1080.cpp
LANG: C++
*/

#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <utility>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define eps 1e-8
#define randin srand((unsigned int)time(NULL))
#define input freopen("input.txt","r",stdin)
#define debug(s) cout << "s = " << s << endl;
#define outstars cout << "*************" << endl;
const double PI = acos(-1.0);
const double e = exp(1.0);
const int inf = 0x3f3f3f3f;
const int INF = 0x7fffffff;
typedef long long ll;

const int maxn = 110;
int score[5][5] = {
    {5, -1, -2, -1, -3},  
    {-1, 5, -3, -2, -4},  
    {-2, -3, 5, -2, -2},  
    {-1, -2, -2, 5, -1},  
    {-3, -4, -2, -1, 0}
}; 

char ch_str1[maxn], ch_str2[maxn];
int str1[maxn], str2[maxn];
int dp[maxn][maxn];

int main() {
    int T;
    int len1, len2;
    scanf("%d", &T);
    while (T --) {
        scanf("%d %s", &len1, ch_str1);
        scanf("%d %s", &len2, ch_str2);
        for (int i = 0; i < len1; i ++) {
            if (ch_str1[i] == 'A') str1[i] = 0;
            else if (ch_str1[i] == 'C') str1[i] = 1;
            else if (ch_str1[i] == 'G') str1[i] = 2;
            else if (ch_str1[i] == 'T') str1[i] = 3;
            else str1[i] = 4;
        }
        for (int i = 0; i < len2; i ++) {
            if (ch_str2[i] == 'A') str2[i] = 0;
            else if (ch_str2[i] == 'C') str2[i] = 1;
            else if (ch_str2[i] == 'G') str2[i] = 2;
            else if (ch_str2[i] == 'T') str2[i] = 3;
            else str2[i] = 4;
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= len1; i ++) dp[i][0] = dp[i-1][0] + score[str1[i-1]][4];
        for (int i = 1; i <= len2; i ++) dp[0][i] = dp[0][i-1] + score[4][str2[i-1]];
        for (int i = 1; i <= len1; i ++) {
            for (int j = 1; j <= len2; j ++) {
                dp[i][j] = max(dp[i-1][j-1] + score[str1[i-1]][str2[j-1]],
                            max(dp[i][j-1] + score[4][str2[j-1]], dp[i-1][j] + score[str1[i-1]][4]));
            }
        }
        printf("%d\n", dp[len1][len2]);
    }

    return 0;
}
```