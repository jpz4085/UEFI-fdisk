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
/**
 * Racine pour les nombres aléatoires.
 */
static uint32_t holdrand = 1 ;
/**
 * Positionne la racine.
 */
void srand( seed )
	unsigned int seed ;
{
	/* store this seed */
	holdrand = (uint32_t) seed ;
}
/*
 * Génère un nombre aléatoire.
 */
int rand()
{
	/* ANSI PRNG */
	holdrand = holdrand * 1103515245L + 12345L ;
	/* return a pseudo-random in range 0-0x7fff */
	return ( holdrand >> 16 ) & 0x7fff ;
}
