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
#include "libmy.h"
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
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
