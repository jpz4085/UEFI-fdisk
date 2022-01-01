/*
 *
 * This file is part of UEFI fdisk.
 *
 * UEFI fdisk is a port of util-linux fdisk to UEFI/BIOS.
 * UEFI fdisk est un portage de util-linux fdisk vers UEFI/BIOS.
 * Ce fichier a été initié par Bernard Burette en janvier 2014.
 *
 * All this work is copyleft Bernard Burette.
 * Gauche d'auteur Bernard Burette.
 *
 * This program is distributed under the terms of the GNU General Public
 *  License version 2 or more.
 * La diffusion de ce code est faite selon les termes de la licence publique
 *  générale GNU version 2 ou plus.
 *
 */
 
/*
 * This file contains all required string functions for compilation/linking.
 */

#define _GNU_SOURCE
#include "libmy.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <endian.h>
#include <ctype.h>

#ifdef strcmp
# undef strcmp
#endif

#undef __USE_EXTERN_INLINES

#if __WORDSIZE == 64
#define ABS_LONG_MIN 9223372036854775808UL
#else
#define ABS_LONG_MIN 2147483648UL
#endif

# define TOLOWER(Ch) tolower (Ch)
# define LOCALE_PARAM
#undef strcasecmp

#ifdef isspace
# undef isspace
#endif
#define isspace( c ) ( c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v' )
#ifdef isalnum
# undef isalnum
#endif
#define isalnum( c ) ( ( c >= '0' && c <= '9' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) )
#ifdef isxdigit
# undef isxdigit
#endif
#define isxdigit( c ) ( ( c >= '0' && c <= '9' ) || ( c >= 'A' && c <= 'F' ) || ( c >= 'a' && c <= 'f' ) )

char* strcat( register char* s , register const char* t )
{
	register char* dest = s ;
	s += strlen( s ) ;
	for(;;) {
		if ( ! ( *s = *t ) ) break ;
		++ s ;
		++ t ;
	}
	return dest ;
}

char *
strchr (register const char *s, int c)
{
	do {
		if (*s == c)
			{
				return (char*)s;
			}
	} while (*s++);
	return (0);
}

__typeof( strchr ) strrchr __attribute__(( weak , alias( "strchr" ) )) ;

int
strcmp (const char *s1, const char *s2)
{
		while (*s1 && *s1 == *s2)
				s1++, s2++;
		return (*s1 - *s2);
}
int strcoll(const char *s,const char* t)       __attribute__((weak,alias("strcmp")));

char *
strcpy (char *s1, const char *s2)
{
		char           *res = s1;
		while ((*s1++ = *s2++));
		return (res);
}

/* Duplicate S, returning an identical malloc'd string.  */
char *
strdup (const char *s)
{
	size_t len = strlen (s) + 1;
	void *new = malloc (len);
	if (new == NULL)
		return NULL;
	return (char *) memcpy (new, s, len);
}

size_t strlen(const char *s) {
	register size_t i;
	for (i=0; *s; ++s) ++i;
	return i;
}

char *strsep(char **stringp, const char *delim) {
	register char *tmp=*stringp;
	register char *tmp2;
	register const char *tmp3;
	if (!*stringp) return 0;
	for (tmp2=tmp; *tmp2; ++tmp2) {
		for (tmp3=delim; *tmp3; ++tmp3)
			if (*tmp2==*tmp3) {	/* delimiter found */
	*tmp2=0;
	*stringp=tmp2+1;
	return tmp;
			}
	}
	*stringp=0;
	return tmp;
}

size_t strspn(const char *s, const char *accept)
{
	size_t l = 0;
	const char *a;
	for (; *s; s++) {
		for (a = accept; *a && *s != *a; a++);
		if (!*a)
			break;
		else
		 l++;
	}
	return l;
}

char *
strstr( haystack, needle )
	const char *haystack __attribute__((unused)) ;
	const char *needle __attribute__((unused)) ;
{
	return NULL ;
}

double strtod( nptr , endptr )
	const char * nptr __attribute__((unused)) ;
	char** endptr __attribute__((unused)) ;
{
	__fortify_fail( "strtod()" ) ;
}

