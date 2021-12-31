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
/* fast strcmp -- Copyright (C) 2003 Thomas M. Ogrisegg <tom@hi-tek.fnord.at> */
#include <ctype.h>
#include <string.h>
# define TOLOWER(Ch) tolower (Ch)
# define LOCALE_PARAM
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
