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
 * This file contains all memory functions needed for compilation/linking.
 */

#define _GNU_SOURCE
#include "libmy.h"
#include <string.h>
#include <sys/types.h>

#define _POSIX_SOURCE 1
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#endif

#define WANT_SMALL_STRING_ROUTINES

void* memchr(const void *s, int c, size_t n) {
	const unsigned char *pc = (unsigned char *) s;
	for (;n--;pc++)
		if (*pc == c)
			return ((void *) pc);
	return 0;
}

int memcmp( s1 , s2 , n )
	const void * s1 ;
	const void * s2 ;
	size_t n ;
{
	const unsigned char * p1 = (const unsigned char *) s1 ;
	const unsigned char * p2 = (const unsigned char *) s2 ;
	size_t i ;

	for ( i = 0 ; i < n ; i ++ ) {
	        if ( * p1 != * p2 ) {
	                return * p1 > * p2 ? 1 : -1 ;
	        }
	        p1 ++ ;
	        p2 ++ ;
	}
	return 0 ;
}

void *memccpy(void *dst, const void *src, int c, size_t count)
{
	char *a = dst;
	const char *b = src;
	while (count--)
	{
		*a++ = *b;
		if (*b==c)
		{
			return (void *)a;
		}
		b++;
	}
	return 0;
}

void *memmove(void *dst, const void *src, size_t count)
{
	char *a = dst;
	const char *b = src;
	if (src!=dst)
	{
		if (src>dst)
		{
			while (count--) *a++ = *b++;
		}
		else
		{
			a+=count-1;
			b+=count-1;
			while (count--) *a-- = *b--;
		}
	}
	return dst;
}

void *mempcpy(void* __restrict__ dst, const void* __restrict__ src, size_t n) {
	return memcpy(dst,src,n)+n;
}

void *
__memcpy_chk( void* dstpp , const void* srcpp , size_t len ,
	size_t dstlen __attribute__((unused)) )
{
	return memcpy( dstpp , srcpp , len ) ;
}

void *
__memset_chk( void* dstpp , int c , size_t len ,
	size_t dstlen __attribute__((unused)) )
{
	return memset( dstpp , c , len ) ;
}

