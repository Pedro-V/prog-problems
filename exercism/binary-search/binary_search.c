#include "binary_search.h"

const int *binary_search_helper(int, const int*, int, int);
const int *binary_search_helper(int value, const int *arr, int a, int b)
{
  if (a > b) return NULL;
  int mid = (a + b) / 2;
  if (arr[mid] == value) return &(arr[mid]);
  if (arr[mid] > value) return binary_search_helper(value, arr, a, mid - 1);
  return binary_search_helper(value, arr, mid + 1, b);
}

// Recursive approach
const int *binary_search(int value, const int *arr, size_t length)
{
  return binary_search_helper(value, arr, 0, length - 1);
}
