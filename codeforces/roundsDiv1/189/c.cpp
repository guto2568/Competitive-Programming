#include<bits/stdc++.h>

using namespace std;

typedef long long ll; 

#define MAXN 100005 

struct line{
	ll m, n;
	line(){}
	line(ll _m, ll _n):
		m(_m), n(_n){}
};

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
	while(hullSize >= 2 && intersection(l, hull[hullSize - 2]) <
		intersection(hull[hullSize - 1], hull[hullSize - 2])){
			if(hullPtr == hullSize - 1)
				hullPtr--;
			hullSize--;
		}
	hull[hullSize++] = l;
}

ll bb_query(ll x){
	if(hullSize == 1)
		return y(0, x);
		
	//printf("inter: %lf\n", intersection(hull[hullSize - 1], hull[hullSize - 2]));	
	if(x >= intersection(hull[hullSize - 1], hull[hullSize - 2]))
		return y(hullSize - 1, x);
		
	int hi = hullSize - 2;
	int lo = 0;
	int best = 0;

	while(lo <= hi){
		int mid = lo + (hi - lo)/2;
		if(x <= intersection(hull[mid], hull[mid + 1])){
			hi = mid - 1;
			best = mid;
		}
		else
			lo = mid + 1;
	}
	
	return y(best, x);
}

int main(){
	ll a[MAXN], b[MAXN];
	int n;
	
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	
	insertline(line(a[n], 0));
	
	for(int i = n - 1; i >= 1; i--){
		//printf("i = %d:", i);
		//for(int j = 0; j < hullSize; j++)
		//	printf("(%lld %lld)", hull[j].m, hull[j].n);
		//printf("\n");
		ll cost = bb_query(b[i]);
		insertline(line(a[i], cost));
		if(i == 1)
			printf("%lld\n", cost);
	}
	
	return 0;
}
