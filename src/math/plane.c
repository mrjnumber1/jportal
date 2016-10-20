/*  =========================================================================
    jp_math_plane - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_math_plane - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_math_plane {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_math_plane

jp_math_plane *
jp_math_plane_new(void)
{
    jp_math_plane *self = (jp_math_plane *) jmalloc(sizeof (jp_math_plane));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_math_plane

void
jp_math_plane_destroy(jp_math_plane **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_math_plane *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_math_plane_test (bool verbose)
{
    puts(" * jp_math_plane: ");

    //  @selftest
    //  Simple create/destroy test
    jp_math_plane *self = jp_math_plane_new();
    jassert(self);
    jp_math_plane_destroy(&self);
    //  @end
    puts("OK!\n");
}
