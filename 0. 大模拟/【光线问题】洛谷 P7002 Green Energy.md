# [NEERC 2013] Green Energy

## 题面翻译

## 题目描述 ##
平地上的技术进步令人惊叹。今年正要建造一种新型的太阳能发电站。在这些发电站中，太阳能电池板不是安装在地面上，而是安装在高塔上。

在二为世界中有要安装 $i$ 个高塔。这些塔塔高固定。第 $i$ 座塔的高度是 $h_i$。现在，工程师们想要选择安装点，以获得最大的总功率。

电厂区域由有 $m$ 顶点的线连接。这些线的顶点坐标为 $(x_i,y_i)$ 满足 $x_i<x_{i+1}$
在平地上，太阳的角度总是 $\alpha$ 度。太阳从左上角照射到右下角。塔产生的功率取决于其表面被太阳照射的面积 (其实是长度)。

当安装的两个塔彼此靠近时，左侧塔的阴影可能落在右侧塔上，从而右侧塔产生的功率降低。此外，电厂区域本身可能包含在某些塔楼上投下阴影的高点。

你的任务是在电厂区域内找到安装给定塔架的点，以得到太阳照射下塔架最大总表面积 (长度)。

## 输入格式 ##

输入第一行包含三个整数：$n$, $m$, $\alpha$ $(1 \le n \le 10^4,2 \le m \le 10^4,1 \le \alpha <90)$。第二行包含 $n$ 整数 $h_i$ (塔高）$(1 \le h_i \le 10^3)$。后面的 $m$ 行每行有 $x_i$, $y_i$ 一对数（电厂顶点坐标) $(|x_i|\le 10^5,x_i < x_{i+1},|y_i|\le 10^3)$

## 输出格式 ##

第一行: 以至少 $10^{-6}$ 精度输出可被太阳照亮的塔的最大可能汇总面积（长度)。在后 n 行上，输出此时塔安装点的 x 坐标，绝对精度至少为 $10^{-9}$。塔的输出顺序应与输入顺序相同。

## 说明/提示 ##
时间限制：1 h

空间顺序：128 PB

## 题目描述

The technological progress in Flatland is impressive. This year, for example, the solar power stations of a new type will be build. In these stations solar panels are mounted not on the ground, but on high towers, along their heights.

There are $n$ towers to be mounted. The towers are already bought. The height of i-th tower is $h_{i}.$ Now engineers want to choose the points where they should be mounted to get the maximal total power.

The landscape of a territory of the power plant is described by a polyline with $m$ vertices. Vertices of the landscape polyline have coordinates $(x_{i}, y_{i}),$ such that $x_{i} < x_{i+1}.$

The sun angle is always $α$ degrees in Flatland. The sun is shining from the top-left to the bottom-right. The power that is produced by a tower depends on the length of its surface illuminated by the sun.

When two towers are mounted close to each other, the shadow of the left tower may fall onto the right tower, so the power, produced by the right tower, decreases. Also, the landscape itself may contain high points that drop shadows on some towers.

![](/upload/images2/ge.png)

Your task is to find the points on the territory of the plant to mount the given towers to maximize the total length of towers surface that is illuminated by the sun.

## 输入格式

The first line of the input file contains three integers $n , m$ and $α (1 \le n \le 10^{4}, 2 \le m \le 10^{4}, 1 \le α < 90)$ . The second line contains $n$ integers $h_{i}$ -- the heights of the towers $(1 \le h_{i} \le 10^{3}).$ The following $m$ lines contain pairs $x_{i}, y_{i}$ -- the coordinates of the vertices of the landscape $(|x_{i}| \le 10^{5}, x_{i} < x_{i+1}, |y_{i}| \le 10^{3}).$

## 输出格式

On the first line output the maximal possible summary length of towers that can be illuminated by the sun with an absolute precision of at least $10^{-6}.$ On the next $n$ lines output the x-coordinates of the points where the towers should be mounted to achieve this maximum with an absolute precision of at least $10^{-9}.$ Towers should be listed in the same order they are given in the input file.

## 样例 #1

### 样例输入 #1

```
5 4 10
20 10 20 15 10
0 10
40 20
50 0
70 30
```

### 样例输出 #1

```
52.342888649592545
16.0
0.0
70.0
65.3
65.3
```

## 提示

Time limit: 1 s, Memory limit: 128 MB.、

## 题解
首先，我们需要注意到下面的一个结论：**我们的每一个信号塔一定是放在我们的折线的顶点**。


考虑将所有塔被光照到的部分沿着光线平移至 $x=x_1$ 处，那么塔 $i$ 就在这条线的最高处，并且不难发现，此时最多能被覆盖的长度即为这条线的最高处到 $(x_1,y_1)$ 之间的长度，即存在一个显然的上界为： $\min\{(x_j-x_1)\tan\alpha+y_j-y_1+h_i,\sum_kh_k\}$,不难发现这个上界是可以取到的，我们只需要先确定
最高点后念小埴就可以了。

```
typedef long double ff;
const int N = 1e4 + 5;
const ff PI = acos(-1), EPS1 = 1e-20, EPS2 = 1e-6, INF = 1e20;

int n, m, h[N], X[N], Y[N]; ff alpha, pos[N];
ff GetHeight(int i) { return (X[i] - X[1]) * tan(alpha) + (Y[i] - Y[1]); }
ff Ints(int x_0, int y_0, int i) {
	ff k_1 = (Y[i + 1] - Y[i]) / (ff)(X[i + 1] - X[i]), k_2 = -tan(alpha),
		b_1 = -k_1 * X[i] + Y[i], b_2 = -k_2 * x_0 + y_0;
	return (b_2 - b_1) / (k_1 - k_2 + EPS1);
}
bool Check(int x_0, int y_0, int i) {
	ff x_ints = Ints(x_0, y_0, i);
	return x_ints > X[i] - EPS2 && x_ints < X[i + 1] + EPS2;
}

int main() {
	rd(n, m, alpha); alpha *= PI / 180;
	int h_sum = 0, h_mx = 0, h_mx_id = 0;
	for(int i = 1; i <= n; ++i) {
		rd(h[i]); h_sum += h[i];
		if(h[i] > h_mx) {
			h_mx = h[i];
			h_mx_id = i;
		}
	}
	for(int i = 1; i <= m; ++i) rd(X[i], Y[i]);
	ff ans = -INF;
	for(int i = 1; i <= m; ++i) {
		ff i_h = GetHeight(i);
		if(i_h > ans) {
			ans = i_h;
			pos[h_mx_id] = X[i];
		}
	}
	ans += h_mx;
	ans = std::min(ans, (ff)h_sum);
	int cur_y = Y[1];
	for(int i = 1, j = 1; i <= n; ++i) {
		if(i == h_mx_id) continue;
		for(; j < m - 1 && !Check(X[1], cur_y, j); ++j);
		pos[i] = std::max(std::min(Ints(X[1], cur_y, j), (ff)X[m]), (ff)X[1]);
		cur_y += h[i];
	}
	printf("%.15LF\n", ans);
	for(int i = 1; i <= n; ++i)
		printf("%.15LF\n", pos[i]);
	return 0;
}

```