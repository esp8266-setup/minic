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

#ifndef mini_sprintf_h_included
#define mini_sprintf_h_included

int vsnprintf(char* str, size_t size, const char *format, va_list arg_ptr);
int vsprintf(char *dest, const char *format, va_list arg_ptr);
int snprintf(char *dest, size_t size, const char *format, ...);
int sprintf(char *dest, const char *format, ...);

#endif /* mini_sprintf_h_included */