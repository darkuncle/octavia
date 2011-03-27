/**
 * Octavia core functions.
 */

#include <sys/types.h>

#include <openssl/hmac.h>
#include <openssl/sha.h>

#include "octavia.h"


unsigned char * hash(unsigned char * data, size_t length, unsigned char digest [HashSize]) {
      (void) SHA512(data, length, digest);
      return SHA512(digest, HashSize, digest);
}


unsigned char * sign(unsigned char * data, size_t length, unsigned char digest [HashSize],
                     unsigned char key [HashSize])
{
      unsigned int ln = HashSize;
      return HMAC(EVP_sha512(), key, HashSize, data, length, digest, &ln);
}


unsigned int ciphertext_size(unsigned int plaintext_size) {
      return plaintext_size / CipherBlockSize +
             (0 == plaintext_size % CipherBlockSize ? 0 : 1) * CipherBlockSize +
                   CipherBlockSize;
}


Boolean exists(const char * path) {
      /* TODO */
}


Boolean is_file(const char * path) {
      /* TODO */
}


Boolean is_directory(const char * path) {
      /* TODO */
}

