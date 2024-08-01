#include <stdio.h>

#define MAX_RECEIPTS 1000000

#define LEFT(i) (2*(i))
#define RIGHT(i) (LEFT(i) + 1)
#define PARENT(i) ((i) / 2)

typedef struct {
  int receipt_index;
  int cost;
} heap_element;

typedef int (*cmp_func)(const heap_element, const heap_element);

void swap(heap_element *a, heap_element *b) {
    heap_element temp = *a;
    *a = *b;
    *b = temp;
}

void heap_insert(heap_element heap[], int *num_heap, int receipt_index, int cost, cmp_func more_priority) {
  int i;

  (*num_heap)++;
  heap[*num_heap] = (heap_element){receipt_index, cost};

  i = *num_heap;
  while (i > 1 && more_priority(heap[i], heap[PARENT(i)])) {
    swap(&heap[i], &heap[PARENT(i)]);
    i = PARENT(i);
  }
}

heap_element heap_extract(heap_element heap[], int *num_heap, cmp_func more_priority) {
  heap_element root;
  int i, left, right, prioritary;

  root = heap[1];
  heap[1] = heap[*num_heap];
  (*num_heap)--;

  prioritary = i = 1;
  while (LEFT(i) <= *num_heap) {
    left = LEFT(i);
    right = RIGHT(i);

    if (more_priority(heap[left], heap[prioritary]))
      prioritary = left;
    if (right <= *num_heap && more_priority(heap[right], heap[prioritary]))
      prioritary = right;

    if (prioritary != i)
      swap(&heap[i], &heap[prioritary]);
    else
      break;

    i = prioritary;
  }

  return root;
}

int less(const heap_element a, const heap_element b) {
  return a.cost < b.cost;
}

int greater(const heap_element a, const heap_element b) {
  return a.cost > b.cost;
}

int main() {
  static int used[MAX_RECEIPTS] = {0};
  static heap_element max_heap[MAX_RECEIPTS + 1];
  static heap_element min_heap[MAX_RECEIPTS + 1];
  int num_days, receipt_index_today, receipt_index = 0;

  // The total_prizes could be up to 5 billion.
  long long total_prizes = 0;

  int i, j, cost;
  int max_num_heap = 0, min_num_heap = 0;
  heap_element max_element, min_element;

  scanf("%d", &num_days);

  for (i = 0; i < num_days; i++) {
    scanf("%d", &receipt_index_today);
    for (j = 0; j < receipt_index_today; j++) {
      scanf("%d", &cost);
      heap_insert(max_heap, &max_num_heap, receipt_index, cost, greater);
      heap_insert(min_heap, &min_num_heap, receipt_index, cost, less);
      receipt_index++;
    }

    max_element = heap_extract(max_heap, &max_num_heap, greater);
    while (used[max_element.receipt_index])
      max_element = heap_extract(max_heap, &max_num_heap, greater);
    used[max_element.receipt_index] = 1;

    min_element = heap_extract(min_heap, &min_num_heap, less);
    while (used[min_element.receipt_index])
      min_element = heap_extract(min_heap, &min_num_heap, less);
    used[min_element.receipt_index] = 1;

    total_prizes += max_element.cost - min_element.cost;
  }
  printf("%lld\n", total_prizes);
  return 0;
}
