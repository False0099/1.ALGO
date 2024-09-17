There are several ancient Greek texts that contain descriptions of the fabled island Atlantis. Some of these texts even include maps of parts of the island. But unfortunately, these maps describe different regions of Atlantis. Your friend Bill has to know the total area for which maps exist. You (unwisely) volunteered to write a program that calculates this quantity.  

Input

The input file consists of several test cases. Each test case starts with a line containing a single integer n (1<=n<=100) of available maps. The n following lines describe one map each. Each of these lines contains four numbers x1;y1;x2;y2 (0<=x1<x2<=100000;0<=y1<y2<=100000), not necessarily integers. The values (x1; y1) and (x2;y2) are the coordinates of the top-left resp. bottom-right corner of the mapped area.  
  
The input file is terminated by a line containing a single 0. Don’t process it.

Output

For each test case, your program should output one section. The first line of each section must be “Test case k”, where k is the number of the test case (starting with 1). The second one must be “Total explored area: a”, where a is the total explored area (i.e. the area of the union of all rectangles in this test case), printed exact to two digits to the right of the decimal point.  
  
Output a blank line after each test case.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>10 10 20 20<br>15 15 25 25.5<br>0|Test case #1<br>Total explored area: 180.00|