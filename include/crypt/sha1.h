/*  =========================================================================
    jp_crypt_sha1 - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef JP_CRYPT_SHA1_H_INCLUDED
#define JP_CRYPT_SHA1_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  Constructor - creates new digest object, which you use to build up a
//  digest by repeatedly calling jp_crypt_sha1_update() on chunks of data.    
jp_crypt_sha1 *
jp_crypt_sha1_new (void);

//  Destroy a digest object
void
jp_crypt_sha1_destroy (jp_crypt_sha1 **self_p);

//  Add buffer into digest calculation
void
jp_crypt_sha1_update (jp_crypt_sha1 *self, const byte *buffer, size_t length);

//  Return final digest hash data. If built without crypto support,
//  returns NULL.                                                  
const byte *
jp_crypt_sha1_data (jp_crypt_sha1 *self);

//  Return final digest hash size
size_t
jp_crypt_sha1_size (jp_crypt_sha1 *self);

//  Return digest as printable hex string; caller should not modify nor   
//  free this string. After calling this, you may not use jp_crypt_sha1_update()
//  on the same digest. If built without crypto support, returns NULL.    
char *
jp_crypt_sha1_string (jp_crypt_sha1 *self);

//  Self test of this class.
void
jp_crypt_sha1_test (bool verbose);

//  @end

#ifdef __cplusplus
}
#endif

#endif
