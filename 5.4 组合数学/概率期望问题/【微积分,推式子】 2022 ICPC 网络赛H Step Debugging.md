Rikka is a talented student. She likes to wander in the corridor while solving ICPC problems. Specifically, she will do
 random walk for $n$ steps. In the i-th random step, she will choose one of the vectors $(x,y)$ such that $x, y\in \mathbb{R}$ and $x^2+ y^2\leq R_4^2$ with equal probability. And then she will walk along the vector. In other words, if she stood at $(A,B)$

 before the random step, she will stand at $(A+x,B+y)$
Afterwards. Before wandering, she stands at the door (0,0). After wandering, she was curious about the expectation of the square of Euclidean distance to

 point (0,0). In other words, she wants to know the expected value of $x^2+y^2$, if she stands at $(x,y)$ after all $n$ random steps.

## 输入：
Input The first line contains an intoger $n$the number of random steps.
The second line contains $n$ positive integers $R_i$, the parameter of the i-th random step.
It is guaranteed that $1\leq n\leq 50000$，and $1\leq R_i\leq1000.$ 

## 输出：
$$\begin{array}{l}\text{You need to output }d,\text{ the expected value of }x^2+y^2.\text{ Assuming the correct result is }d^*,\text{ you need}\\\text{to ensure that }\frac{|d-d^*|}{\max(d^*,1)}\leq10^{-6}.\end{array}$$

## 题解
我们本题的做法是，因为我们每一个原型和下一个圆形之前存在递推，于是我们考虑从前一个的变化去推导我们的后一个的变化。

假设我们之前的是：$E(a^2+b^2)$ 之后我们经过一次操作后，变成：$E((a+x)^2+(b+y)^2)$ 根据期望线性，我们有：$E(a^2+b^2+x^2+y^2+2ax+2by)$ 又因为对称性，我们的 $E(2ax)=E(2ay)=0$。

所以我们最后的式子就是 $E(a^2+b^2)+E(x^2+y^2)$。

在这里，我们就可以通过我们的递推求答案。
```cpp
double ans=0;
for(int i=0;i<n;i++){
	ans+=(x*x)/2;
}
```