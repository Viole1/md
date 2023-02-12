#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
 
class Graph {
private:
    int v, e; // v - вершины, е - рёбра
    vector< vector<int> > adjMatrix;
    vector< vector<int> > incMatrix;
    vector< vector<int> > adjList;
 
    void fromAdjMatToAdjList() {
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (adjMatrix[i][j]) adjList[i].push_back(j);
    }
    void fromAdjListToAdjMat() {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < adjList[i].size(); j++) {
                if (adjList[i][j] == i) adjMatrix[i][adjList[i][j]] = 2;
                else if (adjList[i][j] > -1) adjMatrix[i][adjList[i][j]] = 1;
            }
        }
    }
    void fromAdjListToIncMatrix() {
        int row = 0;
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < adjList[i].size(); j++) {
                if (adjList[i][j] != -1) {
                    if (adjList[i][j] == i) incMatrix[row++][i] = 2;
                    else {
                        incMatrix[row][adjList[i][j]] = 1;
                        incMatrix[row++][i] = -1;
                    }
                    continue;
                }
            }
        }
    }
    void fromIncMatToAdjList() {
        int a = 0, b = 0;
        for (int i = 0; i < e; i++) {
            for (int j = 0; j < v; j++) {
                if (incMatrix[i][j] == -1) {
                    a = j;
                    for (int k = a; k < v; k++) if (incMatrix[i][k] == 1) { b = k; adjList[a].push_back(b); a = 0; b = 0; }
                }
                else if (incMatrix[i][j] == 1) {
                    b = j;
                    for (int k = b; k < v; k++) if (incMatrix[i][k] == -1) { a = k; adjList[a].push_back(b); a = 0; b = 0; }
                }
                else if (incMatrix[i][j] == 2) adjList[incMatrix[i][j]].push_back(incMatrix[i][j]);
            }
        }
        fromAdjListToAdjMat();
    }
public:
    Graph() : v(0), e(0) {}
    Graph(int v1, int e1) : v(v1), e(e1) {
        vector< vector<int> > temp(v, vector<int>(v));
        adjMatrix = temp;
        vector< vector<int> > temp1(e, vector<int>(v)); // чтоб транспонировать матрицу меняй тут е и v
        incMatrix = temp1;
        vector< vector<int> > temp2(v, vector<int>(v, -1));
        adjList = temp2;
    }
    void getAdjacencyMatrix() { // матрица смежности
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                cin >> adjMatrix[i][j];
        fromAdjMatToAdjList();
        fromAdjListToIncMatrix();
    }
    void getIncencyMatrix() { // матрица инцидентности
        for (int i = 0; i < e; i++)
            for (int j = 0; j < v; j++)
                cin >> incMatrix[i][j];
        fromIncMatToAdjList();
    }
    void getAdjacencyList() { // список смежности, по 1 числу вводится
        for (int i = 0; i < adjList.size(); i++) {
            int n, val;
            cout << "\nВведите число смежных узлов у " << i + 1 << " вершины: "; cin >> n;
            if (n) {
                cout << "Введите узлы:\n";
                for (int j = 0; j < n; j++) {
                    cin >> val;
                    adjList[i].push_back(val - 1);
 
                    if (i == (val - 1)) adjMatrix[i][val - 1] = 2;
                    else adjMatrix[i][val - 1] = 1;
                }
            }
            else continue;
        }
        fromAdjListToIncMatrix();
    }
 
    void displayAdjacencyMatrix() {
        for (vector<int> row : adjMatrix) {
            for (int val : row) cout << setw(2) << val << ' ';
            cout << endl;
        }
    }
    void displayIncencyMatrix() {
        for (vector<int> row : incMatrix) {
            for (int val : row) cout << setw(2) << val << ' ';
            cout << endl;
        }
    }
    void displayAdjacencyList() {
        for (int i = 0; i < v; i++) {
            cout << i + 1 << ": ";
            vector<int>::iterator iter;
            for (iter = adjList[i].begin(); iter != adjList[i].end(); iter++) if (*iter != -1) cout << *iter + 1 << ' ';
            cout << endl;
        }
    }
};
 
int main() {
    setlocale(LC_ALL, "Russian");
 
    int choice;
    cout << "Выберите каким способом Вы хотите сохранить граф:\n1.Матрица смежности.\n2.Матрица инцидентности.\n3.Список смежности.\n";
    cin >> choice;
 
    int n, m; // n - вниз, m - вправо
    cout << "Введите количество вершин: "; cin >> n;
    cout << "Введите количество рёбер: "; cin >> m;
    Graph gr(n, m);
 
    switch (choice) {
        case 1: gr.getAdjacencyMatrix(); break;
        case 2: gr.getIncencyMatrix(); break;
        case 3: gr.getAdjacencyList(); break;
    }
    cout << "Введите матрицу/список:\n";
 
    cout << endl << "Список смежности:" << endl;
    gr.displayAdjacencyList();
    cout << "Матрица смежности:" << endl;
    gr.displayAdjacencyMatrix();
    cout << "Матрица инцидентности:" << endl;
    gr.displayIncencyMatrix();
 
    return 0;
}
// ----------------------------------------------------------------------------------------
// 5 7 2 2 5 1 4 2 2 3 1 1 1 4 // СС
// 5 7 -1 1 0 0 0 0 1 -1 0 0 0 -1 0 1 0 1 0 0 -1 0 -1 0 0 0 1 0 0 0 1 -1 0 0 2 0 0 // МИ
// 5 7 0 1 0 0 1 0 0 0 1 0 0 1 2 0 0 1 0 0 0 0 0 0 0 1 0 // МС
