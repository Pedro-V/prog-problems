#include <stdio.h>

#define MAX_SOLDIERS 100000

int main() {
  int soldiers[MAX_SOLDIERS + 1][2];
  int i, num_soldiers, num_reports;
  int left, right, living_left, living_right;

  while (scanf("%d %d", &num_soldiers, &num_reports)) {
    if (num_soldiers == 0)
      break;

    for (i = 1; i <= num_soldiers; i++) {
      soldiers[i][0] = i - 1 < 1 ? -1 : i - 1;
      soldiers[i][1] = i + 1 > num_soldiers ? -1 : i + 1;
    }

    for (i = 0; i < num_reports; i++) {
      scanf("%d %d", &left, &right);
      living_left = soldiers[left][0];
      living_right = soldiers[right][1];

      if (living_left == -1)
        printf("* ");
      else {
        printf("%d ", living_left);
        soldiers[living_left][1] = living_right;
      }

      if (living_right == -1)
        printf("*\n");
      else {
        printf("%d\n", living_right);
        soldiers[living_right][0] = living_left;
      }
    }
    printf("-\n");
  }
  return 1;
}
