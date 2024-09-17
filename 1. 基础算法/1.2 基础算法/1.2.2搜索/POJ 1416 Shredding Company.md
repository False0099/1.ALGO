You have just been put in charge of developing a new shredder for the Shredding Company Although a "normal" shredder would just shred sheets of paper into little pieces so that the contents would become unreadable, this new shredder needs to have the following unusual basic characteristics.  
  
1.The shredder takes as input a target number and a sheet of paper with a number written on it.  
  
2.It shreds (or cuts) the sheet into pieces each of which has one or more digits on it.  
  
3.The sum of the numbers written on each piece is the closest possible number to the target number, without going over it.  
  
For example, suppose that the target number is 50, and the sheet of paper has the number 12346. The shredder would cut the sheet into four pieces, where one piece has 1, another has 2, the third has 34, and the fourth has 6. This is because their sum 43 (= 1 + 2 + 34 + 6) is closest to the target number 50 of all possible combinations without going over 50. For example, a combination where the pieces are 1, 23, 4, and 6 is not valid, because the sum of this combination 34 (= 1 + 23 + 4 + 6) is less than the above combination's 43. The combination of 12, 34, and 6 is not valid either, because the sum 52 (= 12 + 34 + 6) is greater than the target number of 50.  

![](https://vj.csgrandeur.cn/945777e48ec1ab43c93d4ce8bb1def99?v=1695015001)  
Figure 1. Shredding a sheet of paper having the number 12346 when the target number is 50

There are also three special rules :  
  
1.If the target number is the same as the number on the sheet of paper, then the paper is not cut.  
  
For example, if the target number is 100 and the number on the sheet of paper is also 100, then  
  
the paper is not cut.  
  
2.If it is not possible to make any combination whose sum is less than or equal to the target number, then error is printed on a display. For example, if the target number is 1 and the number on the sheet of paper is 123, it is not possible to make any valid combination, as the combination with the smallest possible sum is 1, 2, 3. The sum for this combination is 6, which is greater than the target number, and thus error is printed.  
  
3.If there is more than one possible combination where the sum is closest to the target number without going over it, then rejected is printed on a display. For example, if the target number is 15, and the number on the sheet of paper is 111, then there are two possible combinations with the highest possible sum of 12: (a) 1 and 11 and (b) 11 and 1; thus rejected is printed. In order to develop such a shredder, you have decided to first make a simple program that would simulate the above characteristics and rules. Given two numbers, where the first is the target number and the second is the number on the sheet of paper to be shredded, you need to figure out how the shredder should "cut up" the second number.  
  

## Input

The input consists of several test cases, each on one line, as follows :  
  
tl num1  
t2 num2  
...  
tn numn  
0 0  
  
Each test case consists of the following two positive integers, which are separated by one space : (1) the first integer (ti above) is the target number, (2) the second integer (numi above) is the number that is on the paper to be shredded.  
  
Neither integers may have a 0 as the first digit, e.g., 123 is allowed but 0123 is not. You may assume that both integers are at most 6 digits in length. A line consisting of two zeros signals the end of the input.  
  

## Output

For each test case in the input, the corresponding output takes one of the following three types :  
  
sum part1 part2 ...  
rejected  
error  
  
In the first type, partj and sum have the following meaning :  
  
1.Each partj is a number on one piece of shredded paper. The order of partj corresponds to the order of the original digits on the sheet of paper.  
  
2.sum is the sum of the numbers after being shredded, i.e., sum = part1 + part2 +...  
  
Each number should be separated by one space.  
The message error is printed if it is not possible to make any combination, and rejected if there is  
more than one possible combination.  
No extra characters including spaces are allowed at the beginning of each line, nor at the end of each line.  

## Sample

|Inputcopy|Outputcopy|
|---|---|
|50 12346<br>376 144139<br>927438 927438<br>18 3312<br>9 3142<br>25 1299<br>111 33333<br>103 862150<br>6 1104<br>0 0|43 1 2 34 6<br>283 144 139<br>927438 927438<br>18 3 3 12<br>error<br>21 1 2 9 9<br>rejected<br>103 86 2 15 0<br>rejected|

## 题解
公司现在要发明一种新的碎纸机，要求新的碎纸机能够把纸条上的数字切成最接近而不超过 target 值。比如，我们有一个 target=50，我们纸条上的数字是 12346，我们就应该切成四部分。

我们这样就可以**枚举我们的每一次切割的长度**，然后再去求我们的最优解。
![[无标题 8.png]]

```cpp
for(int i=0;i<=S;i++){
	if(count1(i)==3){
		int i1=lowbit(i)
		int i2=lowbit(i);
		int i3=lowbit(i);
		sum=stoi(i1)+stoi(i2)+stoi(i3);
	}
}
```

```cpp
#include <iostream>
//#include <bits/stdc++.h>
#include <string>
#include <cstdlib>
 
using namespace std;
 
const int N = 6;
 
//记录活动的每片的长度
int a[N] = {0};
//记录最佳的每片的长度
int b[N] = {0};
 
//最佳结果
int best = 0;
//最优解的片数
int best_cnt_p = 0;
//目标
int target = 0;
 
//片计数器
int cnt_p = 0;
//当前长度计数器
int cnt_l = 0;
 
string s = "";
 
//记录是否有多种分解方法
bool hasMore = false;
 
void dfs() {
    //递归出口
    if (cnt_l == s.length()) {//相当于我们枚举我们的断点位置
 
        int cur_len = 0;
        int sum = 0;
        for (int i = 0; i < cnt_p; i++) {
            sum += (atoi(s.substr(cur_len, a[i]).c_str()));
            cur_len += a[i];
 
        }
        //不满足条件
        if (sum > target) {
            return;
        }
        //更新最优解
        else if (sum > best) {
            best = sum;
            hasMore = false;
 
            best_cnt_p = cnt_p;
            for (int i = 0; i < best_cnt_p; i++) {
                b[i] = a[i];
            }
        }
        //最优解不唯一
        else if (sum == best) {
            hasMore = true;
        }
        return;
    }
    for (int i = 0; i < s.length() - cnt_l; i++) {//枚举我们切割的长度
        a[cnt_p] = i + 1;//记录我们的右端点
        cnt_p++;
        cnt_l += (i + 1);//记录我们的左区间
        dfs();
        //恢复状态
        cnt_p--;
        cnt_l -= (i + 1);
    }
}
bool first_check() {
    int sum = 0;
    for (int i = 0; i < s.length(); i++) {
        int temp = s[i] - '0';
        sum += temp;
    }
 
    if (sum > target) {
        return false;
    }
    return true;
}
 
int main() {
    while (cin >> target >> s) {
        if (target == 0 && s == "0") {
            break;
        }
 
        //初始判断
        //若目标直接等于纸张，则直接输出
        if (target == atoi(s.c_str())) {
            cout << target << " " << target << endl;
        }
        //若纸张的最小分解仍然大于目标
        else if (!first_check()) {
            cout << "error" << endl;
        }
        //递归
        else {
            dfs();
            //若含有多组最优解
            if (hasMore) {
                cout << "rejected" << endl;
            } else {
                cout << best << " ";
                int length = 0;
                for (int i = 0; i < best_cnt_p; i++) {
                    cout << s.substr(length, b[i])<< " ";
                    length += b[i];
                }
                cout << endl;
            }
        }
 
        //每一轮完成后，都要清除状态
        //最佳结果
        best = 0;
        //最优解的片数
        best_cnt_p = 0;
        //目标
        target = 0;
 
        //片计数器
        cnt_p = 0;
        //当前长度计数器
        cnt_l = 0;
 
        //记录是否有多种分解方法
        hasMore = false;
    }
 
    return 0;
}
```