__attribute__((nothrow,leaf,nonnull((1))))
long int strtol(const char *nptr, char **endptr, int base)
{
	int neg=0;
	unsigned long int v;
	const char*orig=nptr;
	while(isspace(*nptr)) nptr++;
	if (*nptr == '-' && isalnum(nptr[1])) { neg=-1; ++nptr; }
	v=strtoul(nptr,endptr,base);
	if (endptr && *endptr==nptr) *endptr=(char *)orig;
	if (v>=ABS_LONG_MIN) {
		if (v==ABS_LONG_MIN && neg) {
			errno=0;
			return v;
		}
		errno=ERANGE;
		return (neg?LONG_MIN:LONG_MAX);
	}
	return (neg?-v:v);
}
__attribute__((nothrow,leaf,nonnull((1))))
__typeof (strtol) strtoimax __attribute__((alias("strtol"))) ;

size_t strcspn(const char *s, const char *reject)
{
	size_t l=0;
	int i;
	for (; *s; ++s) {
		for (i=0; reject[i]; ++i)
			if (*s==reject[i]) return l;
		++l;
	}
	return l;
}

/* fast strcmp -- Copyright (C) 2003 Thomas M. Ogrisegg <tom@hi-tek.fnord.at> */
int
strncmp (const char *s1, const char *s2, size_t n)
{
	unsigned char c1 = '\0';
	unsigned char c2 = '\0';
	while (n > 0)
		{
			c1 = (unsigned char) *s1++;
			c2 = (unsigned char) *s2++;
			if (c1 == '\0' || c1 != c2)
				return c1 - c2;
			n--;
		}
	return c1 - c2;
}

/* gcc is broken and has a non-SUSv2 compliant internal prototype.
 * This causes it to warn about a type mismatch here.  Ignore it. */
char *strncpy(char *dest, const char *src, size_t n) {
#ifdef WANT_FULL_POSIX_COMPAT
	memset(dest,0,n);
#endif
	memccpy(dest,src,0,n);
#ifdef WANT_NON_COMPLIANT_STRNCAT
	if (n) dest[n-1]=0;	/* maybe we should rather abort() if n is 0? */
#endif
	return dest;
}

char *strndup(const char *s,size_t n) {
	/* This relies on the fact that our malloc(0) returns NULL.
	 * Otherwise this would be an exploitable integer overflow! */
#ifdef WANT_MALLOC_ZERO
	char *tmp=!(n+1)?0:(char *)malloc(n+1);
#else
	char *tmp=(char *)malloc(n+1);
#endif
	if (!tmp) return 0;
	strncpy(tmp,s,n);
	tmp[n]=0;
	return tmp;
}

size_t strnlen(const char *s,size_t maxlen) {
	const char* x=memchr(s,0,maxlen);
	if (!x) x=s+maxlen;
	return x-s;
}

long double
strtold( nptr, endptr)
	const char *nptr __attribute__((unused)) ;
	char **endptr __attribute__((unused)) ;
{
	return 0 ;
}

__attribute__((nothrow,leaf,nonnull((1))))
unsigned long int strtoul(const char *ptr, char **endptr, int base)
{
	int neg = 0, overflow = 0;
	unsigned long int v=0;
	const char* orig;
	const char* nptr=ptr;
	while(isspace(*nptr)) ++nptr;
	if (*nptr == '-') { neg=1; nptr++; }
	else if (*nptr == '+') ++nptr;
	orig=nptr;
	if (base==16 && nptr[0]=='0') goto skip0x;
	if (base) {
		register unsigned int b=base-2;
		if ((b>34)) { errno=EINVAL; return 0; }
	} else {
		if (*nptr=='0') {
			base=8;
skip0x:
			if ((nptr[1]=='x'||nptr[1]=='X') && isxdigit(nptr[2])) {
				nptr+=2;
				base=16;
			}
		} else
			base=10;
	}
	while((*nptr)) {
		register unsigned char c=*nptr;
		c=(c>='a'?c-'a'+10:c>='A'?c-'A'+10:c<='9'?c-'0':0xff);
		if ((c>=base)) break;     /* out of base */
		{
			register unsigned long x=(v&0xff)*base+c;
			register unsigned long w=(v>>8)*base+(x>>8);
			if (w>(ULONG_MAX>>8)) overflow=1;
			v=(w<<8)+(x&0xff);
		}
		++nptr;
	}
	if ((nptr==orig)) {         /* no conversion done */
		nptr=ptr;
		errno=EINVAL;
		v=0;
	}
	if (endptr) *endptr=(char *)nptr;
	if (overflow) {
		errno=ERANGE;
		return ULONG_MAX;
	}
	return (neg?-v:v);
}
__attribute__((nothrow,leaf,nonnull((1))))
__typeof (strtoul) strtoumax __attribute__((alias("strtoul"))) ;

