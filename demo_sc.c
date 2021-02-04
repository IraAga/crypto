#include"hy457_crypto.h"

int
main(int argc, char **argv)
{
	if (argc < 3) {
		printf("args: <message> <circumference>\n");
		exit(1);
	}

	int key;
	int pt_size;
	uint8_t *plaintext;
	uint8_t *ciphertext;
	uint8_t *decrypted;

	plaintext = strdup(argv[1]);
	key = atoi(argv[2]);
	ciphertext = strdup(plaintext);
	pt_size = strlen(plaintext);
	
	if ( key < 0) {
		printf("Give a valid key value!Should be greater than 2\n");
		exit (1);
	}

	if ( key > (pt_size - 1)) {
		printf("Number of lines should be greater than the plaintext size\n");
		exit(1);
	}

	printf("Message:%s\n", plaintext);
	printf("key: %d\n", key);
	printf("Message Length: %d\n", strlen(plaintext));

	ciphertext = spartan_encrypt(plaintext, key);

	printf("Ciphertext:%s\n", ciphertext);

	decrypted = spartan_decrypt(ciphertext, key);
	printf("Decrypted Message:%s\n", decrypted);
	return 0;
}
