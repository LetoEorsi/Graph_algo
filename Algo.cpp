#include "stdafx.h"
#include "stdio.h"
#include <utility>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;


void downHeap(vector<int> &a, int k, int n) {
	int new_elem;
	int child;
	new_elem = a[k];

	while (k <= n / 2) {
		child = 2 * k;

		if (child < n && a[child] < a[child + 1])
			child++;
		if (new_elem >= a[child]) break;
		a[k] = a[child];
		k = child;
	}
	a[k] = new_elem;

}

void heapSort(vector<int> &a, int size) {
	long i;
	int temp;

	// строим пирамиду 
	for (i = size / 2 - 1 + size%2; i >= 0; i--) downHeap(a, i, size - 1);

	for (i = size-1; i > 0; i--) {
		// меняем первый с последним 
		temp = a[i]; a[i] = a[0]; a[0] = temp;


		// восстанавливаем пирамидальность a[0]...a[i-1] 
		downHeap(a, 0, i - 1);
	}
}

bool Check(int i, int j, vector<vector<bool>> M) {
	if (i > j) {
		return M[i][j];
	}
	else if (j > i) {
		return M[j][i];
	}
	else {
		return false;
	};
};

class graphvert {
private:

	int Color;
public:
	vector<int> List;
	graphvert() {
		int i;
		printf_s("Введите список цветов вершины и закончите 0 \n");
		scanf_s("%d", &i);
		do {
			List.push_back(i);
			scanf_s("%d", &i);
		} while (i != 0);

		heapSort(List, List.size());
		Color = 0;
	};
	int getColor() {
		return Color;
	};
	bool possColor(int v) {
		for (int i = 0; i < List.size(); i++) {
			if (v == List[i]) {
				return true;
			};
		};
		return false;
	};
	void makeColor(int a) {
		if (possColor(a)) {
			Color = a;
		};
	};
};

vector<graphvert> makelist(int N) {

	vector<graphvert> L;

	for (int i = 0; i < N; i++) {
		printf("%d -я вершина ", i);
		L.push_back(graphvert());
	};

	return L;
};

void showlist(vector<graphvert> l) {
	for (int i = 0; i < l.size(); i++) {
		printf("%d  -- \t", i);
		for (int j = 0; j < l[i].List.size(); j++) {
			printf("%d ", l[i].List[j]);
		};
		printf("\n");
	};
};

class Graph {
public:
	vector<vector<bool>> Matrix;
	int size;

	vector<graphvert> Vert;

	Graph(vector<graphvert> L, vector<vector<bool>> M) {
		Vert = L;
		size = L.size();
		Matrix = M;
	};

	void Push_Vertex(graphvert a) {
		Vert.push_back(a);
		size = size + 1;
	};

	bool CheckVert(int i, int j) {
		if (i > j) {
			return Matrix[i][j];
		}
		else if (j > i) {
			return Matrix[j][i];
		}
		else {
			return false;
		};
	};

	bool RegCheck() {
		int M, m = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (Check(i, j, Matrix)) {
					m = m + 1;
				};
			};
			if (i = 0) {
				M = m;
			}
			else {
				if (M != m) {
					return  false;
				};
			};
		};
		return true;
	};

	vector<int> AllowList(int i) {
		vector<int> f;
		for (int k = 0; i < Vert[i].List.size(); i++) {
			bool test = true;
			for (int j = 0; j < size; j++) {
				//printf("- \n");
				//printf("%d -- %d  color  %d -- %d \n",k,j, G.Vert[k].List[i], G.Vert[j].getColor());
				if (Check(i, j, Matrix) && (Vert[j].getColor() == Vert[i].List[k])) {
					test = false;
					break;
				};
			};
			if (test) {
				f.push_back(Vert[i].List[k]);
			};
		};
	};
};

Graph Cons(vector<int> u, Graph G) {

	heapSort(u, u.size());

	vector<graphvert> m;

	for (int i = 0; i < u.size(); i++) {
		m.push_back(G.Vert[u[i]]);
	};

	vector<vector<bool>> M;

	for (int i = 0; i < u.size(); i++) {
		vector<bool> v;
		for (int j = 0; j <= i; j++) {
			v.push_back(G.Matrix[u[i]][u[j]]);
		};
		M.push_back(v);
	};

	Graph H = Graph(m, M);

	return H;
};

