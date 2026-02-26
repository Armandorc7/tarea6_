#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

/*
Problema 2: Red-Black Tree

ANALISIS MATEMATICO (altura O(log n)):
Sea bh(x) el black-height (nro de negros en un camino desde x hasta NIL).
Lema: un subarbol con bh(x)=b tiene al menos 2^b - 1 nodos internos.
Entonces n >= 2^bh(raiz) - 1  =>  bh(raiz) <= log2(n+1).
Como no hay dos rojos consecutivos, en cualquier camino h <= 2*bh(raiz),
por tanto h <= 2*log2(n+1) = O(log n).
*/

enum Color { RED, BLACK };

struct Nodo {
    int key;
    Color color;
    Nodo *left, *right, *parent;
    Nodo(int k=0, Color c=BLACK): key(k), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct NodoBST {
    int key; NodoBST *left, *right;
    NodoBST(int k): key(k), left(nullptr), right(nullptr) {}
};

class BST {
    NodoBST* raiz;
public:
    BST(): raiz(nullptr) {}
    void insertar(int x){
        if(!raiz){ raiz=new NodoBST(x); return; }
        NodoBST* cur=raiz;
        while(true){
            if(x<cur->key){ if(!cur->left){ cur->left=new NodoBST(x); return; } cur=cur->left; }
            else if(x>cur->key){ if(!cur->right){ cur->right=new NodoBST(x); return; } cur=cur->right; }
            else return;
        }
    }
    int alturaBFS() const{
        if(!raiz) return -1;
        queue<NodoBST*> q; q.push(raiz);
        int h=-1;
        while(!q.empty()){
            int sz=(int)q.size(); h++;
            while(sz--){
                auto u=q.front(); q.pop();
                if(u->left) q.push(u->left);
                if(u->right) q.push(u->right);
            }
        }
        return h;
    }
};

class RBT {
    Nodo* raiz;
    Nodo* NIL;

    void rotI(Nodo* x){
        Nodo* y=x->right;
        x->right=y->left;
        if(y->left!=NIL) y->left->parent=x;

        y->parent=x->parent;
        if(x->parent==NIL) raiz=y;
        else if(x==x->parent->left) x->parent->left=y;
        else x->parent->right=y;

        y->left=x; x->parent=y;
    }

    void rotD(Nodo* x){
        Nodo* y=x->left;
        x->left=y->right;
        if(y->right!=NIL) y->right->parent=x;

        y->parent=x->parent;
        if(x->parent==NIL) raiz=y;
        else if(x==x->parent->right) x->parent->right=y;
        else x->parent->left=y;

        y->right=x; x->parent=y;
    }

    void fixInsert(Nodo* z){
        while(z->parent->color==RED){
            Nodo* gp=z->parent->parent;
            if(z->parent==gp->left){
                Nodo* tio=gp->right;
                if(tio->color==RED){
                    z->parent->color=BLACK; tio->color=BLACK; gp->color=RED; z=gp;
                }else{
                    if(z==z->parent->right){ z=z->parent; rotI(z); }
                    z->parent->color=BLACK; gp->color=RED; rotD(gp);
                }
            }else{
                Nodo* tio=gp->left;
                if(tio->color==RED){
                    z->parent->color=BLACK; tio->color=BLACK; gp->color=RED; z=gp;
                }else{
                    if(z==z->parent->left){ z=z->parent; rotD(z); }
                    z->parent->color=BLACK; gp->color=RED; rotI(gp);
                }
            }
        }
        raiz->color=BLACK;
    }

    int verifyBH(Nodo* n) const{
        if(n==NIL) return 0;
        if(n->color==RED){
            if(n->left->color==RED) return -1;
            if(n->right->color==RED) return -1;
        }
        int L=verifyBH(n->left), R=verifyBH(n->right);
        if(L==-1 || R==-1 || L!=R) return -1;
        return L + (n->color==BLACK ? 1 : 0);
    }

public:
    RBT(){
        NIL=new Nodo(0,BLACK);
        NIL->left=NIL->right=NIL->parent=NIL;
        raiz=NIL;
    }

    void insertar(int x){
        Nodo* z=new Nodo(x,RED);
        z->left=z->right=z->parent=NIL;

        Nodo* y=NIL;
        Nodo* cur=raiz;
        while(cur!=NIL){
            y=cur;
            if(x<cur->key) cur=cur->left;
            else if(x>cur->key) cur=cur->right;
            else { delete z; return; }
        }
        z->parent=y;
        if(y==NIL) raiz=z;
        else if(x<y->key) y->left=z;
        else y->right=z;

        fixInsert(z);
    }

    bool verificar() const{
        if(raiz!=NIL && raiz->color!=BLACK) return false;
        return verifyBH(raiz)!=-1;
    }

    int alturaBFS() const{
        if(raiz==NIL) return -1;
        queue<Nodo*> q; q.push(raiz);
        int h=-1;
        while(!q.empty()){
            int sz=(int)q.size(); h++;
            while(sz--){
                auto u=q.front(); q.pop();
                if(u->left!=NIL) q.push(u->left);
                if(u->right!=NIL) q.push(u->right);
            }
        }
        return h;
    }

    void preorden() const{
        cout << "Preorden: ";
        if(raiz==NIL){ cout << "\n"; return; }
        stack<Nodo*> st; st.push(raiz);
        while(!st.empty()){
            Nodo* n=st.top(); st.pop();
            cout << n->key << (n->color==RED?"R":"B") << " ";
            if(n->right!=NIL) st.push(n->right);
            if(n->left!=NIL) st.push(n->left);
        }
        cout << "\n";
    }
};

int main(){
    const int N=20;
    RBT rbt;
    BST bst;

    for(int i=1;i<=N;i++){ rbt.insertar(i); bst.insertar(i); }

    cout << "N="<<N<<"\n";
    cout << "Altura BST: " << bst.alturaBFS() << "\n";
    cout << "Altura RBT: " << rbt.alturaBFS() << "\n";
    cout << "RB valido?  " << (rbt.verificar() ? "SI" : "NO") << "\n";
    rbt.preorden();
    return 0;
}