unsigned long long int strtoull(const char *nptr, char **endptr, int base)
{
	return (unsigned long long int) strtoul(nptr, endptr, base);
}

char*strtok_r(char*s,const char*delim,char**ptrptr) {
	char*tmp=0;
	if (s==0) s=*ptrptr;
	s+=strspn(s,delim);	/* overread leading delimiter */
	if (*s) {
		tmp=s;
		s+=strcspn(s,delim);
		if (*s) *s++=0;	/* not the end ? => terminate it */
	}
	*ptrptr=s;
	return tmp;
}

/* Compare S1 and S2, ignoring case, returning less than, equal to or
	 greater than zero if S1 is lexicographically less than,
	 equal to or greater than S2.  */
int
strcasecmp(const char *s1, const char *s2 LOCALE_PARAM)
{
#if defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
	locale_t loc = _NL_CURRENT_LOCALE;
#endif
	const unsigned char *p1 = (const unsigned char *) s1;
	const unsigned char *p2 = (const unsigned char *) s2;
	int result;
	if (p1 == p2)
		return 0;
	while ((result = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
		if (*p1++ == '\0')
			break;
	return result;
}

/* fast strcmp -- Copyright (C) 2003 Thomas M. Ogrisegg <tom@hi-tek.fnord.at> */
/* Compare S1 and S2, ignoring case, returning less than, equal to or
	 greater than zero if S1 is lexicographically less than,
	 equal to or greater than S2.  */
int
strncasecmp (const char *s1, const char *s2 LOCALE_PARAM , size_t length )
{
#if defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
	locale_t loc = _NL_CURRENT_LOCALE;
#endif
	const unsigned char *p1 = (const unsigned char *) s1;
	const unsigned char *p2 = (const unsigned char *) s2;
	int result;
	if (p1 == p2)
		return 0;
	while ( ((result = TOLOWER (*p1) - TOLOWER (*p2++)) == 0) && length-- != 0 )
		if (*p1++ == '\0')
			break;
	return result;
}

int __ltostr( s , size , i , base , UpCase )
	char * s ;
	size_t size ;
	long i ;
	unsigned int base ;
	char UpCase ;
{
	char *tmp;
	unsigned int j=0;
	s[--size]=0;
	tmp=s+size;
	if ((base==0)||(base>36)) base=10;
	j=0;
	if (!i)
	{
		*(--tmp)='0';
		j=1;
	}
	while((tmp>s)&&(i))
	{
		tmp--;
		if ((*tmp=i%base+'0')>'9') *tmp+=(UpCase?'A':'a')-'9'-1;
		i=i/base;
		j++;
	}
	memmove(s,tmp,j+1);
	return j;
}
__typeof( __ltostr ) ltostr __attribute__((weak,alias("__ltostr"))) ;

int __lltostr( s , size , i , base , UpCase )
	char * s ;
	size_t size ;
	long long i ;
	unsigned int base ;
	char UpCase ;
{
	char *tmp;
	unsigned int j=0;
	s[--size]=0;
	tmp=s+size;
	if ((base==0)||(base>36)) base=10;
	j=0;
	if (!i)
	{
		*(--tmp)='0';
		j=1;
	}
	while((tmp>s)&&(i))
	{
		tmp--;
		if ((*tmp=i%base+'0')>'9') *tmp+=(UpCase?'A':'a')-'9'-1;
		i=i/base;
		j++;
	}
	memmove(s,tmp,j+1);
	return j;
}

