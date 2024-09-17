
An undirected graph is a set V of vertices and a set of $E∈{V*V}$ edges.An undirected graph is connected if and only if for every pair (u,v) of vertices,u is reachable from v.  
You are to write a program that tries to calculate the number of different connected undirected graph with n vertices.  
For example,there are 4 different connected undirected graphs with 3 vertices.  

![](https://vj.csgrandeur.cn/6cf5433dd1e316c2dbfbb67f3c18c209?v=1698065241)
Input

The input contains several test cases. Each test case contains an integer n, denoting the number of vertices. You may assume that 1<=n<=50. The last test case is followed by one zero.

Output

For each test case output the answer on a single line.

Sample

|Inputcopy|Outputcopy|
|---|---|
|1<br>2<br>3<br>4<br>0|1<br>1<br>4<br>38|

## 题解
我们这一题就是给定我们 n 个点，问我们能够构成最多多少个无向联通图。结点有编号。我们这一题可以采用我们的容斥 DP 思路，我们先计算我们 n 个点一共能够构成多少个图，再去计算我们构成的图中不连通的数目。

而且我们能够发现，我们的容斥 dp 都有着类似的形式，就是我们的
$dp[i]=sumall-\sum dp[j]\times sum(j)$

我们可以发现，这一题是和我们的 n 有关，于是我们就设我们 $f[n]$ 表示我们要让 n 个点联通时，我们的连通图的个数是多少。

于是我们就有转移式子如下：
$f[i]=2^{i*(i-1)/2}-\sum f[j]\times C_{i-1}^{j-1}\times 2^{(i-j)(i-j)/2}$
![[Pasted image 20231029185656.png]]


```java
package poj1737;
import java.util.*;
import java.math.BigInteger;
public class Main{								//固定一个点，让0~N-2个点与这个点联通，剩下的点任意连
	public static void main(String[] args){		//总数是2^C(n,2)，也就是完全图所有边数取还是不取
		BigInteger f[]=new BigInteger[2505];	//dp[i]为i个点的种数，则
		BigInteger dp[]=new BigInteger[55];		//dp[i]=2^C(i,2)-∑(j=1->n-1)(dp[j]*C(i-1,j-1)*2^(C(i-j,2)))
		BigInteger c[][]=new BigInteger[55][55];
		int n,i,j;
		BigInteger sum;
	    for(i=0;i<=50;i++)
	    dp[i]=BigInteger.valueOf(0);
	    f[0]=BigInteger.valueOf(1);
	    for(i=1;i<=2500;i++)					//因为大数没有pow因此先存起来
	    f[i]=f[i-1].multiply(BigInteger.valueOf(2));
	    dp[1]=BigInteger.valueOf(1);
	    for(i=1;i<=50;i++){
	        for(j=0;j<=i;j++){
	            if(j==0||j==i)
	            c[i][j]=BigInteger.valueOf(1);
	            else
	            c[i][j]=c[i-1][j].add(c[i-1][j-1]);
	        }
	    }
	    for(i=2;i<=50;i++){
	        sum=BigInteger.valueOf(0);
	        for(j=1;j<=i-1;j++)
	        sum=sum.add(dp[j].multiply(c[i-1][j-1]).multiply(f[(i-j)*(i-j-1)/2]));
	        dp[i]=f[i*(i-1)/2].subtract(sum);
	    }
	    Scanner cin=new Scanner(System.in);    
        while(cin.hasNext()){    
            n=cin.nextInt();    
            if(n==0) break;    
            System.out.println(dp[n]);    
        }  
	}
 
}
```


  

