#include <stdio.h>

#define MAX_PEOPLE 100000

// This is an Union-Find solution.

int find(int person, int parent[]) {
  int temp, community = person;
  // Find the representative.
  while (parent[community] != community)
    community = parent[community];

  // Path compression optimization: Make all nodes along the path be
  // children of the representative.
  while (parent[person] != community) {
    temp = parent[person];
    parent[person] = community;
    person = temp;
  }

  return community;
}

void union_communities(int p1, int p2, int parent[], int size[], int max_size) {
  int c1, c2;
  c1 = find(p1, parent);
  c2 = find(p2, parent);

  // Note that we don't need to update the size of the absorbed community,
  // since it no longer exists.
  if (c1 != c2 && size[c1] + size[c2] <= max_size) {
    // Perform a union by size optimization.
    if (size[c1] > size[c2]) {
      parent[c2] = c1;
      size[c1] += size[c2];
    } else {
      parent[c1] = c2;
      size[c2] += size[c1];
    }
  }
}

int main() {
  // For each representative i, size[i] is the number of people in its community.
  // For each node i, parent[i] is its parent.
  static int parent[MAX_PEOPLE + 1], size[MAX_PEOPLE + 1];
  int num_people, max_size, num_ops, i;
  int person1, person2;
  char op;

  scanf("%d%d", &num_people, &max_size);
  for (i = 1; i <= num_people; i++) {
    parent[i] = i;
    size[i] = 1;
  }

  scanf("%d", &num_ops);
  for (i = 0; i < num_ops; i++) {
    // Important starting space to jump whitespace in input.
    scanf(" %c", &op);

    if (op == 'A') {
      scanf("%d%d", &person1, &person2);
      union_communities(person1, person2, parent, size, max_size);
    }

    else if (op == 'E') {
      scanf("%d%d", &person1, &person2);
      if (find(person1, parent) == find(person2, parent))
        printf("Yes\n");
      else
        printf("No\n");
    }
    
    else {
      scanf("%d", &person1);
      printf("%d\n", size[find(person1, parent)]);
    }
  }
}
