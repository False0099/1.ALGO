Today is army day, but the servicemen are busy with the phalanx for the celebration of the 60th anniversary of the PRC.  
A phalanx is a matrix of size n*n, each element is a character (a~z or A~Z), standing for the military branch of the servicemen on that position.  
For some special requirement it has to find out the size of the max symmetrical sub-array. And with no doubt, the Central Military Committee gave this task to ALPCs.  
A symmetrical matrix is such a matrix that it is symmetrical by the “left-down to right-up” line. The element on the corresponding place should be the same. For example, here is a 3*3 symmetrical matrix:  
cbx  
cpb  
zcc

Input

There are several test cases in the input file. Each case starts with an integer n (0<n<=1000), followed by n lines which has n character. There won’t be any blank spaces between characters or the end of line. The input file is ended with a 0.

Output

Each test case output one line, the size of the maximum symmetrical sub- matrix.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|3<br>abx<br>cyb<br>zca<br>4<br>zaba<br>cbab<br>abbc<br>cacq<br>0|3<br>3|

## 题解
我们考虑每个点作为左下角时，我们能够构成的最大对称矩阵长为多少，令 t 为第 i 行第 j 列的元素相等的数目,如果我们以 $x$ 为左下角，我们先单独计算出，我们这个时候我们最长能延伸到多少，也就是计算出我们的 t，如果能延伸的比我们的 $dp[i+1][j-1]$ 还要大的话，那么我们我们计算出的**答案 $dp[i][j]$ 为 $dp[i+1][j-1]+1$**，这一点是因为我们如果眼神出 t，还要保证我们内部相等，而我们内部的最大只能是我们的 $dp[i+1][j-1]$ 如果我们算出来的是更小的话，说明我们是不能作为矩阵的新加边的，此时我们的 $dp[i][j]=m$;