/*
 * This file is part of UEFI GPT fdisk.
 *
 * UEFI GPT fdisk is a port of GPT fdisk to UEFI/BIOS.
 * UEFI GPT fdisk est un portage de GPT fdisk vers UEFI/BIOS.
 * Ce fichier a été initié par Bernard Burette en janvier 2014.
 *
 * All this work is copyleft Bernard Burette.
 * Gauche d'auteur Bernard Burette.
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
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>

/*
 * Note that RFC4122 defines UUID in more details:
 *
 *     Field               Data Type     Octet  Note
 * -------------------------------------------------
 *  time_low               unsigned 32   0-3    The low field of the
 *                         bit integer          timestamp
 *
 *  time_mid               unsigned 16   4-5    The middle field of the
 *                         bit integer          timestamp
 *
 *  time_hi_and_version    unsigned 16   6-7    The high field of the
 *                         bit integer          timestamp multiplexed
 *                                              with the version number
 *
 *  clock_seq_hi_and_rese  unsigned 8    8      The high field of the
 *  rved                   bit integer          clock sequence
 *                                              multiplexed with the
 *                                              variant
 *
 *  clock_seq_low          unsigned 8    9      The low field of the
 *                         bit integer          clock sequence
 *
 *  node                   unsigned 48   10-15  The spatially unique
 *                         bit integer          node identifier
 *
 * We have clock_seq_hi_and_reserved (8bit) and clock_seq_low (8bit)
 * merged into clock_seq (16bit).
 */
struct uuid {
	uint32_t  time_low ;
	uint16_t  time_mid ;
	uint16_t  time_hi_and_version ;
	uint16_t  clock_seq ;
	uint8_t   node[ 6 ] ;
} ;

/**
 * Remplit un buffer avec des octets aléatoires.
 * Returns 0 when all bytes are randomized for compatibility with
 * util-linux 2.37 and above. The return value is currently unused.
 */
int ul_random_get_bytes( void* , size_t ) ;
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

/*
 * Compresse l'info d'un UUID depuis la structure vers un paquet d'octets.
 */
static void uuid_pack( const struct uuid *uu , uuid_t ptr )
{
	uint32_t tmp;
	uint8_t* out = (uint8_t*) ptr ;

	tmp = uu-> time_low ;
	out[ 3 ] = (unsigned char) tmp ;
	tmp >>= 8;
	out[ 2 ] = (unsigned char) tmp ;
	tmp >>= 8;
	out[ 1 ] = (unsigned char) tmp ;
	tmp >>= 8;
	out[ 0 ] = (unsigned char) tmp ;

	tmp = uu-> time_mid ;
	out[ 5 ] = (unsigned char) tmp ;
	tmp >>= 8 ;
	out[ 4 ] = (unsigned char) tmp ;

	tmp = uu-> time_hi_and_version ;
	out[ 7 ] = (unsigned char) tmp ;
	tmp >>= 8 ;
	out[ 6 ] = (unsigned char) tmp ;

	tmp = uu-> clock_seq ;
	out[ 9 ] = (unsigned char) tmp ;
	tmp >>= 8 ;
	out[ 8 ] = (unsigned char) tmp ;

	memcpy( out + 10 , uu-> node , 6 ) ;
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

/**
 * Convertit une chaîne de caractères en UUID.
 */
int uuid_parse(const char *in, uuid_t uu)
{
	struct uuid uuid ;
	int i ;
	const char* cp ;
	char buf[ 3 ] ;

	if (strlen(in) != 36)
	return -1;
	for (i=0, cp = in; i <= 36; i++,cp++) {
		if ((i == 8) || (i == 13) || (i == 18) ||
			(i == 23))
		{
			if (*cp == '-')
			continue;
			else
			return -1;
		}
		if (i== 36)
		if (*cp == 0)
		continue;
		if (!isxdigit(*cp))
		return -1;
	}
	uuid.time_low = strtoul(in, NULL, 16);
	uuid.time_mid = strtoul(in+9, NULL, 16);
	uuid.time_hi_and_version = strtoul(in+14, NULL, 16);
	uuid.clock_seq = strtoul(in+19, NULL, 16);
	cp = in+24;
	buf[2] = 0;
	for (i=0; i < 6; i++) {
		buf[0] = *cp++;
		buf[1] = *cp++;
		uuid.node[i] = strtoul(buf, NULL, 16);
	}
	uuid_pack(&uuid, uu);
	return 0;
}

/**
 * Décompresse un UUID.
 */
static void uuid_unpack( const uuid_t in , struct uuid* uu )
{
	uint32_t tmp ;
	const uint8_t* ptr = in ;

	tmp = *ptr ;
	ptr ++ ;
	tmp = ( tmp << 8 ) | *ptr ;
	ptr ++ ;
	tmp = ( tmp << 8 ) | *ptr ;
	ptr ++ ;
	tmp = ( tmp << 8 ) | *ptr ;
	ptr ++ ;
	uu-> time_low = tmp ;

	tmp = *ptr ;
	ptr ++ ;
	tmp = ( tmp << 8 ) | *ptr ;
	ptr ++ ;
	uu-> time_mid = tmp ;

	tmp = *ptr ;
	ptr ++ ;
	tmp = ( tmp << 8 ) | *ptr ;
	ptr ++ ;
	uu-> time_hi_and_version = tmp ;

	tmp = *ptr ;
	ptr ++ ;
	tmp = ( tmp << 8 ) | *ptr ;
	ptr ++ ;
	uu-> clock_seq = tmp ;

	memcpy( uu-> node , ptr , 6 ) ;
}

/**
 * Convertit un UUID en chaîne de caractères.
 */
void uuid_unparse_upper(const uuid_t uu, char *out)
{
	struct uuid uuid;

	uuid_unpack(uu, &uuid);
	sprintf(out, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		uuid.time_low, uuid.time_mid, uuid.time_hi_and_version,
		uuid.clock_seq >> 8, uuid.clock_seq & 0xFF,
		uuid.node[0], uuid.node[1], uuid.node[2],
		uuid.node[3], uuid.node[4], uuid.node[5]);
}

