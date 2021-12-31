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
#include "libmy.h"
#include <stdio.h>
#include <unistd.h>
#ifdef putc
# undef putc
#endif
int fputc( c , stream )
	int c ;
	FILE * stream ;
{
	unsigned char bc ;
	bc = (unsigned char) c ;
	/* jamais de buffering ici */
	setvbuf( stream , NULL , _IONBF , 0 ) ;
	if ( write( stream-> _fileno , & bc , 1 ) != 1 ) {
		stream-> _flags |= _IO_ERR_SEEN ;
		return EOF ;
	}
	return bc ;
}
__typeof( fputc ) putc __attribute__((weak,alias("fputc"))) ;