void brln() {
	printf_s("\n");
	printf_s("\n");
	printf_s("********************");
	printf_s("\n");
	printf_s("\n");

};

void getMatrix(vector<vector<bool>> &M, int N) {
	int k;

	for (int i = 0; i < N; i++) {
		vector<bool> h;
		for (int j = 0; j < i; j++) {
			scanf_s("%d", &k);
			if (k == 0) {
				h.push_back(false);
			}
			else {
				h.push_back(true);
			};
		};
		h.push_back(false);
		M.push_back(h);
	};


};

void showMatrix(vector<vector<bool>> &M, int N) {
	printf_s("* \t");

	for (int i = 0; i < N; i++) {

		printf_s("%d \t", i);
	};
	printf_s("\n");
	printf_s("\n");

	for (int i = 0; i < N; i++) {
		printf_s("%d \t", i);
		for (int j = 0; j < N; j++) {
			if (Check(i, j, M)) {
				printf_s("1 \t");
			}
			else { printf_s("0 \t"); }
		};
		printf_s("\n");
	};


};

void showGraph(Graph G) {

	showMatrix(G.Matrix, G.size);

	printf("\n **** \n");

	for (int i = 0; i < G.Vert.size(); i++) {
		printf("%d -- %d \n", i, G.Vert[i].getColor());
	};

	printf("Printed \n");
	system("pause");

};

int* Arr(int N) {

	int *V = new int[N];
	for (int j = 0; j < N; j++) {
		V[j] = 0;
	};

	return V;

};

bool* BoolArr(int N) {

	bool *V = new bool[N];
	for (int j = 0; j < N; j++) {
		V[j] = true;
	};

	return V;

};

bool* BoolArrN(int N) {

	bool *V = new bool[N];
	for (int j = 0; j < N; j++) {
		V[j] = false;
	};

	return V;

};



void GreedyColor(Graph &G, int k, bool* &V) {
	int i, j;

	V[k] = false;
	//printf("\/ %d \n",k);
	for (i = 0; i < G.size; i++) {
		if (G.CheckVert(i, k)) {
			if (V[i]) {
				GreedyColor(G, i, V);
			};
		};
	};
	//printf("stop  %d \n", k);
	bool test;
	if (G.Vert[k].getColor() == 0) {
		for (i = 0; i < G.Vert[k].List.size(); i++) {
			test = true;
			for (j = 0; j < G.size; j++) {
			//printf("- \n");
				//printf("%d -- %d  color  %d -- %d \n",k,j, G.Vert[k].List[i], G.Vert[j].getColor());
				if (G.CheckVert(k, j) && (G.Vert[j].getColor() == G.Vert[k].List[i])) {
					test = false;
					break;
				};
			};
			if (test) {
				G.Vert[k].makeColor(G.Vert[k].List[i]);
				//printf("coloring  %d in color %d \n", k, G.Vert[k].List[i]);
				//printf("color %d is %d \n", k, G.Vert[k].getColor());
				break;
			};
		};
	};
};

void ExepGreedyColor(Graph &G, vector<int> &f) {

	int g = -1;
	bool* V = BoolArr(G.size);

	for (int i = 0; i < f.size(); i++) {
		V[f[i]] = false;
	};

	for (int i = 0; i < G.size; i++) {
		for (int j = 0; j < f.size(); j++) {
			if (Check(i, f[j], G.Matrix) && V[i]) {
				g = i;
				break;
			};
		};
		if (g != -1) {
			GreedyColor(G, g, V);
		};
	};

};

vector<int> getComp(vector<vector<bool>> &R, bool* &V, int k, int size, vector<int> &f) {

	int i;
	V[k] = false;
	for (i = 0; i < size; i++) {
		if (Check(i, k, R)) {
			if (V[i]) {
				getComp(R, V, i, size, f);
			};
		};
	};

	f.push_back(k);
	return f;

};

