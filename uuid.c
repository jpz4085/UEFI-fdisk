/*
 * This file is part of UEFI GPT fdisk.
 *
 * UEFI GPT fdisk is a port of GPT fdisk to UEFI/BIOS.
 * UEFI GPT fdisk est un portage de GPT fdisk vers UEFI/BIOS.
 * Ce fichier a été initié par Bernard Burette en janvier 2014.
 *
 * Original work is copyleft Bernard Burette.
 * Modifications are copyleft Joseph Zeller.
 *
 * This program is distributed under the terms of the GNU GPL version 2.
 * La diffusion de ce code est faite selon les termes de la GPL GNU version 2.
 */

/** @file
 *
 * Fonction de génération de nombres aléatoires et de UUID.
 *
 */

#include "uefi.h"
#include "../libuuid/src/uuidP.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>

/**
 * Remplit un buffer avec des octets aléatoires.
 * Returns 0 when all bytes are randomized for compatibility with
 * util-linux 2.37 and above. The return value is currently unused.
 */
int ul_random_get_bytes( void* buf , size_t nbytes )
{
	uint8_t * p ;
	unsigned char first = 1 ;
	if ( first ) {
		/* au tout premier appel on initialise le générateur */
		srand( time( NULL ) ) ;
		first = 0 ;
	}
	p = (uint8_t*) buf ;
	while ( nbytes > 0 ) {
		int v ;
		/* if we didn't knew max rand() value and since the most
		   random bits are the most significant we would do
		   v=(int)(256.0f*((float)rand()/(RAND_MAX+1.0f)));
		   but here it is simpler because RAND_MAX == 0x7fff  */
		v = rand() >> 7 ;
		* p = (uint8_t) v ;
		p ++ ;
		nbytes -- ;
	}
	return nbytes != 0;
}

void random_get_bytes( void* buf , size_t nbytes )
{
	ul_random_get_bytes( buf , nbytes ) ;
}

/*
 * Construit un UUID.
 */
void uuid_generate_random( uuid_t out )
{
	struct uuid nuuid ;
	/* generates random bits for new UUID */
	ul_random_get_bytes( & nuuid , sizeof( nuuid ) ) ;
	/* set version 4 as required by RFC 4122 */
	nuuid. time_hi_and_version &= 0x0fff ;
	nuuid. time_hi_and_version |= 0x4000 ;
	/* stocke dans le tableau d'octets */
	uuid_pack( & nuuid , out ) ;
	/* set variant 10x as required by RFC 4122 */
	out[ 8 ] &= 0x3f ;
	out[ 8 ] |= 0x80 ;
}

