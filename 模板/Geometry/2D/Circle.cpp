const double eps = 1e-8,PI = acos(-1);
struct Point{
    double x,y;
};

struct Circle{
    Point o;
    double r;
    Circle(){}
    Circle(double x,double y,double r):o({x,y}),r(r){}
    Circle(Point o,double r):o(o),r(r){}
};

Point operator+(Point a,Point b){
	return {a.x+b.x, a.y+b.y};
}

Point operator-(Point a,Point b){
	return {a.x-b.x, a.y-b.y};
}
//叉乘
double operator*(Point a,Point b){
	return a.x*b.y - a.y*b.x;	
}
//数乘
Point operator*(Point a,double b){
	return {a.x*b, a.y*b};
}

Point operator/(Point a,double b){
	return {a.x/b, a.y/b};
}
//两个double数比大小，相等返回0，小于返回-1，大于返回1
int judge(double a,double b){
	if(fabs(a-b) < eps)
		return 0;
	if(a < b)
		return -1;
	return 1;
}
//向量a旋转b°后的向量
Point rotate(Point a,double b){
	return {a.x*cos(b)+a.y*sin(b), -a.x*sin(b)+a.y*cos(b)};
}
//求两点距离
double lens(Point a,Point b){
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}
//求两直线交点
Point intersection(Point p,Point v,Point q,Point w)	{
	Point u = p - q;
	double t = w*u / (v*w);
	return p + v*t;
}
//求两点中垂线
pair<Point,Point> bisector(Point a,Point b)	{
	Point p = (a+b) / 2;	
	Point v = rotate(b-a,PI/2);	
	return {p,v};		
}
//已知三点，求外接圆
Circle circle(Point a,Point b,Point c)	{
	auto n = bisector(a,b),m = bisector(a,c);
	Point o = intersection(n.first,n.second,m.first,m.second);	
	double r = lens(o,a);	
	return {o,r};	
}

Circle min_cover_circle(vector<Point> p){
	random_shuffle(p.begin(),p.end());
	Circle c = {p[0],0};
    int n=p.size();	
	for(int i = 1;i < n;i++){
		if(judge(c.r,lens(c.o,p[i])) == -1){
			c = {p[i],0};			
			for(int j = 0;j < i;j++){
				if(judge(c.r,lens(c.o,p[j])) == -1){
					c = {(p[i]+p[j])/2,lens(p[i],p[j])/2};
					for(int k = 0;k < j;k++){
						if(judge(c.r,lens(c.o,p[k])) == -1){
							c = circle(p[i],p[j],p[k]);	
                        }
					}
				}
			}
		}
	}
    return c;
}



//with my2Dplate
struct Circle{
    Point o;
    double r;
    Circle(){}
    Circle(double x,double y,double r):o({x,y}),r(r){}
    Circle(Point o,double r):o(o),r(r){}
};
int judge(double a,double b){
	if(equal(a,b)){return 0;}
	else if(a<b){return -1;}
	else{return 1;}
}
Point rotate(Point a,double b){return {a.x*cos(b)+a.y*sin(b), -a.x*sin(b)+a.y*cos(b)};}
Point intersection(Line l1,Line l2)	{
	Point u = l1.a - l2.a;
	double t = cross(l2.b,u) / cross(l1.b,l2.b);
	return l1.a + l1.b*t;
}
Line bisector(Point a,Point b)	{
	Point p = (a+b) / 2;	
	Point v = rotate(b-a,PI/2);	
	return {p,v};		
}
Circle circle(Point a,Point b,Point c)	{
	auto n = bisector(a,b),m = bisector(a,c);
	Point o = intersection(n,m);
	double r = dis(o,a);	
	return {o,r};	
}
Circle min_cover_circle(vector<Point> p){
	random_shuffle(p.begin(),p.end());
	Circle c = {p[0],0};
    int n=p.size();	
	for(int i = 1;i < n;i++){
		if(judge(c.r,dis(c.o,p[i])) == -1){
			c = {p[i],0};			
			for(int j = 0;j < i;j++){
				if(judge(c.r,dis(c.o,p[j])) == -1){
					c = {(p[i]+p[j])/2,dis(p[i],p[j])/2};
					for(int k = 0;k < j;k++){
						if(judge(c.r,dis(c.o,p[k])) == -1){
							c = circle(p[i],p[j],p[k]);	
                        }
					}
				}
			}
		}
	}
    return c;
}