vector<pair< Graph , vector<int> > > OntoComps(vector<vector<bool>> &R, int size, vector<pair< Graph, vector<int> > > &f, vector<graphvert> l, bool* &L) {

	bool* V = BoolArr(size);

	//printf("Begin \n");
	//system("pause");

	vector<int> u;
	//printf("Start get");
	//system("pause");
	for (int i = 0; i < size; i++) {
		if (!L[i]) {
			//printf("Get %d \n", i);
			//system("pause");
			u = getComp(R, V, i, size, u);
			//printf("Started from %d \n", i);
			//system("pause");
			break;
		};
	};
	//printf("Composed \n");
	//system("pause");
	heapSort(u, u.size());
	
	vector<graphvert> m;

	for (int i = 0; i < u.size(); i++) {
		m.push_back(l[u[i]]);
		L[u[i]]=1;
	};

	vector<vector<bool>> M;

	for (int i = 0; i < u.size(); i++){
		vector<bool> v;
		for (int j = 0; j <= i; j++) {
			v.push_back(R[u[i]][u[j]]);		
		};
		M.push_back(v);
	};

	//printf("Matrix got %d \n", f.size());
	//system("pause");

	//printf("Taked \n");
	//system("pause");
	Graph H = Graph(m, M);

	brln();

	showGraph(H);
	//system("pause");

	//printf("Size f %d , size u %d", f.size(), u.size());
	//system("pause");
	pair< Graph, vector<int>> p(H,u);
	p.first = H;
	p.second = u;


	f.push_back(p);

	//printf("Size f %d , size u %d \n", f.size(), u.size());

	//printf("Added subgraph \n");
	//system("pause");
	bool d=true;
	for (int i = 0; i < size; i++) {
		/*if (L[i]) {
			printf("1 \n");
		}
		else {
			printf("0 \n");
		}*/
		d = d&&L[i];
	};
	//printf("%d \n", d);
	//system("pause");

	if (!d) {
		OntoComps(R, size, f, l, L);
	};
	return f;
};

bool RegularityCheck(Graph G) {
	int n,m=0;
	for (int i = 0; i < G.size; i++) {
		for (int j = 0; j < G.size; j++) {
			if (Check(i,j, G.Matrix)) {
				m++;
			};
		};
		if (i == 0) {
			n = m;
		};
		if (i > 0) {
			if (n != m) {
				return false;
			};
		};
		m = 0;
	};
	return true;
};

bool FullCheck(Graph G) {
	for (int i = 0; i < G.size; i++) {
		for (int j = 0; j < G.size; j++) {
			if ( !Check(i, j, G.Matrix) && !(i==j) ) {
				return false;
			};
		};
	};
	return true;
};

int notRegVert(Graph G) {
	int n, m = 0;
	for (int i = 0; i < G.size; i++) {
		for (int j = 0; j < G.size; j++) {
			if (Check(i, j, G.Matrix)) {
				m++;
			};
		};
		if (i == 1) {
			n = m;
		};
		if (i > 2) {
			if (n > m) {
				return i;
			}
			else if (m > n) {
				return i - 1;
			}
		};
		m = 0;
	};
};

int notRegVertVec(Graph G, bool* L) {
	int n, m = 0;
	for (int i = 0; i < G.size; i++) {
		for (int j = 0; j < G.size; j++) {
			if (Check(i, j, G.Matrix)&&L[i]&&L[j]) {
				m++;
			};
		};
		if (i == 1) {
			n = m;
		};
		if (i > 2) {
			if (n > m) {
				return i;
			}
			else if (m > n) {
				return i - 1;
			}
		};
		m = 0;
	};
};


void getBiColor(Graph G, int* &V, int k, int &a) {
	int i;
	a++;
	V[k] = a;
	for (i = 0; i < G.size; i++) {
		if (Check(i, k, G.Matrix)) {
			if (V[i] == 0) {
				//printf("%d by %d \n", i, a);
				getBiColor(G, V, i, a);
			};
		};
	};
};

int min(vector<int> a, int r) {
	int k,n;
	if (a.empty()){
		return r;
	};
	if (!a.empty()) {
		n = a[0];
		for (int i = 0; i < a.size(); i++) {
			k = a[i];
			if (k <= n) {
				n=k;
			};
		};
		return n;
	};
};

