#ifndef _sm4_H_
#define _sm4_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <QDebug>
#include <QString>

#define SM4_DECRYPT 0
#define SM4_ENCRYPT 1

#define SM4_BLOCK_SIZE    16
#define SM4_KEY_SCHEDULE  32

#define TEMPFILENAME        "tempDb.txt"
#define TEMPFILEZIPNAME     "tmp.rar"
#define BatchCompressFileName   "证据合集.rar"

typedef struct {
    int mode; // ENCRYPT OR DECRYPT
    //uint32_t rk[SM4_KEY_SCHEDULE]; // rotkey
    int rk[SM4_KEY_SCHEDULE];
}sm4_ctx;

QString sm4_encrypt_string(QString strEnc,sm4_ctx *ctx);
QString sm4_decrypt_string(QString strIn,sm4_ctx *ctx);

#ifdef __cplusplus
extern "C" {
#endif

    int sm4_set_key(uint8_t *key, sm4_ctx *ctx); // key 128 bit len 16
    void sm4_encrypt(const uint8_t *in, uint8_t *out, const sm4_ctx *ctx);
    void sm4_decrypt(const uint8_t *in, uint8_t *out, const sm4_ctx *ctx);

    uint8_t *padding(uint8_t *input, int mode);
    //static inline uint32_t load_uint32_be(const uint8_t *b, int n);
    static inline int load_uint32_be(const uint8_t *b, int n);
    //static inline void store_uint32_be(uint32_t v, uint8_t * const b);
    static inline void store_uint32_be(int v, uint8_t * const b);
    static inline void xor_blk(uint8_t *a, uint8_t *b);

    //static inline void SM4_F(uint32_t * const blks, const uint32_t *rkg);
    static inline void SM4_F(int * const blks, const int *rkg); // blks len should be 4 as 128bit
    //static inline uint32_t SM4_T(uint32_t X);
    static inline int SM4_T(int X);

    void sm4_encrypt_file(FILE *in, FILE *out, sm4_ctx *ctx);
    void sm4_decrypt_file(FILE *in, FILE *out, sm4_ctx *ctx);
    //void sm4_cbc_encrypt_file(FILE *in, FILE *out, sm4_ctx *ctx);
    //void sm4_cbc_decrypt_file(FILE *in, FILE *out, sm4_ctx *ctx);
    void sm4_decrypt_file_test(sm4_ctx *ctx);
    void sm4_decrypt_file_test2(sm4_ctx *ctx,const QString& inName,const QString& outName);


#ifdef __cplusplus
}
#endif

#endif // _sm4_H_
