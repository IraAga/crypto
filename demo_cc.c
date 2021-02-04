#include"crypto.h"

int 
main(int argc, char **argv)
{
	if (argc < 3) {
		printf("Usage: ./demo_cc <message> <shift_value>\n");
		exit (1);
	}

	uint8_t *plaintext;
	uint8_t *ciphertext;
	ushort key;
	int i;

	plaintext = strdup(argv[1]);
	key = (ushort)atoi(argv[2]);

	printf("Message:%s\n", plaintext);
	printf("Key: %d\n", key);

	ciphertext = caesar_encrypt(plaintext, key);

	plaintext = NULL;
	printf("Encrypted Message:%s\n", ciphertext);

	plaintext = caesar_decrypt(ciphertext, key);

	printf("Decrypted Message:%s\n", plaintext);

	return 0;
}
