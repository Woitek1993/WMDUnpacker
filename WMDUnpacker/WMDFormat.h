#ifndef WMD_FORMAT_H
#define WMD_FORMAT_H

#include <assert.h>

#define COMPILE_TIME_SIZE_CHECK(type, expected)               \
    typedef char _compile_time_size_check_##type[            \
        (sizeof(type) == (expected)) ? 1 : -1                \
    ]

#pragma pack(push,1)
struct BKW_HEADER
{
	int vars[84];

};

COMPILE_TIME_SIZE_CHECK(BKW_HEADER, 0x150);

#pragma pack(pop)

#endif
