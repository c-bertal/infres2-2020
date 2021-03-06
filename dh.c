// Alfred Sawaya - 1ère année SRC - 2007

#include <stdio.h>
#include <stdint.h>
#include <gmp.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct dh_key_s {
	int group;
	int length;
	char *key;
} typedef dh_key_t;

enum crypt_oper {
	UNCRYPT,
	ENCRYPT
};

/* Puts length character from /dev/urandom to s */
void read_random(char* s, int length) {
	int fd = open("/dev/urandom", O_RDONLY); 

	s[length] = '\0'; 

	if(fd != -1) { 
		read(fd, s, length); 
		for(int i = 0; i < length; i++) 
			s[i] = (s[i] & 0x07) + '0'; 
	} else {
		fprintf(stderr, "Can't open /dev/urandom\n"); 
	}
	close(fd);
}

/* return the modp (modulus prime) from a keysize */
int modpfromkeysize(int keysize) {
	switch( keysize ) {
		case 192 : return 1;
		case 256 : return 2;
		case 384 : return 5;
		case 512 : return 14;
		case 768 : return 15;
		case 1024 : return 16;
		case 1536 : return 17;
		case 2048 : return 18;
	}
	return -1;
}

/* Initialize the prime modulus modulo and the group generator group according to the modp */
int dh_init_group(int modp, mpz_t modulo, mpz_t group, int andg) {
	switch(modp) {
		case 1 : { /* 768 */
			mpz_set_str(modulo,
				"FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 					 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A63A3620 FFFFFFFF FFFFFFFF"
				,16);
			if (andg) mpz_set_si(group,2L);
			return 192;
		}
		case 2 : { /* 1024 */
			mpz_set_str(modulo,
				"FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 					 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 					 49286651 ECE65381 FFFFFFFF FFFFFFFF"
				,16);
			if (andg) mpz_set_si(group,2L);
			return 256;
		}
		case 5 : { /* 1536 */
			mpz_set_str(modulo,
				"FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 					 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 					 49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8 FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D 					 670C354E 4ABC9804 F1746C08 CA237327 FFFFFFFF FFFFFFFF"
				,16);
			if (andg) mpz_set_si(group,2L);
			return 384;
		}
		case 14 : { /* 2048 */
			mpz_set_str(modulo,
				"FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 					 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 					 49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8 FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D 					 670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C 180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718 					 3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AACAA68 FFFFFFFF FFFFFFFF"
				,16);
			if (andg) mpz_set_si(group,2L);
			return 512;
		}
		case 15 : { /* 3072 */
			mpz_set_str(modulo,
				"FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 					 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 					 49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8 FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D 					 670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C 180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718 					 3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AAAC42D AD33170D 04507A33 A85521AB DF1CBA64 ECFB8504 58DBEF0A 8AEA7157 5D060C7D 					 B3970F85 A6E1E4C7 ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226 1AD2EE6B F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C 	 					 BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31 43DB5BFC E0FD108E 4B82D120 A93AD2CA FFFFFFFF FFFFFFFF"
				,16);
			if (andg) mpz_set_si(group,2L);
			return 768;
		}
		case 16 : { /* 4096 */
			mpz_set_str(modulo,
				"FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 					 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 					 49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8 FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D 					 670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C 180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718 					 3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AAAC42D AD33170D 04507A33 A85521AB DF1CBA64 ECFB8504 58DBEF0A 8AEA7157 5D060C7D 					 B3970F85 A6E1E4C7 ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226 1AD2EE6B F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C 					 BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31 43DB5BFC E0FD108E 4B82D120 A9210801 1A723C12 A787E6D7 88719A10 BDBA5B26 					 99C32718 6AF4E23C 1A946834 B6150BDA 2583E9CA 2AD44CE8 DBBBC2DB 04DE8EF9 2E8EFC14 1FBECAA6 287C5947 4E6BC05D 99B2964F A090C3A2 					 233BA186 515BE7ED 1F612970 CEE2D7AF B81BDD76 2170481C D0069127 D5B05AA9 93B4EA98 8D8FDDC1 86FFB7DC 90A6C08F 4DF435C9 34063199 					 FFFFFFFF FFFFFFFF"
				,16);
			if (andg) mpz_set_si(group,2L);
			return 1024;
		}
		case 17 : { /* 6144 */
			mpz_set_str(modulo,
				"FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 					 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 					 49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8 FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D 					 670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C 180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718 					 3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AAAC42D AD33170D 04507A33 A85521AB DF1CBA64 ECFB8504 58DBEF0A 8AEA7157 5D060C7D 					 B3970F85 A6E1E4C7 ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226 1AD2EE6B F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C 					 BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31 43DB5BFC E0FD108E 4B82D120 A9210801 1A723C12 A787E6D7 88719A10 BDBA5B26 					 99C32718 6AF4E23C 1A946834 B6150BDA 2583E9CA 2AD44CE8 DBBBC2DB 04DE8EF9 2E8EFC14 1FBECAA6 287C5947 4E6BC05D 99B2964F A090C3A2 					 233BA186 515BE7ED 1F612970 CEE2D7AF B81BDD76 2170481C D0069127 D5B05AA9 93B4EA98 8D8FDDC1 86FFB7DC 90A6C08F 4DF435C9 34028492 					 36C3FAB4 D27C7026 C1D4DCB2 602646DE C9751E76 3DBA37BD F8FF9406 AD9E530E E5DB382F 413001AE B06A53ED 9027D831 179727B0 865A8918 					 DA3EDBEB CF9B14ED 44CE6CBA CED4BB1B DB7F1447 E6CC254B 33205151 2BD7AF42 6FB8F401 378CD2BF 5983CA01 C64B92EC F032EA15 D1721D03 					 F482D7CE 6E74FEF6 D55E702F 46980C82 B5A84031 900B1C9E 59E7C97F BEC7E8F3 23A97A7E 36CC88BE 0F1D45B7 FF585AC5 4BD407B2 2B4154AA 					 CC8F6D7E BF48E1D8 14CC5ED2 0F8037E0 A79715EE F29BE328 06A1D58B B7C5DA76 F550AA3D 8A1FBFF0 EB19CCB1 A313D55C DA56C9EC 2EF29632 					 387FE8D7 6E3C0468 043E8F66 3F4860EE 12BF2D5B 0B7474D6 E694F91E 6DCC4024 FFFFFFFF FFFFFFFF"
				,16);
			if (andg) mpz_set_si(group,2L);
			return 1536;
		}
		case 18 : { /* 8192 */
			mpz_set_str(modulo,
				"FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 					 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 					 49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8 FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D 					 670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C 180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718 					 3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AAAC42D AD33170D 04507A33 A85521AB DF1CBA64 ECFB8504 58DBEF0A 8AEA7157 5D060C7D 					 B3970F85 A6E1E4C7 ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226 1AD2EE6B F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C 					 BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31 43DB5BFC E0FD108E 4B82D120 A9210801 1A723C12 A787E6D7 88719A10 BDBA5B26 					 99C32718 6AF4E23C 1A946834 B6150BDA 2583E9CA 2AD44CE8 DBBBC2DB 04DE8EF9 2E8EFC14 1FBECAA6 287C5947 4E6BC05D 99B2964F A090C3A2 					 233BA186 515BE7ED 1F612970 CEE2D7AF B81BDD76 2170481C D0069127 D5B05AA9 93B4EA98 8D8FDDC1 86FFB7DC 90A6C08F 4DF435C9 34028492 					 36C3FAB4 D27C7026 C1D4DCB2 602646DE C9751E76 3DBA37BD F8FF9406 AD9E530E E5DB382F 413001AE B06A53ED 9027D831 179727B0 865A8918 					 DA3EDBEB CF9B14ED 44CE6CBA CED4BB1B DB7F1447 E6CC254B 33205151 2BD7AF42 6FB8F401 378CD2BF 5983CA01 C64B92EC F032EA15 D1721D03 					 F482D7CE 6E74FEF6 D55E702F 46980C82 B5A84031 900B1C9E 59E7C97F BEC7E8F3 23A97A7E 36CC88BE 0F1D45B7 FF585AC5 4BD407B2 2B4154AA 					 CC8F6D7E BF48E1D8 14CC5ED2 0F8037E0 A79715EE F29BE328 06A1D58B B7C5DA76 F550AA3D 8A1FBFF0 EB19CCB1 A313D55C DA56C9EC 2EF29632 					 387FE8D7 6E3C0468 043E8F66 3F4860EE 12BF2D5B 0B7474D6 E694F91E 6DBE1159 74A3926F 12FEE5E4 38777CB6 A932DF8C D8BEC4D0 73B931BA 					 3BC832B6 8D9DD300 741FA7BF 8AFC47ED 2576F693 6BA42466 3AAB639C 5AE4F568 3423B474 2BF1C978 238F16CB E39D652D E3FDB8BE FC848AD9 					 22222E04 A4037C07 13EB57A8 1A23F0C7 3473FC64 6CEA306B 4BCBC886 2F8385DD FA9D4B7F A2C087E8 79683303 ED5BDD3A 062B3CF5 B3A278A6 					 6D2A13F8 3F44F82D DF310EE0 74AB6A36 4597E899 A0255DC1 64F31CC5 0846851D F9AB4819 5DED7EA1 B1D510BD 7EE74D73 FAF36BC3 1ECFA268 					 359046F4 EB879F92 4009438B 481C6CD7 889A002E D5EE382B C9190DA6 FC026E47 9558E447 5677E9AA 9E3050E2 765694DF C81F56E8 80B96E71 					 60C980DD 98EDD3DF FFFFFFFF FFFFFFFF"
				,16);
			if (andg) mpz_set_si(group,2L);
			return 2048;
		}
	}
	return -1;
}

