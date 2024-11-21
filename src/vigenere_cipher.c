#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void vigenere_cipher(const char *text, const char *key, int decrypt,
                     char *result) {
  size_t text_len = strlen(text);
  size_t key_len = strlen(key);
  size_t key_index = 0;

  for (size_t i = 0; i < text_len; i++) {
    char c = text[i];
    if (isalpha(c)) {
      char base = islower(c) ? 'a' : 'A';
      char key_char = islower(key[key_index]) ? tolower(key[key_index])
                                              : toupper(key[key_index]);
      int shift = key_char - 'A';

      if (decrypt) {
        result[i] = base + (c - base - shift + 26) % 26;
      } else {
        result[i] = base + (c - base + shift) % 26;
      }

      key_index = (key_index + 1) % key_len;
    } else {
      result[i] = c;
    }
  }
  result[text_len] = '\0';
}

int validate_key_vigenere(const char *key) {
  for (size_t i = 0; i < strlen(key); i++) {
    if (!isalpha(key[i])) {
      return 0;
    }
  }
  return 1;
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

  if (!validate_key_vigenere(key)) {
    printf("Chave inválida! Deve conter apenas caracteres alfabéticos.\n");
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

  vigenere_cipher(text, key, decrypt, result);

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
