You want to hold a party. Here's a polygon-shaped cake on the table. You'd like to cut the cake into several triangle-shaped parts for the invited comers. You have a knife to cut. The trace of each cut is a line segment, whose two endpoints are two vertices of the polygon. Within the polygon, any two cuts ought to be disjoint. Of course, the situation that only the endpoints of two segments intersect is allowed.

The cake's considered as a coordinate system. You have known the coordinates of vexteces. Each cut has a cost related to the coordinate of the vertex, whose formula is costi, j = |xi + xj| * |yi + yj| % p. You want to calculate the minimum cost.

**NOTICE: input assures that NO three adjacent vertices on the polygon-shaped cake are in a line. And the cake is not always a convex.**

#### Input

There're multiple cases. There's a blank line between two cases. The first line of each case contains two integers, N and p (3 ≤ N, p ≤ 300), indicating the number of vertices. Each line of the following N lines contains two integers, x and y (-10000 ≤ x, y ≤ 10000), indicating the coordinate of a vertex. You have known that no two vertices are in the same coordinate.

#### Output

If the cake is not convex polygon-shaped, output "I can't cut.". Otherwise, output the minimum cost.

#### Sample

|Inputcopy|Outputcopy|
|---|---|
|3 3<br>0 0<br>1 1<br>0 2|0|


## 题解
