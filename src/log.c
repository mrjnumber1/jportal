/*  =========================================================================
    jp_log - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_log - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_log {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_log

jp_log *
jp_log_new(void)
{
    jp_log *self = (jp_log *) jmalloc(sizeof (jp_log));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_log

void
jp_log_destroy(jp_log **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_log *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_log_test (bool verbose)
{
    puts(" * jp_log: ");

    //  @selftest
    //  Simple create/destroy test
    jp_log *self = jp_log_new();
    jassert(self);
    jp_log_destroy(&self);
    //  @end
    puts("OK!\n");
}
