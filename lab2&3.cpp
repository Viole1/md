#include <iostream>
#include <list>
#include <map>
using namespace std;
 
class Graph {
private:
    int v, e; // v - вершины; e - дуги
    map<int, list<int> > adjList;
    map<int, bool> visitedDFS;
    map<int, bool> notVisitedDFS;
    map<int, bool> visitedBFS;
    map<int, bool> notVisitedBFS;
 
    void DFS(int vertex) {
        visitedDFS[vertex] = true;
        notVisitedDFS[vertex] = false;
        cout << vertex + 1 << " ";
        
        list<int>::iterator i;
        for (i = adjList[vertex].begin(); i != adjList[vertex].end(); i++)
            if (!visitedDFS[*i])
                DFS(*i);
        for (int i = 0; i < v; i++) if (notVisitedDFS[i]) DFS(i);
    }
    void BFS(int vertex) {
        list<int> queue;
        
        visitedBFS[vertex] = true;
        notVisitedBFS[vertex] = false;
        queue.push_back(vertex);
 
        while (!queue.empty()) {
            vertex = queue.front();
            cout << vertex + 1 << ' ';
            queue.pop_front();
 
            list<int>::iterator i;
            for (i = adjList[vertex].begin(); i != adjList[vertex].end(); i++) {
                if (!visitedBFS[*i]) {
                    visitedBFS[*i] = true;
                    notVisitedBFS[*i] = false;
                    queue.push_back(*i);
                }
            }
        }
        for (int i = 0; i < v; i++) if (notVisitedBFS[i]) BFS(i);
    }
public:
    friend istream& operator>> (istream& s, Graph& g);
    friend ostream& operator<< (ostream& s, Graph& g);
 
    void DFS() {
        for (int i = 0; i < v; i++) notVisitedDFS[i] = true;
        DFS(0);
    }
    void BFS() {
        for (int i = 0; i < v; i++) notVisitedBFS[i] = true;
        BFS(0);
    }
};
 
istream& operator>>(istream& s, Graph& g) {
    cout << "Введите количество вершин: "; s >> g.v;
    cout << "Введите количество дуг: "; s >> g.e;
    map<int, list<int> > tmp;
    int n, value;
    for (int i = 0; i < g.v; i++) {
        cout << "Введите количество связанных вершин с " << (i + 1) << " вершиной: "; cin >> n;
        for (int j = 0; j < n; j++) {
            cout << "Введите " << (j + 1) << " вершину: ";
            s >> value;
            tmp[i].push_back(value - 1);
        }
    }
    g.adjList = tmp;
    return s;
}
 
ostream& operator<< (ostream& s, Graph& g) {
    s << endl;
    for (int i = 0; i < g.v; i++) {
        s << i + 1 << ": ";
        for (int value : g.adjList[i]) {
                s << value + 1 << ' ';
        }
        s << endl;
    }
    return s;
}
 
int main() {
    setlocale(LC_ALL, "Russian");
 
    Graph graph;
    cin >> graph;
    cout << graph;
    graph.DFS();
    cout << endl;
    graph.BFS();
 
    return 0;
}
// 5 7 2 2 5 1 4 2 2 3 1 1 1 4
