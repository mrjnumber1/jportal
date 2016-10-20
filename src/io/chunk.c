/*  =========================================================================
    jp_io_chunk - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_io_chunk - 
@discuss
@end
*/

#include "jp_classes.h"

#define JP_CHUNK_TAG 0xc0ffee50
#define JP_CHUNK_DEADTAG 0xDeadBeef;

//  Structure of our class

struct _jp_io_chunk {
    uint32 tag;
    size_t size;
    size_t max_size;
    size_t consumed;
    jp_crypt_sha1 *digest;
    byte *data;
};


//  --------------------------------------------------------------------------
//  Create a new jp_io_chunk

jp_io_chunk *
jp_io_chunk_new(const void *data, size_t size)
{
    jp_io_chunk *self = (jp_io_chunk *) malloc(sizeof (jp_io_chunk) + size);

    if (self) {
        self->tag = JP_CHUNK_TAG;
        self->size = 0;
        self->max_size = size;
        self->consumed = 0;
        self->data = (byte*)self + sizeof(jp_io_chunk);
        self->digest = NULL;
        if (data) {
            self->size = size;
            memcpy(self->data, data, self->size);
        }
    }

    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_io_chunk

void
jp_io_chunk_destroy(jp_io_chunk **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_io_chunk *self = *self_p;
        assert(jp_io_chunk_is(self));
        if (self->data != (byte*)self + sizeof(jp_io_chunk))
            free(self->data);
        self->tag = JP_CHUNK_DEADTAG;
        jp_crypt_sha1_destroy(&self->digest);
        free(self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Certify it is a jp_io_chunk
bool 
jp_io_chunk_is(void *self)
{
    assert(self);
    return ((jp_io_chunk*)self)->tag == JP_CHUNK_TAG;
}


//  --------------------------------------------------------------------------
void
jp_io_chunk_resize(jp_io_chunk *self, size_t size)
{
    assert(self);
    assert(jp_io_chunk_is(self));
    jp_crypt_sha1_destroy(&self->digest);

    self->max_size = size;
    self->size = 0;

    if (self->data == (byte*)self + sizeof(jp_io_chunk))
        self->data = (byte*)malloc(self->max_size);
    else
        self->data = (byte*)realloc(self->data, self->max_size);
}
        
//  --------------------------------------------------------------------------
size_t
jp_io_chunk_size(jp_io_chunk *self)
{
    assert(self);
    assert(jp_io_chunk_is(self));
    return self->size;
}
//  --------------------------------------------------------------------------
size_t
jp_io_chunk_max_size(jp_io_chunk *self)
{
    assert(self);
    assert(jp_io_chunk_is(self));
    return self->max_size;
}

//  --------------------------------------------------------------------------
byte*
jp_io_chunk_data(jp_io_chunk *self)
{
    assert(self);
    assert(jp_io_chunk_is(self));
    return self->data;
}
    
//  --------------------------------------------------------------------------
size_t
jp_io_chunk_set(jp_io_chunk *self, const void *data, size_t size)
{
    assert(self);
    assert(jp_io_chunk_is(self));
    jp_crypt_sha1_destroy(&self->digest);

    if (size > self->max_size)
        size = self->max_size;
    if (data)
        memcpy(self->data, data, size);

    self->size = size;
    return size;
}

//  --------------------------------------------------------------------------
size_t
jp_io_chunk_fill(jp_io_chunk *self, byte filler, size_t size)
{
    assert(self);
    assert(jp_io_chunk_is(self));
    jp_crypt_sha1_destroy(&self->digest);

    if (size > self->max_size)
        size = self->max_size;

    memset(self->data, filler, size);
    self->size = size;
    return size;
}

//  --------------------------------------------------------------------------
size_t
jp_io_chunk_append(jp_io_chunk *self, const void *data, size_t size)
{
    assert(self);
    assert(jp_io_chunk_is(self));
    jp_crypt_sha1_destroy(&self->digest);

    if (self->size + size > self->max_size)
        size = self->max_size - self->size;

    memcpy(self->data+self->size, data, size);
    self->size += size;
    return size;
}

//  --------------------------------------------------------------------------
size_t
jp_io_chunk_extend(jp_io_chunk *self, const void *data, size_t size)
{
    assert(self);
    if (self->size + size > self->max_size) {
        self->max_size = (self->size+size)*2;

        if (self->data == (byte*)self + sizeof(jp_io_chunk)) {
            byte *old_data = self->data;
            self->data = (byte*)malloc(self->max_size);
            memcpy(self->data, old_data, self->size);
        }
        else
            self->data = (byte*)realloc(self->data, self->max_size);

    }
    assert(self->size + size <= self->max_size);
    memcpy(self->data + self->size, data, size);
    self->size += size;
    return size;
}

//  --------------------------------------------------------------------------
size_t 
jp_io_chunk_consume(jp_io_chunk *self, jp_io_chunk *src)
{
    assert(self);
    assert(jp_io_chunk_is(self));
    assert(src);
    assert(jp_io_chunk_is(src));
    assert(self != src);

    size_t size = src->size - src->consumed;

    if (self->size+size > self->max_size)
        size = self->max_size - self->size;

    memcpy(self->data + self->size, src->data + src->consumed, size);
    src->consumed += size;
    self->size += size;
    return size;
}

//  --------------------------------------------------------------------------
bool
jp_io_chunk_exhausted(jp_io_chunk *self)
{
    assert(self);
    assert(jp_io_chunk_is(self));

    assert(self->consumed <= self->size);
    return self->consumed == self->size;
}

//  --------------------------------------------------------------------------
jp_io_chunk *
jp_io_chunk_read(FILE *handle, size_t bytes)
{
    assert(handle);
    jp_io_chunk *self = jp_io_chunk_new(NULL, bytes);
    if (self)
        self->size = fread(self->data, 1, bytes, handle);
    return self;
}

//  --------------------------------------------------------------------------
bool
jp_io_chunk_write(jp_io_chunk *self, FILE *handle)
{
    assert(self);
    assert(jp_io_chunk_is(self));
    assert(handle);

    size_t written = fwrite(self->data, 1, self->size, handle);
    
    return (written >= self->size);
}

//  --------------------------------------------------------------------------
jp_io_chunk*
jp_io_chunk_slurp(const char *filename, size_t maxsize)
{
    struct stat stat_buf;
    size_t filesize = -1;

    assert(filename);

    if (stat((char *)filename, &stat_buf) == 0)
        filesize = stat_buf.st_size;

    if (filesize == -1)
        return NULL;

    if (filesize > maxsize && maxsize != 0)
        filesize = maxsize;

    FILE *handle = fopen(filename, "r");
    jp_io_chunk *chunk = jp_io_chunk_read(handle, filesize);
    assert(chunk);
    fclose(handle);
    return chunk;
}

//  --------------------------------------------------------------------------
jp_io_chunk*
jp_io_chunk_dup(jp_io_chunk *self)
{
    if (self) {
        assert(jp_io_chunk_is(self));
        return jp_io_chunk_new(self->data, self->max_size);
    }
    else
        return NULL;
}

//  --------------------------------------------------------------------------
char *
jp_io_chunk_strhex(jp_io_chunk *self)
{
    assert(self);
    assert(jp_io_chunk_is(self));

    static const char digits[] = "0123456789ABCDEF";

    size_t size = jp_io_chunk_size(self);
    byte *data = jp_io_chunk_data(self);
    char *hxstr = (char*)jmalloc(size*2+1);
    if (!hxstr)
        return NULL;

    uint offset;
    for (offset=0; offset < size; offset++) {
        hxstr[offset*2+0] = digits[data[offset]>>4];
        hxstr[offset*2+1] = digits[data[offset]&15];
    }
    hxstr[size*2] = '\0';
    return hxstr;
}

//  --------------------------------------------------------------------------
char*
jp_io_chunk_strdup(jp_io_chunk *self)
{
    assert(self);
    assert(jp_io_chunk_is(self));

    size_t size = jp_io_chunk_size(self);

    char *string = (char *)malloc(size+1);
    if (string)
    {
        memcpy(string, jp_io_chunk_data(self), size);
        string[size] = 0;
    }
    return string;
}

//  --------------------------------------------------------------------------
bool
jp_io_chunk_streq(jp_io_chunk *self, const char *string)
{
    assert(self);
    assert(jp_io_chunk_is(self));

    if (jp_io_chunk_size(self) == strlen(string)
            && memcmp(jp_io_chunk_data(self), string, strlen(string))==0)
        return true;
    else
        return false;
}

//  --------------------------------------------------------------------------
const char*
jp_io_chunk_digest(jp_io_chunk *self)
{
    assert(self);
    if (!self->digest)
        self->digest = jp_crypt_sha1_new(); 
    if (self->digest) {
        jp_crypt_sha1_update(self->digest, self->data, self->size);
        return jp_crypt_sha1_string(self->digest);
    }
    else
        return NULL;
}

//  --------------------------------------------------------------------------
void
jp_io_chunk_fprint(jp_io_chunk *self, FILE *handle)
{
    assert(self);
    assert(jp_io_chunk_is(self));

    fprintf(handle, "--------------------------------------\n");
    if (!self) {
        fprintf(handle, "NULL");
        return;
    }
    assert(self);
    bool is_binary = false;
    uint offset;
    for (offset=0; offset < self->size; offset++)
        if (self->data[offset] < '\t' || self->data[offset] > 127)
            is_binary = true;

    fprintf(handle, "[%03d] ", (int)self->size);
    for (offset=0; offset < self->size; offset++) {
        if (is_binary) {
            fprintf(handle, "%02X", (uchar)self->data[offset]);
            if (offset > 35) {
                fprintf(handle, "...");
                break;
            }
        }
        else {
            fprintf(handle, "%c", self->data[offset]);
            if (offset > 35*2) {
                fprintf(handle, "...");
                break;
            }
        }
    }
    fprintf(handle, "\n");
}

//  --------------------------------------------------------------------------
void
jp_io_chunk_print(jp_io_chunk* self)
{
    assert(self);
    assert(jp_io_chunk_is(self));

    jp_io_chunk_fprint(self, stderr);
}



//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_io_chunk_test (bool verbose)
{
    puts(" * jp_io_chunk: ");

    //  @selftest
    //  Simple create/destroy test
    jp_io_chunk *self = jp_io_chunk_new("1234567890", 10);
    jassert(self);
    jassert_eq(jp_io_chunk_size(self), 10);
    jassert_eq(memcmp(jp_io_chunk_data(self), "1234567890", 10), 0);
    jp_io_chunk_destroy(&self);

    self = jp_io_chunk_new(NULL, 10);
    jassert(self);
    jp_io_chunk_append(self, "12345678", 8);
    jp_io_chunk_append(self, "90ABCDEF", 8);
    jp_io_chunk_append(self, "GHIJKLMN", 8);
    jassert_eq(memcmp(jp_io_chunk_data(self), "1234567890", 10), 0);
    jassert_eq(jp_io_chunk_size(self), 10);
    jassert(jp_io_chunk_streq(self, "1234567890"));
    jstrassert_eq(jp_io_chunk_digest(self), "01B307ACBA4F54F55AAFC33BB06BBBF6CA803E9A");
    char* string = jp_io_chunk_strdup(self);
    jstrassert_eq(string, "1234567890");
    free(string);
    string = jp_io_chunk_strhex(self);
    jstrassert_eq(string, "31323334353637383930");
    free(string);

    jp_io_chunk *copy = jp_io_chunk_dup(self);
    jassert(copy);
    jassert_eq(memcmp(jp_io_chunk_data(copy), "1234567890", 10), 0);
    jassert_eq(jp_io_chunk_size(copy), 10);
    jp_io_chunk_destroy(&copy);
    jp_io_chunk_destroy(&self);

    self = jp_io_chunk_new(NULL, 0);
    jp_io_chunk_extend(self, "12345678", 8);
    jp_io_chunk_extend(self, "90ABCDEF", 8);
    jp_io_chunk_extend(self, "GHIJKLMN", 8);
    jassert_eq(jp_io_chunk_size(self), 24);
    jassert(jp_io_chunk_streq(self, "1234567890ABCDEFGHIJKLMN"));
    jp_io_chunk_destroy(&self);

    copy = jp_io_chunk_new("1234567890abcdefghij", 20);
    jassert(copy);
    self = jp_io_chunk_new(NULL, 8);
    assert(self);
    jp_io_chunk_consume(self, copy);
    jassert_false(jp_io_chunk_exhausted(copy));
    jassert_eq(memcmp(jp_io_chunk_data(self), "12345678", 8), 0);
    jp_io_chunk_set(self, NULL, 0);
    jp_io_chunk_consume(self, copy);
    jassert_false(jp_io_chunk_exhausted(copy));
    jassert_eq(memcmp(jp_io_chunk_data(self), "90abcdef", 8), 0);
    jp_io_chunk_set(self, NULL, 0);
    jp_io_chunk_consume(self, copy);
    jassert(jp_io_chunk_exhausted(copy));
    jassert_eq(jp_io_chunk_size(self), 4);
	
    jassert_eq(memcmp(jp_io_chunk_data(self), "ghij", 4), 0);

    jp_io_chunk_destroy(&copy);
    jp_io_chunk_destroy(&self);
    //  @end
    puts("OK!\n");
}
