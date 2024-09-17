There is a new intense giant wheel in UNAL town, in UNAL town the wheels move in counterclockwise direction, also as this wheel has _n_ cabins, everyone and everything can play. In particular, numbers come to this attraction. However, a complete number doesn't fit in one cabin, in fact, each cabin have space only for one bit. For this reason a number splits into its binary from and ride the wheel each bit per cabin. As numbers do not want to mess it up, the bits enter into the attraction in the same order the number is formed. Nonetheless, the wheel moves _k_ times (entering and exiting from the attraction don't count as moves), then when the bits have to get out of the wheel they probably don't do it in the same order they entered, therefore making a different number.

For example, when the number 13 enter in a intense 8-bit it will look like the left side of the image below, after 5 moves the wheel will look like the right side of the image, in this case the number exiting the wheel will be 161.

![](https://vj.csgrandeur.cn/ee44f6b31728df45c6e52878c50adb49?v=1705733665)

You as the chief of the numbers in the UNAL town want to know how the wheel can affect the numbers that ride this attraction.

### Input

First line of input contains 2 numbers _n_ (1 ≤ _n_ ≤ 50) and _m_ (1 ≤ _m_ ≤ 1000) - the quantity of cabins in the wheel and the quantity of numbers that ride in the wheel, respectively.

Next _m_ lines of input contains each 2 integers _num_ (0 ≤ _num_ < 2_n_) and _k_ (1 ≤ _k_ ≤ 1018) - the number that ride the wheel and the quantity of times the wheel move, respectively.

### Output

For each number that ride the wheel print the resulting number after leaving the wheel. Output this number in its decimal form.

### Sample 1

|Inputcopy|Outputcopy|
|---|---|
|8 3<br>1 1<br>13 5<br>17 12|2<br>161<br>17|

### Note

Note that all numbers that ride into the wheel have exactly _n_ bits, for example the number 13 in a 8-cabin wheel is not 1101 but 00001101 (see example).

## 题解
我们这一把可以通过我们的一个数学公式推导来计算得到我们的结果：假设我们现在有 n 个二进制位，我们的每一次旋转之和我们的 k 有关有关。于是我们就可以通过我们的数学推导来得到结论：我们每一次的操作就是把我们的所有数字全都循环右移 k 位。

于是，我们可以通过我们的取模运算得到我们的末尾 k 位，然后再通过我们的移位运算得到我们的结果。

```cpp
int main(){
	int n,m;
	cin>>n>>m;
	while(m--){
		long long x,y;
		cin>>x>>y;
		y%=n;
		cout<<(x<<y)
	}%(1ll<<n)+(x>>n-y);
}
```