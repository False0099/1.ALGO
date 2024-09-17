You're in space.  
You want to get home.  
There are asteroids.  
You don't want to hit them.  

## Input

Input to this problem will consist of a (non-empty) series of up to 100 data sets. Each data set will be formatted according to the following description, and there will be no blank lines separating data sets.  
  
A single data set has 5 components:  
  
Start line - A single line, "START N", where 1 <= N <= 10.  
  
Slice list - A series of N slices. Each slice is an N x N matrix representing a horizontal slice through the asteroid field. Each position in the matrix will be one of two values:  
  
'O' - (the letter "oh") Empty space  
  
'X' - (upper-case) Asteroid present  
  
Starting Position - A single line, "A B C", denoting the <A,B,C> coordinates of your craft's starting position. The coordinate values will be integers separated by individual spaces.  
  
Target Position - A single line, "D E F", denoting the <D,E,F> coordinates of your target's position. The coordinate values will be integers separated by individual spaces.  
  
## End line - A single line, "END"  
  
The origin of the coordinate system is <0,0,0>. Therefore, each component of each coordinate vector will be an integer between 0 and N-1, inclusive.  
  
The first coordinate in a set indicates the column. Left column = 0.  
  
The second coordinate in a set indicates the row. Top row = 0.  
  
The third coordinate in a set indicates the slice. First slice = 0.  
  
Both the Starting Position and the Target Position will be in empty space.  
  

## Output

For each data set, there will be exactly one output set, and there will be no blank lines separating output sets.  
  
A single output set consists of a single line. If a route exists, the line will be in the format "X Y", where X is the same as N from the corresponding input data set and Y is the least number of moves necessary to get your ship from the starting position to the target position. If there is no route from the starting position to the target position, the line will be "NO ROUTE" instead.  
  
A move can only be in one of the six basic directions: up, down, left, right, forward, back. Phrased more precisely, a move will either increment or decrement a single component of your current position vector by 1.  
  

## Sample

| Inputcopy                                                                                                                                                                                                                                                                                                                                                                                                     | Outputcopy            |
| ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------- |
| START 1<br>O<br>0 0 0<br>0 0 0<br>END<br>START 3<br>XXX<br>XXX<br>XXX<br>OOO<br>OOO<br>OOO<br>XXX<br>XXX<br>XXX<br>0 0 1<br>2 2 1<br>END<br>START 5<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>XXXXX<br>XXXXX<br>XXXXX<br>XXXXX<br>XXXXX<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>OOOOO<br>0 0 0<br>4 4 4<br>END | 1 0<br>3 4<br>NO ROUT |


## 题解
已知起点 (A, B, C)和终点（D, E, F）求三维空间最短路径。这一题很简答，我们只需要从我们的起点开始 bfs 更新我们的最短距离，可以用 dij 或堆优化都可以。
```cpp
#include <iostream>
#include <queue>
using namespace std;
const int MAXN=15;
int N,x,y,z,ax,ay,az,tot,flag;
#define Check(a,b,c) (a>=0&&a<N&&b>0&&b<N&&c>0&&c<N)
//宏定义检验移动过程中是否在范围内
struct node{int x,y,z;int step=0;};
//会出现警告，不让在类内初始化非静态数据成员，不过没大问题。
char Data[MAXN][MAXN][MAXN];
int dir[6][3]={{0,0,1},{0,1,0},{1,0,0},{0,0,-1},{0,-1,0},{-1,0,0}};
//用dir数组来控制移动方向
void bfs(){
    flag=false;
    queue<node> q;
    node start,next;
    start.x=x;start.y=y;start.z=z;
    q.push(start);
    while(!q.empty()){
        start=q.front();
        q.pop();
        if(start.x==ax&&start.y==ay&&start.z==az){
            flag=true;
            tot=next.step;
            return;
        }
        \
        for(int i=0;i<6;i++){
            next.x=start.x+dir[i][0];
            next.y=start.y+dir[i][1];
            next.z=start.z+dir[i][2];
            
            if(Check(next.x,next.y,next.z)&&Data[next.x][next.y][next.z]=='O'){
                
                if(next.x==ax&&next.y==ay&&next.z==az){
                    flag=true;
                    tot=next.step+1;
                    return;
                }
                Data[next.x][next.y][next.z]='X';
                next.step=start.step+1;
                q.push(next);
            }
        }
    }
}
int main(){
    string s;
    while(cin>>s>>N){
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                for(int k=0;k<N;k++)
                    cin>>Data[k][j][i];
        cin>>x>>y>>z>>ax>>ay>>az;
        cin>>s;
        bfs();
        if(flag)
        cout<<N<<" "<<tot<<endl;
        else cout<<"NO ROUTE"<<endl;
    }
    //system("pause");
    return 0;
}

```