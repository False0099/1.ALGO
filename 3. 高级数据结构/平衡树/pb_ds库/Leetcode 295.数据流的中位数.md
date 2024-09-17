**中位数**是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。

- 例如 `arr = [2,3,4]` 的中位数是 `3` 。
- 例如 `arr = [2,3]` 的中位数是 `(2 + 3) / 2 = 2.5` 。

实现 MedianFinder 类:

- `MedianFinder()` 初始化 `MedianFinder` 对象。
    
- `void addNum(int num)` 将数据流中的整数 `num` 添加到数据结构中。
    
- `double findMedian()` 返回到目前为止所有元素的中位数。与实际答案相差 `10-5` 以内的答案将被接受。
    

**示例 1：**

**输入**
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
**输出**
[null, null, null, 1.5, null, 2.0]

**解释**
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0

**提示:**

- `-105 <= num <= 105`
- 在调用 `findMedian` 之前，数据结构中至少有一个元素
- 最多 `5 * 104` 次调用 `addNum` 和 `findMedian`

## 题解
我们这一题很显然，我们可以用一个堆来解决我们的问题，或者用我们的平衡树来解决我们的问题，在这里，我们呢选择用我们的平衡树，并且，因为我们本题的操作相对简单，所以我们可以考虑用我们的库函数来解决我们的问题。

```cpp
#include <bits/stdc++.h>

#include<ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

using namespace std;

template<typename T>

using ordered_multiset=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

  

class MedianFinder {

public:

    ordered_multiset<int> tr;

    MedianFinder() {

  

    }

    void addNum(int num) {

        tr.insert(num);

    }

    double findMedian() {

        int n=tr.size();

        if(n%2!=0){

            return 1.0*(*tr.find_by_order(n/2));

        }

        return 0.5*(*tr.find_by_order(n/2-1)+*tr.find_by_order(n/2));

    }

};

  

/**

 * Your MedianFinder object will be instantiated and called as such:

 * MedianFinder* obj = new MedianFinder();

 * obj->addNum(num);

 * double param_2 = obj->findMedian();

 */
```