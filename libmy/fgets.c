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
#define _GNU_SOURCE
#include "libmy.h"
#include <stdio.h>
char *fgets_unlocked(char *s, int size, FILE *stream) {
	/* comme on ajoute toujours un \0 on lit un caractère de moins */
	size --;
	int l;
	for (l=0; l<size; ) {
		register int c;
			c=fgetc(stream);
			if (c==EOF) {
	if (!l) return NULL ;
	goto fini;
			}
		s[l]=c;
		++l;
		if (c=='\n'||l==size) {
fini:
			s[l]=0;
			return s;
		}
	}
	return NULL ;
}
char*fgets(char*s,int size,FILE*stream) __attribute__((weak,alias("fgets_unlocked")));
