#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define ISBN_LEN 13
#define AUTHOR_LEN 50
#define TITLE_LEN 100

typedef struct {
  char isbn[ISBN_LEN + 1];
  char author[AUTHOR_LEN + 1];
  char title[TITLE_LEN + 1];
} book;

typedef struct {
  int idx, calls;
} pair;

FILE* input = NULL, *output = NULL;

// Função de busca binária iterativa
pair binary_search(book* books , int num_books, char* isbn) {
  int mid, low = 0, high = num_books - 1;
  pair result = { -1, 1 };
  fflush(stdout);

  mid = (low + high) / 2;
  while (high >= low && (strcmp(books[mid].isbn, isbn) != 0)) {
    if (strcmp(books[mid].isbn, isbn) > 0)
      high = mid - 1;
    else
      low = mid + 1;
    mid = (low + high) / 2;
    result.calls++;
  }

  result.idx = strcmp(books[mid].isbn, isbn) == 0 ? mid : -1;
  return result;
}


int heuristic(book* books, int i, int j) {
  char **tmp_isbn = malloc(sizeof(ISBN_LEN + 1));
  uint64_t isbn_i = strtol(books[i].isbn, tmp_isbn, 10);
  uint64_t isbn_j = strtol(books[j].isbn, tmp_isbn, 10);
  return i + (isbn_j - isbn_i) % (j - i + 1);
}


pair interpolated_search(book* books, int num_books, char* isbn) {
  int guess, low = 0, high = num_books - 1;
  pair result = { -1, 1 };

  guess = heuristic(books, low, high);
  while (high >= low && guess != 0 && strcmp(books[guess].isbn, isbn) != 0) {
    if (strcmp(books[guess].isbn, isbn) > 0)
      high = guess - 1;
    else
      low = guess + 1;

    if (high >= low)
      guess = heuristic(books, low, high);
    else
      break;
    result.calls++;
  }

  result.idx = strcmp(books[guess].isbn, isbn) == 0 ? guess : -1;
  return result;
}

int main(int argc, char** argv){
  int i, num_books, num_queries;
  int binary_wins = 0, interpolated_wins = 0;
  int binary_calls, interpolated_calls;
  char isbn[ISBN_LEN + 1];
  book* books;

  input = fopen(argv[1], "r");
  output = fopen(argv[2], "w");
  if(!input || !output ){
    printf("Error opening files.\n");
    exit(EXIT_FAILURE);
  }

  fscanf(input, "%d", &num_books);
  books = malloc(sizeof(book) * num_books);
  for (i = 0; i < num_books; i++)
    fscanf(input, " %s %[^&]%*c%[^\n]", books[i].isbn, books[i].author, books[i].title);

  fscanf(input, "%d ", &num_queries);
  for (i = 0; i < num_queries; i++) {
    fscanf(input, " %s", isbn);
    pair binary_result = binary_search(books, num_books, isbn);
    pair interpolated_result = interpolated_search(books, num_books, isbn);
    binary_calls += binary_result.calls;
    interpolated_calls += interpolated_result.calls;

    fprintf(output, "[%s]B=%d,I=%d:", isbn, binary_result.calls, interpolated_result.calls);
    if (binary_result.idx == -1)
      fprintf(output, "ISBN_NOT_FOUND\n");
    else 
      fprintf(output, "Author:%s,Title:%s\n", books[binary_result.idx].author, books[binary_result.idx].title);

    if (interpolated_result.calls > binary_result.calls)
      binary_wins++;
    else
      interpolated_wins++;
  }

  fprintf(output, "BINARY=%d:%d\n", binary_wins, binary_calls / num_queries);
  fprintf(output, "INTERPOLATION=%d:%d\n", interpolated_wins,  interpolated_calls / num_queries);

  fclose(input);
  fclose(output);
}

