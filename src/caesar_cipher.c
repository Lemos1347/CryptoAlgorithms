#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Cipher {
  int key;
};

char shift_char(char input, int shift) {
  if (isalpha(input)) {
    char base = islower(input) ? 'a' : 'A';
    return (char)(((input - base + shift) % 26 + 26) % 26 + base);
  }
  return input;
}

const char *encrypt(const struct Cipher *cipher, const char *text) {
  char *result = malloc(strlen(text) + 1);
  if (result == NULL) {
    printf("Erro ao alocar memória!\n");
    return NULL;
  }

  for (int i = 0; i < strlen(text); i++) {
    result[i] = shift_char(text[i], cipher->key);
  }

  result[strlen(text)] = '\0';
  return result;
}

const char *decrypt(const struct Cipher *cipher, const char *text) {
  char *result = malloc(strlen(text) + 1);
  if (result == NULL) {
    printf("Erro ao alocar memória!\n");
    return NULL;
  }

  for (int i = 0; i < strlen(text); i++) {
    result[i] = shift_char(text[i], -cipher->key);
  }

  result[strlen(text)] = '\0';
  return result;
}

int main(int argc, char *argv[]) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  if (argc <= 1) {
    printf("You must pass an option: -d or -e\n");
    return 1;
  }

  char *option = argv[1];

  if (argc <= 2) {
    printf("No key passed!\n");
    return 1;
  }

  struct Cipher cipher;
  cipher.key = atoi(argv[2]);

  if (argc <= 3) {
    printf("No message passed!\n");
    return 1;
  }

  char *text = argv[3];

  if (strcmp(option, "-e") == 0) {
    const char *encryptedText = encrypt(&cipher, text);
    if (encryptedText == NULL) {
      return 1;
    }

    printf("Encrypted text: %s\n", encryptedText);

    free((void *)encryptedText);
  } else if (strcmp(option, "-d") == 0) {
    const char *dencryptedText = decrypt(&cipher, text);
    if (dencryptedText == NULL) {
      return 1;
    }

    printf("Encrypted text: %s\n", dencryptedText);

    free((void *)dencryptedText);
  } else {
    printf("Invalid option\n");
    return 1;
  }

  clock_gettime(CLOCK_MONOTONIC, &end);
  long seconds = end.tv_sec - start.tv_sec;
  long nanoseconds = end.tv_nsec - start.tv_nsec;
  long elapsed_time = seconds * 1e9 + nanoseconds;

  printf("Tempo de execução: %ld nanosegundos\n", elapsed_time);
  return 0;
}
