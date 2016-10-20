/*  =========================================================================
    jp_sector - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef JP_SECTOR_H_INCLUDED
#define JP_SECTOR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  Create a new jp_sector
jp_sector *
    jp_sector_new(void);

//  Destroy the jp_sector
void
    jp_sector_destroy(jp_sector **self_p);

//  Self test of this class
void
    jp_sector_test(bool verbose);


#ifdef __cplusplus
}
#endif

#endif
