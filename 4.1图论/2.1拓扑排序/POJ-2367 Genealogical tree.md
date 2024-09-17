The system of Martians' blood relations is confusing enough. Actually, Martians bud when they want and where they want. They gather together in different groups, so that a Martian can have one parent as well as ten. Nobody will be surprised by a hundred of children. Martians have got used to this and their style of life seems to them natural.  
And in the Planetary Council the confusing genealogical system leads to some embarrassment. There meet the worthiest of Martians, and therefore in order to offend nobody in all of the discussions it is used first to give the floor to the old Martians, than to the younger ones and only than to the most young childless assessors. However, the maintenance of this order really is not a trivial task. Not always Martian knows all of his parents (and there's nothing to tell about his grandparents!). But if by a mistake first speak a grandson and only than his young appearing great-grandfather, this is a real scandal.  
Your task is to write a program, which would define once and for all, an order that would guarantee that every member of the Council takes the floor earlier than each of his descendants.

## Input

The first line of the standard input contains an only number N, 1 <= N <= 100 — a number of members of the Martian Planetary Council. According to the centuries-old tradition members of the Council are enumerated with the natural numbers from 1 up to N. Further, there are exactly N lines, moreover, the I-th line contains a list of I-th member's children. The list of children is a sequence of serial numbers of children in a arbitrary order separated by spaces. The list of children may be empty. The list (even if it is empty) ends with 0.

## Output

The standard output should contain in its only line a sequence of speakers' numbers, separated by spaces. If several sequences satisfy the conditions of the problem, you are to write to the standard output any of them. At least one such sequence always exists.

## Sample

|Inputcopy|Outputcopy|
|---|---|
|5<br>0<br>4 5 1 0<br>1 0<br>5 3 0<br>3 0|2 4 5 3 1|


## 题解
我们这一题，我们需要运用我们的拓扑排序即可。

```CPP
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
 
#define M 110
 
int main()
{
    int n;
    int map[M][M];
    int ingreed[M];
    int ans[M];
 
    while(cin>>n && n != 0){
 
        memset(map,0,sizeof(map));
        memset(ingreed,0,sizeof(ingreed));
 
        for(int i = 1;i <= n; i++){
            int p;
            while(cin>>p,p){
                map[i][p] = 1;
                ingreed[p]++;
            }
        }
        int all = 0;
        for(int i = 1;i <= n; i++)
            for(int j = 1;j <= n; j++)
                if(ingreed[j] == 0){
                    ans[all++] = j;
                    ingreed[j] = -1;
                    for(int k = 1;k <= n; k++)
                        if(map[j][k] == 1)
                            ingreed[k]--;
                    break;
                }
 
        for(int i = 0;i < all; i++)
            printf("%d%c",ans[i],i == all - 1 ? '\n' : ' ');
    }
    return 0;
}
```
