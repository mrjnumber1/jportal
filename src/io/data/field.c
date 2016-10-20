/*  =========================================================================
    jp_io_data_field - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_io_data_field - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_io_data_field {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_io_data_field

jp_io_data_field *
jp_io_data_field_new(void)
{
    jp_io_data_field *self = (jp_io_data_field *) jmalloc(sizeof (jp_io_data_field));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_io_data_field

void
jp_io_data_field_destroy(jp_io_data_field **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_io_data_field *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_io_data_field_test (bool verbose)
{
    puts(" * jp_io_data_field: ");

    //  @selftest
    //  Simple create/destroy test
    jp_io_data_field *self = jp_io_data_field_new();
    jassert(self);
    jp_io_data_field_destroy(&self);
    //  @end
    puts("OK!\n");
}
