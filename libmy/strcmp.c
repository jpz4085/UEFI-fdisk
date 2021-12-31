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
#ifdef strcmp
# undef strcmp
#endif
int
strcmp (const char *s1, const char *s2)
{
		while (*s1 && *s1 == *s2)
				s1++, s2++;
		return (*s1 - *s2);
}
int strcoll(const char *s,const char* t)       __attribute__((weak,alias("strcmp")));
