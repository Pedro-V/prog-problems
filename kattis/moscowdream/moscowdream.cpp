#include <cstdio>

int main() {
  int a, b, c, n;
  scanf("%d %d %d %d", &a, &b, &c, &n);
  if (
      n >= 3
      and a >= 1 and b >= 1 and c >= 1
      and (a + b + c) >= n
  ) {
    printf("YES\n");
  }
  else {
    printf("NO\n");
  }
}
