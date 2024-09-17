Search is important in the acm algorithm. When you want to solve a problem by using the search method, try to cut is very important.  
Now give you a number sequence, include n (<=1000) integers, each integer not bigger than 2^31, you want to find the first P subsequences that is not decrease (if total subsequence W is smaller than P, than just give the first W subsequences). The order of subsequences is that: first order the length of the subsequence. Second order the sequence of each integer’s position in the initial sequence. For example initial sequence 1 3 2 the total legal subsequences is 5. According to order is {1}; {3}; {2}; {1,3}; {1,2}. {1,3} is first than {1,2} because the sequence of each integer’s position in the initial sequence are {1,2} and {1,3}. {1,2} is smaller than {1,3}. If you also can not understand , please see the sample carefully.  

Input

The input contains multiple test cases.  
Each test case include, first two integers n, P. (1<n<=1000, 1<p<=10000).  

Output

For each test case output the sequences according to the problem description. And at the end of each case follow a empty line.

Sample

|Inputcopy|Outputcopy|
|---|---|
|3 5<br>1 3 2<br>3 6<br>1 3 2<br>4 100<br>1 2 3 2|1<br>3<br>2<br>1 3<br>1 2<br><br>1<br>3<br>2<br>1 3<br>1 2<br><br>1<br>2<br>3<br>1 2<br>1 3<br>2 3<br>2 2<br>1 2 3<br>1 2 2|

Hint

Hint : You must make sure each subsequence in the subsequences is unique.