#include<bits/stdc++.h>
using namespace std;
//乘，加用这个 10000！
const int MAX=10001;
struct HP{
    int num[MAX];
    
    HP&operator=(const char*);
    HP&operator=(int);
    HP();
    HP(int);
    
    bool operator>(const HP&)const;
    bool operator<(const HP&)const;
    bool operator<=(const HP&)const;
    bool operator>=(const HP&)const;
    bool operator!=(const HP&)const;
    bool operator==(const HP&)const;

    HP operator+(const HP&)const;
    HP operator-(const HP&)const;
    HP operator*(const HP&)const;
    HP operator/(const HP&)const;
    HP operator%(const HP&)const;
    
    HP&operator+=(const HP&);
    HP&operator-=(const HP&);
    HP&operator*=(const HP&);
    HP&operator/=(const HP&);
    HP&operator%=(const HP&);
    HP&operator&(const HP&);
    HP&operator&(int);
    HP power(HP x,HP y);
    HP sqrt(HP x,HP y);
};
HP&HP::operator=(const char* c){
    memset(num,0,sizeof(num));
    int n=strlen(c),j=1,k=1;
    for(int i=1;i<=n;i++){
        if(k==10000) j++,k=1;
        num[j]+=k*(c[n-i]-'0');
        k*=10;
    }
    num[0]=j;
    return *this;
}

HP&HP::operator=(int a){
    char s[MAX];
    sprintf(s,"%d",a);
    return *this=s;
}
HP::HP(){
	memset(num,0,sizeof(num)); 
	num[0]=1;
}
HP::HP(int n){
	*this=n;
}

bool HP::operator > (const HP &b) const{
    if(num[0]!=b.num[0]) return num[0]>b.num[0];
    for(int i=num[0];i>=1;i--)
        if(num[i]!=b.num[i])
            return (num[i]>b.num[i]);
    return false;
}
bool HP::operator<(const HP &b)const{return b>*this;}
bool HP::operator<=(const HP &b)const{return !(*this>b);}
bool HP::operator>=(const HP &b)const{return !(b>*this);}
bool HP::operator!=(const HP &b)const{return (b>*this)||(*this>b);}
bool HP::operator==(const HP &b)const{return !(b>*this)&&!(*this>b);}

HP HP::operator+(const HP&b)const{
    HP c;
    c.num[0]=max(num[0],b.num[0]);
    for(int i=1;i<=c.num[0];i++){
        c.num[i]+=num[i]+b.num[i];
        if(c.num[i]>=10000){
            c.num[i]-=10000;
            c.num[i+1]++;
        }
    }
    if(c.num[c.num[0]+1]>0) c.num[0]++;
    return c;
}

