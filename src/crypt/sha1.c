/*  =========================================================================
    jp_crypt_sha1 - class description

    Copyright(c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_crypt_sha1 - 
@discuss
@end
*/

#include "jp_classes.h"
#include "external/sha1/sha1.inc_c"


//  Structure of our class

struct _jp_crypt_sha1 {
    SHA_CTX context;            //  Digest context
    //  Binary hash
    byte hash[SHA_DIGEST_LENGTH];
    //  ASCII representation(hex)
    char string[SHA_DIGEST_LENGTH * 2 + 1];
    bool final;                 //  Finished calculating
};


//  --------------------------------------------------------------------------
//  Constructor - creates new digest object, which you use to build up a
//  digest by repeatedly calling jp_crypt_sha1_update() on chunks of data.

jp_crypt_sha1 *
jp_crypt_sha1_new(void)
{
    jp_crypt_sha1 *self =(jp_crypt_sha1 *) jmalloc(sizeof(jp_crypt_sha1));
    assert(self);
    SHA1_Init(&self->context);
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy a digest object

void
jp_crypt_sha1_destroy(jp_crypt_sha1 **self_p)
{
    assert(self_p);
    if(*self_p) {
        jp_crypt_sha1 *self = *self_p;
        free(self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Add buffer into digest calculation

void
jp_crypt_sha1_update(jp_crypt_sha1 *self, const byte *buffer, size_t length)
{
    //  Calling this after jp_crypt_sha1_data() is illegal use of the API
    assert(self);
    assert(!self->final);
    SHA1_Update(&self->context, buffer, length);
}


//  --------------------------------------------------------------------------
//  Return final digest hash data. If built without crypto support, returns
//  NULL.

const byte *
jp_crypt_sha1_data(jp_crypt_sha1 *self)
{
    assert(self);
    if(!self->final) {
        SHA1_Final(self->hash, &self->context);
        self->final = true;
    }
    return self->hash;
}


//  --------------------------------------------------------------------------
//  Return final digest hash size

size_t
jp_crypt_sha1_size(jp_crypt_sha1 *self)
{
    assert(self);
    return SHA_DIGEST_LENGTH;
}


//  --------------------------------------------------------------------------
//  Return digest as printable hex string; caller should not modify nor
//  free this string. After calling this, you may not use jp_crypt_sha1_update()
//  on the same digest. If built without crypto support, returns NULL.

char *
jp_crypt_sha1_string(jp_crypt_sha1 *self)
{
    assert(self);
    const byte *data = jp_crypt_sha1_data(self);
    char hex_char[] = "0123456789ABCDEF";
    int byte_nbr;
    for(byte_nbr = 0; byte_nbr < SHA_DIGEST_LENGTH; byte_nbr++) {
        self->string[byte_nbr * 2 + 0] = hex_char[data[byte_nbr] >> 4];
        self->string[byte_nbr * 2 + 1] = hex_char[data[byte_nbr] & 15];
    }
    self->string[SHA_DIGEST_LENGTH * 2] = 0;
    return self->string;
}


//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_crypt_sha1_test(bool verbose)
{
    puts(" * jp_crypt_sha1: ");

    //  @selftest
    byte *buffer = (byte *) jmalloc(1024);
    memset(buffer, 0xAA, 1024);

    jp_crypt_sha1 *digest = jp_crypt_sha1_new();
    jassert(digest);
    jp_crypt_sha1_update(digest, buffer, 1024);
    const byte *data = jp_crypt_sha1_data(digest);
    jassert_eq(data[0], 0xDE);
    jassert_eq(data[1], 0xB2);
    jassert_eq(data[2], 0x38);
    jassert_eq(data[3], 0x07);
    jstrassert_eq(jp_crypt_sha1_string(digest),
                   "DEB23807D4FE025E900FE9A9C7D8410C3DDE9671");
    jp_crypt_sha1_destroy(&digest);
    free(buffer);
    //  @end

    puts("OK!\n");
}
