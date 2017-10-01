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

#ifndef mini_ctype_h_included
#define mini_ctype_h_included

int toupper(int ch);
int tolower(int ch);

int isalnum(int ch);
int isalpha(int ch);
int isdigit(int ch);
int isxdigit(int ch);

int isupper(int ch);
int islower(int ch);

int isspace(int ch);
int isblank(int ch);

int isgraph(int ch);
int isascii(int ch);

#endif /* mini_ctype_h_included */