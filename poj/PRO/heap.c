#include <stdio.h>

#define MAX_RECEIPTS 1000000

#define parent_index(i) (i - 1)/2
#define left_index(i) (i * 2) + 1
#define right_index(i) (i * 2) + 2

typedef struct {
  int arr[MAX_RECEIPTS];
  int n;
} heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push_max(heap *h, int x) {
  int parent, curr = h->n;

  h->arr[curr] = x;
  h->n++;

  while (curr > 0) {
    parent = parent_index(curr);
    if (h->arr[curr] > h->arr[parent]) {
      swap(&h->arr[curr], &h->arr[parent]);
      curr = parent;
    }
    else
      break;
  }
}

void heapify_max(int arr[], int n) {
  int curr, left, right, prioritary;

  curr = 0;

  while (1) {
    left = left_index(curr);
    right = right_index(curr);

    if (left < n && arr[left] > arr[curr])
      prioritary = left;

    if (right < n && arr[right] > arr[curr])
      prioritary = right;

    if (prioritary != curr) {
      swap(&arr[prioritary], &arr[curr]);
      curr = prioritary;
    }
    else
      break;
  }

}

int pop_max(heap *h) {
  int root = h->arr[0];

  h->n--;
  h->arr[0] = h->arr[h->n];
  heapify_max(h->arr, h->n);

  return root;
}

void push_min(heap *h, int x) {
  int parent, curr = h->n;

  h->arr[curr] = x;
  h->n++;

  while (curr > 0) {
    parent = parent_index(curr);
    if (h->arr[curr] < h->arr[parent]) {
      swap(&h->arr[curr], &h->arr[parent]);
      curr = parent;
    }
    else
      break;
  }
}

void heapify_min(int arr[], int n) {
  int curr, left, right, prioritary;

  curr = 0;
  while (1) {
    left = left_index(curr);
    right = right_index(curr);

    if (left < n && arr[left] < arr[curr])
      prioritary = left;

    if (right < n && arr[right] < arr[curr])
      prioritary = right;

    if (prioritary != curr) {
      swap(&arr[prioritary], &arr[curr]);
      curr = prioritary;
    }
    else
      break;
  }
}

int pop_min(heap *h) {
  int root = h->arr[0];

  h->n--;
  h->arr[0] = h->arr[h->n];
  heapify_min(h->arr, h->n);

  return root;
}

int main() {
  heap max_h = {
    { 3, 1, 0 },
    3
  };

  push_max(&max_h, 10);
  int x = pop_max(&max_h);
	printf("%d %d\n", x, max_h.arr[0]);
}
