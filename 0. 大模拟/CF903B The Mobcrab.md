# The Modcrab

## 题面翻译

## 题目描述

沃瓦又在玩一个 RPG 游戏。在游戏里沃瓦扮演的角色收到了一个任务：去干死一只叫做魔之蟹的大 Boss。

在打了两个小时游戏后沃瓦知道了魔之蟹的各种数值。魔之蟹有 $h_2$ 点生命值和 $a_2$ 点攻击力。沃瓦是个手残，他不想死那么多回，于是就去商店氪了一大堆强力生命回复药剂来准备战斗。

沃瓦的角色有 $h_1$ 点初始生命和 $a_1$ 点攻击力。他还有无限多的强力生命回复药剂，每一瓶都可以给他回复 $c_1$ 点血。沃瓦的每一瓶药剂都是完全一样的。题目数据可以保证 $c_1 > a_2$ 。

战斗包含多个回合。在沃瓦的回合中，它既可以攻击魔之蟹（可以将他的生命值减少 $a_1$ ），也可以喝下一瓶药剂（可将沃瓦的生命值增加 $c_1$ ，沃瓦的生命值值可以超过 $h_1$ ）。现在如果沃瓦和魔之蟹都没有死的话，魔之蟹就会攻击沃瓦，将沃瓦的生命值减少 $a_2$ 。战斗会在沃瓦或魔之蟹中任意一方死亡后结束。

当然，沃瓦想赢，而且他还想赢的越快越好。所以他想制作一个让他用最短时间获胜的策略。

帮帮沃瓦把策略写出来吧！你可以假设沃瓦有无数瓶药水，而且测试数据能保证沃瓦总能赢。

## 输入输出格式
### 输入格式
第一行包含三个正整数 $h_1$, $a_1$, $c_1$ ($1 \leq h_1, a_1 \leq 100$)($2\leq c_1\leq 100$)，分别代表沃瓦的初始生命值，沃瓦的攻击力和一瓶强效生命药剂能回复的生命值。

第二行包含两个正整数 $h_2$, $a_2$ ($1\leq h2\leq 100$)($1\leq a_2, c_1$)，分别代表魔之蟹的生命值和攻击力。

### 输出格式
在第一行输出一个正整数 $n$，代表赢得战斗需要的最少回合数。

接下来输出 $n$ 行。第 $i$ 行可以是代表沃瓦在这回合中喝了一瓶生命药剂的 `HEAL`，也可以是代表沃瓦在这回合中攻击了魔之蟹的 `STRIKE`。

必胜策略必须满足以下条件：沃瓦的角色必须在死亡之前击败魔之蟹，在沃瓦进行最后的操作后魔之蟹的生命值必须小于等于 $0$。

如果有多组解，输出任意一组即可。

## 题目描述

Vova is again playing some computer game, now an RPG. In the game Vova's character received a quest: to slay the fearsome monster called Modcrab.

After two hours of playing the game Vova has tracked the monster and analyzed its tactics. The Modcrab has $ h_{2} $ health points and an attack power of $ a_{2} $ . Knowing that, Vova has decided to buy a lot of strong healing potions and to prepare for battle.

Vova's character has $ h_{1} $ health points and an attack power of $ a_{1} $ . Also he has a large supply of healing potions, each of which increases his current amount of health points by $ c_{1} $ when Vova drinks a potion. All potions are identical to each other. It is guaranteed that $ c_{1}&gt; a_{2} $ .

The battle consists of multiple phases. In the beginning of each phase, Vova can either attack the monster (thus reducing its health by $ a_{1} $ ) or drink a healing potion (it increases Vova's health by $ c_{1} $ ; Vova's health can exceed $ h_{1} $ ). Then, if the battle is not over yet, the Modcrab attacks Vova, reducing his health by $ a_{2} $ . The battle ends when Vova's (or Modcrab's) health drops to $ 0 $ or lower. It is possible that the battle ends in a middle of a phase after Vova's attack.

Of course, Vova wants to win the fight. But also he wants to do it as fast as possible. So he wants to make up a strategy that will allow him to win the fight after the minimum possible number of phases.

Help Vova to make up a strategy! You may assume that Vova never runs out of healing potions, and that he can always win.

## 输入格式

The first line contains three integers $ h_{1} $ , $ a_{1} $ , $ c_{1} $ ( $ 1<=h_{1}, a_{1}<=100 $ , $ 2<=c_{1}<=100 $ ) — Vova's health, Vova's attack power and the healing power of a potion.

The second line contains two integers $ h_{2} $ , $ a_{2} $ ( $ 1<=h_{2}<=100 $ , $ 1<=a_{2}&lt; c_{1} $ ) — the Modcrab's health and his attack power.

## 输出格式

In the first line print one integer $ n $ denoting the minimum number of phases required to win the battle.

Then print $ n $ lines. $ i $ -th line must be equal to HEAL if Vova drinks a potion in $ i $ -th phase, or STRIKE if he attacks the Modcrab.

The strategy must be valid: Vova's character must not be defeated before slaying the Modcrab, and the monster's health must be $ 0 $ or lower after Vova's last action.

If there are multiple optimal solutions, print any of them.

## 样例 #1

### 样例输入 #1

```
10 6 100
17 5
```

### 样例输出 #1

```
4
STRIKE
HEAL
STRIKE
STRIKE
```

## 样例 #2

### 样例输入 #2

```
11 6 100
12 5
```

### 样例输出 #2

```
2
STRIKE
STRIKE
```

## 提示

In the first example Vova's character must heal before or after his first attack. Otherwise his health will drop to zero in $ 2 $ phases while he needs $ 3 $ strikes to win.

In the second example no healing needed, two strikes are enough to get monster to zero health and win with $ 6 $ health left.

## 题解
这一题，我们最好的办法就是去进行我们的暴力模拟，这里，因为我们不能快速计算出我们的次数是多少。于是，我们就需要用一个 while 循环来进行我们的程序：
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	int h1,a1,c1;
	int h2,a2;
	cin>>h1>>a1>>c1>>h2>>a2;
	int cnt=0;
	vector<string> ans;
	while(1){
		if(h1<=a2){
			h1+=c1;
			a.push_back("HEAL");
		}
		if(h2<=a1){
			h2-=a1;
			a.push_back("STRIKE");
		}else{
			h2-=a1;
			a.push_back("STRIKE");
		}
		h1-=a2;
	}
	cout<<a.size()<<endl;
	for(auto u:a){
		cout<<u<<endl;
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	vector<int> a(n+1);
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	vector<int> query(n);
	for(int i=0;i<m;i++){
		cin>>query[i]; 
	}
	for(int i=1;i<=n;i++){
		
	}
}
```