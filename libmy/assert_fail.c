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
#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
void __assert_fail( assertion , file , line , function )
	const char* assertion ;
	const char* file ;
	unsigned int line ;
	const char* function ;
{
	fprintf( stderr , "assertion '%s' failed: %s:%d: %s()\n" ,
		assertion , file , line , function ) ;
	abort() ;
}
link_warning("__assert_fail","your code has assertions enabled!")
