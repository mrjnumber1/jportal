/*  =========================================================================
    jp_io_chunk - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           

    This class is almost a complete 1:1 rip from zeromq's czmq's zchunk_t 
    =========================================================================
*/

#ifndef JP_IO_CHUNK_H_INCLUDED
#define JP_IO_CHUNK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  Create a new jp_io_chunk
jp_io_chunk *
    jp_io_chunk_new(const void * data, size_t size);

//  Destroy the jp_io_chunk
void
    jp_io_chunk_destroy(jp_io_chunk **self_p);

//  Certify the data passed is a jp_io_chunk
bool
    jp_io_chunk_is(void* self);

//  resize max_size as requested 
void
    jp_io_chunk_resize(jp_io_chunk *self, size_t size);

// current chunk size used 
size_t
    jp_io_chunk_size(jp_io_chunk *self);

//  max size possible 
size_t
    jp_io_chunk_max_size(jp_io_chunk *self);

//  get chunk data
byte*
    jp_io_chunk_data(jp_io_chunk *self);

//  set chunk data 
size_t
    jp_io_chunk_set(jp_io_chunk *self, const void *data, size_t size);

//  fill chunk with filler
size_t
    jp_io_chunk_fill(jp_io_chunk *self, byte filler, size_t size);

//  append data to chunk
size_t
    jp_io_chunk_append(jp_io_chunk *self, const void *data, size_t size);

//  append with extend possible
size_t
    jp_io_chunk_extend(jp_io_chunk *self, const void *data, size_t size);

// copy data from source into self 
size_t
    jp_io_chunk_consume(jp_io_chunk *self, jp_io_chunk *src);

// returns if the chunk is consumed
bool
    jp_io_chunk_exhausted(jp_io_chunk *self);

//  read file into chunk
jp_io_chunk*
    jp_io_chunk_read(FILE *handle, size_t bytes);

//  write chunk into FILE
//  returns whether or not it wrote everything to the file
bool
    jp_io_chunk_write(jp_io_chunk *self, FILE *handle);

// try to slurp maxsize bytes into a chunk 
// returns the block or NULL if it failed 
jp_io_chunk*
    jp_io_chunk_slurp(const char *filename, size_t maxsize);

// copy a chunk
jp_io_chunk*
    jp_io_chunk_dup(jp_io_chunk *self);

// return chunk data encoded as hex string
char*
    jp_io_chunk_strhex(jp_io_chunk *self);

// copy chunk data into fresh string
char*
    jp_io_chunk_strdup(jp_io_chunk *self);

//  returns whether or not chunk equals the string
bool
    jp_io_chunk_streq(jp_io_chunk *self, const char *string);

// calculates sha1 digest of chunk
const char*
    jp_io_chunk_digest(jp_io_chunk *self);

// dump chunk into FILE
void
    jp_io_chunk_fprint(jp_io_chunk *self, FILE *file);

// dump msg about chunk to stderr
void
    jp_io_chunk_print(jp_io_chunk *self);

//  Self test of this class
void
    jp_io_chunk_test(bool verbose);


#ifdef __cplusplus
}
#endif

#endif
