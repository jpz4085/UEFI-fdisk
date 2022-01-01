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
#include <fcntl.h>
#include <errno.h>

int fstat64( int fd , struct stat64 *buf )
{
	return __fxstat64( _STAT_VER_LINUX , fd , buf ) ;
}

int
fstatat64 ( fd, file, buf, flag )
	int fd __attribute__((unused)) ;
	const char *file __attribute__((unused)) ;
	struct stat64 *buf __attribute__((unused)) ;
	int flag __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1 ;
}

int
stat64 ( const char *file, struct stat64 *buf )
{
	return fstatat64 (AT_FDCWD, file, buf, 0);
}

