#include"crypto.h"

int
main (int argc, char **argv)
{

	if (argc < 2) {
		printf("run: ./demo_otp <message>\n");
		exit(1);
	}

	uint8_t *plaintext;
	int i;
	int len_pl;						/* length of the plaintext */
	uint8_t * otp_key;

	plaintext = strdup(argv[1]);	
	len_pl = strlen(plaintext);		/* get the size of plaintext */

	/* Generate otp key*/
	otp_key = generate_otp_key(len_pl);

	printf(GREEN"PLAINTEXT\n"RESET);
	print_plaintext(plaintext, len_pl);

	printf(RED"\nKey Generation...\n"RESET);

	printf(GREEN"KEY\n"RESET);
	print_key(otp_key, len_pl);

	/* Encryption */
	printf(RED"\nOne-Time Pad Encrypt...\n"RESET);
	uint8_t *ciphertext = otp_encrypt(plaintext, otp_key);

	printf(GREEN"CIPHERTEXT\n"RESET);
	print_ciphertext(ciphertext, len_pl);

	/* Decryption */
	plaintext = NULL;
	printf(RED"\nOne-Time Pad Decrypt...\n"RESET);
	plaintext = otp_decrypt(ciphertext, otp_key);


	printf(GREEN"PLAINTEXT\n"RESET);
	print_plaintext(plaintext, len_pl);
	
	return 0;
}