int getBiComp(Graph G, int* &V, int k, int j, bool* &L, int* &H) {
	L[k] = false;
	int M, N;
	vector<int> y;
	for (int i=0; i < G.size; i++) {
		//printf("Curr %d  Parent %d   %d\n", k, j, i);
		//system("pause");
		if (Check(i, k, G.Matrix) && (L[i])) {
			//printf("%d %d\n", k, j);
			j = k;
			//system("pause");
			y.push_back(getBiComp(G, V, i, j, L, H));
		};
	};
	M = min(y, G.size+1);
	//printf("Min M  -- %d by %d\n", M, k);
	//system("pause");

	vector<int> z;
	for (int i = 0; i < G.size; i++) {
		if ((Check(i, k, G.Matrix)|(i == k)) && (i != j)) {
			z.push_back(V[i]);
		};
	};
	N = min(z,G.size+1);
	
	if (M > N) {
		H[k]=N;
	}
	else {
		H[k]=M;
	};

	return H[k];

};

vector<int> GetBic(Graph G) {

	int* V = Arr(G.size);
	int a = 0;

	vector<int> w;

	getBiColor(G, V, 0, a);


	bool* L = BoolArr(G.size);
	int* H = Arr(G.size);

	

	int t;
	t= getBiComp(G, V, 0, 0, L, H);


	for (int i = 0; i < G.size; i++) {
		if (H[0] = H[i]) {
			w.push_back(i);
		};
	};
	return w;
};


void findCl(Graph G, int* V, int k, int &a, int &d, vector<int> &f) {

	a++;
	V[k] = a;
	for (int i = 0; i < G.size; i++) {
		if (Check(i, k, G.Matrix)&&f.empty()) {
			if (V[i] == 0) {
				d = k;
				findCl(G, V, i, a, d, f);
			};
		};
	};

	

	if (!f.empty()) {
		if (V[k] >= a) {
			//printf("Added induct %d with a= %d and order %d \n", k, a, V[k]);
			//system("pause");
			f.push_back(k);
		};
	};

	if (f.empty()) {
		for (int i = 0; i < G.size; i++) {
			if (Check(i, k, G.Matrix) && (d != i)) {
				f.push_back(k);
				a = V[i];
				//printf("Added %d with a= %d \n", k, a);
				//system("pause");
			};
		};
	};

};

void findClique(Graph G, vector<int> &f) {

	queue<int> r;

	bool *V = BoolArr(G.size);

	for (int i = 0; i < f.size(); i++) {
		V[f[i]] = false;
	};

	for (int i=0; i < f.size(); i++) {
		for (int j = 0; j < G.size; j++) {
			if (Check(j, f[i], G.Matrix) && (V[j])) {
				r.push(j);
			};
		};
	};


	while (!r.empty()){
			for (int j = 0; j < G.size; j++) {
				if (Check(j, r.front(), G.Matrix)&&(V[j])) {
					r.push(j);
				};
			};
			V[r.front()] = false;
			bool t = true;
			for (int j = 0; j < f.size(); j++) {
				if (!Check(r.front(), f[j], G.Matrix)) {
					t = false;
					break;
				};
			};
			if (t) {
				f.push_back(r.front());
			};
			r.pop();
	};
};

vector<int> Neigh(Graph G, vector<int> &f){

	bool* V = BoolArr(G.size);

	for (int i = 0; i < f.size(); i++) {
		V[f[i]] = false;
	};

	for (int i = 0; i < f.size(); i++) {
		for (int j = 0; j < G.size; j++) {
			if (Check(j, f[i], G.Matrix) && (V[j])) {
				f.push_back(j);
				V[j] = false;
			};
		};
	};

	return f;

};

vector<int> NeighSt(Graph G, int b, vector<int> &f) {

	bool* V = BoolArr(G.size);
	vector<int> g;

	for (int i = 0; i < f.size(); i++) {
		V[f[i]] = false;
	};
		for (int j = 0; j < G.size; j++) {
			if (Check(j, b, G.Matrix) && (V[j])) {
				g.push_back(j);
				V[j] = false;
			};
		};
		return g;
};

