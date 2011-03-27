/**
 * Octavia core functions and data types.
 */


#ifndef OCTAVIA_H
#define OCTAVIA_H

#include "util.h"


enum {
      MaxDescriptorSize  = 1024 * 1024 * 1,
      NameSize           = 64,
      KeySize            = 32,     // AES-256
      HashSize           = 64,     // SHA-512
      NonceSize          = 16,
      CipherBlockSize    = 16,
      DefaultSegmentSize = 4096,
      MaxDataSize        = 0xffff
} Sizes;


typedef enum {
      StorageRequest     = 0,
      StorageResponse    = 1,
      RetrievalRequest   = 2,
      RetrievalResponse  = 3,
      DeletionRequest    = 4,
      DeletionResponse   = 5,
      ExistenceRequest   = 6,
      ExistenceResponse  = 7
} MessageType;

//
// Protocol message definitions. mac = sign(key, all the bytes that come
// after the mac).
//

typedef struct {
      uint8_t version,
              type,
              key_id [KeySize],
              mac [HashSize],
              nonce [NonceSize],
              data [MaxDataSize];
} StorageRequest;

typedef struct {
      uint8_t version,
              type,
              key_id [KeySize],
              mac [HashSize],
              nonce [NonceSize];
} StorageResponse;

typedef struct {
      uint8_t version,
              type,
              block_id [HashSize];
} RetrievalRequest;

typedef struct {
      uint8_t version,
              type,
              data [MaxDataSize];
} RetrievalResponse;

typedef struct {
      uint8_t version,
              type,
              key_id [KeySize],
              mac [HashSize],
              nonce [NonceSize],
              block_id [HashSize];
} DeletionRequest;

typedef struct {
      uint8_t version,
              type,
              key_id [KeySize],
              mac [HashSize],
              nonce [NonceSize];
} DeletionResponse;

typedef struct {
      uint8_t version,
              type,
              block_id [HashSize];
} ExistenceRequest;

typedef struct {
      uint8_t version,
              type,
              key_id [KeySize],
              mac [HashSize],
              nonce [NonceSize],
              block_id [HashSize];
} ExistenceResponse;


/**
 * Cryptographically hashes length bytes of data, and stores the result in
 * digest.
 */
unsigned char * hash(unsigned char * data, size_t length, unsigned char digest [HashSize]);


/**
 * Cryptographically (symmetrically) signs (MAC) length bytes of data using
 * key. Stores the result in digest.
 *
 * XXX: Should key be KeySize bytes?
 */
unsigned char * sign(unsigned char * data, size_t length, unsigned char digest [HashSize],
                     unsigned char key [HashSize]);


/**
 * Given a plaintext_size, returns what the size of the ciphertext will be.
 */
unsigned int ciphertext_size(unsigned int plaintext_size);


/**
 * Returns whether or not a given Octavia path exists.
 */
Boolean exists(const char * path);


/**
 * Returns whether or not a given Octavia path is a file.
 */
Boolean is_file(const char * path);


/**
 * Returns whether or not a given Octavia path is a directory.
 */
Boolean is_directory(const char * path);


/**
 * Search d for a file or directory named name.
 */
File * search(Directory * d, char * name);

#endif

