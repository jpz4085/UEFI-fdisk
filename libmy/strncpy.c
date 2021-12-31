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
#include <string.h>
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
