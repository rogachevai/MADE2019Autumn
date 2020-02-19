/* 11_2. Количество различных путей
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).
Ввод: v: кол-во вершин (макс. 50000), n: кол-во ребер (макс. 200000), n пар реберных вершин,
пара вершин v, w для запроса.
Вывод: количество кратчайших путей от v к w.
*/
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include <cassert>
using namespace std;

class Graph {
public:
    Graph(int V): vertCount(V), outgoing(vertCount){};
    void Edge(int start, int finish);
    int find(int start, int finish);
    void nextV(int vert, vector<int> &vertices) const;
    void build(int v, int n);

private:
    struct Vert{
        Vert(): bfsDepth(0), count(0){};
        int bfsDepth;
        int count;
    };
    int vertCount;
    vector<list<int>> outgoing; // список смежности
};
void Graph::Edge(int start, int finish) {
    for(int i: outgoing[start]){ // если вершина уже существует
        if (i== finish){
            return;
        }
    }
    outgoing[finish].push_back(start);
    outgoing[start].push_back(finish);
}
void Graph::nextV(int vert, vector<int> &vertices) const {
    for(int i : outgoing[vert]) {
        vertices.push_back(i);
    }
}
int Graph::find(int start, int finish) { // функция для подсчета количества путей
    vector<Vert> visited(vertCount);
    queue<int> bfs;
    bfs.push(start);
    visited[start].count=1;
    while (!bfs.empty()){
        vector<int> next;
        int frt=bfs.front();
        bfs.pop();
        nextV(frt, next);
        for (int i: next){
            if(visited[i].count==0){
                bfs.push(i);
                visited[i].bfsDepth= visited[frt].bfsDepth+1;
                visited[i].count=visited[frt].count;
            } else if (visited[i].bfsDepth==visited[frt].bfsDepth+1){
                visited[i].count=visited[i].count+visited[frt].count;
            }
        }
    }
    return visited[finish].count;
}
void Graph::build(int v, int n){ // функция для ввода пар и построения графа
    for(int i = 0; i < n; i++){
        int vStart, vFinish;
        cin >> vStart >> vFinish;
        Edge(vStart, vFinish);
    }

}

int main() {
    int v=0;
    int n=0;
    int from = 0;
    int to = 0;
    cin >> v;
    assert (v<50001);
    cin >> n;
    assert( n<200001);
    Graph graph(v);
    graph.build(v,n);
    cin >> from >> to;
    cout << graph.find(from, to);
}