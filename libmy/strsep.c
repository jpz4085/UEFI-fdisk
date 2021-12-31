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
