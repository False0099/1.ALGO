Given a set of sticks of various lengths, is it possible to join them end-to-end to form a square?

## Input

The first line of input contains N, the number of test cases. Each test case begins with an integer 4 <= M <= 20, the number of sticks. M integers follow; each gives the length of a stick - an integer between 1 and 10,000.

## Output

For each case, output a line containing "yes" if is is possible to form a square; otherwise output "no".

## Sample

|Inputcopy|Outputcopy|
|---|---|
|3<br>4 1 1 1 1<br>5 10 20 30 40 50<br>8 1 7 2 6 4 4 3 5|yes<br>no<br>yes|

## 题解
给定一系列小木棍，长度不同，问有没有可能构成一个正方形。

我们枚举正方形的可能的长度，然后看能不能把我们的正方形分成长度相等的四个组，如果可以，我们就输出 yes，不行我们就不可。
```cpp
void dfs(int u,int len,int cnt){
	for(int i=0;i<n;i++){
		vis[i]=true;
		int u=len+a[i];
		if(u>len){
			return false;
		}
		if(len+a[i]>=lens){
			return false;
		}
		
	}
}
```


```cpp
#include <iostream>
#include <cstring>


using namespace std;

const int MAXN = 25;

bool visit[MAXN];   //记录木棍是否被用过
int stick[MAXN];    //记录木棍的长度

int m;              //一共有m根木棍
int side;           //木棍拼成的正方形的边长


//sum表示当前的边已经拼凑的长度
//number表示已经拼凑了几条边
bool DFS(int sum,int number){
    if(number == 4){     //4条边都凑好了，结束
        return true;
    }

    //遍历子节点
    for(int i=0;i<m;i++){
            //如果当前拼凑的长度加上这跟棍子后长度大于边长，或者这根棍子被用过了，则跳过
        if(sum + stick[i] >side ||visit[i]){
            continue;
        }
            //当前拼凑的长度加上这根棍子后长度正好等于边长,则开始拼下一条边
        visit[i] = true;
        if(sum + stick[i] == side){
            if(DFS(0,number+1)){
                return true;
            }
        }
        if(DFS(sum +stick[i],number)){
            return true;
        }
        //能走到这说明这根棍子不能用，则将它擦除掉然后回溯
        visit[i] = false;
    }
    return false;

}

int main()
{
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&m);
        int length = 0;
        for(int i=0;i<m;i++){
            scanf("%d",&stick[i]);
            length += stick[i];
        }
        memset(visit,false,sizeof(visit));
        side = length / 4;
        if(DFS(0,0)){
            printf("yes\n");
        }
        else{
            printf("no  \n");
        }
    }
    return 0;
}
```