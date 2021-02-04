#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<fcntl.h>
#include<ctype.h>
#include<unistd.h>

#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define RESET "\e[0;40m"
#define WHITE_GREEN "\e[0;42m"


/* One-Time Pad Encr/Decr */
void print_key(uint8_t *key, int size);
void print_plaintext(uint8_t *plaintext, int size);
void print_ciphertext(uint8_t *ciphertext, int size); 

uint8_t * generate_otp_key(int size); 

uint8_t * otp_encrypt(uint8_t *plaintext, uint8_t *key);

uint8_t * otp_decrypt(uint8_t *ciphertext, uint8_t *key);


/* Caesar's Alphabet */
extern char letters[62];

int search_letter(char letter);

uint8_t * caesar_encrypt(uint8_t *plaintext, ushort N);

uint8_t * caesar_decrypt(uint8_t *ciphertext, ushort N);


/* Spartan's Cipher */
int round_i(float num);

uint8_t * spartan_encrypt(uint8_t *plaintext, int circ);

int count_pad_char(uint8_t *ciphertext);

uint8_t * spartan_decrypt(uint8_t *ciphertext, int circ);

/* Vigenere's Cipher */
extern uint8_t dump[26];

uint8_t **init_alphabet(void);

int find_column(uint8_t **alphabet, uint8_t letter);

int find_row(uint8_t **alphabet, uint8_t letter);

int find_cordinate(uint8_t **alphabet, uint8_t letter, int row);

uint8_t  * vigenere_encrypt(uint8_t *plaintext, uint8_t *key);

uint8_t * vigenere_decrypt(uint8_t *plaintext, uint8_t *key);
