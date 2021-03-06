#include <stdlib.h>

#include "include/_pow.h"
#include "include/pow.h"
#include <string.h>
#include "include/hashcash.h"
#include "include/trit_tryte.h"


#define NONCE_LENGTH 27 * 3


char* iota_pow(const char* trytes_in, uint8_t mwm) {
    Curl curl;
    init_curl(&curl);
    curl.type = CURL_P_81;

    int tryte_len = (int)strlen(trytes_in);
    int trits_len = tryte_len * 3;

    trit_t* trits = (trit_t*)malloc(sizeof(trit_t) * trits_len);

    trytes_to_trits((tryte_t*)trytes_in, trits, tryte_len);
    tryte_t* nonce_trytes =
            (tryte_t*)calloc(NONCE_LENGTH / 3 + 1, sizeof(tryte_t));

    trit_t* nonce_trits = (trit_t*)do_pow(&curl,(char*)trits,trits_len,mwm);
    free(trits);

    trits_to_trytes(nonce_trits, nonce_trytes,
                    NONCE_LENGTH);
    free(nonce_trits);

    return (char*)nonce_trytes;
}

