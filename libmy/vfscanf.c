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
#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdarg.h>
#include "dietstdio.h"
int __vfscanf( FILE* stream , const char* format , va_list arg_ptr )
{
	struct arg_scanf ap = { stream ,
		(int(*)(void*)) fgetc ,
		(int(*)(int,void*)) ungetc };
	return __v_scanf( & ap , format , arg_ptr ) ;
}
__typeof (__vfscanf) vfscanf __attribute__((weak, alias("__vfscanf"))) ;
__typeof (__vfscanf) __isoc99_vfscanf __attribute__((weak, alias("__vfscanf"))) ;
