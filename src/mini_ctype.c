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

int toupper(int ch) {
    if ((unsigned int)(ch - 'a') < 26u) {
        ch += 'A' - 'a';
    }
    
    return ch;
}

int tolower(int ch) {
    if ((unsigned int)(ch - 'A') < 26u) {
        ch += 'a' - 'A';
    }
    
    return ch;
}

int isalnum(int ch) {
    return (unsigned int)((ch | 0x20) - 'a') < 26u ||
           (unsigned int)( ch         - '0') < 10u;
}

int isupper(int ch) {
    return (unsigned int)(ch - 'A') < 26u;
}

int islower(int ch) {
    return (unsigned int) (ch - 'a') < 26u;
}

int isspace(int ch) {
    return (unsigned int)(ch - 9) < 5u  ||  ch == ' ';
}

int isgraph(int ch) {
    return (unsigned int)(ch - '!') < 127u - '!';
}

int isdigit(int ch) {
    return (unsigned int)(ch - '0') < 10u;
}

int isblank(int ch) {
    return ch == ' ' ||  ch == '\t';
}

int isascii(int ch) {
    return (unsigned int)ch < 128u;
}

int isalpha(int ch) {
    return (unsigned int)((ch | 0x20) - 'a') < 26u;
}

int isxdigit(int ch) {
    return (unsigned int)( ch         - '0') < 10u || 
           (unsigned int)((ch | 0x20) - 'a') <  6u;
}

