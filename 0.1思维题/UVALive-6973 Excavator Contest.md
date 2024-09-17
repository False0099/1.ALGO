## 题目描述
•输入一个整数 n(n<=512)，输出一个 n * n 网格中的哈密顿道路（起点和终点任意），使得至少转弯 n(n-1)-1次。只能左转或者右转。


Bluefly University is famous of excavator technology. Lots of students take part in many excavator-related courses. After the students finish their courses, they will compete in a contest called International Collegiate Excavator Contest (ICEC). This year’s ICEC will be held at Marjar University. This is an individual competition that each contestant will start the match one by one. The task of the contest is to drive an excavator passing a square field. The judge partitioned the field into N × N equal-sized square chunks. Each chunk should be visited exactly one time. The contestant will drive the excavator, starting from and ending at the center of two different boundary chunks. In order to show off their superb excavator operating skills, the contestants need to drive the excavator with as many as possible turnings. Since the excavator is a kind of large and heavy vehicle, it can only make a turn to left or right at the center of any chunk. Bob is a student from Marjar University. He wants to win the contest. To fulfill this dream, he needs to drive the excavator with at least N × (N − 1) − 1 turnings. It seems to be a difficult task, so he turns to you for help. Please write a program to find a feasible route for him

## 输入格式

There are multiple test cases. The first line of input contains an integer T indicating the number of test cases. For each test case: There is only one integer N (2 ≤ N ≤ 512).

## 输出格式

For each test case, output a matrix with N × N integers indicating the route to pass all the chunks. Bob will drive the excavator passing the chunks in the order of 1, 2, . . . , N2 . If there are multiple solutions, any one will be acceptable.

## 样例 #1

### 样例输入 #1

```
2 4 3
```

### 样例输出 #1

```
2 1 16 15 3 4 13 14 6 5 12 11 7 8 9 10 1 2 3 8 7 4 9 6 5
```

## 题解
这是一道 ACM 冠军级别的构造题，我们的偶数构造应该如下图所示 ![[Pasted image 20230912165133.png]]

我们**奇数**的构造应该如下![[Pasted image 20230912165153.png]]

## 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
const int maxn = 550;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
 
//const int G[5][50] = {{0}, {0}, {3, 4, 2, 1}, {5, 6, 9, 4, 7, 8, 3, 2, 1}};
 
const int dir_down[4][4][4] = { {{3, 1, 2, 1}, {3, 3, 0, 3}, {1, 3, 0, 3}, {1, 3, 0, 0}},
    {{2, 1, 3, 1}, {2, 1, 3, 3}, {0, 3, 1, 3}, {3, 0, 2, 0}}, 
    {{3, 1, 2, 1}, {1, 3, 0, 3}, {1, 3, 0, 0}} };
 
const int dir_left[5][4] = { {1, 2, 0, 2}, {1, 2, 0, 2}, {2, 1, 3, 1}, {0, 2, 1, 2}, {0, 2, 1, 1}};
const int dir_up[5][4] = { {2, 0, 3, 0}, {2, 0, 3, 0}, {0, 2, 1, 2}, {3, 0, 2, 0}, {3, 0, 2, 2} };
 
int L, R, g[maxn][maxn];
 
void put(int n);
 
inline void jump(int n, int& x, int& y, int& mv, int len, const int d[4]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            g[x][y] = mv;
            mv += len;
            x += dir[d[j]][0];
            y += dir[d[j]][1];
        }
    }
}
 
inline void moveup(int n, int& x, int& y, int& mv, int len) {
    //printf("moveup:%d\n", len);
    if (n&1) {
        jump(n / 2 - 1, x, y, mv, len, dir_up[0]);
        for (int t = 0; t < 2; t++) {
            g[x][y] = mv;
            x += dir[2][0];
            y += dir[2][1];
            mv += len;
        }
    } else if ((n/2) % 4) {
        jump(n / 2 - 2, x, y, mv, len, dir_up[1]);
        jump(1, x, y, mv, len, dir_up[2]);
    } else {
        jump(n / 2 - 2, x, y, mv, len, dir_up[3]);
        jump(1, x, y, mv, len, dir_up[4]);
    }
}
 
