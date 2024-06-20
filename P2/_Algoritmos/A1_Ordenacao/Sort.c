#include <stdio.h>
#include <math.h>

#define TAM 5

void swap(int* a, int* b){
    int temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}

//=================================================================

void bubbleSort(int vetor[]){
    for(int i=0; i<TAM; i++){
        for(int j = i+1; j<TAM-1; j++){
            if(vetor[i] > vetor[j]){
                swap(&vetor[i], &vetor[j]);
            }
        }
    }
}

void selectionSort(int A[]){
    for(int i=0; i<TAM-1; i++){
	    int min = i;
        for(int j = i+1; j<TAM; j++)
            if(A[j] < A[min]) min = j;
        swap (A[i],A[min]);
    }
}

void insertionSort(int A[]){
    for(int i=1; i<TAM; i++){
        int v = A[i], j = i-1;
        while(j>=0 && A[j]>v){
            A[j+1] = A[j]; j--;
        }
        A[j+1] = v;
    }
}

void mergesort(int A[], int l, int r){
	if(l<r){
		int m = floor((((float)l+(float)r)/2));
		mergesort(A, l, m);
		mergesort(A, m+1, r);
		merge(A, l, r);
	}
}
void Merge(int A[], int l, int r){
	int temp[r+1];
	for(int i=l; i<=r; i++)
		temp[i] = A[i];
	int m = floor((((float)l+(float)r)/2));
	int i1 = l, i2 = m+1;
	for(int curr = l; curr<=r; curr++){
		if(i1 == m+1) A[curr] = temp[i2++];
		else if(i2>r) A[curr] = temp[i1++];
		else if(temp[i1] <= temp[i2]) A[curr] = temp[i1++];
		else A[curr] = temp[i2++];
	}
}

void quicksort(int A[], int l, int r){
	int s = HoarePartition(A, l, r);
	quicksort(A, l, s-1);
	quicksort(A, s+1, r);
}
int HoarePartition(int A[], int l, int r){
	int p = A[l]; 
	int i = l;
	int j = r+1;
	do{
		do{
			i++;
		}while(!(A[i]>=p || i>= r));
		do{
			j--;
		}while(!(A[i] <=p ));
		swap(A[i], A[j]);
	}while(!(i>=j));
	swap(A[i], A[j]);
	swap(A[l], A[j]);
	return j;
}

//=================================================================