/* Init a dh_key_t */
void dh_init(dh_key_t **k) {
	*k = calloc(1, sizeof(dh_key_t));
}

/* free a dh_key_t */
void dh_clean(dh_key_t *k) {
	free(k->key);
	free(k);
}

/* Create the keying material for the peer */
char* dh1(dh_key_t *k, int keysize) {
	clock_t start, end;
	mpz_t modulo, group, secret_key_mpz, keying_material_mpz;
	char *secret_key_str, *keying_material_str;

	mpz_inits(modulo, group, secret_key_mpz, keying_material_mpz, NULL);
	k->group = modpfromkeysize(keysize);

	k->length = dh_init_group(k->group, modulo, group, 1);
	secret_key_str = calloc(2 * (k->length) + 1, sizeof(char));

	start = clock();
	read_random(secret_key_str, 2 * (k->length));
	end = clock();
	printf("read_random : %f seconds\n", (end - start) / (double)CLOCKS_PER_SEC); 

	mpz_set_str(secret_key_mpz, secret_key_str, 16);
	mpz_powm(keying_material_mpz, group, secret_key_mpz,modulo); /* On a ga */
	keying_material_str = calloc(mpz_sizeinbase(keying_material_mpz, 16) + 1, sizeof(char));
	mpz_get_str(keying_material_str, 16, keying_material_mpz);
	k->key = secret_key_str;
	mpz_clears(modulo, group, secret_key_mpz, keying_material_mpz, NULL);
	return keying_material_str;
}

