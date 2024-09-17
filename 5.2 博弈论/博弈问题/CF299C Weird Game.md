Yaroslav, Andrey and Roman can play cubes for hours and hours. But the game is for three, so when Roman doesn't show up, Yaroslav and Andrey play another game.

Roman leaves a word for each of them. Each word consists of 2·_n_ binary characters "0" or "1". After that the players start moving in turns. Yaroslav moves first. During a move, a player must choose an integer from 1 to 2·_n_, which hasn't been chosen by anybody up to that moment. Then the player takes a piece of paper and writes out the corresponding character from his string.

Let's represent Yaroslav's word as _s_ = _s_1_s_2... _s_2_n_. Similarly, let's represent Andrey's word as _t_ = _t_1_t_2... _t_2_n_. Then, if Yaroslav choose number _k_ during his move, then he is going to write out character _s__k_ on the piece of paper. Similarly, if Andrey choose number _r_ during his move, then he is going to write out character _t__r_ on the piece of paper.

The game finishes when no player can make a move. After the game is over, Yaroslav makes some integer from the characters written on his piece of paper (Yaroslav can arrange these characters as he wants). Andrey does the same. The resulting numbers can contain leading zeroes. The person with the largest number wins. If the numbers are equal, the game ends with a draw.

You are given two strings _s_ and _t_. Determine the outcome of the game provided that Yaroslav and Andrey play optimally well.

Input

The first line contains integer _n_ (1 ≤ _n_ ≤ 106). The second line contains string _s_ — Yaroslav's word. The third line contains string _t_ — Andrey's word.

It is guaranteed that both words consist of 2·_n_ characters "0" and "1".

Output

Print "First", if both players play optimally well and Yaroslav wins. If Andrey wins, print "Second" and if the game ends with a draw, print "Draw". Print the words without the quotes.

Sample 1

|Inputcopy|Outputcopy|
|---|---|
|2<br>0111<br>0001|First|

Sample 2

|Inputcopy|Outputcopy|
|---|---|
|3<br>110110<br>001001|First|

Sample 3

|Inputcopy|Outputcopy|
|---|---|
|3<br>111000<br>000111|Draw|

Sample 4

|Inputcopy|Outputcopy|
|---|---|
|4<br>01010110<br>00101101|First|

Sample 5

|Inputcopy|Outputcopy|
|---|---|
|4<br>01100000<br>10010011|Second|

## 题解
我们这一题采用我们贪心的思路，如果能先手拿到让对面拿不了 1 的操作，那么这个操作一定能让我们获得最优，因此我们只需要贪心的即可。

