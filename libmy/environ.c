/*
 *
 * This file is part of UEFI fdisk.
 *
 * UEFI fdisk is a port of util-linux fdisk to UEFI/BIOS.
 * UEFI fdisk est un portage de util-linux fdisk vers UEFI/BIOS.
 * Ce fichier a été initié par Bernard Burette en janvier 2014.
 *
 * Original work is copyleft Bernard Burette.
 * Modifications are copyleft Joseph Zeller.
 *
 * This program is distributed under the terms of the GNU General Public
 *  License version 2 or more.
 * La diffusion de ce code est faite selon les termes de la licence publique
 *  générale GNU version 2 ou plus.
 *
 */
 
/*
 * This file contains unused Linux environment functions that return a standard
 * failure condition and are needed only to prevent linking errors.
 */

#include "libmy.h"
#include <stdlib.h>
#include <errno.h>

char **environ;

int
setenv( name, value, overwrite )
	const char * name __attribute__((unused)) ;
	const char * value __attribute__((unused)) ;
	int overwrite __attribute__((unused)) ;
{
	errno = EINVAL ;
	return -1 ;
}

char* getenv( const char* n __attribute__((unused)) ) { return NULL ; }
__THROW __attribute_const__
__typeof( getenv ) secure_getenv __attribute__(( weak , alias( "getenv" ) )) ;

