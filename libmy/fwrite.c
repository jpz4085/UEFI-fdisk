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
#define _XOPEN_SOURCE 600
#define _GNU_SOURCE
#include "libmy.h"
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#ifdef fwrite_unlocked
# undef fwrite_unlocked
#endif
size_t fwrite_unlocked( ptr , size , count , stream )
	const void * ptr ;
	size_t size ;
	size_t count ;
	FILE * stream ;
{
	const char * p ;
	size_t n ;
	/* jamais de buffering ici */
	setvbuf( stream , NULL , _IONBF , 0 ) ;
	p = (const char *) ptr ;
	n = 0 ;
	while ( count ) {
	        if ( write( stream-> _fileno , p , size ) != (ssize_t) size ) {
			stream-> _flags |= _IO_ERR_SEEN ;
			break ;
	        }
	        p += size ;
	        count -- ;
	        n ++ ;
	}
	return n ;
}
__typeof( fwrite_unlocked ) fwrite __attribute__((weak,alias("fwrite_unlocked"))) ;
