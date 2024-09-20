using ld = double;
// using ld = long double;
#define eps 1e-7
bool equal(ld x,ld y){
    return fabs(x-y)<eps;
}
struct Point{
    ld x,y;
    Point(ld _x=0,ld _y=0):x(_x),y(_y){}
    Point &operator+=(const Point &p) & {x += p.x;y += p.y;return *this;}
    Point &operator+=(const ld &p) & {x += p;y += p;return *this;}
    Point &operator-=(const Point &p) & {x -= p.x;y -= p.y;return *this;}
    Point &operator-=(const ld &p) & {x -= p;y -= p;return *this;}
    Point &operator*=(const ld &v) & {x *= v;y *= v;return *this;}
    Point &operator/=(const ld &v) & {x /= v;y /= v;return *this;}
    Point operator-() const {return Point(-x, -y);}
    friend Point operator+(Point a, const Point &b) {return a += b;}
    friend Point operator-(Point a, const Point &b) {return a -= b;}
    friend Point operator*(Point a, const ld &b) {return a *= b;}
    friend Point operator/(Point a, const ld &b) {return a /= b;}
    friend Point operator*(const ld &a, Point b) {return b *= a;}
    friend bool operator==(const Point &a, const Point &b) {return a.x == b.x && a.y == b.y;}
    friend bool operator<(Point a, Point b) {
        return equal(a.x, b.x) ? a.y < b.y - eps : a.x < b.x - eps;
    }
    friend bool operator>(Point a, Point b) { return b < a; }
    friend std::istream &operator>>(std::istream &is, Point &p) {return is >> p.x >> p.y;}
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {return os << "(" << p.x << ", " << p.y << ")";}
};
struct Line{
    Point a,b;
    Line(const Point _a=Point(), const Point _b=Point()):a(_a),b(_b){}
    friend auto &operator<<(ostream &os, Line l) {return os << "<" << l.a << ", " << l.b << ">";}
};
ld dot(const Point a, const Point b) {return a.x * b.x + a.y * b.y;}
ld cross(const Point a, const Point b) {return a.x * b.y - a.y * b.x;}
ld square(const Point p) {return dot(p, p);}
ld len(const Point p) {return sqrt(square(p));}
ld len(const Line l) {return len(l.a - l.b);}
ld dis(const Point a, const Point b) {return len(a - b);}
Point lineIntersection(const Line l1, const Line l2) {return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));}
Point norm(const Point p) {if (p==Point()) return p; else return p / len(p);}
bool parallel(const Line &l1, const Line &l2) {return cross(l1.b - l1.a, l2.b - l2.a) == 0;}
Point rotate(const Point a) {return Point(-a.y, a.x);}
ld triangleArea(const Point a,const Point b,const Point c){
    auto u=b-a, v=b-c;
    return fabs(cross((b-a),(b-c)))/2;
}