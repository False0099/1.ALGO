# LuoTianyi and the Show

## 题面翻译

#### 题目描述

有 $n$ 个人观看一场与 VOCALOID 有关的演出，场地里有一行座位，从左到右标号 $1$ 到 $m$，接下来观众将按顺序以如下三种方式中的一种选择座位：

1. 如果没人坐在座位上，就坐在座位 $m$ 上，否则坐在目前最靠左的人的左边。若座位 $1$ 有人，则离开。
2. 如果没人坐在座位上，就坐在座位 $1$ 上，否则坐在目前最靠右的人的右边。若座位 $m$ 有人，则离开。
3. 如果 $x_i$ 没人则坐在 $x_i$，否则离开。

现在知道每个人选择座位的方式，你可以让人们按照任意顺序入场，求最多找到座位的人数。

#### 输入格式

每一个测试点有多组测试数据，第一行包含一个整数 $t$ ( $1 \le t \le 10^4$ ) 为测试数据的组数。

每组数据格式如下：

第一行包含两个整数 $n$ 和 $m$ ( $1 \le n, m \le 10^5$ )，分别为人数和座位数。

第二行包含 $n$ 个整数 $x_1, x_2, \ldots, x_n$ ( $-2 \le x_i \le m$ , $x_i \ne 0$ ) 表示观众入座方式，第 $i$ 个人入座的方式如下：

1. 如果 $x_i=-1$，那么第 $i$ 个人以第一种方式选择座位。
2. 如果 $x_i=-2$，那么第 $i$  个人以第二种方式选择座位。
3. 如果 $x_i > 0$，那么第 $i$ 个人选择第 $x_i$ 个座位并以第三种方式选择座位。

保证每组数据中 $n$ 和 $m$ 的总和不超过 $10^5$。

#### 输出格式

每一组测试数据输出一个整数，表示这组数据中找到座位的最多人数。

#### 提示

第一组测试样例中，所有人都想占用座位 $5$，因此只有 $1$ 个人能找到座位。

第二组测试样例中，我们可以让人们按照 $1,2,3,4$ 的顺序入场，那么除了最后一个人以外的人都能找到座位。

在第三组测试样例中，我们可以让人们按照这样的顺序入场：  
让第三个人入场：  

| –   | –   | –   | 3   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第四个人入场：  

| –   | –   | –   | 3   | 4   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第五个人入场：

| –   | –   | –   | 3   | 4   | 5   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第一个人入场：

| –   | –   | 1   | 3   | 4   | 5   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第二个人入场：

| –   | 2   | 1   | 3   | 4   | 5   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

于是 $5$ 个人都找到了座位。

在第五组测试样例中，我们可以让人们按照这样的顺序入场：  
让第四个人入场：

| –   | –   | –   | –   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第三个人入场：

| –   | –   | –   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第六个人入场，由于他选择了第四个座位按照第三种方式入场，但第四个座位已经被占，所以离开：

| –   | –   | –   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第五个人入场：

| –   | –   | 5   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第一个人入场：

| –   | 1   | 5   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第二个人入场：

| 2   | 1   | 5   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- | 

于是 $5$ 个人找到了座位。

在第七组测试样例中，我们可以让人们按照这样的顺序入场：  
让第三个人入场：

| 3   | –   | –   | –   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第四个人入场：

| 3   | 4   | –   | –   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第五个人入场：

| 3   | 4   | 5   | –   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第六个人入场：

| 3   | 4   | 5   | 6   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第一个人入场：

| 3   | 4   | 5   | 6   | 1   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第二个人入场，他以第一种方式选择座位，而座位 $1$ 被占用，所以离开：

| 3   | 4   | 5   | 6   | 1   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

于是 $5$ 个人找到了座位。

## 题目描述

There are $ n $ people taking part in a show about VOCALOID. They will sit in the row of seats, numbered $ 1 $ to $ m $ from left to right.

The $ n $ people come and sit in order. Each person occupies a seat in one of three ways:

1. Sit in the seat next to the left of the leftmost person who is already sitting, or if seat $ 1 $ is taken, then leave the show. If there is no one currently sitting, sit in seat $ m $ .
2. Sit in the seat next to the right of the rightmost person who is already sitting, or if seat $ m $ is taken, then leave the show. If there is no one currently sitting, sit in seat $ 1 $ .
3. Sit in the seat numbered $ x_i $ . If this seat is taken, then leave the show.

