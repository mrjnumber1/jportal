/*  =========================================================================
    jp_container_queue - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_container_queue - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_container_queue {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_container_queue

jp_container_queue *
jp_container_queue_new(void)
{
    jp_container_queue *self = (jp_container_queue *) jmalloc(sizeof (jp_container_queue));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_container_queue

void
jp_container_queue_destroy(jp_container_queue **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_container_queue *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_container_queue_test (bool verbose)
{
    puts(" * jp_container_queue: ");

    //  @selftest
    //  Simple create/destroy test
    jp_container_queue *self = jp_container_queue_new();
    jassert(self);
    jp_container_queue_destroy(&self);
    //  @end
    puts("OK!\n");
}
