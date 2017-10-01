/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * The implementations have been lifted from dietlibc
 * https://www.fefe.de/dietlibc/
 */

#include <sys/types.h>
#include "mini_mem.h"

#define __likely(x)    __builtin_expect (!!(x), 1)
#define __unlikely(x)  __builtin_expect (!!(x), 0)

#if OVERRIDE_ROM

//
// memcmp
//

int memcmp(const void *dst, const void *src, size_t count) {
    register int r;
    register const unsigned char *d = dst;
    register const unsigned char *s = src;
    ++count;

    while (__likely(--count)) {
        if (__unlikely(r = (*d - *s))) {
            return r;
        }
        ++d;
        ++s;
    }

    return 0;
}

//
// memcpy
//

void *memcpy(void *dst, const void *src, size_t n) {
    void *res = dst;
    unsigned char *c1, *c2;
    c1 = (unsigned char *) dst;
    c2 = (unsigned char *) src;

    while (n--) {
      *c1++ = *c2++;
    }

    return (res);
}

//
// memset
//

void *memset(void *dst, int s, size_t count) {
    register char *a = dst;
    count++;    /* this actually creates smaller code than using count-- */
    while (--count) {
        *a++ = s;
    }

    return dst;
}

//
// memmove
//

void *memmove(void *dst, const void *src, size_t count) {
    char *a = dst;
    const char *b = src;
    if (src != dst) {
        if (src > dst) {
            while (count--) {
                *a++ = *b++;
            }
        } else {
            a += count - 1;
            b += count - 1;
            while (count--) {
                *a-- = *b--;
            }
        }
    }
    
    return dst;
}

#endif /* OVERRIDE_ROM */

//
// memccpy
//

void *memccpy(void *dst, const void *src, int c, size_t count) {
    char *a = dst;
    const char *b = src;
    while (count--) {
        *a++ = *b;
        if (*b == c) {
            return (void *)a;
        }
        b++;
    }

    return 0;
}
