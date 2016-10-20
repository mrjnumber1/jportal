/*  =========================================================================
    jp_timing_stopwatch - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_timing_stopwatch - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_timing_stopwatch {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_timing_stopwatch

jp_timing_stopwatch *
jp_timing_stopwatch_new(void)
{
    jp_timing_stopwatch *self = (jp_timing_stopwatch *) jmalloc(sizeof (jp_timing_stopwatch));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_timing_stopwatch

void
jp_timing_stopwatch_destroy(jp_timing_stopwatch **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_timing_stopwatch *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_timing_stopwatch_test (bool verbose)
{
    puts(" * jp_timing_stopwatch: ");

    //  @selftest
    //  Simple create/destroy test
    jp_timing_stopwatch *self = jp_timing_stopwatch_new();
    jassert(self);
    jp_timing_stopwatch_destroy(&self);
    //  @end
    puts("OK!\n");
}
