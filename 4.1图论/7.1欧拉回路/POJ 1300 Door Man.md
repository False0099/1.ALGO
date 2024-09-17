You are a butler in a large mansion. This mansion has so many rooms that they are merely referred to by number (room 0, 1, 2, 3, etc...). Your master is a particularly absent-minded lout and continually leaves doors open throughout a particular floor of the house. Over the years, you have mastered the art of traveling in a single path through the sloppy rooms and closing the doors behind you. Your biggest problem is determining whether it is possible to find a path through the sloppy rooms where you:  

  
2. Always shut open doors behind you immediately after passing through  
    
3. Never open a closed door  
    
4. End up in your chambers (room 0) with all doors closed  
    

  
In this problem, you are given a list of rooms and open doors between them (along with a starting room). It is not needed to determine a route, only if one is possible.  

Input

Input to this problem will consist of a (non-empty) series of up to 100 data sets. Each data set will be formatted according to the following description, and there will be no blank lines separating data sets.  
A single data set has 3 components:  

  
2. Start line - A single line, "START M N", where M indicates the butler's starting room, and N indicates the number of rooms in the house (1 <= N <= 20).  
    
3. Room list - A series of N lines. Each line lists, for a single room, every open door that leads to a room of higher number. For example, if room 3 had open doors to rooms 1, 5, and 7, the line for room 3 would read "5 7". The first line in the list represents room 0. The second line represents room 1, and so on until the last line, which represents room (N - 1). It is possible for lines to be empty (in particular, the last line will always be empty since it is the highest numbered room). On each line, the adjacent rooms are always listed in ascending order. It is possible for rooms to be connected by multiple doors!  
    
4. End line - A single line, "END"  
    

  
Following the final data set will be a single line, "ENDOFINPUT".  
  
Note that there will be no more than 100 doors in any single data set.

Output

For each data set, there will be exactly one line of output. If it is possible for the butler (by following the rules in the introduction) to walk into his chambers and close the final open door behind him, print a line "YES X", where X is the number of doors he closed. Otherwise, print "NO".

Sample

|Inputcopy|Outputcopy|
|---|---|
|START 1 2<br>1<br><br>END<br>START 0 5<br>1 2 2 3 3 4 4<br><br><br><br><br>END<br>START 0 10<br>1 9<br>2<br>3<br>4<br>5<br>6<br>7<br>8<br>9<br><br>END<br>ENDOFINPUT|YES 1<br>NO<br>YES 10|

## 题解
我们这一题就是判断我们从某个点出发是否有到达某固定点的欧拉路径，如果存在，我们就输出我们的长度，否则，我们输出不存在。我们这一题仍然是模板级别的题目，所以我们就可以用我们的并查集来连接即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstring>
#include <queue>
#include <set>
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
#define PI acos(-1.0)
#define Max 2505
#define inf 1<<28
#define LL(x) ( x << 1 )
#define RR(x) ( x << 1 | 1 )
#define REP(i,s,t) for( int i = ( s ) ; i <= ( t ) ; ++ i )
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define mp(a,b) make_pair(a,b)
#define PII pair<int,int>
using namespace std;


inline void RD(int &ret) {
    char c;
    do {
        c = getchar();
    } while(c < '0' || c > '9') ;
    ret = c - '0';
    while((c=getchar()) >= '0' && c <= '9')
        ret = ret * 10 + ( c - '0' );
}
inline void OT(int a){
    if(a >= 10)OT(a / 10) ;
    putchar(a % 10 + '0') ;
}
#define N 1111
char in[111] ;
int degree[N] ;
int main() {
    while(cin >> in){
        if(in[0] == 'E')break ;
        mem(degree , 0) ;
        int n , m ;
        cin >> n >> m ;
        getchar() ;
        int sum = 0 ;
        for (int i = 0 ; i < m ;i ++ ){
            int now ;
            gets(in) ;
            int l = strlen(in) ;
            if(!l)continue ;
            int num = 0 ;
            for (int j = 0  ;j < l ;j ++ ){
                if(in[j] == ' '){
                    degree[i] ++ ;
                    degree[num] ++ ;
                    sum ++ ;
                    num = 0 ;
                }
                else {
                    num = num * 10 + (in[j] - '0') ;
                }
            }
            if(num){
                degree[i] ++ ;
                degree[num] ++ ;
                sum ++ ;
            }
        }
        cin >> in ;
        int odd = 0 ;
        int even = 0 ;
        for (int i = 0 ; i < m ; i ++ ){
            if(degree[i] & 1)odd ++ ;
            else even ++ ;
        }
        if(!odd){
            if(n == 0){
                printf("YES %d\n",sum) ;
            }
            else {
                puts("NO") ;
            }
        }
        else {
            if(odd == 2){
                if((degree[n] & 1) && (degree[0] & 1) && (n != 0)){
                    printf("YES %d\n" ,sum) ;
                }
                else {
                    puts("NO") ;
                }
            }else {
                puts("NO") ;
            }
        }
    }
    return 0 ;
}
```