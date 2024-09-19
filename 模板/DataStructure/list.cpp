#include<bits/stdc++.h>
using namespace std;
constexpr int N = 1e6+10;
int e[N],head,ne[N],ind;
void init(){
    head=-1;
    ind=0;
}
void add_to_head(int x){
    e[ind]=x;
    ne[ind]=head;
    head=ind++;
}
void del(int k){
    ne[k]=ne[ne[k]];
}
void ins(int k,int x){
    e[ind]=x;
    ne[ind]=ne[k];
    ne[k]=ind;
    ind++;
}
void delhead(){
    head=ne[head];
}

class LinkedList {
public:
	LinkedList(int N) : N(N), next(N) { clear(); }
	void clear() { head.assign(N, -1); }
	int front(int h) { return head[h]; }
	void pop(int h) { head[h] = next[head[h]]; }
	void push(int h, int u) { next[u] = head[h], head[h] = u; }
private:
	int N;
	vector<int> next, head;
};
 
class DoublyLinkedList {
private:
	struct Node { int prev, next; };
public:
	DoublyLinkedList(int N) : N(N), nodes(N) { clear(); }
	void clear() { head.assign(N, -1); }
	void erase(int h, int u) {
		int pv = nodes[u].prev, nx = nodes[u].next;
		if (nx >= 0) nodes[nx].prev = pv;
		if (pv >= 0) nodes[pv].next = nx;
		else head[h] = nx;
	}
	void insert(int h, int u) {
		nodes[u] = { -1, head[h]};
		if (head[h] >= 0) nodes[head[h]].prev = u;
		head[h] = u;
	}
	template <typename Func>
	void erase_all(int first, int last, Func f) {
		for (int i = first; i <= last; ++i) {
			for (int h = head[i]; h >= 0; h = nodes[h].next) f(h);
			head[i] = -1;
		}
	}
private:
	int N;
	vector<int> head;
	vector<Node> nodes;
};
 