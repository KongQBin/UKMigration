#ifndef __STDIO_H__
#define __STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <ctype.h>
#include <errno.h>
#include <fifo.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#ifndef EOF
#define EOF		(-1)
#endif

#ifndef BUFSIZ
#define BUFSIZ	(4096)
#endif

enum {
	_IONBF		= 0,
	_IOLBF		= 1,
	_IOFBF		= 2,
};

enum {
	SEEK_SET	= 0,		/* set file offset to offset */
	SEEK_CUR	= 1,		/* set file offset to current plus offset */
	SEEK_END	= 2,		/* set file offset to EOF plus offset */
};

/*
 * Stdio file position type
 */
typedef loff_t fpos_t;

/*
 * stdio state variables.
 */
typedef struct __FILE FILE;
struct __FILE {
	int fd;

	ssize_t (*read)(FILE *, unsigned char *, size_t);
	ssize_t (*write)(FILE *, const unsigned char *, size_t);
	fpos_t (*seek)(FILE *, fpos_t, int);
	int (*close)(FILE *);

	struct fifo_t * fifo_read;
	struct fifo_t * fifo_write;

	unsigned char * buf;
	size_t bufsz;
	int (*rwflush)(FILE *);

	fpos_t pos;
	int mode;
	int eof, error;
};

#define stdin		(__runtime_get_stdin())
#define stdout		(__runtime_get_stdout())
#define stderr		(__runtime_get_stderr())

FILE * fopen(const char * path, const char * mode);
FILE * freopen(const char * path, const char * mode, FILE * f);
int fclose(FILE * f);

int feof(FILE * f);
int ferror(FILE * f);
int fflush(FILE * f);
void clearerr(FILE * f);

int fseek(FILE * f, fpos_t off, int whence);
fpos_t ftell(FILE * f);
void rewind(FILE * f);

int fgetpos(FILE * f, fpos_t * pos);
int fsetpos(FILE * f, const fpos_t * pos);

size_t fread(void * buf, size_t size, size_t count, FILE * f);
size_t fwrite(const void * buf, size_t size, size_t count, FILE * f);

int getc(FILE * f);
int fgetc(FILE * f);
char * fgets(char * s, int n, FILE * f);
int putc(int c, FILE * f);
int fputc(int c, FILE * f);
int fputs(const char * s, FILE * f);
int ungetc(int c, FILE * f);

int setvbuf(FILE * f, char * buf, int mode, size_t size);
void setbuf(FILE * f, char * buf);

FILE * tmpfile(void);

int fprintf(FILE * f, const char * fmt, ...);
int fscanf(FILE * f, const char * fmt, ...);

int vsnprintf(char * buf, size_t n, const char * fmt, va_list ap);
int vsscanf(const char * buf, const char * fmt, va_list ap);
int sprintf(char * buf, const char * fmt, ...);
int snprintf(char * buf, size_t n, const char * fmt, ...);
int sscanf(const char * buf, const char * fmt, ...);

/*
 * Inner function
 */
int __stdio_no_flush(FILE * f);
int	__stdio_read_flush(FILE * f);
int __stdio_write_flush(FILE * f);

ssize_t __stdio_read(FILE * f, unsigned char * buf, size_t size);
ssize_t __stdio_write(FILE * f, const unsigned char * buf, size_t size);

FILE * __file_alloc(int fd);

FILE * __runtime_get_stdin(void);
FILE * __runtime_get_stdout(void);
FILE * __runtime_get_stderr(void);

#ifdef __cplusplus
}
#endif

#endif /* __STDIO_H__ */
