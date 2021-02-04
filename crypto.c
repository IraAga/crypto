#include"hy457_crypto.h"

/* print key in bytes/chars/ints */
void
print_key(uint8_t *key, int size) 
{
	int i;

	printf("%sPrinting Bytes of Key%s\n", YELLOW, RESET);
	for(i = 0; i < size; i++) {
		printf("%x ", key[i]);
	}
	printf("\n");

	printf("%sPrinting Chars of Key%s\n", YELLOW, RESET);
	for(i = 0; i < size; i++) {
		if (isprint(key[i]) != 0) printf("%c ", key[i]);
		else printf("** ");
	} 
	printf("\n");

	printf("%sPrinting Ints of Key%s\n", YELLOW, RESET);
	for(i = 0; i < size; i++) {
		printf("%d ", key[i]);
	}
	printf("\n");
}

/* print plaintext in bytes/chars/ints */
void
print_plaintext(uint8_t *plaintext, int size)
{
	int i;

	printf("%sPrinting Chars of Plaintext%s\n", YELLOW, RESET);
	for(i = 0; i < size; i++) {
		printf("%c ", plaintext[i]);
	}
	printf("\n");	
}

/* print the ciphertext in bytes/chars/ints */
void 
print_ciphertext(uint8_t *ciphertext, int size) 
{
	int i;

	printf("%sPrinting Bytes of Ciphertext%s\n", YELLOW, RESET);
	for(i = 0; i < size; i++) {
		printf("%02X ", ciphertext[i]);
	}
	printf("\n");	

	printf("%sPrinting Chars of Ciphertext%s\n", YELLOW, RESET);
	for(i = 0; i < size; i++) {
		if (isprint(ciphertext[i]) != 0) printf("%c ", ciphertext[i]);
		else printf("** ");
	}
	printf("\n");

	printf("%sPrinting Ints of Ciphertext%s\n", YELLOW, RESET);
	for(i = 0; i < size; i++) {
		printf("%d ", ciphertext[i]);
	} 
	printf("\n");	
}

/* Generate the One-Time Pad Encryption/Decryption Key */
uint8_t *
generate_otp_key(int size) 
{	
	int ur_fd; 		/* fd tou urandom */
	uint8_t *key;
	ssize_t res_rand;

	key = (uint8_t *)malloc(size);
	memset(key, 0, size);	/* initialize */

	/* Open to /dev/urandom */
	ur_fd =  open("/dev/urandom", O_RDONLY);
	if (ur_fd < 0) {
			printf("open FAILED\n");
			exit(1);
	} else {
		/* read len_pl bytes from /dev/urandom */
		res_rand = read(ur_fd, key, size);	
		if (res_rand == -1)	{
			printf("read FAILED\n");
		}
	}

	return key;
}

/* One-Time Pad encryption */
uint8_t *
otp_encrypt(uint8_t *plaintext, uint8_t *key) 
{

	int i;
	int size;

	size = strlen(plaintext);

	uint8_t tmp[size];
	uint8_t *cipher;

	for(i = 0; i < size; i++) {
		tmp[i] = plaintext[i] ^ key[i];
	}
	tmp[size] = '\0';
	cipher = strdup(tmp);

	return cipher;
}

/* One-Time Pad decryption */
uint8_t *
otp_decrypt(uint8_t *ciphertext, uint8_t *key) 
{

	int i;
	int size;

	size = strlen(ciphertext);

	uint8_t tmp[size];
	uint8_t *plaintext;

	for(i = 0; i < size; i++) {
		tmp[i] = ciphertext[i] ^ key[i];
	}
	tmp[size] = '\0';
	plaintext = strdup(tmp);

	return plaintext;
}


/* --- Caesar's Cipher --- */
char letters[62] = { 
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z'	
			};

/* Caesar's Cipher functions */
int 
search_letter(char letter)
{

	int i;

	for(i = 0; i < 62; i++) {
		if (letter == letters[i]) {
			return i;
		}
	}
	printf("Letter not found...This is not normal!\n");
	return -1;
}

/* Caesar's Cipher Encryption */
uint8_t *
caesar_encrypt(uint8_t *plaintext, ushort N)
{
	int i, index, new_index;
	uint8_t *ciphertext;

	ciphertext = (uint8_t *)malloc(strlen(plaintext));

	for (i = 0; i < strlen(plaintext); i++) {
		index = search_letter(plaintext[i]);
		if (index == -1) {
			printf("Letter not found...exiting\n");
			exit(1);
		}
		new_index = index + N;
		if (new_index >= 62) {
			/* wrap around */
			ciphertext[i] = letters[new_index - 62]; 
		} else {
			ciphertext[i] = letters[new_index];
		}
	}
	return ciphertext;
}

