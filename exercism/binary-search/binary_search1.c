#include "binary_search.h"

// Iterative approach
const int *binary_search(int value, const int *arr, size_t length)
{
  int left = 0, right = length - 1;
  int mid;
  while (left <= right) {
    mid = (left + right) / 2;
    if (arr[mid] == value) return &(arr[mid]);
    if (arr[mid] > value) right = mid - 1;
    else left = mid + 1;
  }
  return NULL;
}
