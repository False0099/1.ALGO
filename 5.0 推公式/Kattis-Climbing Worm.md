A worm is at the bottom of a pole. It wants to reach the top, but it is too lazy to climb to the top without stopping. It can crawl up the pole a certain number of inches at a time, falling down a lesser number of inches right after while it rests. How many times does the worm need to crawl up in order to reach the top of the pole?

## Input

The input consists of a single line that contains three integers a,b (0≤b<a≤100), and ℎh, (0<h≤100000) indicating the amount a of inches the worm can climb at a time, the amount b of inches the worm falls during its resting period, and the height ℎh of the pole, respectively. For the purposes of this problem, the worm is modeled as a point and thus has no length.

## Output

Output the number of times the worm must crawl up in order to reach the top of the pole.

## Sample 1

|Inputcopy|Outputcopy|
|---|---|
|5 0 15|3|

## Sample 2

|Inputcopy|Outputcopy|
|---|---|
|3 1 4|2|

## 题解
我们这一题的思路就是通过我们的模拟法，直接进行一波简单的模拟操作，我们当然也可以考虑推式子，但是这么做太费时间了。于是我们就可以直接模拟一遍。

```cpp
while(true){
	if(dist+a>=n){
		cnt++;
		break;
	}else{
		dist+=b-a;
		cnt++;
	}
}
```