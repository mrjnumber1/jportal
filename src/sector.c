/*  =========================================================================
    jp_sector - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_sector - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_sector {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_sector

jp_sector *
jp_sector_new(void)
{
    jp_sector *self = (jp_sector *) jmalloc(sizeof (jp_sector));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_sector

void
jp_sector_destroy(jp_sector **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_sector *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_sector_test (bool verbose)
{
    puts(" * jp_sector: ");

    //  @selftest
    //  Simple create/destroy test
    jp_sector *self = jp_sector_new();
    jassert(self);
    jp_sector_destroy(&self);
    //  @end
    puts("OK!\n");
}
