The famous ACM (Advanced Computer Maker) Company has rented a floor of a building whose shape is in the following figure.  
  

![](https://vj.csgrandeur.cn/a74c8ffcd138148ec900dc6bb09d32dd?v=1694314440)

  
  
The floor has 200 rooms each on the north side and south side along the corridor. Recently the Company made a plan to reform its system. The reform includes moving a lot of tables between rooms. Because the corridor is narrow and all the tables are big, only one table can pass through the corridor. Some plan is needed to make the moving efficient. The manager figured out the following plan: Moving a table from a room to another room can be done within 10 minutes. When moving a table from room i to room j, the part of the corridor between the front of room i and the front of room j is used. So, during each 10 minutes, several moving between two rooms not sharing the same part of the corridor will be done simultaneously. To make it clear the manager illustrated the possible cases and impossible cases of simultaneous moving.  
  

![](https://vj.csgrandeur.cn/bb95b88268c2f9e12a0430067bc6669e?v=1694314440)

  
  
For each room, at most one table will be either moved in or moved out. Now, the manager seeks out a method to minimize the time to move all the tables. Your job is to write a program to solve the manager’s problem.  

## Input

The input consists of T test cases. The number of test cases ) (T is given in the first line of the input. Each test case begins with a line containing an integer N , 1<=N<=200 , that represents the number of tables to move. Each of the following N lines contains two positive integers s and t, representing that a table is to move from room number s to room number t (each room number appears at most once in the N lines). From the N+3-rd line, the remaining test cases are listed in the same manner as above.  

## Output

The output should contain the minimum time in minutes to complete the moving, one per line.  

## Sample

|Inputcopy|Outputcopy|
|---|---|
|3 <br>4 <br>10 20 <br>30 40 <br>50 60 <br>70 80 <br>2 <br>1 3 <br>2 200 <br>3 <br>10 100 <br>20 80 <br>30 50|10<br>20<br>30|

## 题解
将每个输入的起始房间和结束房间转换为房间前面的区间，按区间起始位置从小到大排序。首先取第一个区间，后续如果有区间的起始位置在该区间的终止位置之后，则这两个区间的操作可以同时进行。借用visited[]控制操作的次数，最后输出操作次数值ans。