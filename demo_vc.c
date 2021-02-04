#include"hy457_crypto.h"

int
main(int argc, char **argv)
{
	if (argc < 3) {
		printf("args: <message> <key> \n");
		exit(1);
	}

	uint8_t *key;
	uint8_t *plaintext;
	uint8_t *ciphertext;
	uint8_t *decrypted;

	plaintext = strdup(argv[1]);
	key = strdup(argv[2]);
	ciphertext = malloc(strlen(plaintext));
	decrypted = malloc(strlen(plaintext));

	printf("Message: %s\n", plaintext);
	printf("Key: %s\n", key);

	ciphertext = vigenere_encrypt(plaintext, key);	

	printf("ciphertext:%s\n", ciphertext);
	
	key = strdup(argv[2]);	

	decrypted = vigenere_decrypt(ciphertext, key);
	printf("decrypted:%s\n", decrypted);

	return 0;
}