HP HP::operator-(const HP&b)const{
   HP c;
   c.num[0]=num[0];
   for (int i=1;i<=c.num[0];i++){
       c.num[i]+=num[i]-b.num[i];
       if(c.num[i]<0){ 
            c.num[i]+=10000;
            c.num[i+1]--;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;
    return c;
}

HP&HP::operator+=(const HP &b){return *this=*this+b;}
HP&HP::operator-=(const HP &b){return *this=*this-b;}

HP HP::operator*(const HP&b)const{
    HP c;
    c.num[0]=num[0]+b.num[0]+1;
    for(int i=1;i<=num[0];i++){
        for(int j=1;j<=b.num[0];j++){
            c.num[i+j-1]+=num[i]*b.num[j];            
            c.num[i+j]+=c.num[i+j-1]/10000;           
            c.num[i+j-1]%=10000;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;   
    return c;
}

HP&HP::operator*=(const HP &b){return *this=*this*b;}
HP HP::operator/(const HP&b)const{
    HP c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        if(d!=0) d.num[0]++;
        d.num[1]=num[i];

        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*HP(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*HP(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--; 
    return c;            
}
HP HP::operator%(const HP&b)const{
    HP c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        if(d!=0) d.num[0]++;
        d.num[1]=num[i];
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*HP(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*HP(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;
    return d;            
}
HP&HP::operator/=(const HP &b){return *this=*this/b;}
HP&HP::operator%=(const HP &b){return *this=*this%b;}
inline HP power(HP x,HP y){
	HP result=1;
	while(y>0){
		if(y%2==1) result=result*x;
		x=x*x;
		y/=2;
	}
	return result;
}
inline HP sqrt(HP x,HP y){
	if(x==1) return x;
	HP l=0,r=x+1;
	while(l<r){
		HP mid=(l+r)/2;
		if(power(mid,y)>x) r=mid;
		else l=mid+1;
	}
	return l-1;
}
inline HP factorial(HP x){
	HP ans=1;
	for(HP i=1;i<=x;i+=1) ans*=i;
	return ans;
}
istream & operator>>(istream &in, HP &n){
    char s[MAX];
    in>>s;
    n=s;
    return in;
}
ostream&operator<<(ostream &o,HP n){
    o<<n.num[n.num[0]];
    for(int i=n.num[0]-1;i>=1;i--){
        o.width(4);
        o.fill('0');
        o<<n.num[i];
    }
    return o;
}
inline HP read(){
	HP ans=0,flag=1;
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*flag;
}


//除，模，取位数 1000！
const int MAXN = 10010;  
struct BInt  
{  
    int len, s[MAXN];  
    BInt () 
    {  
        memset(s, 0, sizeof(s));  
        len = 1;  
    }  
    BInt (int num) { *this = num; }  
    BInt (const char *num) { *this = num; }
    BInt operator = (const int num)  
    {  
        char s[MAXN];  
        sprintf(s, "%d", num);
        *this = s;  
        return *this;
    }  
    BInt operator = (const char *num)  
    {  
        for(int i = 0; num[i] == '0'; num++) ; 
        len = strlen(num);  
        for(int i = 0; i < len; i++) s[i] = num[len-i-1] - '0';
        return *this;
    }  
    BInt operator + (const BInt &b) const
    {  
        BInt c;  
        c.len = 0;  
        for(int i = 0, g = 0; g || i < max(len, b.len); i++)  
        {  
            int x = g;  
            if(i < len) x += s[i];  
            if(i < b.len) x += b.s[i];  
            c.s[c.len++] = x % 10;
            g = x / 10;  
        }  
        return c;  
    }  
    BInt operator += (const BInt &b)
    {  
        *this = *this + b;  
        return *this;  
    }  
    void clean() 
    {  
        while(len > 1 && !s[len-1]) len--; 
    }   
    BInt operator * (const BInt &b)
    {  
        BInt c;  
        c.len = len + b.len;  
        for(int i = 0; i < len; i++)  
        {  
            for(int j = 0; j < b.len; j++)  
            {  
                c.s[i+j] += s[i] * b.s[j];
            }  
        }  
        for(int i = 0; i < c.len; i++) 
        {  
            c.s[i+1] += c.s[i]/10;
            c.s[i] %= 10;
        }  
        c.clean();
        return c;  
    }  
    BInt operator *= (const BInt &b)  
    {  
        *this = *this * b;  
        return *this;  
    }  
    BInt operator - (const BInt &b)
    {  
        BInt c;  
        c.len = 0;  
        for(int i = 0, g = 0; i < len; i++)  
        {  
            int x = s[i] - g;  
            if(i < b.len) x -= b.s[i];  
            if(x >= 0) g = 0; 
            else  
            {  
                g = 1;  
                x += 10;  
            }  
            c.s[c.len++] = x;  
        }  
        c.clean();  
        return c;   
    }  
    BInt operator -= (const BInt &b)  
    {  
        *this = *this - b;  
        return *this;  
    }  
    BInt operator / (const BInt &b)  
    {  
        BInt c, f = 0; 
        for(int i = len-1; i >= 0; i--)  
        {  
            f = f*10;  
            f.s[0] = s[i]; 
            while(f >= b)  
            {  
                f -= b;  
                c.s[i]++;  
            }  
        }  
        c.len = len; 
        c.clean();  
        return c;  
    }  
    BInt operator /= (const BInt &b)  
    {  
        *this  = *this / b;  
        return *this;  
    }  
    BInt operator % (const BInt &b) 
    {  
        BInt r = *this / b;  
        r = *this - r*b;  
        r.clean();
        return r;  
    }  
    BInt operator %= (const BInt &b)  
    {  
        *this = *this % b;  
        return *this;  
    }  
    bool operator < (const BInt &b) 
    {  
        if(len != b.len) return len < b.len;  
        for(int i = len-1; i != -1; i--)  
        {  
            if(s[i] != b.s[i]) return s[i] < b.s[i];  
        }  
        return false;  
    }  
    bool operator > (const BInt &b)  
    {  
        if(len != b.len) return len > b.len;  
        for(int i = len-1; i != -1; i--)  
        {  
            if(s[i] != b.s[i]) return s[i] > b.s[i];  
        }  
        return false;  
    }  
    bool operator == (const BInt &b)  
    {  
        return !(*this > b) && !(*this < b);  
    }  
    bool operator != (const BInt &b)  
    {  
        return !(*this == b);  
    }  
    bool operator <= (const BInt &b)  
    {  
        return *this < b || *this == b;  
    }  
    bool operator >= (const BInt &b)  
    {  
        return *this > b || *this == b;  
    }  
    string str() const
    {  
        string res = "";  
        for(int i = 0; i < len; i++) res = char(s[i]+'0')+res;  
        return res;  
    }  
};  

istream& operator >> (istream &in, BInt &x) 
{  
    string s;  
    in >> s;  
    x = s.c_str(); 
    return in;  
}  

ostream& operator << (ostream &out, const BInt &x) 
{  
    out << x.str();  
    return out;  
}

inline BInt fac(BInt x){
	BInt ans=1;
	for(BInt i=1;i<=x;i+=1) ans*=i;
	return ans;
}
inline BInt qpow(BInt a,BInt b){
    BInt x=a,y=b;
	BInt result=1;
	while(y>=1){
		if(y%2==1) result=result*x;
		x=x*x;
		y/=2;
	}
	return result;
}
inline BInt sqrt(BInt x,BInt y){
	if(x==1) return x;
	BInt l=0,r=x+1;
	while(l<r){
		BInt mid=(l+r)/2;
		if(qpow(mid,y)>x) r=mid;
		else l=mid+1;
	}
	return l-1;
}



struct Bign
{
    #define MK 510
	int c[MK],len,sign;
    int base = 10000;
	//初始化 
	Bign()
	{
		memset(c,0,sizeof(c));
		len = 1;
		sign = 0;
	}
	//清高位零
	void Zero()
	{
		while(len > 1 && c[len] == 0)
		{
			len--;
		}
		if(len == 1 && c[len] == 0)
		{
			sign = 0;
		}
	} 
	//压位读入 
	void Write(char *s)
	{
		int k = 1,l = strlen(s);
		for(register int i = l - 1;i >= 0;i--)
		{
			c[len] += (s[i] - '0') * k;
			k *= 10;
			if(k == base)
			{
				k = 1;
				len++;
			}
		}
	}
	void Read()
	{
		char s[MK] = {0};
		scanf("%s",s);
		Write(s);
	}
	//输出
	void Print()
	{
		if(sign)
		{
			printf("-");
		}
		printf("%d",c[len]);
		for(register int i = len - 1;i >= 1;i--)
		{
			printf("%04d",c[i]);
		}
		printf("\n");
	} 
	//重载 = 运算符，将低精赋值给高精 
	Bign operator = (int a)
	{
		char s[100];
		sprintf(s,"%d",a);
		Write(s);
		return *this;
	} 
	//重载 < 运算符
	bool operator < (const Bign &a)const
	{
		if(len != a.len)
		{
			return len < a.len;
		}
		for(register int i = len;i >= 1;i--)
		{
			if(c[i] != a.c[i])
			{
				return c[i] < a.c[i];
			}
		}
		return 0;
	}
	bool operator > (const Bign &a)const
	{
		return a < *this;
	}
	bool operator <= (const Bign &a)const
	{
		return !(a < *this);
	}
	bool operator >= (const Bign &a)const
	{
		return !(*this < a);
	}
	bool operator != (const Bign &a)const
	{
		return a < *this || *this < a;
	}
	bool operator == (const Bign &a)const
	{
		return !(a < *this) && !(*this < a);
	}
	bool operator == (const int &a)const
	{
		Bign b;b = a;
		return *this == b;
	}
	//重载 + 运算符
	Bign operator + (const Bign &a)
	{
		Bign r;
		r.len = max(len,a.len) + 1;
		for(register int i = 1;i <= r.len;i++)
		{
			r.c[i] += c[i] + a.c[i];
			r.c[i + 1] += r.c[i] / base;
			r.c[i] %= base; 
		}
		r.Zero();
		return r;
	} 
	Bign operator + (const int &a)
	{
		Bign b;
		b = a;
		return *this + b;
	}
	//重载 - 运算符
	Bign operator - (const Bign &a)
	{
		Bign b,c;// b - c
		b = *this;
		c = a;
		if(c > b)
		{
			Bign t;
			t = b;
			b = c;
			c = t;
			b.sign = 1;
		}
		for(register int i = 1;i <= b.len;i++)
		{
			b.c[i] -= c.c[i];
			if(b.c[i] < 0)
			{
				b.c[i] += base;
				b.c[i + 1]--;
			}
		}
		b.Zero();
		return b;
	} 
	Bign operator - (const int &a)
	{
		Bign b;b = a;
		return *this - b;
	}
	//重载 * 运算符 
	Bign operator * (const Bign &a)
	{
		Bign r;
		r.len = len + a.len + 2;
		for(register int i = 1;i <= len;i++)
		{
			for(register int j = 1;j <= a.len;j++)
			{
				r.c[i + j - 1] += c[i] * a.c[j];
				r.c[i + j] += r.c[i + j - 1] / base;
				r.c[i + j - 1] %= base;
			}
		} 
		r.Zero();
		return r;
	} 
	Bign operator * (const int &a)
	{
		Bign b;b = a;
		return *this * b;
	}
	//重载 / 运算符 
	Bign operator / (const Bign &b)
	{
		Bign r,t,a;
		a = b;
		if(a == 0)
		{
			return r;
		}
		r.len =len;
		for(register int i = len;i >= 1;i--)
		{
			t = t * base + c[i];
			int div,ll = 0,rr = base;
			while(ll <= rr)
			{
				int mid = (ll + rr) / 2;
				Bign k = a * mid;
				if(k > t)
				{
					rr = mid - 1;
				}else
				{
					ll = mid + 1;	
					div = mid; 
				} 
			}
			r.c[i] = div;
			t = t - a * div;
		}
		r.Zero();
		return r; 
	}
	Bign operator / (const int &a)
	{
		Bign b;b = a;
		return *this / b;
	}
	//重载 % 运算符
	Bign operator % (const Bign &a)
	{
		return *this - *this / a * a;
	}
	Bign operator % (const int &a)
	{
		Bign b;
		b = a;
		return *this % b;
	}
    #undef MK
};