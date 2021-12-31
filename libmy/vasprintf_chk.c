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
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <stdio.h>
#include "dietstdio.h"
int __vasprintf_chk( char ** strp , int flag , const char* format , va_list ap )
{
	size_t n ;
	size_t alloc = 50 ;
	char* dest ;
	va_list args ;
	for(;;) {
		dest = (char*) malloc( alloc ) ;
		if ( dest == NULL ) return -1 ;
		/* il faut faire une copie sinon explosion */
		va_copy( args , ap ) ;
		n = __vsnprintf_chk( dest , alloc , flag , alloc ,
			format , args ) ;
		va_end( args ) ;
		/* n ne compte pas le \0 de la fin */
		if ( n < alloc ) break ;
		/* double l'allocation de mémoire */
		free( dest ) ;
		alloc <<= 1 ;
	}
	*strp = dest ;
	return n ;
}
