//Catalan
template<typename T>
struct Catalan{
    T c=1;
    T C(int x, int y){
        T m;
        if( x < 0 || y < 0 || y > x ){
            m = 0;
        }
        else if( y == 0 ){
            m = 1;
        }
        else if( y > x / 2 ){
            y = x - y;
            m = C( x , y );
        }
        else{
            m = C( x - 1, y - 1)*x / y;
        }
        return m;
    };

    T query1(int n){
        for(int i=1;i<=n;i++){
            c=c*(4*i-2)/(i+1);
        }
        return c;
    } 
    T query2(int n,int m){
        return C(n+m,n)-C(n+m,m-1);
    }
    T query3(int n){
        return C(2*n,n)/(n+1);
    }
};