/* Calculate the shared key from our secret key and the peer keying material */
void dh2(dh_key_t *k, char *keying_material_str) {
	clock_t start, end;
	mpz_t modulo, secret_key_mpz, final_key, keying_material_mpz;
	mpz_inits(modulo, secret_key_mpz, final_key, keying_material_mpz, NULL);
	mpz_set_str(keying_material_mpz, keying_material_str, 16);
	mpz_set_str(secret_key_mpz, k->key, 16);
	dh_init_group(k->group, modulo, NULL, 0);

	start = clock();
	mpz_powm(final_key, keying_material_mpz, secret_key_mpz, modulo);
	end = clock();
	printf("powm : %f seconds\n", (end - start) / (double)CLOCKS_PER_SEC); 

	k->length = mpz_sizeinbase(final_key, 16) + 1;
	free(k->key);
	k->key = calloc(k->length, sizeof(char));
	mpz_get_str(k->key, 16, final_key);
	mpz_clears(modulo, secret_key_mpz, final_key, keying_material_mpz, NULL);
}

/* Return the Vernam Mask (OTP) with adapted length */
char* getMask(dh_key_t* k, int msg_length) {
	char *mask = calloc(msg_length, sizeof(char));

	for(int i = 0, j = 0; i < msg_length - 1; i++, j++)
		mask[i] = (k->key)[j = (j == k->length) ? 0 : j];

	mask[msg_length - 1]='\0';
	return mask;
}

/* Crypt or uncrypt msg of msg_length characters with the key k */
char* dh_crypt(dh_key_t *k, char* msg, int msg_length, enum crypt_oper oper) {
  	char *res = calloc(msg_length, sizeof(char));
	char *mask = getMask(k, msg_length);
	for(int i = 0; i < msg_length; i++)
		if(oper == ENCRYPT)
			res[i] = msg[i] + mask[i];
		else
			res[i] = msg[i] - mask[i];
	free(mask);
	return res;
}

/* Crypt msg with k */
char* dh_crypt_str(dh_key_t *k, char* msg) {
	int msg_length = strlen(msg)+1;
	return dh_crypt(k, msg, msg_length, ENCRYPT);
}

/* Uncrypt msg with k */
char* dh_decrypt_str(dh_key_t *k, char* msg) {
	int msg_length = strlen(msg) + 1;
	char *res = dh_crypt(k, msg, msg_length, UNCRYPT);
	res[msg_length-1] = '\0';
	return res;
}


int main (int argc, char* argv[]) {
	if(argc != 2) {
		printf("usage: ./%s <message to encrypt and decrypt>\n", argv[0]);
		return 1;
	}

	char *km1, *km2;
	char *msg = argv[1];
	
	dh_key_t *k1, *k2;

	dh_init(&k1);
	dh_init(&k2);

	km1 = dh1(k1, 192);
	km2 = dh1(k2, 192);

	dh2(k1, km2);
	dh2(k2, km1);

	char *encrypted_msg = dh_crypt_str(k1, msg);
	char *decrypted_msg = dh_decrypt_str(k2, encrypted_msg);

	printf("Original message: %s\n", msg);
	printf("Encrypted message: %s\n", encrypted_msg);
	printf("Decrypted message: %s\n", decrypted_msg);

	free(km1);
	free(km2);
	free(encrypted_msg);
	free(decrypted_msg);
	dh_clean(k1);
	dh_clean(k2);
	return 0;
}
