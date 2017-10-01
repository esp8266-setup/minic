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

#ifndef mini_string_h_included
#define mini_string_h_included

/* We only provide stuff that's not already in the ESP8266 ROM by default */
#ifndef OVERRIDE_ROM
#define OVERRIDE_ROM 0
#endif

/** Return pointer to first occurence of character in string
 *
 * @warning if the string is not correctly zero terminated the result is undefined
 *
 * @param t: string to search
 * @param c: character to find
 *
 * @returns pointer to first occurence of c or NULL if not found
 */
char *strchr(register const char *t, int c);

/** Return pointer to last occurence of character in string
 *
 * @warning if the string is not correctly zero terminated the result is undefined
 *
 * @param t: string to search
 * @param c: character to find
 *
 * @returns pointer to last occurence of c or Null if not found
 */
char *strrchr(const char *t, int c);

/** find beginning of a string in another string
 *
 * @param haystack: string to search in
 * @param needle: string to search for
 *
 * @returns pointer to first occurence of needle or NULL
 */
char *strstr(const char *haystack, const char *needle);

/** Calculate length of string
 *
 * @warning if the string is not correctly zero terminated the result is undefined
 *
 * @param s: string to calculate length of
 * 
 * @returns size in bytes of string
 */
size_t strlen(const char *s);

/** Copy string from one buffer to another
 *
 * @param dest: destination buffer (has to be of equal or bigger size than s1)
 * @param src: source
 *
 * @returns dest
 */
char *strcpy(char *dest, const char *src);

/** Copy at most n characters of src to dest
 *
 * @warning if the string in src is longer than the dest buffer the string in
 *          the dest buffer will be unterminated! Use strlcpy to avoid this.
 *
 * @param dest: destination buffer, has to be at least n bytes long
 * @param src: source buffer
 * @param n: size of dest buffer (or smaller)
 *
 * @returns dest
 */
char *strncpy(char *dest, const char *src, size_t n);

/** Copy at most n characters of src to dest
 *
 * @note this copies at most n-1 characters to dest to make sure
 *       the string is properly zero terminated.
 *
 * @param dest: destination buffer, has to be at least n bytes long
 * @param src: source buffer
 * @param n: size of dest buffer (or smaller)
 *
 * @returns number of bytes copied
 */
size_t strlcpy(char *dst, const char *src, size_t n);

/** duplicate string
 *
 * @note free() the result after use
 *
 * @param s: string to duplicate
 */
char *strdup(const char *s);

/** compare two strings
 *
 * @param s1: first string
 * @param s2: second string
 *
 * @returns zero if strings match
 */
int strcmp(const char *s1, const char *s2);

/** compare at most n characters of two strings
 *
 * @param s1: first string
 * @param s2: second string
 * @param n: number of bytes to compare at maximum, comparison stops if zero
 *           byte is reached in either string though
 *
 * @returns zero if strings match
 */
int strncmp(const char *s1, const char *s2, size_t n);

/** case insensitive compare two strings
 *
 * @param s1: first string
 * @param s2: second string
 *
 * @returns zero if strings match
 */
int strcasecmp(const char* s1, const char* s2);

/** case insensitive compare at most n characters of two strings
 *
 * @param s1: first string
 * @param s2: second string
 * @param n: number of bytes to compare at maximum, comparison stops if zero
 *           byte is reached in either string though
 *
 * @returns zero if strings match
 */
int strncasecmp(const char* s1, const char* s2, size_t n);

/** convert string to unsigned long long
 *
 * @param ptr: pointer to string to convert
 * @param endptr: output parameter, pointer to position where parsing stopped
 * @param base: number base 10 to 36
 *
 * @returns parsed number
 */
unsigned long long int strtoull(const char *ptr, char **endptr, int base);

/** convert string to unsigned long
 *
 * @param ptr: pointer to string to convert
 * @param endptr: output parameter, pointer to position where parsing stopped
 * @param base: number base 10 to 36
 *
 * @returns parsed number
 */
unsigned long int strtoul(const char *ptr, char **endptr, int base);

/** convert string to signed long long
 *
 * @param ptr: pointer to string to convert
 * @param endptr: output parameter, pointer to position where parsing stopped
 * @param base: number base 10 to 36
 *
 * @returns parsed number
 */
long long int strtoll(const char *nptr, char **endptr, int base);

/** convert string to signed long
 *
 * @param ptr: pointer to string to convert
 * @param endptr: output parameter, pointer to position where parsing stopped
 * @param base: number base 10 to 36
 *
 * @returns parsed number
 */
long int strtol(const char *nptr, char **endptr, int base);

/** convert string to float
 *
 * @warning currently does not parse scientific notation (e.g. 1.3e+13)
 *
 * @param ptr: pointer to string to convert
 * @param endptr: output parameter, pointer to position where parsing stopped
 *
 * @returns parsed number
 */
float strtof(const char *s, char **endptr);

/** convert string to double
 *
 * @warning currently does not parse scientific notation (e.g. 1.3e+13)
 *
 * @param ptr: pointer to string to convert
 * @param endptr: output parameter, pointer to position where parsing stopped
 *
 * @returns parsed number
 */
double strtod(const char* s, char** endptr);

/** convert string to float
 *
 * @warning currently does not parse scientific notation (e.g. 1.3e+13)
 *
 * @param s: pointer to string to convert
 *
 * @returns parsed number
 */
double atof(const char *s);

/** convert string to int
 *
 * @param s: pointer to string to convert
 *
 * @returns parsed number
 */
int atoi(const char *s);

/** convert string to long int
 *
 * @param s: pointer to string to convert
 *
 * @returns parsed number
 */
long int atol(const char *s);

#endif /* mini_string_h_included */