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
/* needed to get definition of "struct stat64" from sys/stat.h
 do this first otherwise file "sys/types.h" will have already
 been included by others. */
#define _LARGEFILE64_SOURCE 1
#include <sys/stat.h>
#include "libmy.h"
#include <sys/types.h>
#include <unistd.h>
int fstat64( fd , buf )
				int fd ;
				struct stat64 * buf ;
{
				return __fxstat64( _STAT_VER_LINUX , fd , buf ) ;
}
