#include <stdio.h>

//=================================================================

int sequentialSearch(int A[], int n, int k){
	int i=0;
	while(i<n && A[i] != k)
		i++;
	if(i<n) return i;
	return -1;
}

//=================================================================

int binarySearch_recursive(int A[], int l, int r, int k){
	if(r>=l){
		int m = floor(((float)(l+r))/2);
		if(k == A[m]) return m;
		else if(k<A[m]) return BS(A, l, m-1, k);
		else return BS(A, m+1, r, k);
	}
	else return -1;
}
int binarySearch(int A[], int n, int k){
	int l=0;
	int r = n-1;
	while(l<=r){
		int m = floor(((float)(l+r))/2);
		if(k==A[m]) return m;
		else if(k<A[m]) r = m-1;
		else l = m+1;
	}
}

//=================================================================
