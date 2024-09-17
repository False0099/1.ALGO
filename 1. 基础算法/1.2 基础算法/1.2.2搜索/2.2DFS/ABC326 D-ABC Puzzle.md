### Problem Statement

You are given an integer $N$ and strings $R$ and $C$ of length $N$ consisting of `A`, `B`, and `C`. Solve the following problem.

There is a $N \times N$ grid. All cells are initially empty.  
You can write at most one character from `A`, `B`, and `C` in each cell. (You can also leave the cell empty.)

Determine if it is possible to satisfy all of the following conditions, and if it is possible, print one way to do so.

-   Each row and each column contain exactly one `A`, one `B`, and one `C`.
-   The leftmost character written in the $i$ \-th row matches the $i$ \-th character of $R$.
-   The topmost character written in the $i$ \-th column matches the $i$ \-th character of $C$.

### Constraints

-   $N$ is an integer between $3$ and $5$, inclusive.
-   $R$ and $C$ are strings of length $N$ consisting of `A`, `B`, and `C`.

### Input

The input is given from Standard Input in the following format:

```
$N$
$R$
$C$
```

### Output

If there is no way to fill the grid to satisfy the conditions in the problem statement, print `No` in one line.  
Otherwise, print one such way to fill the grid in the following format:

```
Yes
$A_1$
$A_2$
$\vdots$
$A_N$
```

The first line should contain `Yes`. The $i$ \-th of the subsequent $N$ lines should contain a string $A_i$ of length $N$.

-   If the $j$ \-th character of $A_i$ is `.`, it indicates that the cell in the $i$ \-th row from the top and the $j$ \-th column from the left is empty.
-   If the $j$ \-th character of $A_i$ is `A`, it indicates that `A` is written in the cell in the $i$ \-th row from the top and the $j$ \-th column from the left.
-   If the $j$ \-th character of $A_i$ is `B`, it indicates that `B` is written in the cell in the $i$ \-th row from the top and the $j$ \-th column from the left.
-   If the $j$ \-th character of $A_i$ is `C`, it indicates that `C` is written in the cell in the $i$ \-th row from the top and the $j$ \-th column from the left.

If there are multiple correct ways to fill the grid, you may print any of them.

## 题解
我们这一题一眼看得出来我们这一题是剪枝，我们不难发现，我们每一行都是 $ABC..$ 的组合，于是我们就可以枚举我们每一行的排列是什么，这一天我们可以用我们的 $next-permutation$ 来实现，而我们每一行的检验则可以通过我们的如下规则：
1. 我们每一行第一个有效字母必须是我们的 $Ri$，
2. 我们每行最多包含 1 个 A, B, C

```cpp
#include<bits/stdc++.h>

using namespace std;

vector<vector<string>> row(3);
bool fnd=false;
int n;
string r,c;
vector<string> grid;

void dfs(int i,int fl){
  if(fnd){return;}
  if(i==n){
    if(fl==0){
      cout << "Yes\n";
      for(auto &nx : grid){cout << nx << "\n";}
      fnd=true;
    }
    return;
  }
  for(auto &nx : row[r[i]-'A']){
    grid.push_back(nx);

    int ufl=fl;
    bool und=true;
    for(int j=0;j<n;j++){
      if(nx[j]=='.'){continue;}
      int kind=(nx[j]-'A');
      if((fl&(1<<(4*j+kind)))==0){und=false;break;}
      ufl^=(1<<(4*j+kind));
      if((fl&(1<<(4*j+3)))!=0){
        if(nx[j]!=c[j]){und=false;break;}
        ufl^=(1<<(4*j+3));
      }
    }

    if(und){dfs(i+1,ufl);}
    grid.pop_back();
  }
}

int main(){
  cin >> n >> r >> c;
  string abc="ABC";
  while(abc.size()<n){abc.push_back('.');}
  sort(abc.begin(),abc.end());
  do{
    char tg='.';
    for(auto &nx : abc){
      if(nx!='.'){tg=nx;break;}
    }
    row[tg-'A'].push_back(abc);
  }while(next_permutation(abc.begin(),abc.end()));

  dfs(0,(1<<(4*n))-1);
  if(!fnd){cout << "No\n";}
  return 0;
}

```