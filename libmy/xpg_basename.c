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
 
 /* Fail for unused glibc __xpg_basename function to prevent linking errors. */
 
#include "libmy.h"
#include <string.h>
#include <libgen.h>

char *
__xpg_basename ( filename )
	char *filename __attribute__((unused)) ;
{
	__fortify_fail( "__xpg_basename()" ) ;
}