vector<int> NeighExep(Graph G, int b, vector<int> &f) {
	bool* V = BoolArrN(G.size);
	vector<int> g;

	for (int i = 0; i < f.size(); i++) {
		V[f[i]] = true;
	};
	for (int j = 0; j < G.size; j++) {
		if (Check(j, b, G.Matrix) && (V[j])) {
			g.push_back(j);
			V[j] = false;
		};
	};
	return g;
};

int findG(Graph G, vector<int> f, bool* h) {
	for (int i = 0; i < f.size(); i++) {
		for (int j = 0; j < G.size; j++) {
			if (Check(f[i], j, G.Matrix) && (!h[j])) {
				return f[i];
			};
		};
	};
};

void ShPath(Graph G, bool* &f, int a, vector<int> &S, pair<int, int> &h, bool* &V) {

	V[a] = false;
	if (f[a] && (S.size() == 0)) {
		//printf("Added start %d \n", a);
		//system("pause");
		S.push_back(a);
		h.first = a;

	};

	if (f[a] && (S.size() == 1) && (h.first != a)) {
		//printf("Added end %d \n", a);
		//system("pause");
		S.push_back(a);
		h.second = a;
	};

	if(S.size()<2){
	
	for (int i = 0; i < G.size; i++) {
		if (Check(i, a, G.Matrix) && ((V[i]) | ((!f[a]) && (f[i]))) && (h.first != i)&& (S.size()<2)) {
			ShPath(G, f, i, S, h, V);
		};
	};
};

	if ((S.size() >= 2)&&(h.second !=a)&&(h.first != a)) {
		//printf("Added sub %d \n", a);
		//system("pause");
		S.push_back(a);
	};
};

pair<vector<int>, pair<int, int> > FindThetaT(Graph G, vector<int> &f){
	vector<int> h;
	int b, t;

	findClique(G,f);

	bool* V = BoolArr(G.size);
	for (int i = 0; i < f.size(); i++) {
		V[f[i]] = false;
	};

	//printf("Start finding \n");
	//system("pause");
	for (int i = 0; i < f.size(); i++) {
		vector<int> u;
		u = NeighSt(G, f[i], f);
		//printf("Neigh finding  %d \n", f[i]);
		//for (int i = 0; i < u.size(); i++) {
		//	printf("%d \n", u[i]);
		//};
		//system("pause");
		for (int j = 0; j < u.size(); j++) {
			vector<int> v = NeighExep(G, u[j], f);
			//printf("NeiExep finding  %d \n", u[j]);
			//for (int i = 0; i < v.size(); i++) {
			//	printf("%d \n", v[i]);
			//};
			//system("pause");
			if (v.size() > 1) {
				//printf("Find \n");
				for (int k = 0; k < v.size(); k++) {
					//printf("%d  %d \n", v[k], f[i]);
					if (v[k] != f[i]) {
						//printf("%d %d %d \n", v[k],f[i],u[j]);
						b = v[k];
						t = f[i];
						h.push_back(b);
						h.push_back(u[j]);
						break;
					};
				};
				//printf("h is \n");
				//for (int i = 0; i < h.size(); i++) {
				//	printf("%d \n", h[i]);
				//};

				for (int k = 0; k < f.size(); k++) {
					//printf("3-d finding  %d %d  %d\n", f[k], u[j], f[i]);
					//system("pause");
					if (!Check(f[k], u[j], G.Matrix)&&(f[k]!=f[i])) {
						
						h.push_back(f[k]);
						break;
					};
				};

				//printf("h is \n");
				//for (int i = 0; i < h.size(); i++) {
				//	printf("%d \n", h[i]);
				//};

				//printf("4-d finding  %d \n", i);
				//system("pause");
				h.push_back(f[i]);

			};
	

			//printf("Size  %d \n", h.size());
			//system("pause");
			if (!h.empty()) {
				//printf("Ended \n");
				//system("pause");
				pair<int, int> j(b, t);
				pair<vector<int>, pair<int, int> > s( h,j );
				return s;
			};
		};
	};


	h.~vector();


	//printf("Trying another variant \n");
	//system("pause");

	pair<int, int> m;

	bool* L = BoolArrN(G.size);
	for (int i = 0; i < f.size(); i++) {
		L[f[i]] = true;
	};

	int i;
	i = findG(G, f, L);
	vector<int> S;
	ShPath(G, L, i, S, m, V);

	for (int j = 0; j < f.size(); j++) {
		if ((f[j] != m.first) && (f[j] != m.second)) {
			S.push_back(f[j]);
			break;
		};
	};

	pair<vector<int>, pair<int, int>> g(S,m);
	return g;

	//printf("Stoped bad case");
	//system("pause");

};

