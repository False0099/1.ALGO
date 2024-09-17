The ministers of the cabinet were quite upset by the message from the Chief of Security stating that they would all have to change the four-digit room numbers on their offices.  
— It is a matter of security to change such things every now and then, to keep the enemy in the dark.  
— But look, I have chosen my number 1033 for good reasons. I am the Prime minister, you know!  
— I know, so therefore your new number 8179 is also a prime. You will just have to paste four new digits over the four old ones on your office door.  
— No, it’s not that simple. Suppose that I change the first digit to an 8, then the number will read 8033 which is not a prime!  
— I see, being the prime minister you cannot stand having a non-prime number on your door even for a few seconds.  
— Correct! So I must invent a scheme for going from 1033 to 8179 by a path of prime numbers where only one digit is changed from one prime to the next prime.  
  
Now, the minister of finance, who had been eavesdropping, intervened.  
— No unnecessary expenditure, please! I happen to know that the price of a digit is one pound.  
— Hmm, in that case I need a computer program to minimize the cost. You don't know some very cheap software gurus, do you?  
— In fact, I do. You see, there is this programming contest going on... Help the prime minister to find the cheapest prime path between any two given four-digit primes! The first digit must be nonzero, of course. Here is a solution in the case above.  

> 1033  
> 1733  
> 3733  
> 3739  
> 3779  
> 8779  
> 8179

The cost of this solution is 6 pounds. Note that the digit 1 which got pasted over in step 2 can not be reused in the last step – a new 1 must be purchased.



## Input

One line with a positive number: the number of test cases (at most 100). Then for each test case, one line with two numbers separated by a blank. Both numbers are four-digit primes (without leading zeros).

## Output

One line for each case, either with a number stating the minimal cost or containing the word Impossible.

## Sample

|Inputcopy|Outputcopy|
|---|---|
|3<br>1033 8179<br>1373 8017<br>1033 1033|6<br>7<br>0|


## Translate
我们给定一个两个质数，每次只能改变其中的一位，问多少次更改后能从 A 到达 B。打印出我们的最少打印次数。我们考虑**枚举每一次更改哪一位**，**那一位改成哪一个数字**。判断我们变更后的数字是否出现过，或者我们变更后的数字是否是质数。如果两个都满足，我们就扩展这个数。


## 题解
```cpp
#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
#include <string.h>
#include <cstdio>
#include <stdio.h>

using namespace std;

int n,k;
bool prime[10010];

void iprime()
{
    int i,j;
    for(i=1000;i<=10000;i++)
    {
        for( j=2;j<i;j++)
        {
            if(i%j==0)
            {
                prime[i]=false;
                break;
            }
        }
        if(j==i)
        {
            prime[i]=true;
            //cout<<i<<endl;
        }
    }
}

int BFS()
{
    int temp,vtemp,count1[10010],vis[10010],t[4];
    queue<int>q;
    q.push(n);
    memset(count1,0,sizeof(count1));
    memset(vis,false,sizeof(vis));
    while(!q.empty())
    {
         temp=q.front();
         q.pop();
         if(temp==k)//终点
         {
             return count1[temp];
         }
         t[0]=temp/1000;//我们的第一位
         t[1]=temp/100%10;//第二位
         t[2]=temp/10%10;//第三位
         t[3]=temp%10;//第四位
         for(int i=0;i<4;i++)//枚举我们要更改哪一位
         {
             vtemp=t[i];
             for(int j=0;j<10;j++)
             {
                 if(j!=vtemp)
                 {
                     t[i]=j;
                 int rtemp=t[0]*1000+t[1]*100+t[2]*10+t[3];//这是我们更改后的数
                 //cout<<rtemp<<endl;
                 if(!vis[rtemp]&&prime[rtemp])
                 {
                     vis[rtemp]=true;
                     q.push(rtemp);
                     count1[rtemp]=count1[temp]+1;
                 }
                  if(rtemp==k)
                     {
                         return count1[rtemp];
                     }
                 }
             }
             t[i]=vtemp;//回复现场
         }
    }
    return -1;
}


int main()
{
    int t;
    iprime();
    for(cin>>t;t;t--)
    {
        cin>>n>>k;
        int key=BFS();
        if(key==-1)
        {
            cout<<"Impossible"<<endl;
        }
        else
        {
            cout<<key<<endl;
        }
    }
}

```