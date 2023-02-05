#include<iostream>

using namespace std;

void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}

void selectionSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int min_pos = i;
		for (int j = i +1; j < n; j++) {
			if (a[j] < a[min_pos])
			min_pos = j;
		}
		swap(a[i], a[min_pos]);
	}
}

void insertionSort(int a[], int n) {
	for (int i = 1 ; i < n; i++) {
		int x = a[i];
		int pos = i -1;
		while (pos >= 0 && a[pos] > x) {
			a[pos + 1] = a[pos--];
		}
		a[pos + 1] = x;
	}
}

void interchangeSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++){
			if (a[j] < a[i]){
				swap(a[i],a[j]);
			}
		}
	}
}

void bubbleSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (a[j] < a[j-1])
			swap(a[j], a[j-1]);
		}
	}
}

void quickSort(int a[], int left, int right) {
	if (left < right) {
		int l = left, r = right;
		int pivot = a[(left + right)/ 2];
		do {
			while (a[l] < pivot)
			l++;
			while (a[r] > pivot)
			r--;
			if (l <= r) {
				swap(a[l],a[r]);
				l++;
				r--;
			}
		} while (l <= r);
		if (left < r)
			quickSort(a, left, r);
		if (l < right)
			quickSort(a, l, right);
	} 
}

int* merge(int *a, int n, int *b, int m) {
	int* c = new int[n + m];
	int i =0, j = 0, dem = 0;
	while (i < n && j < m) {
		if ( a[i] < b[j]) {
			c[dem++] = a[i++];
		} else 
			c[dem++] = b[j++];
	}
	for (int k = i; k < n; k++) {
		c[dem++] = a[k];
	}
	for (int k = j; k < m; k++) {
		c[dem++] = b[k];
	}
	
	return c;
}

int* mergeSort(int a[], int n) {
	if (n == 1)
		return a;
	int mid = n / 2;
	int *m1 = new int[mid];
	int *m2 = new int[n - mid];
	
	for (int i = 0; i < mid; i++)
		m1[i] = a[i];
	for (int i = 0; i < n - mid; i++)
		m2[i] = a[mid + i];
	m1 = mergeSort(m1, mid);
	m2 = mergeSort(m2, n - mid);
	
	return merge(m1, mid, m2, n-mid);
}

void heapify(int a[], int n, int i) {
	int left = 2*i + 1;
	int right = 2*i + 2;
	int max = i;
	if (left < n && a[left] > a[max]) 
		max = left;
	if (right < n && a[right] > a[max]) 
		max = right;
	if (max != i) {
		swap(a[i], a[max]);
		heapify(a, n, max);
	}
}

void heapSort(int a[], int n) {
	for (int i = n/2 -1; i >= 0; i--) {
		heapify(a, n, i);
	}
	for (int j = n -1; j > 0; j--) {
		swap(a[0], a[j]);
		heapify(a, j, 0);
	}
}


int main() {
	int a[] = {1, 3, 6, 7, 9, 2, 4, 8, 5};
	int n = sizeof(a)/sizeof(a[0]);
	
//	selectionSort(a, n);
//	insertionSort(a, n);
//	interchangeSort(a, n);	
//	bubbleSort(a, n);
	quickSort(a, 0, n - 1);
//	int* c = mergeSort(a, n );
	// heapSort(a, n);

	cout << "------------List--------------" << endl;
	
	
	for (int i = 0; i < n; i++) {
		cout << a[i] << "\t";
	}
	cout << endl;
	
	return 0;
}
