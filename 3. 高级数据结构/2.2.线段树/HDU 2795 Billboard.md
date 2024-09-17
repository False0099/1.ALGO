At the entrance to the university, there is a huge rectangular billboard of size h * w (h is its height and w is its width). The board is the place where all possible announcements are posted: nearest programming competitions, changes in the dining room menu, and other important information.  
  
On September 1, the billboard was empty. One by one, the announcements started being put on the billboard.  
  
Each announcement is a stripe of paper of unit height. More specifically, the i-th announcement is a rectangle of size 1 * wi.  
  
When someone puts a new announcement on the billboard, she would always choose the topmost possible position for the announcement. Among all possible topmost positions she would always choose the leftmost one.  
  
If there is no valid location for a new announcement, it is not put on the billboard (that's why some programming contests have no participants from this university).  
  
Given the sizes of the billboard and the announcements, your task is to find the numbers of rows in which the announcements are placed.

Input

There are multiple cases (no more than 40 cases).  
  
The first line of the input file contains three integer numbers, h, w, and n (1 <= h,w <= 10^9; 1 <= n <= 200,000) - the dimensions of the billboard and the number of announcements.  
  
Each of the next n lines contains an integer number wi (1 <= wi <= 10^9) - the width of i-th announcement.

Output

For each announcement (in the order they are given in the input file) output one number - the number of the row in which this announcement is placed. Rows are numbered from 1 to h, starting with the top row. If an announcement can't be put on the billboard, output "-1" for this announcement.

Sample

|Inputcopy|Outputcopy|
|---|---|
|3 5 5<br>2<br>4<br>3<br>3<br>3|1<br>2<br>1<br>3<br>-1|

## 题解
我们这一题的初始思路是进行暴力模拟，每一次，我们从左到右找到我们能容纳下这个海报的第一个位置，然后把这个位置贴上我们的海报，再更新我们的信息。所以我们就需要**维护，每一个区间所能容纳下的最长广告的长度**

我们这一题需要用到一个 mlen 维护我们每一个区间能够装下最长广告的长度，之后我们单点更新的时候顺带返回下表（？）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5+5;

struct Node {
  int l, r;
  int mlen;
};

Node BTree[maxn << 2];
int val[maxn];
int w,h,n;

inline void PushUp(int idx) {
  BTree[idx].mlen = max(BTree[idx << 1].mlen, BTree[idx << 1 | 1].mlen);
}

void bulid(int l, int r, int idx) {
  BTree[idx].l = l;
  BTree[idx].r = r;

  if (l == r) {
    BTree[idx].mlen = w;
    return ;
  }
  int mid = l + (r - l >> 1);
  bulid(l, mid, idx << 1);
  bulid(mid + 1, r, idx << 1 | 1);
  PushUp(idx);
}

//单点更新  返回更新的位置
int update(int num, int idx) {
  if (BTree[idx].l == BTree[idx].r) {
    if (BTree[idx].mlen >= num)
      BTree[idx].mlen -= num;
    else
      return -1;  //特判点
    return BTree[idx].l;
  }
  int flag = -1;
  if (BTree[idx << 1].mlen >= num) {
    flag = update(num, idx << 1);
  } else if (BTree[idx << 1 | 1].mlen >= num) {
    flag = update(num, idx << 1 | 1);
  }
  PushUp(idx);
  return flag;
}

int main() {
  while (scanf("%d%d%d", &h, &w, &n) != EOF) {
    if (h > n) h = n;
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    bulid(1, h, 1);
    for (int i = 1; i <= n; i++) {
      printf("%d\n", update(val[i], 1));
    }
  }
  return 0;
}


```