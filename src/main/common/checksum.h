#pragma once

#include <type_traits>
#include <stdint.h>
#include <stddef.h>

constexpr uint16_t checksum(const char* s, size_t n, size_t i, uint16_t sum1, uint16_t sum2) {
  return (i <= n) ? checksum(s, n, i+1, (sum1 + s[i]) % 255, (sum2 + sum1) % 255) : ((sum2 << 8) | sum1);
}

constexpr uint16_t operator "" _checksum(const char* s, size_t n) {
  return checksum(s, n, 0, 0, 0);
}

#define CHECKSUM(X) std::integral_constant<uint16_t, X##_checksum>::value

uint16_t getChecksum(const char *to_check) {
    // From: http://en.wikipedia.org/wiki/Fletcher%27s_checksum
    uint16_t sum1 = 0;
    uint16_t sum2 = 0;
    const char *p = to_check;
    char c;
    while((c = *p++) != 0) {
        sum1 = (sum1 + c) % 255;
        sum2 = (sum2 + sum1) % 255;
    }
    return (sum2 << 8) | sum1;
}
