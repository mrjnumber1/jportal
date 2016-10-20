/*  =========================================================================
    jp_container_map - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_container_map - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_container_map {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_container_map

jp_container_map *
jp_container_map_new(void)
{
    jp_container_map *self = (jp_container_map *) jmalloc(sizeof (jp_container_map));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_container_map

void
jp_container_map_destroy(jp_container_map **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_container_map *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_container_map_test (bool verbose)
{
    puts(" * jp_container_map: ");

    //  @selftest
    //  Simple create/destroy test
    jp_container_map *self = jp_container_map_new();
    jassert(self);
    jp_container_map_destroy(&self);
    //  @end
    puts("OK!\n");
}
