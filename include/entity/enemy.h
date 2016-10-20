/*  =========================================================================
    jp_entity_enemy - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef JP_ENTITY_ENEMY_H_INCLUDED
#define JP_ENTITY_ENEMY_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  Create a new jp_entity_enemy
jp_entity_enemy *
    jp_entity_enemy_new(void);

//  Destroy the jp_entity_enemy
void
    jp_entity_enemy_destroy(jp_entity_enemy **self_p);

//  Self test of this class
void
    jp_entity_enemy_test(bool verbose);


#ifdef __cplusplus
}
#endif

#endif
