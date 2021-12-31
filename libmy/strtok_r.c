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
