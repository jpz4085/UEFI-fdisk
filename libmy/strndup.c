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
#include <stdlib.h>
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
