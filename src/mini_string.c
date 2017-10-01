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

#include <stdlib.h>
#include <limits.h>
#include "mini_ctype.h"
#include "mini_string.h"
#include "mini_mem.h"

#define __likely(x)    __builtin_expect (!!(x), 1)
#define __unlikely(x)  __builtin_expect (!!(x), 0)

//
// strchr
//

char *strchr(register const char *t, int c) {
    register char ch;

    ch = c;
    for (;;) {
        if (__unlikely(*t == ch)) {
            break;
        }
        if (__unlikely(!*t)) {
            return 0;
        }
        ++t;
    }
    return (char *)t;
}

//
// strrchr
//

char *strrchr(const char *t, int c) {
    register char ch;
    register const char *l=0;

    ch = c;
    for (;;) {
        if (__unlikely(*t == ch)) {
            l = t;
        }
        if (__unlikely(!*t)) {
            return (char *)l;
        }
        ++t;
    }
    return (char *)l;
}

//
// strdup
//

char *strdup(const char *s) {
    size_t l = strlen(s) + 1;
    char *tmp = (char *)malloc(l);
    if (!tmp) {
        return 0;
    }

    return memcpy(tmp, s, l);
}

//
// strcasecmp
//

int strcasecmp(const char* s1, const char* s2) {
    register unsigned int  x2;
    register unsigned int  x1;

    while (1) {
        x2 = *s2 - 'A';
        if (__unlikely(x2 < 26u)) {
            x2 += 32;
        }

        x1 = *s1 - 'A';
        if (__unlikely(x1 < 26u)) {
            x1 += 32;
        }

        s1++;
        s2++;
        
        if (__unlikely(x2 != x1)) {
            break;
        }
        if (__unlikely(x1 == (unsigned int)-'A')) {
            break;
        }
    }

    return x1 - x2;
}

//
// strncasecmp
//

int strncasecmp(const char* s1, const char* s2, size_t len) {
    register unsigned int  x2;
    register unsigned int  x1;
    register const char *end = s1 + len;

    while (1) {
        if (__unlikely(s1 >= end)) {
            return 0;
        }
        
        x2 = *s2 - 'A';
        if (__unlikely(x2 < 26u)) {
            x2 += 32;
        }
        
        x1 = *s1 - 'A';
        if (__unlikely(x1 < 26u)) {
            x1 += 32;
        }
        
        s1++;
        s2++;
        
        if (__unlikely(x2 != x1)) {
            break;
        }
        if (__unlikely(x1 == (unsigned int)-'A')) {
            break;
        }
    }

    return x1 - x2;
}

//
// strlcpy
//
size_t strlcpy(char *dst, const char *src, size_t siz) {
    register char *d = dst;
    register const char *s = src;
    register size_t n = siz;

    /* Copy as many bytes as will fit */
    if (n != 0 && --n != 0) {
        do {
            if ((*d++ = *s++) == 0) {
                break;
            }
        } while (--n != 0);
    }

    /* Not enough room in dst, add NUL and traverse rest of src */
    if (n == 0) {
        if (siz != 0) {
            *d = '\0';      /* NUL-terminate dst */
        }
        while (*s++);
    }

    return (s - src - 1);    /* count does not include NUL */
}


//
// strtoull
//

unsigned long long int strtoull(const char *ptr, char **endptr, int base) {
    int neg = 0, overflow = 0;
    long long int v = 0;
    const char* orig;
    const char* nptr = ptr;

    while(isspace(*nptr)) ++nptr;

    if (*nptr == '-') {
        neg=1;
        nptr++;
    } else if (*nptr == '+') {
        ++nptr;
    }
    orig = nptr;

    if (base == 16 && nptr[0] == '0') {
        goto skip0x;
    }
    
    if (base) {
        register unsigned int b = base - 2;
        if (__unlikely(b > 34)) {
            return 0;
        }
    } else {
        if (*nptr == '0') {
            base = 8;
skip0x:
            if (((*(nptr + 1) == 'x') || (*(nptr + 1) == 'X')) && isxdigit(nptr[2])) {
               nptr += 2;
               base = 16;
            }
        } else {
            base=10;
        }
    }

    while(__likely(*nptr)) {
        register unsigned char c=*nptr;
        c = (c >= 'a' ? c - 'a' + 10 : c >= 'A' ? c - 'A' + 10 : c <= '9' ? c - '0' : 0xff);
        if (__unlikely(c >= base)) {
            break;  /* out of base */
        }
        {
            register unsigned long x = (v & 0xff) * base + c;
            register unsigned long long w = (v >> 8) * base + (x >> 8);
            if (w > (ULLONG_MAX >> 8)) {
                overflow = 1;
            }
            v = (w << 8) + (x & 0xff);
        }
        ++nptr;
    }

    if (__unlikely(nptr == orig)) {     /* no conversion done */
        nptr = ptr;
        v = 0;
    }
    if (endptr) {
        *endptr = (char *)nptr;
    }
    if (overflow) {
        return ULLONG_MAX;
    }
    return (neg ? -v : v);
}


