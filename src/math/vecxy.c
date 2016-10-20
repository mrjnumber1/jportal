/*  =========================================================================
    jp_math_vecxy - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_math_vecxy - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_math_vecxy {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_math_vecxy

jp_math_vecxy *
jp_math_vecxy_new(void)
{
    jp_math_vecxy *self = (jp_math_vecxy *) jmalloc(sizeof (jp_math_vecxy));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_math_vecxy

void
jp_math_vecxy_destroy(jp_math_vecxy **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_math_vecxy *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_math_vecxy_test (bool verbose)
{
    puts(" * jp_math_vecxy: ");

    //  @selftest
    //  Simple create/destroy test
    jp_math_vecxy *self = jp_math_vecxy_new();
    jassert(self);
    jp_math_vecxy_destroy(&self);
    //  @end
    puts("OK!\n");
}
