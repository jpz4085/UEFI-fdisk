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
/*#include <stdlib.h>*/
/*double*/ long long strtod( nptr , endptr )
	const char * nptr __attribute__((unused)) ;
	char** endptr __attribute__((unused)) ;
{
	/* TODO: ? */
	__fortify_fail( "strtod()" ) ;
	/*
	return 0 ;
	*/
}
//__typeof (__strtod_l) strtod_l __attribute__((weak, alias("__strtod_l"))) ;
//__typeof (__strtod_l) strtod __attribute__((weak, alias("__strtod_l"))) ;
