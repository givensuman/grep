#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_substring(char *line, char *target, int index_of_target) {
  for (int i = 0; i < index_of_target; i++) {
    printf("%c", line[i]);
  }
  printf("\033[1;31m%s\033[0m", target);
  for (int i = index_of_target + strlen(target); i < strlen(line); i++) {
    printf("%c", line[i]);
  }
}

int main(int argc, char **argv) {
  char *line = NULL;
  size_t line_length = 0;
  ssize_t read;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <target> <file/stream>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *target = argv[1];

  FILE *file = fopen(argv[2], "r");
  if (file == NULL) {
    fprintf(stderr, "Could not read file %s.\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  while ((read = getline(&line, &line_length, file)) != -1) {
    Node *match = kmp_search(target, line);
    while (match != NULL) {
      print_substring(line, target, match->data);
      match = match->next;
    }
  }

  fclose(file);
  if (line)
    free(line);

  exit(EXIT_SUCCESS);
}