inline void moveleft(int n, int& x, int& y, int& mv, int len) {
    //printf("moveleft:%d\n", len);
    if (n&1) {
        jump(n / 2, x, y, mv, len, dir_left[0]);
        for (int t = 0; t < 2; t++) { // down twice;
            g[x][y] = mv;
            x += dir[1][0];
            y += dir[1][1];
            mv += len;
        }
    } else if ((n/2) % 4) {
        jump(n / 2 - 1, x, y, mv, len, dir_left[1]);
        jump(1, x, y, mv, len, dir_left[2]);
    } else {
        jump(n / 2 - 1, x, y, mv, len, dir_left[3]);
        jump(1, x, y, mv, len, dir_left[4]);
    }
}
 
inline void movedown(int n, int& x, int& y, int& mv, int len) {
    int p;
 
    //printf("movedown!\n");
    if (n&1) {
        for (int k = 0; k < 4; k++) {
            if (k == 0) p = n / 2;
            else if (k == 1 || k == 3) p = 1;
            else p = n / 2 - 2;
            jump(p, x, y, mv, len, dir_down[0][k]);
        }
    } else if ((n/2) % 4 == 1) {
        for (int k = 0; k < 4; k++) {
            if (k == 0) p = n / 2 - 1;
            else if (k == 1 || k == 3) p = (n == 2 && k == 3 ? 0 : 1);
            else p = max(n / 2 - 2, 0);
            jump(p, x, y, mv, len, dir_down[1][k]);
        }
    } else {
        for (int k = 0; k < 3; k++) {
            if (k == 0 || k == 1) p = n / 2 - 1;
            else p = 1;
            jump(p, x, y, mv, len, dir_down[2][k]);
        }
    }
}
 
void solve (int n, int sx, int sy, int ex, int ey, int flag) {
    if (n <= 1) {
        if (n == 1)
            g[sx][sy] = L;
        return;
    } 
 
    /*
    printf("%d:\n", n);
    put(10);
    */
 
    if (n&1) {
        if ((n/2)&1) {
            if (flag) {
                moveup(n, sx, sy, L, 1);
                moveleft(n, ex, ey, R, -1);
            } else {
                moveup(n, ex, ey, R, -1);
                moveleft(n, sx, sy, L, 1);
            }
            solve(n - 2, sx, sy, ex, ey, flag);
        } else {
            if (flag)
                movedown(n, ex, ey, R, -1);
            else 
                movedown(n, sx, sy, L, 1);
            solve(n - 2, sx, sy, ex, ey, flag^1);
        }
    } else {
        if ((n/2)&1) {
            if (flag)
                movedown(n, ex, ey, R, -1);
            else
                movedown(n, sx, sy, L, 1);
            solve(n - 2, sx, sy, ex, ey, flag^1);
        } else {
            if (flag) {
                moveup(n, sx, sy, L, 1);
                moveleft(n, ex, ey, R, -1);
            } else {
                moveup(n, ex, ey, R, -1);
                moveleft(n, sx, sy, L, 1);
            }
            solve(n - 2, sx, sy, ex, ey, flag);
        }
    }
}
 
void put (int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d", g[i][1]);
        for (int j = 2; j <= n; j++)
            printf(" %d", g[i][j]);
        printf("\n");
    }
}
 
int main () {
    int cas, n;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d", &n);
 
        int sx, sy, ex, ey, flag;
        L = 1, R = n * n;
 
        if (n&1) {
            if ((n/2)&1)
                ex = 1, ey = sx = sy = n, flag = 1;
            else
                sx = sy = ex = 1, ey = n, flag = 0;
        } else {
            int t = n / 2;
            t = (t - 1) % 4 + 1;
            if (t == 1)
                sx = 1, sy = ex = 2, ey = n, flag = 0;
            else if (t == 2)
                sx = sy = ey = n, ex = 1, flag = 1;
            else if (t == 3)
                sx = sy = ex = 1, ey = n, flag = 0;
            else
                sx = ey = n, sy = n - 1, ex = 2, flag = 1;
        }
 
        //printf("%d %d %d %d %d!!!\n", sx, sy, ex, ey, flag);
        solve(n, sx, sy, ex, ey, flag);
        put(n);
    }
    return 0;
}
```