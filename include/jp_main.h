#ifndef JP_MAIN_H_
#define JP_MAIN_H_

#include "jp_prelude.h"

#define JP_VERSION_MAJOR 0
#define JP_VERSION_MINOR 0
#define JP_VERSION_PATCH 0

#define JP_MAKE_VERSION(major, minor, patch) \
    ((major)*1000000 + (minor)*1000 + (patch))
#define JP_VERSION \
    JP_MAKE_VERSION(JP_VERSION_MAJOR, JP_VERSION_MINOR, JP_VERSION_PATCH)

#endif
