/*  =========================================================================
    jp_io_input_kb - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef JP_IO_INPUT_KB_H_INCLUDED
#define JP_IO_INPUT_KB_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  Create a new jp_io_input_kb
jp_io_input_kb *
    jp_io_input_kb_new(void);

//  Destroy the jp_io_input_kb
void
    jp_io_input_kb_destroy(jp_io_input_kb **self_p);

//  Self test of this class
void
    jp_io_input_kb_test(bool verbose);


#ifdef __cplusplus
}
#endif

#endif