/* Caesar's Cipher Decryption */
uint8_t *
caesar_decrypt(uint8_t *ciphertext, ushort N)
{
	int i, index, new_index;
	uint8_t *plaintext;

	plaintext = (uint8_t *)malloc(strlen(plaintext));

	for (i = 0; i < strlen(ciphertext); i++) {
		index = search_letter(ciphertext[i]);
		if (index == -1) {
			printf("Letter not found...exiting\n");
			exit(1);
		}
		new_index = index - N;
		if (new_index < 0) {
			/* wrap around */
			plaintext[i] = letters[62 - abs(new_index)];
		} else {
			plaintext[i] = letters[new_index];
		}	
	}
	return plaintext;
}

/* --- Spartan's Cipher --- */
int 
round_i(float num) 
{
	return num < 0 ? num - 0.5 : num + 0.5;
}

/* Spartan/Scytale Cipher Encryption */
uint8_t * 
spartan_encrypt(uint8_t *plaintext, int circ)
{
	int i;
	int j;
	int col;
	int save;
	int len_pl;
	float tmp;
	char **table;
	uint8_t *ciphertext;
	
	len_pl = strlen(plaintext);

	tmp = (float)len_pl/ (float)circ;
	col = round_i(tmp);

	// allocate the rows first
	table = malloc(circ * sizeof(uint8_t *));
	if (table == NULL) {
		printf("Error while allocating rows\n");
		exit(1);
	}

	// Before we allocate the columns we have to know
	// if the col number we found is enough for the 2d array
	// to contain the whole plaintext
	int vrf_size = col * circ;
	if (vrf_size < len_pl) {
		// if its not | de xwraei
		// allocate ++col columns 
		col++;
	}
	ciphertext = malloc(col*circ);

	for (i = 0; i < circ; i++) {
		table[i] = malloc(col * sizeof(uint8_t));
		if (table[i] == NULL) {
			printf("Error while allocating columns\n");
			exit(1);
		}
	}

	/* Memset */
	for(i = 0; i < circ; i++) {
		for (j = 0; j < col; j++) {
			table[i][j] = '#';
		}
	}

	/* Right the plaintext in column order inside the table */
	j = 0;
	save = 0;
	for (i = 0; i < col; i++) {
		while(j < circ) {
			table[j][i] = plaintext[save++];
			j++;
			if (save == len_pl) break;
		}
		j = 0;
	}

	/* Write the cipher */
	save = 0;
	for(i = 0; i < circ; i++) {
		for (j = 0; j < col; j++) {
			// printf("%c ", table[i][j]);
				if ((table[i][j] != '#') || (table[i][j] == '\0'))
					ciphertext[save++] = table[i][j];
		}
		// printf("\n");
	}

	// padding
	while (save < (col*circ)) {
		ciphertext[save++] = '#';
	}
	ciphertext[(col*circ)] = '\0';

	return ciphertext;
}

/* Returns the number of padding chars ('#') found
 * in the ciphertext
 */
int
count_pad_char(uint8_t *ciphertext) 
{
	int i; 
	int pad_chars;

	pad_chars = 0;

	for (i = 0; i < strlen(ciphertext); i++) {
		if (ciphertext[i] == '#') {
			pad_chars++;
		}
	}

	return pad_chars;
}

/* Spartan/Scytale Decryption */
uint8_t *
spartan_decrypt(uint8_t *ciphertext, int circ)
{	
	int i;				
	int j;		
	int pads; 			/* number of characters added as padding */
	int col;			/* column counter */
	int save;			/* counter used to perform operations on pt/ct buffers */
	int len_ci;			/* ciphertext length */
	int tmp;			/* temp to help calculate columns' number */
	int tmp_s; 			/* temp to help calculate columns' number */
	uint8_t *plaintext; 

	len_ci = strlen(ciphertext);

	tmp = (float)len_ci/ (float)circ;
	col = round_i(tmp);
	tmp_s = circ * col;

	plaintext = malloc(strlen(ciphertext));

	/* an to size to cipher einai megalutero apo to 
	 * exwn tote theloume allh mia sthlh
	 */
	if (tmp_s < len_ci) col++;
	uint8_t table[circ][col];

	/* Memset */
	for(i = 0; i < circ; i++) {
		for (j = 0; j < col; j++) {
			table[i][j] = '-';
		}
	}

	pads = count_pad_char(ciphertext);
	i = circ - pads;  
	for ( i = (circ - pads); i < circ; i++) {
		table[i][col-1] = '#';
	}

	/* apply padding (row manner) */    
	j = 0;
	save = 0;
	for (i = 0; i < circ; i++) {
		// if (save == len_ci) break;
		while (j < col) {
			if ( table[i][j] != '#') {
				table[i][j++] = ciphertext[save++];
			} else {
				j++;
			}
		}
		j = 0;
	}

	/* Decipher */
	save = 0;
	for (i = 0; i < col; i++) {
		for ( j = 0; j < circ; j++){
			if (table[j][i] != '#')
				plaintext[save++] = table[j][i];
		}
	}
	plaintext[save] = '\0';	
	return plaintext;
}