//
// strtoul
//

unsigned long int strtoul(const char *ptr, char **endptr, int base) {
    int neg = 0, overflow = 0;
    unsigned long int v = 0;
    const char* orig;
    const char* nptr = ptr;

    while(isspace(*nptr)) {
        ++nptr;
    }

    if (*nptr == '-') {
        neg = 1;
        nptr++;
    } else if (*nptr == '+') {
        ++nptr;
    }
    orig = nptr;
    if (base == 16 && nptr[0] == '0') {
        goto skip0x;
    }
    if (base) {
        register unsigned int b = base - 2;
        if (__unlikely(b > 34)) {
            return 0;
        }
    } else {
        if (*nptr=='0') {
            base=8;
skip0x:
            if ((nptr[1] == 'x' || nptr[1] == 'X') && isxdigit(nptr[2])) {
               nptr += 2;
               base = 16;
            }
        } else {
            base = 10;
        }
    }
  
    while(__likely(*nptr)) {
        register unsigned char c = *nptr;
        c = (c >= 'a' ? c - 'a' + 10 : c >= 'A' ? c - 'A' + 10 : c <= '9' ? c - '0' : 0xff);
        if (__unlikely(c >= base)) {
            break;  /* out of base */
        }
        {
            register unsigned long x=(v&0xff)*base+c;
            register unsigned long w=(v>>8)*base+(x>>8);
            if (w > (ULONG_MAX >> 8)) {
                overflow = 1;
            }
            v = (w << 8) + (x & 0xff);
        }
        ++nptr;
    }
  
    if (__unlikely(nptr == orig)) {     /* no conversion done */
        nptr = ptr;
        v = 0;
    }
    
    if (endptr) {
        *endptr = (char *)nptr;
    }
    if (overflow) {
        return ULONG_MAX;
    }
    return (neg ? -v : v);
}

//
// strtoll
//

long long int strtoll(const char *nptr, char **endptr, int base) {
    int neg = 0;
    unsigned long long int v;
    const char *orig = nptr;

    while(isspace(*nptr)) {
        nptr++;
    }

    if (*nptr == '-' && isalnum(nptr[1])) {
        neg = -1;
        nptr++;
    }
  
    v = strtoull(nptr, endptr, base);
    if (endptr && *endptr == nptr) {
        *endptr = (char *)orig;
    }
    
    if (v > LLONG_MAX) {
        if (v == 0x8000000000000000ull && neg) {
            return v;
        }
        return (neg ? LLONG_MIN : LLONG_MAX);
    }
    
    return (neg ? -v : v);
}

//
// strtol
//

#define ABS_LONG_MIN 2147483648UL

long int strtol(const char *nptr, char **endptr, int base) {
    int neg = 0;
    unsigned long int v;
    const char *orig = nptr;

    while(isspace(*nptr)) {
        nptr++;
    }

    if (*nptr == '-' && isalnum(nptr[1])) {
        neg = -1;
        ++nptr;
    }
    
    v = strtoul(nptr, endptr, base);
    if (endptr && *endptr == nptr) {
        *endptr = (char *)orig;
    }
    if (v >= ABS_LONG_MIN) {
        if (v == ABS_LONG_MIN && neg) {
            return v;
        }
        return (neg ? LONG_MIN : LONG_MAX);
    }
    return (neg ? -v : v);
}

//
// strtof
//

