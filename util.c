#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

uint
g32(uchar *p)
{
	return p[0]<<24|p[1]<<16|p[2]<<8|p[3]<<0;
}

uvlong
g64(uchar *p)
{
	return ((uvlong)g32(p)<<32)|g32(p+4);
}

void
p32(uint v, uchar *p)
{
	p[0] = v>>24;
	p[1] = v>>16;
	p[2] = v>>8;
	p[3] = v>>0;
}

void
p64(uvlong v, uchar *p)
{
	p32(v>>32, p);
	p32(v, p+4);
}

void
p128(Uvvlong v, uchar *p)
{
	p64(v.hi, p);
	p64(v.lo, p+8);
}


void
uvvadd(Uvvlong *v, int n)
{
	v->lo += n;
	if(v->lo < n)
		v->hi++;
}

void
uvvmult8(Uvvlong *v)
{
	v->hi = (v->hi<<3) | (v->lo >> (64-3));
	v->lo <<= 3;
}


char
hexchar(uchar c)
{
	if(c <= 9)
		return '0'+c;
	if(c < 16)
		return 'a'+c-10;
	return ~0;
}

uchar
unhexchar(char c)
{
	if(c >= '0' && c <= '9')
		return c-'0';
	if(c >= 'A' && c <= 'F')
		return c-'A'+10;
	if(c >= 'a' && c <= 'f')
		return c-'a'+10;
	return ~0;
}

char *
hex(uchar *f, int n, char *t)
{
	int i;
	char *o;

	o = t;
	for(i = 0; i < n; i++) {
		*t++ = hexchar(f[i]>>4);
		*t++ = hexchar(f[i]&0xf);
	}
	*t = 0;
	return o;
}

void
printhex(char *s, uchar *f, int n)
{
	char *buf;

	buf = malloc(2*n+1);
	if(buf == nil)
		abort();
	fprintf(stderr, "%s %s\n", s, hex(f, n, buf));
	free(buf);
}

char *
unhex(char *s, uchar *p, int n)
{
	uchar a, b;
	int len;

	len = strlen(s);
	if(len > n*2)
		return "input too long";
	if(len % 2 != 0)
		return "input has odd length, bad hex";

	for(; len > 0 && n > 0; len -= 2, n--) {
		a = unhexchar(*s++);
		b = unhexchar(*s++);
		if(a == 0xff || b == 0xff)
			return "bad hex character";
		*p++ = (a<<4)|b;
	}
	return nil;
}
