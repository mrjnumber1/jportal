/*  =========================================================================
    jp_timing_event - class description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is publically available for educational use by mrj!!!    
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef JP_TIMING_EVENT_H_INCLUDED
#define JP_TIMING_EVENT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  Create a new jp_timing_event
jp_timing_event *
    jp_timing_event_new(void);

//  Destroy the jp_timing_event
void
    jp_timing_event_destroy(jp_timing_event **self_p);

//  Self test of this class
void
    jp_timing_event_test(bool verbose);


#ifdef __cplusplus
}
#endif

#endif
