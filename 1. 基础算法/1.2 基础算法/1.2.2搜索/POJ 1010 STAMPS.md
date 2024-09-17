Have you done any Philately lately?  
  
You have been hired by the Ruritanian Postal Service (RPS) to design their new postage software. The software allocates stamps to customers based on customer needs and the denominations that are currently in stock.  
  
Ruritania is filled with people who correspond with stamp collectors. As a service to these people, the RPS asks that **all stamp allocations have the maximum number of different types of stamps in it**. In fact, the RPS has been known to issue several stamps of the same denomination in order to please customers (these count as different types, even though they are the same denomination). The maximum number of different types of stamps issued at any time is twenty-five.  
  
To save money, the RPS would like to **issue as few duplicate stamps as possible** (given the constraint that they want to issue as many different types). Further, the RPS won't sell more than four stamps at a time.  

## Input

The input for your program will be pairs of positive integer sequences, consisting of two lines, alternating until end-of-file. The first sequence are the available values of stamps, while the second sequence is a series of customer requests. For example:  
  
1 2 3 0 ; three different stamp types  
7 4 0 ; two customers  
1 1 0 ; a new set of stamps (two of the same type)  
6 2 3 0 ; three customers  
  
Note: the comments in this example are *not* part of the data file; data files contain only integers.

## Output

For each customer, you should print the "best" combination that is exactly equal to the customer's needs, with a maximum of four stamps. If no such combination exists, print "none".  
The "best" combination is defined as the maximum number of different stamp types. In case of a tie, the combination with the fewest total stamps is best. If still tied, the set with the highest single-value stamp is best. If there is still a tie, print "tie".  
  
For the sample input file, the output should be:  
  
7 (3): 1 1 2 3  
4 (2): 1 3  
6 ---- none  
2 (2): 1 1  
3 (2): tie  
  
That is, you should print the customer request, the number of types sold and the actual stamps. In case of no legal allocation, the line should look like it does in the example, with four hyphens after a space. In the case of a tie, still print the number of types but do not print the allocation (again, as in the example).Don't print extra blank at the end of each line.  

## Sample

|Inputcopy|Outputcopy|
|---|---|
|1 2 3 0	; three different stamp types<br>7 4 0		; two customers<br>1 1 0		; a new set of stamps (two of the same type)<br>6 2 3 0	; three customers|7 (3): 1 1 2 3 <br>4 (2): 1 3 <br>6 ---- none<br>2 (2): 1 1<br>3 (2): tie|

## 题解
给顾客提供他需要的面值的邮票，需要满足三个条件，种类尽可能多，数量尽可能少，最大面值尽可能大。
我们对于这种搜索题目，枚举每一个人得到什么邮票，并且我们把邮票按照我们的面值排序，优先满足我们的最大面值，并且如果不是最后我们都只选一张，这样我们的选择才会更优。并且由于我们有深度限制，所以我们可以采用 DFS 的思路

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> Stamp;   // first: 面值, second: 种类编号

bool lessByTheSecond( const Stamp& a, const Stamp& b ) {
    return a.second < b.second;
}

class Allocator {
    protected:
        vector<Stamp> solution; // 最优解
        int types;  // 最优解中邮票的种类数
        bool tie;   // 是否存在多个最优解
        vector<Stamp> tmpSolution;  // 临时解
    public:
        vector<Stamp> stamps;   // 全部邮票
        int req;    // 需求
    protected:
        void dfs( const int& curPos = 0, const int& curValue = 0, const int& dealt = 0 );   // 核心算法
        void update();  // 更新最优解
    public:
        Allocator();
        void allocate();    // 求解
        void print();   // 打印结果
};

Allocator::Allocator() {
}

void Allocator::dfs( const int& curPos, const int& curValue, const int& dealt ) {
    if( curValue > req ) {
        return;
    }
    if( curValue == req ) {
        update();
    }
    if( dealt == 4 || stamps[curPos].first * ( 4 - dealt ) < req - curValue ) {
        return;
    }
    for( int i = curPos; i < stamps.size(); ++i ) {//枚举我们分配邮票的个数
        tmpSolution.push_back( stamps[i] );
        dfs( i, curValue + stamps[i].first, dealt + 1 );
        tmpSolution.resize( dealt );
    }
}

void Allocator::allocate() {
    // 初始化
    solution.clear();
    tmpSolution.clear();
    types = 0;
    tie = false;
    // 运行核心算法
    dfs();
}

void Allocator::update() {
    // 统计邮票种类数
    int tmpTypes = 1;
    for( int i = 0, j = 1; j < tmpSolution.size(); ++i, ++j ) {
        if( tmpSolution[i].second != tmpSolution[j].second ) {
            ++tmpTypes;
        }
    }
    // 比较邮票种类数 (>)
    if( tmpTypes < types ) {
        return;
    }
    if( tmpTypes == types ) {
        // 比较邮票张数 (<)
        if( tmpSolution.size() > solution.size() ) {
            return;
        }
        if( tmpSolution.size() == solution.size() ) {
            // 比较邮票最高价值 (>)
            if( tmpSolution[0].first < solution[0].first ) {
                return;
            }
            if( tmpSolution[0].first == solution[0].first ) {
                // 三者皆相等则判为平局
                tie = true;
                return;
            }
        }
    }
    // 临时解优胜, 更新最优解
    tie = false;
    solution = tmpSolution;
    types = tmpTypes;
}

void Allocator::print() {
    cout << req;
    if( solution.size() == 0 ) {
        cout << " ---- none";
    } else {
        cout << " (" << types << "):";
        if( tie ) {
            cout << " tie";
        } else {
            sort( solution.begin(), solution.end(), lessByTheSecond );  // 依邮票编号从小到大排序
            for( vector<Stamp>::const_iterator pos = solution.begin(); pos < solution.end(); ++pos ) {
                cout << " " << pos->first;
            }
        }
    }
    cout << endl;
}

int main() {
    Allocator a;
    while( !cin.eof() ) {
        a.stamps.clear();
        for( int tmp, i = 0; cin >> tmp, tmp != 0; ++i ) {
            a.stamps.push_back( Stamp( tmp, i ) );
        }
        sort( a.stamps.begin(), a.stamps.end(), greater<Stamp>() ); // 依邮票价值从大到小排序
        while( cin >> a.req && a.req != 0 ) {
            a.allocate();
            a.print();
        }
    }
}
```