float strtof(const char *s, char **endptr) {
    register const char *p = s;
    register float value = 0.0;
    int sign = +1;
    float factor;
    unsigned int expo;

    while (isspace(*p)) {
        p++;
    }

    switch (*p) {
        case '-': 
            sign = -1;
        case '+': 
            p++;
        default:
            break;
    }

    while ((unsigned int)(*p - '0') < 10u) {
        value = value*10 + (*p++ - '0');
    }

    if (*p == '.') {
        factor = 1.0;

        p++;
        while ((unsigned int)(*p - '0') < 10u) {
            factor *= 0.1;
            value  += (*p++ - '0') * factor;
        }
    }

    if ((*p | 32) == 'e') {
        expo = 0;
        factor = 10.0L;

        switch (*++p) {
            case '-':
                factor = 0.1;
            case '+':
                p++;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                break;
            default:
                value = 0.0L;
                p = s;
                goto done;
        }

        while ((unsigned int)(*p - '0') < 10u) {
            expo = 10 * expo + (*p++ - '0');
        }

        for (;;) {
            if (expo & 1) {
                value *= factor;
            }
            if ((expo >>= 1) == 0) {
                break;
            }
            factor *= factor;
        }
    }

done:
    if (endptr != NULL) {
        *endptr = (char*)p;
    }

    return value * sign;
}

//
// strtod
//

double strtod(const char* s, char** endptr) {
    register const char *p = s;
    register long double value = 0.0L;
    int sign = +1;
    long double factor;
    unsigned int expo;

    while (isspace(*p)) {
        p++;
    }

    switch (*p) {
        case '-':
            sign = -1;
        case '+':
            p++;
        default:
            break;
    }

    while ((unsigned int)(*p - '0') < 10u) {
        value = value*10 + (*p++ - '0');
    }

    if (*p == '.') {
        factor = 1.0;

        p++;
        while ((unsigned int)(*p - '0') < 10u) {
            factor *= 0.1;
            value += (*p++ - '0') * factor;
        }
    }

    if ((*p | 32) == 'e') {
        expo = 0;
        factor = 10.L;

        switch (*++p) {
            case '-':
                factor = 0.1;
            case '+':
                p++;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                break;
            default:
                value = 0.0L;
                p = s;
                goto done;
        }

        while ((unsigned int)(*p - '0') < 10u) {
            expo = 10 * expo + (*p++ - '0');
        }

        for(;;) {
            if (expo & 1) {
                value *= factor;
            }
            if ((expo >>= 1) == 0) {
                break;
            }
            factor *= factor;
        }
    }

done:
    if (endptr != NULL) {
        *endptr = (char*)p;
    }

    return value * sign;
}

//
// atof
//

double atof(const char *s) {
  return strtod(s, 0);
}

//
// atoi
//

int atoi(const char *s) {
    long int v = 0;
    int sign = 1;
  
    while (*s == ' ' || (unsigned int)(*s - 9) < 5u) {
        s++;
    }
  
    switch (*s) {
        case '-':
            sign = -1;
        case '+':
            ++s;
            break;
    }

  while ((unsigned int) (*s - '0') < 10u) {
    v = v * 10 + *s - '0';
    ++s;
  }

  return sign == -1 ? -v : v;
}

//
// atol
//

long int atol(const char *s) {
    return strtol(s, 0, 10);
}


#if OVERRIDE_ROM

//
// strstr
//

char *strstr(const char *haystack, const char *needle) {
    size_t nl = strlen(needle);
    size_t hl = strlen(haystack);
    size_t i;

    if (!nl) {
        goto found;
    }
    if (nl > hl) {
        return 0;
    }
    for (i = hl - nl + 1; __likely(i); --i) {
        if (*haystack == *needle && !memcmp(haystack, needle, nl))
found:
            return (char*)haystack;
        ++haystack;
    }
    return 0;
}

//
// strlen
//

size_t strlen(const char *s) {
    register size_t i;
    
    if (__unlikely(!s)) {
        return 0;   
    } 
    for (i = 0; __likely(*s); ++s) {
        ++i;
    }
    return i;
}

//
// strncpy
//
char *strncpy(char *dest, const char *src, size_t n) {
    memset(dest, 0, n);
    memccpy(dest, src, 0, n);
    return dest;
}

//
// strcpy
//

char *strcpy(char *s1, const char *s2) {
    char *res = s1;
    while ((*s1++ = *s2++));
    return (res);
}

//
// strncmp
//

int strncmp(const char *s1, const char *s2, size_t n) {
    register const unsigned char *a = (const unsigned char *)s1;
    register const unsigned char *b = (const unsigned char *)s2;
    register const unsigned char *fini = a + n;
    while (a != fini) {
        register int res = *a - *b;
        if (res){
            return res;
        }
        if (!*a) {
            return 0;
        }
        ++a;
        ++b;
    }

    return 0;
}

//
// strcmp
//

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

#endif /* OVERRIDE_ROM */