pair< vector<int>, pair<int, int> > FindThetaSp(Graph G, int c, vector<int> v, vector<int> f) {
	pair<int, int> y;
	y.first = c;

	int a;
	vector<int> q;
	q.push_back(c);
	a = v[0];

	bool* V = BoolArr(G.size);
	V[a] = false;

	bool* L = BoolArr(G.size);

	for (int i = 0; i < v.size(); i++) {
		L[v[i]] = false;
	};

	while (L[a]|(a == v[0])) {
		q.push_back(a);
		//printf("Taking a = %d by 1-st side \n",a);
		//system("pause");
		for (int t = 0; t < f.size(); t++) {
			if (Check(f[t], a, G.Matrix) && V[f[t]]) {
				a = f[t];
				V[f[t]] = false;
				break;
			};
		};
	};
	//printf("Taking a = %d by end 1-st side \n", a);
	//system("pause");
	q.push_back(a);

	a = v[0];
	while (L[a] | (a == v[0])) {
		if (a != v[0]){
			q.push_back(a);
			//printf("Taking a = %d by 2-nd side \n", a);
			//system("pause");
		};

		for (int t = 0; t < f.size(); t++) {
			if (Check(t, a, G.Matrix) && V[f[t]]) {
				a = t;
				V[f[t]] = false;
				break;
			};
		};
	};
	//printf("Taking a = %d by end 2-nd side \n", a);
	//system("pause");
	q.push_back(a);

	y.second = v[0];
	pair<vector<int>, pair<int, int>> r(q, y);
	return r;
};

pair< vector<int>, pair<int, int> > FindThetaC(Graph G, vector<int> &f) {
	vector<int> h;
	int a;

	for (int i = 0; i < f.size(); i++) {
		vector<int> u;
		u = NeighSt(G, f[i], f);
		for (int j = 0; j < u.size(); j++) {
			vector<int> v;
			v = NeighExep(G, u[j], f);
			if (v.size() > 2) {
				//printf("Trying variant 1 \n");
				//system("pause");
				pair< vector<int>, pair<int, int> > g = FindThetaSp(G, u[j], v, f);
				return g;
			}
			else if(v.size() == 2){
				//printf("Trying variant 2 \n");
				//system("pause");
				f.push_back(u[j]);
				pair<int, int> y(v[0], v[1]);
				pair<vector<int>, pair<int, int> > r(f, y);
				return r;
			};
		};
	};



	//printf("Trying another variant 3 \n");
	//system("pause");


	pair<int, int> m;

	bool* L = BoolArrN(G.size);
	for (int i = 0; i < f.size(); i++) {
		L[f[i]] = true;
	};

	int i;
	i = findG(G, f, L);
	vector<int> S;

	bool* V = BoolArr(G.size);
	for (int i = 0; i < f.size(); i++) {
		V[f[i]] = false;
	};

	ShPath(G, L, i, S, m, V);


	for (int j = 0; j < f.size(); j++) {
		if ((f[j] != m.first) && (f[j] != m.second)) {
			S.push_back(f[j]);
		};
	};

	pair<vector<int>, pair<int, int>> g(S, m);
	return g;

	//printf("Stoped bad case");
	//system("pause");


};

void CorrInj(Graph &G, Graph &H, vector<int> &f) {
	for (int i = 0; i < f.size(); i++) {
		if (G.Vert[f[i]].getColor() == 0) {
			G.Vert[f[i]].makeColor(H.Vert[i].getColor());
			//printf("%d --> %d with color %d \n", i, f[i] , G.Vert[f[i]].getColor());
		};
	};
};

