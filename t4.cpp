/*
Problema 4: BFS Iterativo Avanzado

- Completo: en BFS, despues del primer hijo faltante, ya no debe aparecer ningun hijo.
- Ancho maximo: maximo tamaño de la cola por nivel.
- Profundidad minima: primera hoja encontrada en BFS (nivel mas cercano).
*/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Nodo {
    int val;
    Nodo* left;
    Nodo* right;
    Nodo(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool esCompleto(Nodo* raiz) {
    if (!raiz) return true;
    queue<Nodo*> q;
    q.push(raiz);

    bool encontroNulo = false;

    while (!q.empty()) {
        Nodo* n = q.front(); q.pop();

        if (n->left) {
            if (encontroNulo) return false;
            q.push(n->left);
        } else encontroNulo = true;

        if (n->right) {
            if (encontroNulo) return false;
            q.push(n->right);
        } else encontroNulo = true;
    }
    return true;
}

int anchoMaximo(Nodo* raiz) {
    if (!raiz) return 0;
    queue<Nodo*> q;
    q.push(raiz);

    int best = 0;

    while (!q.empty()) {
        int sz = (int)q.size();
        best = max(best, sz);

        for (int i = 0; i < sz; i++) {
            Nodo* n = q.front(); q.pop();
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
    return best;
}

int profundidadMinima(Nodo* raiz) {
    if (!raiz) return 0;
    queue<pair<Nodo*, int>> q;
    q.push({raiz, 1});

    while (!q.empty()) {
        auto par = q.front(); q.pop();
        Nodo* n = par.first;
        int d = par.second;

        if (!n->left && !n->right) return d;
        if (n->left) q.push({n->left, d + 1});
        if (n->right) q.push({n->right, d + 1});
    }
    return 0;
}

int main() {
    Nodo* r1 = new Nodo(1);
    r1->left  = new Nodo(2);
    r1->right = new Nodo(3);
    r1->left->left  = new Nodo(4);
    r1->left->right = new Nodo(5);
    r1->right->left = new Nodo(6);

    cout << (esCompleto(r1) ? "SI" : "NO") << "\n";
    cout << anchoMaximo(r1) << "\n";
    cout << profundidadMinima(r1) << "\n";

    Nodo* r2 = new Nodo(1);
    r2->left  = new Nodo(2);
    r2->right = new Nodo(3);
    r2->left->right = new Nodo(5);

    cout << (esCompleto(r2) ? "SI" : "NO") << "\n";
    cout << anchoMaximo(r2) << "\n";
    cout << profundidadMinima(r2) << "\n";

    return 0;
}