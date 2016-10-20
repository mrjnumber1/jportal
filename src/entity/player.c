/*  =========================================================================
    jp_entity_player - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    jp_entity_player - 
@discuss
@end
*/

#include "jp_classes.h"

//  Structure of our class

struct _jp_entity_player {
	union {
		jp_entity_entity* entity;
	};
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new jp_entity_player

jp_entity_player *
jp_entity_player_new(void)
{
    jp_entity_player *self = (jp_entity_player *) jmalloc(sizeof (jp_entity_player));
    assert(self);
    //  Initialize class properties here
	jp_entity_entity* parent = jp_entity_entity_new();

	assert(parent);

	self->entity = parent;
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the jp_entity_player

void
jp_entity_player_destroy(jp_entity_player **self_p)
{
    assert(self_p);
    if (*self_p) {
        jp_entity_player *self = *self_p;
        //  Free class properties here
	jp_entity_entity_destroy(&(self->entity));
	self->entity = NULL;

        //  Free object itself
        free(self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
jp_entity_player_test (bool verbose)
{
    puts(" * jp_entity_player: ");

    //  @selftest
    //  Simple create/destroy test
    jp_entity_player *self = jp_entity_player_new();
    jassert(self);
    jp_entity_player_destroy(&self);
    //  @end
    puts("OK!\n");
}
