# minic library

This a library to be used in firmware for the ESP8266.

## What is this

This library implements a small subset of the c library to avoid having to link the complete c library from the RTOS SDK.
If you're missing some functionality feel free to open an issue or send a pull request.

### Implemented functionality

Most functionality has been lifted from [dietlibc](https://www.fefe.de/dietlibc/) which is itself licensed under GPL 2.
The `asprintf` implementation is from [littlstar/asprintf.c](https://github.com/littlstar/asprintf.c) and licensed MIT.

#### String functions

**Various sprintf variants:**

	int vsnprintf(char* str, size_t size, const char *format, va_list arg_ptr);
	int vsprintf(char *dest, const char *format, va_list arg_ptr);
	int snprintf(char *dest, size_t size, const char *format, ...);
	int sprintf(char *dest, const char *format, ...);

	int vasprintf(char **dest, const char *format, va_list arg_ptr);
	int asprintf(char **dest, const char *format, ...);

**Searching strings:**

	char *strchr(register const char *t, int c);
	char *strrchr(const char *t, int c);
	int strcasecmp(const char* s1, const char* s2);
	int strncasecmp(const char* s1, const char* s2, size_t len);

**Copying strings:**

	size_t strlcpy(char *dst, const char *src, size_t siz);
	char *strdup(const char *s);

**Parsings strings:**

	unsigned long long int strtoull(const char *ptr, char **endptr, int base);
	unsigned long int strtoul(const char *ptr, char **endptr, int base);
	long long int strtoll(const char *nptr, char **endptr, int base);
	long int strtol(const char *nptr, char **endptr, int base);
	int atoi(const char *s);
	long int atol(const char *s);

	float strtof(const char *s, char **endptr);
	double strtod(const char* s, char** endptr);
	double atof(const char *s)

#### Memory functions

	void *memccpy(void *dst, const void *src, int c, size_t count);

#### c_type functions

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


## Usage instructions

This library is built with the [esp8266-setup](http://github.com/esp8266-setup/esp8266-setup) tool in mind.

If you are already using the `esp8266-setup` build system just issue the following command in your project dir:

```bash
esp8266-setup add-library git+https://github.com/esp8266-setup/minic.git
```

If you do not want to use the `esp8266-setup` build system just grab the files from the `src` and `include` directories and add them to your project.

Be aware that most libraries built with this build system use the `C99` standard, so you may have to add `--std=c99` to your `CFLAGS`.

## Build instructions

- Install the ESP8266 Toolchain
- Download the ESP8266 RTOS SDK
- Compile the library: 
```bash
    make \
      XTENSA_TOOLS_ROOT=/path/to/compiler/bin \
      SDK_PATH=/path/to/ESP8266_RTOS_SDK
```

- The finished library will be placed in the current directory under the name
  of `libminic.a`
- Corresponding include files are in `include/`

If you installed the ESP SDK and toolchain to a default location (see below) you may just type `make` to build.

### Default locations

#### Windows

- **XTENSA\_TOOLS\_ROOT**: `c:\ESP8266\xtensa-lx106-elf\bin`
- **SDK_PATH**: `c:\ESP8266\ESP8266_RTOS_SDK`

#### MacOS X

We assume that your default file system is not case sensitive so you will have created a sparse bundle with a case sensitive filesystem which is named `ESP8266`:

- **XTENSA\_TOOLS\_ROOT**: `/Volumes/ESP8266/esp-open-sdk/xtensa-lx106-elf/bin`
- **SDK_PATH**: `/Volumes/ESP8266/ESP8266_RTOS_SDK`

#### Linux

- **XTENSA\_TOOLS\_ROOT**: `/opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin`
- **SDK_PATH**: `/opt/Espressif/ESP8266_RTOS_SDK`