Now you want to know what is the maximum number of people that can take a seat, if you can let people into the show in any order?

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 10^5 $ ) — the number of people and the number of seats.

The second line of each test case contains $ n $ integers $ x_1, x_2, \ldots, x_n $ ( $ -2 \le x_i \le m $ , $ x_i \ne 0 $ ), the $ i $ -th of which describes the way in which the $ i $ -th person occupies a seat:

1. If $ x_i=-1 $ , then $ i $ -th person takes the seat in the first way.
2. If $ x_i=-2 $ , then $ i $ -th person takes the seat in the second way.
3. If $ x_i > 0 $ , then the $ i $ -th person takes a seat in the third way, i.e. he wants to sit in the seat with the number $ x_i $ or leave the show if it is occupied..

It is guaranteed that sum of $ n $ and the sum of $ m $ over all test cases don't exceed $ 10^5 $ .

## 输出格式

For each test case output a single integer — the maximum number of people who can occupy a seat.

## 样例 #1

### 样例输入 #1

```
10
3 10
5 5 5
4 6
1 -2 -2 1
5 7
-1 -1 4 -2 -2
6 7
5 -2 -2 -2 -2 -2
6 6
-1 1 4 5 -1 4
6 8
-1 -1 -1 3 -1 -2
6 7
5 -1 -2 -2 -2 -2
3 1
-2 -2 1
2 5
5 -2
1 2
-1
```

### 样例输出 #1

```
1
3
5
6
5
5
5
1
2
1
```

## 提示

In the first test case, all the people want to occupy the $ 5 $ seat, so only $ 1 $ people can occupy the seat.

In the second test case, we can let people in order $ 1, 2, 3, 4 $ , then all but the last person can take a seat.

In the third test case, we can let people into the show in that order:

Let the third person in:

–––3–––Let the fourth person in:

–––34––Let the fifth person in:

–––345–Let the first person in:

––1345–Let the second person in:

–21345–Thus, all $ 5 $ people took seats.

In the fifth test case, we can let people into the show in this order:

Let the fourth person in:

––––4–Let the third person in:

–––34–Let the sixth person in, he'll leave the show because he takes the third seat the third way and has to sit in the $ 4 $ seat, but it's already taken:

–––34–Let the fifth person in:

––534–Let the first person in:

–1534–Let the second person in:

21534–Thus, $ 5 $ of people took seats.

In the seventh test case, we can let people into the show in this order:

Let the third person in:

3––––––Let the fourth person in:

34–––––Let the fifth person in:

345––––Let the sixth person in:

3456–––Let the first person in:

34561––Let the second person in, he will leave the show because he occupies the first way, but the $ 1 $ seat is taken:

34561––Thus, $ 5 $ people took seats.

## 题解
本题我们可以考虑在安排第三种的同时再去考虑我们的第一种和第二种观众。此时，我们可以发现，在固定位置之间有一些会空开的位置，这些位置是否可以做人我们就可以根据我们的入场顺序来决定，所以我们就可以先让某个空白区间的做右端点中的一个先进厂，再让我们第一种或者第二种直到填满。我们再让另一个端点入场，这样就不会有空座位了。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1e5+10;
int t,n,m,a[N],st[N];
int k1,k2,k3;
int ans1,ans2,ans3,res;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		memset(a,0,sizeof a);
		memset(st,0,sizeof st);
		k1=k2=k3=res=ans1=ans2=ans3=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]>0){
				if(st[a[i]]==0){
					st[a[i]]=1;
					k3++;//第三种观众的数量
				}
			}
			else if(a[i]==-1){
				k1++;//第一种观众的数量
			}
			else{
				k2++;//第二种观众的数量
			}
		}
		ans1=min(k1+k3,m);//只让第一三种观众入场
		ans2=min(k2+k3,m);//只让第二三种观众入场
		for(int i=1;i<=m;i++){
			st[i]+=st[i-1];//前缀和
		}
		for(int i=1;i<=m;i++){
			if(st[i]-st[i-1]>0){
				ans3=max(ans3,min(k1,i-1-st[i-1])+min(k2,m-i-(st[m]-st[i]))+k3);//枚举从哪个固定位置开始作为分水岭，让第一二种观众向两侧填线
			}
			
		}
		res=max(ans1,max(ans2,ans3));
		printf("%d\n",res);
	}
}
```