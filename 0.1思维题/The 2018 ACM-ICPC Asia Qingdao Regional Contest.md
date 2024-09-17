In computability theory, the halting problem is the problem of determining, from a description of an arbitrary computer program, whether the program will finish running (i.e., halt) or continue to run forever.

Alan Turing proved in 1936 that a general algorithm to solve the halting problem cannot exist, but DreamGrid, our beloved algorithm scientist, declares that he has just found a solution to the halting problem in a specific programming language -- the Dream Language!

Dream Language is a programming language consists of only 5 types of instructions. All these instructions will read from or write to a 8-bit register r, whose value is initially set to 0. We now present the 5 types of instructions in the following table. Note that we denote the current instruction as the i-th instruction.

|Instruction|Description|
|---|---|
|add v|Add v to the register r. As r is a 8-bit register, this instruction actually calculates (r+v)mod256 and stores the result into r, i.e. r←(r+v)mod256. After that, go on to the (i+1)-th instruction.|
|beq v k|If the value of r is equal to v, jump to the k-th instruction, otherwise go on to the (i+1)-th instruction.|
|bne v k|If the value of r isn't equal to v, jump to the k-th instruction, otherwise go on to the (i+1)-th instruction.|
|blt v k|If the value of r is strictly smaller than v, jump to the k-th instruction, otherwise go on to the (i+1)-th instruction.|
|bgt v k|If the value of r is strictly larger than v, jump to the k-th instruction, otherwise go on to the (i+1)-th instruction.|

A Dream Language program consisting of n instructions will always start executing from the 1st instruction, and will only halt (that is to say, stop executing) when the program tries to go on to the (n+1)-th instruction.

As DreamGrid's assistant, in order to help him win the Turing Award, you are asked to write a program to determine whether a given Dream Language program will eventually halt or not.

#### Input

There are multiple test cases. The first line of the input is an integer T, indicating the number of test cases. For each test case:

The first line contains an integer n (1≤n≤104), indicating the number of instructions in the following Dream Language program.

For the following n lines, the i-th line first contains a string s (∈{"add","beq","bne","blt","bgt"}s∈{"add","beq","bne","blt","bgt"}), indicating the type of the i-th instruction of the program.

- If s equals to "add", an integer v follows (0≤v≤255), indicating the value added to the register;
    
- Otherwise, two integers v and k follow (0≤v≤255, 1≤k≤n), indicating the condition value and the destination of the jump.
    

It's guaranteed that the sum of n of all test cases will not exceed 105105.

#### Output

For each test case output one line. If the program will eventually halt, output "Yes" (without quotes); If the program will continue to run forever, output "No" (without quotes).

#### Sample

|Inputcopy|Outputcopy|
|---|---|
|4<br>2<br>add 1<br>blt 5 1<br>3<br>add 252<br>add 1<br>bgt 252 2<br>2<br>add 2<br>bne 7 1<br>3<br>add 1<br>bne 252 1<br>beq 252 1|Yes<br>Yes<br>No<br>No|

#### Hint

For the second sample test case, note that r is a 8-bit register, so after four "add 1" instructions the value of r will change from 252 to 0, and the program will halt.

For the third sample test case, it's easy to discover that the value of r will always be even, so it's impossible for the value of r to be equal to 7, and the program will run forever.

## 题解
我们这一题属于是纯纯的思维题了，要判断一个指令会不会停止，我们只需要**按照顺序执行**，然后判断**每一条指令执行时我们的值是否是相同的**，如果**是，那么我们就输出否，因为这样一定会陷入循环**，反之，我们就是出是。

**当然，我们也可以用图论的写法，但是这样我们就会复杂的很多**

```cpp
//C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;
typedef long long llong;
const int MAXN = 10000 + 10;

typedef struct
{
	int p, v, k;
} node;

bool book[MAXN][260];

int main()
{
	int t, n, i, r, sgn;
	char str[7];
	int p, v, k;
	node a[MAXN];
	
	scanf("%d", &t);
	getchar();
	while(t--)
	{
		scanf("%d", &n);
		getchar();
		for(i = 1; i <= n; i++)
		{
			scanf("%s", str);
			getchar();
			if(str[1] == 'd')
			{
				scanf("%d", &k);
				getchar();
				p = 1;
				a[i] = (node){p, v, k};
				continue;
			}
			scanf("%d%d", &v, &k);
			getchar();
			if(str[1] == 'e')
			{
				p = 2;
			}
			else if(str[1] == 'n')
			{
				p = 3;
			}
			else if(str[1] == 'l')
			{
				p = 4;
			}
			else if(str[1] == 'g')
			{
				p = 5;
			}
			a[i] = (node){p, v, k};
		}
		
		memset(book, false, sizeof(book));
		i = 1; r = 0;
		book[i][r] = true;
		sgn = 1;
		while(i <= n)
		{
			p = a[i].p;
			v = a[i].v;
			k = a[i].k;
			if(p == 1)
			{
				r += k;
				r %= 256;
				i++;
			}
			else if(p == 2)
			{
				i = (r == v) ? k : i + 1;
			}
			else if(p == 3)
			{
				i = (r != v) ? k : i + 1;
			}
			else if(p == 4)
			{
				i = (r < v) ? k : i + 1;
			}
			else if(p == 5)
			{
				i = (r > v) ? k : i + 1;
			}
			if(book[i][r] == true)
			{
				sgn = 0;
				break;
			}
			book[i][r] = true;
		}
		if(sgn == 1)
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}
	}
    return 0;
}
```