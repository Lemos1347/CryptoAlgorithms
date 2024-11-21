#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int validate_key(const char *key) {
  int seen[26] = {0};
  if (strlen(key) != 26) {
    return 0;
  }
  for (int i = 0; i < 26; i++) {
    if (!isalpha(key[i])) {
      return 0;
    }
    int index = toupper(key[i]) - 'A';
    if (seen[index]) {
      return 0;
    }
    seen[index] = 1;
  }
  return 1;
}

void substitution_cipher(const char *text, const char *key, int decrypt,
                         char *result) {
  char substitution[26];
  char reverse_substitution[26];
  for (int i = 0; i < 26; i++) {
    substitution[i] = toupper(key[i]);
    reverse_substitution[(int)(substitution[i] - 'A')] = 'A' + i;
  }

  for (size_t i = 0; i < strlen(text); i++) {
    char c = text[i];
    if (isalpha(c)) {
      char base = islower(c) ? 'a' : 'A';
      int index = c - base;
      if (decrypt) {
        result[i] = base + (reverse_substitution[index] - 'A');
      } else {
        result[i] = base + (substitution[index] - 'A');
      }
    } else {
      result[i] = c;
    }
  }
  result[strlen(text)] = '\0';
}

int main(int argc, char *argv[]) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  if (argc != 4) {
    printf("Uso: %s -e|-d key text\n", argv[0]);
    return 1;
  }

  const char *mode = argv[1];
  const char *key = argv[2];
  const char *text = argv[3];

  if (!validate_key(key)) {
    printf("Chave inválida! Deve conter 26 caracteres únicos e alfabéticos.\n");
    return 1;
  }

  int decrypt = strcmp(mode, "-d") == 0;
  if (strcmp(mode, "-e") != 0 && strcmp(mode, "-d") != 0) {
    printf("Modo inválido! Use -e para criptografar ou -d para "
           "descriptografar.\n");
    return 1;
  }

  char *result = malloc(strlen(text) + 1);
  if (!result) {
    printf("Erro ao alocar memória!\n");
    return 1;
  }

  substitution_cipher(text, key, decrypt, result);

  if (decrypt) {
    printf("Texto descriptografado: %s\n", result);
  } else {
    printf("Texto criptografado: %s\n", result);
  }

  free(result);

  clock_gettime(CLOCK_MONOTONIC, &end);
  long seconds = end.tv_sec - start.tv_sec;
  long nanoseconds = end.tv_nsec - start.tv_nsec;
  long elapsed_time = seconds * 1e9 + nanoseconds;

  printf("Tempo de execução: %ld nanosegundos\n", elapsed_time);
  return 0;
}
