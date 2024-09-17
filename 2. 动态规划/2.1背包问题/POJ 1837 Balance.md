Gigel has a strange "balance" and he wants to poise it. Actually, the device is different from any other ordinary balance.  
It orders two arms of negligible weight and each arm's length is 15. Some hooks are attached to these arms and Gigel wants to hang up some weights from his collection of G weights (1 <= G <= 20) knowing that these weights have distinct values in the range 1..25. Gigel may droop any weight of any hook but he is forced to use all the weights.  
Finally, Gigel managed to balance the device using the experience he gained at the National Olympiad in Informatics. Now he would like to know in how many ways the device can be balanced.  
  
Knowing the repartition of the hooks and the set of the weights write a program that calculates the number of possibilities to balance the device.  
It is guaranteed that will exist at least one solution for each test case at the evaluation.  

Input

The input has the following structure:  
• the first line contains the number C (2 <= C <= 20) and the number G (2 <= G <= 20);  
• the next line contains C integer numbers (these numbers are also distinct and sorted in ascending order) in the range -15..15 representing the repartition of the hooks; each number represents the position relative to the center of the balance on the X axis (when no weights are attached the device is balanced and lined up to the X axis; the absolute value of the distances represents the distance between the hook and the balance center and the sign of the numbers determines the arm of the balance to which the hook is attached: '-' for the left arm and '+' for the right arm);  
• on the next line there are G natural, distinct and sorted in ascending order numbers in the range 1..25 representing the weights' values.  

Output

The output contains the number M representing the number of possibilities to poise the balance.

Sample

|Inputcopy|Outputcopy|
|---|---|
|2 4	<br>-2 3 <br>3 4 5 8|2|

## 题解
我们本题问我们能够构成的平衡的方案数，于是我们就可以考虑使用我们的二维数组：我们用 $dp[i][j]$ 表示我们用了前 i 个，左右差为 j 的方案数有多少个，然后我们的转移就可以用我们的 $dp[i][j]=dp[i-1][j+w[i]],dp[i-1][j-w[i]]$ 来进行。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 15000;
int dp[30][maxn],xi[50],wi[50],c,g;
int main(void){
	scanf("%d%d",&c,&g);
	for(int i=1;i<=c;i++) scanf("%d",&xi[i]);
	for(int i=1;i<=g;i++) scanf("%d",&wi[i]);
	memset(dp,0,sizeof(dp));
	dp[0][7500] = 1;
	for(int i=1;i<=g;i++){
		for(int j=1;j<=c;j++){
			for(int k=maxn;k>=1;k--)
			if(k+wi[i]*xi[j]>=0&&k+wi[i]*xi[j]<=maxn&&dp[i-1][k+wi[i]*xi[j]]!=0){
				dp[i][k]+=dp[i-1][k+wi[i]*xi[j]];
			}
		}
	}
	printf("%d\n",dp[g][7500]);
	return 0;
}
```