/* Vigenere's Cipher */

uint8_t dump[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
				'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
				'U', 'V', 'W', 'X', 'Y', 'Z' 
				};

uint8_t **
init_alphabet(void)
{
	int i;
	int j;
	int c;
	int counter;
	uint8_t **alphabet;

	//allocation 
	alphabet = malloc(sizeof(char *) * 26);
	if (alphabet == NULL) {
		printf("Error!Allocating rows\n");
		exit(1);
	}
	for (i = 0; i < 26; i++) {
		alphabet[i] = malloc(sizeof(char) * 26);
		if (alphabet[i] == NULL) {
			printf("Error!Allocating columns\n");
		}
	}

	/* Memset */
	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			alphabet[i][j] = '#';
		}
	}

	c = 0;
	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			if (j+i < 26) {
				alphabet[i][j] = dump[c+i];
				c++;
			} else {	//wrap around
				counter = 0;
				while (j < 26) {
					alphabet[i][j++] = dump[counter++];
				}
				break;
			}
		}
		c = 0;
	}
	return alphabet;
}

int
find_column(uint8_t **alphabet, uint8_t letter)
{
	int i;

	for (i = 0; i < 26; i++) {
		if (alphabet[0][i] == letter) {
			return i;
		}
	}
	return -1;
}

int 
find_row(uint8_t **alphabet, uint8_t letter)
{
	int i;
	for (i = 0; i < 26; i++) {\
		if (alphabet[i][0] == letter) {
			return i;
		}
	}
	return -1;
}

uint8_t *
vigenere_encrypt(uint8_t *plaintext, uint8_t *key)
{
	int i, j;
	int key_len;		/* key length*/
	int pt_len;			/* plaintext length */		
	int c;
	int row;
	int column;
	uint8_t *ciphertext;
	uint8_t **alphabet;

	if (strlen(key) > strlen(plaintext)) {
		printf("Error: Plaintext length should be greater than the Key's length\n");
		exit(1);
	}

	pt_len = strlen(plaintext);
	key_len = strlen(key);
	ciphertext = malloc(pt_len);

	/* First must fix the key to decrypt */
	key = realloc(key, pt_len);

	/* Fill the rest of the key's array  repeating the key string*/
	for (i = key_len; i < pt_len; i++) {
		key[i] = key[i - key_len];
	}
	key[i] = '\0';

	alphabet = init_alphabet();

	/* Encrypt */
	for (c = 0; c < strlen(plaintext); c++) {
		row = find_row(alphabet, toupper(key[c]));
		column = find_column(alphabet, toupper(plaintext[c]));

		if (row == -1) printf("Error!Finding the row\n");
		if (column == -1) printf("Error!Finding the row\n");
		
		ciphertext[c] = alphabet[row][column];
	}
	ciphertext[c] = '\0';

	return ciphertext;
}

/* 	
 * Receives 1) alphabet
 *			2) the letter(from ciphertext) it looks four 
 *			3) the row to look for (2) 
 * Returns the index of the column with the plaintext letter */
int
find_cordinate(uint8_t **alphabet, uint8_t letter, int row)
{
	int i;
	for (i = 0; i < 26; i++) {
		if (alphabet[row][i] == letter) {
			return i;
		}
	}
	return -1;
}

uint8_t *
vigenere_decrypt(uint8_t *ciphertext, uint8_t *key)
{
	int i;
	int j;
	int c;
	int row;
	int column;
	int ci_len;			/* ciphertext length */
	int key_len;        /* key length */
	uint8_t *plaintext;	
	uint8_t **alphabet;

	if (strlen(key) > strlen(ciphertext)) {
		printf("Error: Plaintext length should be greater than the Key's length");
		exit(1);
	}

	ci_len = strlen(ciphertext);
	key_len = strlen(key);
	plaintext = malloc(ci_len);

	/* First must fix the key to decrypt */
	key = realloc(key, ci_len);

	/* Fill the rest of the key's array  repeating the key string*/
	for (i = key_len; i < ci_len; i++) {
		key[i] = key[i - key_len];
	}
	key[i] = '\0';

	alphabet = init_alphabet();

	/* Decrypt */
	for (c = 0; c < strlen(ciphertext); c++) {
		row = find_row(alphabet, toupper(key[c]));
		column = find_cordinate(alphabet, ciphertext[c], row);

		if (row == -1) printf("Error!Finding the row\n");
		if (column == -1) printf("Error!Finding the row\n");

		plaintext[c] = alphabet[0][column];
	}
	plaintext[c] = '\0';

	return plaintext;
}
