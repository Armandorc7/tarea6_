/*
Problema 3: DFS Iterativo Avanzado

Enunciado:
Usando exclusivamente std::stack, determinar si existe un camino raiz-hoja
cuya suma sea K y devolver ese camino. No recursion.

Por que DFS es adecuado:
Queremos evaluar caminos completos raiz->hoja. DFS explora un camino hasta
el fondo (hoja) antes de cambiar a otro, asi que es natural para probar
sumas de caminos sin almacenar niveles completos (como haria BFS).

Complejidad:
Se visita cada nodo a lo sumo un par de veces (entrada/salida) => O(n).
Uso de memoria: O(h) por el stack (h = altura del arbol).
*/

#include <iostream>
#include <stack>
using namespace std;

struct Nodo {
    int key;
    Nodo* left;
    Nodo* right;
    Nodo(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
    Nodo* raiz;
public:
    BST() : raiz(nullptr) {}

    void insertar(int x) {
        if (!raiz) { raiz = new Nodo(x); return; }
        Nodo* cur = raiz;
        while (true) {
            if (x < cur->key) {
                if (!cur->left) { cur->left = new Nodo(x); return; }
                cur = cur->left;
            } else if (x > cur->key) {
                if (!cur->right) { cur->right = new Nodo(x); return; }
                cur = cur->right;
            } else return;
        }
    }

    Nodo* getRoot() const { return raiz; }
};

bool existeCaminoSumaK(Nodo* raiz, int K, stack<int>& camino) {
    while (!camino.empty()) camino.pop();
    if (!raiz) return false;

    struct Frame {
        Nodo* n;
        int state;
        int suma;
    };

    stack<Frame> st;
    st.push({raiz, 0, raiz->key});
    camino.push(raiz->key);

    while (!st.empty()) {
        Frame &top = st.top();
        Nodo* u = top.n;

        if (!u->left && !u->right) {
            if (top.suma == K) return true;
        }

        if (top.state == 0) {
            top.state = 1;
            if (u->left) {
                st.push({u->left, 0, top.suma + u->left->key});
                camino.push(u->left->key);
            }
        } else if (top.state == 1) {
            top.state = 2;
            if (u->right) {
                st.push({u->right, 0, top.suma + u->right->key});
                camino.push(u->right->key);
            }
        } else {
            st.pop();
            camino.pop();
        }
    }

    return false;
}

void imprimirCamino(stack<int> camino) {
    stack<int> aux;
    while (!camino.empty()) { aux.push(camino.top()); camino.pop(); }
    while (!aux.empty()) { cout << aux.top() << " "; aux.pop(); }
    cout << "\n";
}

int main() {
    BST bst;
    for (int v : {10, 5, 15, 3, 7, 18}) bst.insertar(v);

    int K = 22;
    stack<int> camino;

    cout << "K = " << K << "\n";
    if (existeCaminoSumaK(bst.getRoot(), K, camino)) {
        cout << "Existe camino raiz-hoja con suma K: ";
        imprimirCamino(camino);
    } else {
        cout << "No existe camino raiz-hoja con suma K.\n";
    }

    return 0;
}
    /*
    Ejemplo (BST):
    10
    / \
    5  15
    / \  \
    3  7  18

    Camino 10->5->7 suma = 22
    */