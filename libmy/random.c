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
 * Random number generation functions needed for compilation/linking. Only
 * random()/rand() and srandom()/srand() are used by fdisk. The others are
 * not and return a standard failure condition.
 */
 
#include "libmy.h"
#include <stdlib.h>
#include <sys/random.h>
#include <errno.h>

static uint32_t holdrand = 1 ;

long int
random ( void )
{
	/* ANSI PRNG */
	holdrand = holdrand * 1103515245L + 12345L ;
	/* return a pseudo-random in range 0-0x7fff */
	return ( holdrand >> 16 ) & 0x7fff ;
}

int
rand ( void )
{
 	return (int) random ();
}

void
srandom ( seed )
	unsigned int seed ;
{
	/* store this seed */
	holdrand = (uint32_t) seed ;
}

void 
srand ( seed )
	unsigned int seed ;
{
	(void) srandom (seed);
}

long int
jrand48 ( xsubi )
	unsigned short xsubi[3] __attribute__((unused)) ;
{
	return -1 ;
}

ssize_t
getrandom( buf, buflen, flags )
	void *buf __attribute__((unused)) ;
	size_t buflen __attribute__((unused)) ;
	unsigned int flags __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

