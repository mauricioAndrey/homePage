#include <iostream>
#include <vector>
using namespace std;

struct mochila{
    int itens, capacity;
    vector<int> w, v;
    vector<vector<int>> F;
    mochila(int size, int cap){
        itens = size;
        capacity = cap;
        w.resize(itens+1,0);
        v.resize(itens+1, 0);
        F.resize(itens+1, vector<int>(capacity+1, -1));
    }
};

//knapsack bottom-up
int Knapsack(mochila *M){
    for(int i=0; i<=M->itens; i++)
        for(int j=0; j<=M->capacity; j++){
            if(i==0 || j==0)
                M->F[i][j] = 0;
            else if(M->w[i] <= j)
                M->F[i][j] = max(M->F[i-1][j], M->v[i] + M->F[i-1][j - M->w[i]]);
            else
                M->F[i][j] = M->F[i-1][j];
        }
    return M->F[M->itens][M->capacity];
}
//knapsack top-down
int MFKnapsack(int i, int j, mochila *M){
    int value;
    if(M->F[i][j]<0 && i>=1 && j>=1){
        if(j < M->w[i])
            value = MFKnapsack(i-1,j,M);
        else
            value = max(MFKnapsack(i-1,j,M), M->v[i] + MFKnapsack(i-1,j - M->w[i],M));
        M->F[i][j] = value;
    }
    if(M->F[i][j] == -1) return 0;
    return M->F[i][j];
}
