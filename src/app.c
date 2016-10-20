/*  =========================================================================
    jp_app - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_app - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_app {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_app

jp_app *
jp_app_new(void)
{
    jp_app *self = (jp_app *) jmalloc(sizeof (jp_app));
    assert(self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_app

void
jp_app_destroy(jp_app **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_app *self = *self_p;
        //  Free class properties here

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_app_test (bool verbose)
{
    puts(" * jp_app: ");

    //  @selftest
    //  Simple create/destroy test
    jp_app *self = jp_app_new();
    jassert(self);
    jp_app_destroy(&self);
    //  @end
    puts("OK!\n");
}
