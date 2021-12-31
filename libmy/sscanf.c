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
#include <stdio.h>
#include "dietstdio.h"
#ifdef __sscanf
# undef __sscanf
#endif
#ifdef vsscanf
# undef vsscanf
#endif
#ifdef __vsscanf
# undef __vsscanf
#endif
#ifdef sscanf
# undef sscanf
#endif
int __sscanf( const char* s , const char* format , ... ) ;
int __sscanf( const char* s , const char* format , ... )
{
	va_list arg ;
	int done ;
	va_start( arg , format ) ;
	done = vsscanf( s , format , arg ) ;
	va_end( arg ) ;
	return done ;
}
__typeof (__sscanf) sscanf __attribute__((weak, alias("__sscanf"))) ;
__typeof (__sscanf) __isoc99_sscanf __attribute__((weak, alias("__sscanf"))) ;
