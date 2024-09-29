What is done is done, and the spoilt milk cannot be helped.

Little John is as little as night is day — he was known to be a giant, at possibly $2.1$ metres tall. It has everything to do with his love for milk.

His dairy diary has $n$ entries, showing that he acquired $a_i$ pints of fresh milk on day $d_i$. Milk declines in freshness with time and stays drinkable for a maximum of $k$ days. In other words, fresh milk acquired on day $d_i$ will be drinkable between days $d_i$ and $d_i+k-1$ inclusive.

Every day, Little John drinks drinkable milk, up to a maximum of $m$ pints. In other words, if there are less than $m$ pints of milk, he will drink them all and not be satisfied; if there are at least $m$ pints of milk, he will drink exactly $m$ pints and be satisfied, and it's a milk satisfaction day.

Little John always drinks **the freshest** drinkable milk first.

Determine the number of milk satisfaction days for Little John.

**Input**

The first line of the input contains a single integer $t$ ($1\leq t \leq 10^4$), the number of test cases.

The first line of each test case consists of three integers $n$, $m$, $k$ ($1\le n$, $m$, $k \le 10^5$), the number of diary entries, the maximum pints needed for a milk satisfaction day, and the duration of milk's freshness.

Then follow $n$ lines of each test case, each with two integers $d_i$ and $a_i$ ($1\le d_i$, $a_i \le 10^6$), the day on which the milk was acquired and the number of pints acquired. They are sorted in increasing values of $d_i$, and all values of $d_i$ are distinct.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

**Output**

For each test case, output a single integer, the number of milk satisfaction days.

## 题解
本题，我们可以通过我们的