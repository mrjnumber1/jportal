/*  =========================================================================
    jp_io_data_texture - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef JP_IO_DATA_TEXTURE_H_INCLUDED
#define JP_IO_DATA_TEXTURE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  Create a new jp_io_data_texture
jp_io_data_texture *
    jp_io_data_texture_new(void);

//  Destroy the jp_io_data_texture
void
    jp_io_data_texture_destroy(jp_io_data_texture **self_p);

//  Self test of this class
void
    jp_io_data_texture_test(bool verbose);


#ifdef __cplusplus
}
#endif

#endif
