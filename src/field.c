/*  =========================================================================
    jp_field - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_field - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_field {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_field

jp_field *
jp_field_new(void)
{
    jp_field *self = (jp_field *) jmalloc(sizeof (jp_field));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_field

void
jp_field_destroy(jp_field **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_field *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_field_test (bool verbose)
{
    puts(" * jp_field: ");

    //  @selftest
    //  Simple create/destroy test
    jp_field *self = jp_field_new();
    jassert(self);
    jp_field_destroy(&self);
    //  @end
    puts("OK!\n");
}
