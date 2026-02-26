#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

/*
Problema 1: BST Iterativo y Analisis de Degradacion

ANALISIS (degradacion):
Insertando en orden ascendente k1<k2<...<kn, cada ki cae siempre al hijo derecho,
entonces el BST se vuelve una lista hacia la derecha y su altura h = n-1 = O(n).
Por eso buscar/insert/eliminar pasan de O(log n) a O(n).
Ademas el costo total de insertar n elementos ordenados es:
  sum_{i=1}^{n} (i-1) = n(n-1)/2 = Theta(n^2).
*/

template<typename T>
struct Nodo {
    T x;
    Nodo<T>* left;
    Nodo<T>* right;
    Nodo<T>* padre;
    Nodo(T dato) {
        x = dato;
        left = nullptr;
        right = nullptr;
        padre = nullptr;
    }
};

template<typename T>
class BST {
    Nodo<T>* raiz;

public:
    BST(): raiz(nullptr) {}

    // Insercion iterativa (con padre, como en tus labs)
    void insertar(T dato) {
        if (raiz == nullptr) {
            raiz = new Nodo<T>(dato);
            return;
        }

        Nodo<T>* cur = raiz;
        Nodo<T>* p = nullptr;

        while (cur != nullptr) {
            p = cur;
            if (dato < cur->x) cur = cur->left;
            else if (dato > cur->x) cur = cur->right;
            else return; // duplicado
        }

        Nodo<T>* nuevo = new Nodo<T>(dato);
        nuevo->padre = p;

        if (dato < p->x) p->left = nuevo;
        else p->right = nuevo;
    }

    // Eliminacion iterativa (0,1,2 hijos)
    void eliminar(T dato) {
        Nodo<T>* cur = raiz;
        Nodo<T>* p = nullptr;

        while (cur != nullptr && cur->x != dato) {
            p = cur;
            if (dato < cur->x) cur = cur->left;
            else cur = cur->right;
        }
        if (cur == nullptr) return; // no existe

        // si tiene 2 hijos -> usar sucesor (min del right)
        if (cur->left != nullptr && cur->right != nullptr) {
            Nodo<T>* padreSucc = cur;
            Nodo<T>* succ = cur->right;
            while (succ->left != nullptr) {
                padreSucc = succ;
                succ = succ->left;
            }
            cur->x = succ->x;    // copiar dato
            // ahora borramos succ (0 o 1 hijo)
            p = padreSucc;
            cur = succ;
        }

        // 0 o 1 hijo
        Nodo<T>* hijo = (cur->left != nullptr) ? cur->left : cur->right;

        if (hijo != nullptr) hijo->padre = p;

        if (p == nullptr) {
            raiz = hijo; // borrando raiz
        } else if (p->left == cur) {
            p->left = hijo;
        } else {
            p->right = hijo;
        }

        delete cur;
    }

    // Inorden iterativo con stack
    void inorder() const {
        stack<Nodo<T>*> st;
        Nodo<T>* cur = raiz;

        while (cur != nullptr || !st.empty()) {
            while (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top(); st.pop();
            cout << cur->x << " ";
            cur = cur->right;
        }
        cout << endl;
    }

    // Altura iterativa (en aristas). Vacio -> -1 (como tus labs)
    int altura() const {
        if (raiz == nullptr) return -1;

        stack<pair<Nodo<T>*, int>> st;
        st.push({raiz, 0});
        int h = 0;

        while (!st.empty()) {
            auto par = st.top(); st.pop();
            Nodo<T>* n = par.first;
            int d = par.second;

            h = max(h, d);
            if (n->left)  st.push({n->left, d+1});
            if (n->right) st.push({n->right, d+1});
        }
        return h;
    }
};

int main() {
    BST<int> bst;

    cout << "Insertando 1..20 en orden ascendente:\n";
    for (int i = 1; i <= 20; i++) bst.insertar(i);

    cout << "Altura (esperada 19): " << bst.altura() << endl;

    bst.eliminar(10);
    bst.eliminar(15);

    cout << "Inorder: ";
    bst.inorder();
    cout << "Altura: " << bst.altura() << endl;

    return 0;
}