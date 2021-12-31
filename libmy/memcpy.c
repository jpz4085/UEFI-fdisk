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
#define WANT_SMALL_STRING_ROUTINES
#include <string.h>
/* fast memcpy -- Copyright (C) 2003 Thomas M. Ogrisegg <tom@hi-tek.fnord.at> */
void *
memcpy (void *dst, const void *src, size_t n)
{
		void           *res = dst;
		unsigned char  *c1, *c2;
#ifdef WANT_SMALL_STRING_ROUTINES
		c1 = (unsigned char *) dst;
		c2 = (unsigned char *) src;
		while (n--) *c1++ = *c2++;
		return (res);
#else
		int             tmp;
		unsigned long  *lx1 = NULL;
		const unsigned long *lx2 = NULL;
		if (!UNALIGNED(dst, src) && n > sizeof(unsigned long)) {
	if ((tmp = STRALIGN(dst))) {
	    c1 = (unsigned char *) dst;
	    c2 = (unsigned char *) src;
	    while (tmp-- && n--)
		*c1++ = *c2++;
	    if (n == (size_t) - 1)
		return (res);
	    dst = c1;
	    src = c2;
	}
	lx1 = (unsigned long *) dst;
	lx2 = (unsigned long *) src;
	for (; n >= sizeof(unsigned long); n -= sizeof(unsigned long))
	    *lx1++ = *lx2++;
		}
		if (n) {
	c1 = (unsigned char *) (lx1?lx1:dst);
	c2 = (unsigned char *) (lx1?lx2:src);
	while (n--)
	    *c1++ = *c2++;
		}
		return (res);
#endif
}
