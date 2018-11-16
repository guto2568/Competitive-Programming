#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAXN 200010

#define db(x) cerr << #x << " = " << x << endl;

struct line{
	ll m, n;
	line(){}
	line(ll _m, ll _n):
		m(_m), n(_n){}
};

ll v[MAXN], acc[MAXN];
line hull[MAXN];
int hullSize = 0, hullPtr = 0;

ll y(int idx, ll x){
	return hull[idx].m*x + hull[idx].n;
}

double intersection(line t, line r){
	double num = double(r.n - t.n);
	double den = double(t.m - r.m);
	return num/den;
}

void insertline(line l){
	while(hullSize >= 2 && intersection(hull[hullSize - 2], hull[hullSize - 1]) > intersection(hull[hullSize - 2], l)){
			if(hullPtr == hullSize - 1)
				hullPtr--;
			hullSize--;
		}
	
	hull[hullSize++] = l;
}

ll bb_query(int x){
	if(hullSize == 1){
		return y(0, x);
	}
	if(x >= intersection(hull[hullSize - 1], hull[hullSize - 2])){
		return y(hullSize - 1, x);
	}
	
	int hi = hullSize - 2;
	int lo = 0;
		
	while(lo < hi){
		int mid = (hi + lo)/2;
		if(x <= intersection(hull[mid], hull[mid + 1])){
			hi = mid;
		}
		else{
			lo = mid + 1;
		}
	}
	
	return y(lo, x);
}	

int main(){
	int n;
	scanf("%d", &n);
	ll mx = 0LL, base = 0LL;
	acc[0] = 0LL;
	for(int i = 1; i <= n; i++){
		scanf("%lld", &v[i]);
		acc[i] = acc[i-1] + v[i];
		base += i*v[i];
	}
	
	//db(mx);
	
	insertline(line(1, -acc[0]));
	
	for(int i = 2; i <= n; i++){
		mx = max(mx, bb_query(v[i]) - i*v[i] + acc[i-1]);
		//printf("query1: %lld (%lld %lld %lld)\n", bb_query(v[i]) - i*v[i] + acc[i-1], bb_query(v[i]), - i*v[i], acc[i-1]);
		insertline(line(i, -acc[i-1]));
	}
	
	hullSize = 0;
	hullPtr = 0;
	
	insertline(line(-n, -acc[n]));

	for(int i = n-1; i >= 1; i--){
		mx = max(mx, bb_query(-v[i]) + acc[i] - i*v[i]);
	//	printf("query2: %lld (%lld %lld %lld)\n", bb_query(-v[i]) + acc[i] - i*v[i], bb_query(-v[i]), acc[i], -i*v[i]);
		insertline(line(-i, -acc[i]));
	}
	
	
	printf("%lld\n", mx + base);
}
