#include<bits/stdc++.h>
using namespace std;

// 2~36 base converter
struct BaseConverter {
    int s;int t;bool u=false;
    BaseConverter(int source, int target,bool upper) : s(source), t(target),u(upper) {}
    BaseConverter(int source, int target) : s(source), t(target){}
    BaseConverter(bool upper):u(upper){}
    BaseConverter(){}
    string work(const string& source) {
        int v = XTD(source, s);
        return DTX(v, t);
    }
    // 将源进制的数字字符串转为十进制
    int XTD(const string& source, int b) {
        int v = 0;
        int p = 1;
        for (int i = source.length() - 1; i >= 0; --i) {
            int bits = charToDigit(source[i]);
            if (bits == -1 || bits >= b) {
                cerr << "Invalid x in source number.\n";
                return -1;
            }
            v += bits * p;
            p *= b;
        }
        return v;
    }
    // 将十进制的值转为目标进制的字符串
    string DTX(int v, int b) {
        if (v == 0) return "0";
        string res = "";
        while (v > 0) {
            int rem = v % b;
            res = digitToChar(rem) + res;
            v /= b;
        }
        return res;
    }
    // 获取字符对应的数字值
    int charToDigit(char x) {
        if (x >= '0' && x <= '9') {
            return x - '0';
        } else if (x >= 'A' && x <= 'Z') {
            return x - 'A' + 10;
        } else if (x >= 'a' && x <= 'z') {
            return x - 'a' + 10;
        }
        return -1;
    }
    // 获取数字值对应的字符
    char digitToChar(int val) {
        if (val >= 0 && val <= 9) {
            return '0' + val;
        } else if (val >= 10 && val <= 35) {
            if(!u){
                return 'a' + val - 10;
            }else{
                return 'A'+val-10;
            }
        }
        return '\0';
    }
};
