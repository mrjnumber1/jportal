/*  =========================================================================
    jp_io_input_mouse - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_io_input_mouse - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_io_input_mouse {
	union {
		jp_io_input_input* input;
	};
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_io_input_mouse

jp_io_input_mouse *
jp_io_input_mouse_new(void)
{
    jp_io_input_mouse *self = (jp_io_input_mouse *) jmalloc(sizeof (jp_io_input_mouse));
    assert(self);
    //  Initialize class properties here
	jp_io_input_input* parent = jp_io_input_input_new();

	assert(parent);

	self->input = parent;
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_io_input_mouse

void
jp_io_input_mouse_destroy(jp_io_input_mouse **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_io_input_mouse *self = *self_p;
        //  Free class properties here
	jp_io_input_input_destroy(&(self->input));
	self->input = NULL;

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_io_input_mouse_test (bool verbose)
{
    puts(" * jp_io_input_mouse: ");

    //  @selftest
    //  Simple create/destroy test
    jp_io_input_mouse *self = jp_io_input_mouse_new();
    jassert(self);
    jp_io_input_mouse_destroy(&self);
    //  @end
    puts("OK!\n");
}
