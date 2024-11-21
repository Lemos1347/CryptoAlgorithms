CC = gcc
CFLAGS = -O3
TARGETS = caesar monoalphabetic vigenere

all: $(TARGETS)

caesar: ./src/caesar_cipher.c
	$(CC) $(CFLAGS) -o caesar ./src/caesar_cipher.c

monoalphabetic: ./src/monoalphabetic_substitution_cipher.c
	$(CC) $(CFLAGS) -o monoalphabetic ./src/monoalphabetic_substitution_cipher.c

vigenere: ./src/vigenere_cipher.c
	$(CC) $(CFLAGS) -o vigenere ./src/vigenere_cipher.c

clean:
	rm -f $(TARGETS)

rebuild: clean all
