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
 
 /*
 * This file contains unused Linux directory functions that return a standard
 * failure condition and are needed only to prevent linking errors.
 */
 
 #include "libmy.h"
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <dirent.h>
 #include <stddef.h>
 #include <errno.h>
 
struct dirent64 *
readdir64 ( dirp )
	DIR * dirp __attribute__((unused)) ;
{
	errno = ENOENT ;
	return NULL ;
}

DIR *
opendir( name )
	const char * name __attribute__((unused)) ;
{
	errno = ENOENT ;
	return NULL ;
}

DIR *
fdopendir( fd )
	int fd __attribute__((unused)) ;
{
	errno = ENOENT ;
	return NULL ;
}

int
closedir( dirp )
	DIR * dirp __attribute__((unused)) ;
{
	errno = ENOENT ;
	return -1 ;
}

int
dirfd( dirp )
	DIR * dirp __attribute__((unused)) ;
{
	errno = ENOTSUP ;
	return -1 ;
}

void
rewinddir ( dirp )
	DIR * dirp __attribute__((unused)) ;
{
	errno = ENOSYS ;
}

int
mkdir( pathname, mode )
	const char * pathname __attribute__((unused)) ;
	mode_t mode __attribute__((unused)) ;
{
	errno = ENOENT ;
	return -1 ;
}

