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
 * This file contains unused Linux user/group id functions that return a
 * standard failure condition and are needed only to prevent linking errors.
 */
 
#include "libmy.h"
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#pragma GCC diagnostic ignored "-Wredundant-decls"

int
setgid( gid )
	gid_t gid __attribute__((unused)) ;
{
	errno = EINVAL ;
	return -1;
}

int
setuid( uid )
	uid_t uid __attribute__((unused)) ;
{
	errno = EINVAL ;
	return -1;
}

uid_t getuid() { return 0 ; }
uid_t geteuid() { return 0 ; }
gid_t getgid() { return 0 ; }
gid_t getegid() { return 0 ; }

