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

#ifndef mini_mem_h_included
#define mini_mem_h_included

/* We only provide stuff that's not already in the ESP8266 ROM by default */
#ifndef OVERRIDE_ROM
#define OVERRIDE_ROM 0
#endif

/** Compare memory areas
 *
 * @param dst: first memory area
 * @param src: second memory area
 * @param count: number of bytes to compare
 *
 * @returns zero if the areas match, other if they don't match
 */
int memcmp(const void *dst, const void *src, size_t count);

/** Copy memory areas
 *
 * @param dst: destination area
 * @param src: source memory
 * @param n: number of bytes to copy
 *
 * @returns pointer to destination area
 */
void *memcpy(void *dst, const void *src, size_t n);

/** Set memory to defined content
 *
 * @param dst: destination area
 * @param s: byte value to copy into destination area
 * @param count: number of bytes to overwrite
 *
 * @returns dst
 */
void *memset(void *dst, int s, size_t count);

/** Move memory from one area to another
 *
 * It is save if src and dst overlap
 *
 * @param dst: destination area
 * @param src: source area
 * @param count: number of bytes to move
 *
 * @returns: dst
 */
void *memmove(void *dst, const void *src, size_t count);

/** Copy memory areas until a special character has been found
 *
 * @param dst: destination area
 * @param src: source memory
 * @param c: the character to stop copying at
 * @param count: number of bytes to copy
 *
 * @returns pointer to the first occurence of c
 */
void *memccpy(void *dst, const void *src, int c, size_t count);

#endif /* mini_mem_h_included */