vector<int> SetMinus(vector<int> h, vector<int> m){
	vector<int> y;
	int j=0;
	int i = 0;
	while((i<h.size())&&(j<m.size())){
		if (h[i]<m[j]) {
			y.push_back(i);
				i++;
		}
		else if (h[i] == m[j]) {
			i++;
			j++;
		}
		else {
			if (j != m.size()-1) {
				j++;
			}
			else {
				y.push_back(i);
				i++;
				j = 0;
			};

		};
	};

	return y;
};

void LineColor(Graph &G, vector<int> &f ,bool* &V, int g, int a) { 
	
	if (f[a] == g) {
		goto end;
	};

	V[a] = false;

	for (int i = 0; i < f.size(); i++) {
		if (Check(f[i], a, G.Matrix) && V[f[i]]) {
			for (int j = 0; j < G.Vert[f[i]].List.size(); j++) {
				if (G.Vert[a].getColor() != G.Vert[f[i]].List[j]) {
					G.Vert[f[i]].makeColor(G.Vert[f[i]].List[j]);
				};
			};
			LineColor(G, f, V, g, f[i]);
		}
	
	};
	end: ;
};

void ColorTheta(Graph &G, vector<int> &f, int h, int g) {

	ExepGreedyColor(G, f);

	bool* H = BoolArrN(G.size);
	for (int i = 0; i < f.size(); i++) {
		H[f[i]] = true;
	};

	for (int j = 0; j < f.size(); j++){
		for (int i = 0; i < G.size; i++) {
			if (Check(i,f[j],G.Matrix)&&(!H[i])) {
				SetMinus(G.Vert[f[j]].List, G.Vert[i].List);
			};
		};
	};

	vector<int> y;

	for (int j = 0; j < f.size(); j++) {
		if (Check(h, f[j], G.Matrix)) {
			if (G.Vert[j].List.size() > 2) {
				vector<int> r;
				r.push_back(G.Vert[j].List[0]);
				r.push_back(G.Vert[j].List[1]);
				G.Vert[j].List = r;
			};
		};
	};

	int k;

	for (int i = 1; i < G.Vert[h].List.size(); i++) {
		bool test=true;
		for (int j = 0; j < f.size(); j++) {
			if (Check(h, f[j], G.Matrix)) {
				if (G.Vert[f[j]].possColor(G.Vert[h].List[i])) {
					test = false;
					k = f[j];
					break;
				};
			};
		};
		if (!test){
			G.Vert[h].makeColor(G.Vert[h].List[i]);
			break;
		};
	};


	bool* V = BoolArr(G.size);

		for (int i; i < f.size(); i++) {
			if (Check(f[i], h, G.Matrix)) {
				LineColor(G, f, V, g, f[i]);
			};
		};
	
		LineColor(G, f, V, h, g);
};

void IsGoodCycle(Graph G, vector<int> &f, bool* &V,int a, pair<bool, pair< int, int > > p) {
	V[a] = false;

	for (int i = 0; i < f.size(); i++) {
		if (Check(a, f[i], G.Matrix) && V[f[i]]&&!p.first) {
			if (G.Vert[f[i]].List == G.Vert[a].List) {
				IsGoodCycle(G, f, V, a, p);
			}
			else {
				p.first = true;
				p.second.first = a;
				p.second.second = i;
			};
		};
	};
};

void ColorCycle(Graph &G, vector<int> &f){
	pair <int, int> t(-1, -1);
	pair<bool, pair< int , int > > r(false, t);
	bool* V = BoolArr(G.size);
	IsGoodCycle(G,f,V,f[0],r);
	if (r.first) {
		ColorTheta(G, f, r.second.first, r.second.second);
	}
	else {
		bool* W = BoolArrN(G.size);
		for (int i = 0; i < G.size; i++) {
			W[f[i]] = true;
		};
		GreedyColor(G,f[0],W);

	};
};

