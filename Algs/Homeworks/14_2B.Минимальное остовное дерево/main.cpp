/*14. «MST». Дан неориентированный связный граф.
*Требуется найти вес минимального остовного дерева в этом графе.
*/
#include <iostream>
#include <vector>
#include <algorithm> // для сортировки
#include <cassert>
using namespace std;

struct Graph {
public:
    int V, E;
    vector< pair<int, pair<int, int>> > edges;
    Graph(int v, int e): V(v),E(e){};
    void addEdge(int u, int v, int w);
    int MST(); // сам алгоритм Крускала
};

void Graph::addEdge(int u, int v, int w) {
    edges.push_back({w, {u, v}});
}

// Нужно ли нам улучшать асимптотику я не совсем понял, в задании, вроде как про это не сказано
// но, сделаем с DSU

struct DisjointSets {
public:
    int *parent, *rn;
    int n;
    DisjointSets(int n);
    int find(int u);
    void merge(int a, int b);
};

DisjointSets::DisjointSets(int n){
    this->n = n;
    parent = new int[n+1];
    rn = new int[n+1];
    for (int i = 0; i <= n; i++){
        rn[i] = 0;
        parent[i] = i;
    }
}
int DisjointSets::find(int u) {
    if (u != parent[u]){
        parent[u] = find(parent[u]);
    }
    return parent[u];
}
void DisjointSets::merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (rn[a] > rn[b])
        parent[b] = a;
    else
        parent[a] =b;
    if (rn[a] == rn[b]) {
        rn[b]++;
    }
}

int Graph::MST() {
    sort(edges.begin(), edges.end());
    DisjointSets disjointSet(V);
    int mstWeight = 0;
    vector< pair<int, pair<int, int>> >::iterator i;
    for (i=edges.begin(); i!=edges.end(); i++){
        int u = i->second.first;
        int v = i->second.second;
        int set_u = disjointSet.find(u);
        int set_v = disjointSet.find(v);
        if (set_u != set_v){ // смотрим, получается ли цикл
            mstWeight += i->first;
            disjointSet.merge(set_u, set_v);
        }
    }return mstWeight;
}


int main() {
    int n, m;
    cin >> n >> m;
    assert ( n<20001);
    assert(m<100001);
    Graph g(n,m);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        g.addEdge(x,y,z);
    }
    int mstWeight = g.MST();
    cout << mstWeight;
    return 0;
}
/*
5 10
4 3 3046
4 5 90110
5 1 57786
3 2 28280
4 3 18010
4 5 61367
4 1 18811
4 2 69898
3 5 72518
3 1 85838
 */