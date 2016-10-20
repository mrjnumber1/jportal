/*  =========================================================================
    jp_io_input_input - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_io_input_input - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_io_input_input {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_io_input_input

jp_io_input_input *
jp_io_input_input_new(void)
{
    jp_io_input_input *self = (jp_io_input_input *) jmalloc(sizeof (jp_io_input_input));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_io_input_input

void
jp_io_input_input_destroy(jp_io_input_input **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_io_input_input *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_io_input_input_test (bool verbose)
{
    puts(" * jp_io_input_input: ");

    //  @selftest
    //  Simple create/destroy test
    jp_io_input_input *self = jp_io_input_input_new();
    jassert(self);
    jp_io_input_input_destroy(&self);
    //  @end
    puts("OK!\n");
}
