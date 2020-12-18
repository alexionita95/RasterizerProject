#pragma once
#include <stdint.h>
namespace Utils {
    static bool isInInterval(uint32_t value, uint32_t min, uint32_t max)
    {
        return min <= value && max >= value;
    }
}