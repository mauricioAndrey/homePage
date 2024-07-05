#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//=======================================================================

typedef int E; typedef int Key;

typedef struct BSTNode{
    E element;
    Key key;
    int height;
    int depth;
    BSTNode* left;
    BSTNode* right;
}BSTNode;
 
class BST{
    private:
        BSTNode* root;
        int nodecount;
        //helpPrincipal-------------------------------------------------
        BSTNode* inserthelp(BSTNode* rt, Key k, E e){
            if(rt == nullptr){
                BSTNode* temp = new BSTNode;
                temp->key = k; 
                temp->element = e;
                temp->left = nullptr;
                temp->right = nullptr;
                return temp;
            }
            if(rt->key > k){
                rt->left = inserthelp(rt->left, k, e);
            }
            else{
                rt->right = inserthelp(rt->right, k, e);
            }
            return rt;
        }
        BSTNode* removehelp(BSTNode* rt, Key k){
            if(rt==nullptr) return nullptr;
            if(rt->key>k){
                rt->left = removehelp(rt->left, k);
            }
            else if(rt->key < k){
                rt->right = removehelp(rt->right, k);
            }
            else{
                if(rt->left==nullptr) return rt->right;
                else if(rt->right == nullptr) return rt->left;
                else{
                    BSTNode* temp = getmin(rt->right);
                    rt->element = temp->element;
                    rt->key = temp->key;
                    rt->right = deletemin(rt->right);
                }
            }
        }
        E findhelp(BSTNode* rt, Key k){
            if(rt==nullptr) return E();
            if(rt->key > k) 
                return findhelp(rt->left, k);
            else if(rt->key == k)
                return rt->element;
            else 
                return findhelp(rt->right, k);
        }
        //min------------------------------------------------------------
        BSTNode* getmin(BSTNode* rt){
            if(rt->left == nullptr) return rt;
            return getmin(rt->left);
        }
        BSTNode* deletemin(BSTNode* rt){
            if(rt->left == nullptr) return rt->right;
            rt->left = deletemin(rt->left);
            return rt;
        }
        //helpSub--------------------------------------------------------
        void clearhelp(BSTNode* rt){
            if(rt!= nullptr){
                clearhelp(rt->left);
                clearhelp(rt->right);
                //delete[] rt;
                delete rt;
            }
        }
        //print----------------------------------------------------------
        void printTab(int level){
            while(level>=0){
                cout << "\t";
                level--;
            }
        }
        void printhelpTree(BSTNode* rt, int level){
            if(rt!=nullptr){
                printhelpTree(rt->left, level+1);
                
                printTab(level);
                cout << "Nivel " << level << ": \n";
                printTab(level);
                cout << "Elemento: "<< rt->element << ", Chave: " << rt->key << endl;
                
                printhelpTree(rt->right, level+1);
            }
        }
        //order----------------------------------------------------------
        void preorder(BSTNode* rt){
            if(rt!=nullptr){
                //do something here
                preorder(rt->left);
                preorder(rt->right);
            }
        }
        void inorder(BSTNode* rt){
            if(rt!=nullptr){
                inorder(rt->left);
                //do something here
                inorder(rt->right);
            }
        }
        void posorder(BSTNode* rt){
            if(rt!=nullptr){
                posorder(rt->left);
                posorder(rt->right);
                //do something here
            }
        }

    public:
        BST(){
            this->root = nullptr;
            nodecount = 0;
        }
        ~BST(){
            clearhelp(this->root);
        }
        //limpa----------------------------------------------------------
        void clear(){
            clearhelp(this->root);
            this->root = nullptr;
            nodecount=0;        
        }
        //operacoes----------------------------------------------------------
        void insert(Key k, E e){
            root = inserthelp(root, k, e);
            nodecount++;
        }
        E remove(Key k){
            E temp = findhelp(root, k);
            if(temp != E()){
                root = removehelp(root, k);
                nodecount--;
            }
            return temp;
        }
        E find(Key k){
            return findhelp(root, k);
        }
        //printa----------------------------------------------------------
        void printTree(){
            printhelpTree(this->root, 0);
        }

};

//-----------------------------------------------------------------------

void usarBST(){
    BST arvore;
    
    int escolha = 5; 
    E elemento; Key chave; 

    cout << "1. Limpar\n2. Inserir\n3. Remover\n4. Encontrar\n5. Sair\n";
    do{
        cout << "Escolha: "; cin >> escolha;
        switch (escolha)
        {
        case 1:
            arvore.clear();
            break;
        case 2:
            cout << "Chave: "; cin >> chave;
            cout << "Elemento: "; cin >> elemento;
            arvore.insert(chave, elemento);
            break;
        case 3:
            cout << "Chave: "; cin >> chave;
            arvore.remove(chave);
            break;
        case 4:
            cout << "Chave: "; cin >> chave;
            elemento = arvore.find(chave);
            break;
        case 5:
            cout << "Saindo...\n";
            break;
        
        default:
            cout <<"Entrada invalida\n";
            break;
        }

        arvore.printTree();

    }while(escolha!=5);

}

//=======================================================================
