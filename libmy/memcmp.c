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
#include <sys/types.h>
#include <string.h>
int memcmp( s1 , s2 , n )
	const void * s1 ;
	const void * s2 ;
	size_t n ;
{
	const unsigned char * p1 = (const unsigned char *) s1 ;
	const unsigned char * p2 = (const unsigned char *) s2 ;
	size_t i ;
/*
				if ( ! s1 && ! s2 ) return 0 ;
				if ( s1 && ! s2 ) return 1 ;
				if ( ! s1 && s2 ) return -1 ;
*/
	for ( i = 0 ; i < n ; i ++ ) {
	        if ( * p1 != * p2 ) {
	                return * p1 > * p2 ? 1 : -1 ;
	        }
	        p1 ++ ;
	        p2 ++ ;
	}
	return 0 ;
}
