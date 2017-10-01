/* The MIT License (MIT)
 *
 * Copyright (c) 2014 Little Star Media, Inc.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * `asprintf.c' - asprintf
 *
 * copyright (c) 2014 joseph werle <joseph.werle@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "mini_asprintf.h"
#include "mini_sprintf.h"

int asprintf(char **str, const char *fmt, ...) {
    int size = 0;
    va_list args;
    va_start(args, fmt);
    size = vasprintf(str, fmt, args);
    va_end(args);
    return size;
}

int vasprintf(char **str, const char *fmt, va_list args) {
    int size = 0;
    va_list tmpa;
    va_copy(tmpa, args);


    size = vsnprintf(NULL, size, fmt, tmpa);
    va_end(tmpa);

    if (size < 0) {
        return -1;
    }

    *str = (char *)malloc(size + 1);
    if (NULL == *str) {
        return -1;
    }

    size = vsprintf(*str, fmt, args);
    
    return size;
}