vector<pair< Graph, vector<int>>> makeGr(vector<vector<bool>> &R, int size, vector<graphvert> l) {

	bool* L = BoolArrN(size);


	vector<pair< Graph, vector<int>>> A;
	//printf("Going to comp comps \n");
	//system("pause");
	A=OntoComps(R, size, A, l, L);


	//printf("G divided onto %d comps \n", A.size());
	//system("pause");


	for (int i = 0; i < A.size(); i++) {
		vector<int> u;
		printf("Start Checking %d comp", i);
		u = GetBic(A[i].first);
		//printf("Stop Checking %d comp %d", i, u.size());


		vector<int> v;
		for (int j = 0; j < u.size(); j++) {
			 v.push_back(A[i].second[u[j]]);
		};
		//printf("Checking %d comp, %d , %d", i, u.size(), A[i].first.size);

		Graph H = Cons(u, A[i].first);

		//printf(" Stop checking %d bicomp, %d ", i, u.size());

		if(RegularityCheck(H))
		printf("%d going to bicomp comps \n", i);

		//system("pause");
		if (FullCheck(H)) {
			printf("variant A \n");
			bool* V = BoolArr(H.size);
			GreedyColor(H, 0, V);
			CorrInj(A[i].first, H, u);
		}
		else if (!RegularityCheck(H)) {
			printf("variant B \n");
			printf("Color \n");
			system("pause");
			int j = notRegVert(H);
			bool* V = BoolArr(H.size);
			GreedyColor(H, j, V);
			brln();
			showGraph(H);
			brln();
			CorrInj(A[i].first, H, u);
			printf("%d Colored! \n", i);
			showGraph(A[i].first);
			brln();
			system("pause");
		}
		else {
			printf("variant C \n");
			int a = 0;
			int d = 0;
			int* V = Arr(H.size);
			vector<int> u;

			findCl(H,V,0,a,d,u);

			if (u.size() == 0) {
				printf("variant Ca \n");
				bool* V = BoolArrN(H.size);
				for (int i = 0; i < H.size; i++) {
					V[u[i]] = true;
				};
				int i = notRegVertVec(H,V);
				GreedyColor(H, i, V);

			} else if (u.size() == 3) {
				printf("variant Cb \n");
				pair<vector<int>, pair<int, int> > d;
				d=FindThetaT(H,u);
				ColorTheta(H, u, d.second.first, d.second.second);
			}
			else if ((u.size() % 2 == 0) && (u.size() > 3)) {
				printf("variant Cc \n");
				ColorCycle(H,u);
			}
			else if ((u.size() % 2 != 0) && (u.size() > 3)) {
				printf("variant Cd \n");
				pair<vector<int>, pair<int, int> > d;
				d=FindThetaC(H, u);
			

				if ((d.first.size() != 0) && (d.second.first != d.second.second)) {
					ColorTheta(H, u, d.second.first, d.second.second);
				}
				else {
					printf("All that bad \n");
					bool* V = BoolArr(H.size);
					GreedyColor(H, 0, V);
					
				};

			};

			showGraph(H);
			system("pause");

			CorrInj(A[i].first, H, u);
		};
	};

	return A;
	
};





int main() {
	setlocale(LC_ALL, "Russian");


	vector<vector<bool>> M;
	vector<graphvert> l;
	vector<int> S;

	//pair< vector<int> , pair <int, int> > u;


	int N;
	int a = 0;


	scanf_s("%d", &N);

	int* V = Arr(N);

	getMatrix(M, N);

	brln();

	showMatrix(M, N);

	brln();

	
	l = makelist(N);
	brln();


	vector<pair< Graph, vector<int>>> G;
		G = makeGr(M, N, l);


	printf("Size G %d", G.size());
	system("pause");

	for(int i = 0; i < G.size(); i++){
		showGraph(G[i].first);
		brln();
	};
	

	brln();

	printf("Making graph \n");
	system("pause");

	Graph H = Graph(l,M);


	for (int i = 0; i < G.size() ; i++) {
		CorrInj(H, G[i].first, G[i].second);
	};


	showGraph(H);

	brln();

	brln();

	



	

	scanf_s("%d", &N);
	return 0;
};
