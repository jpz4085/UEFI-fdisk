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
 * This file contains unused Linux process/CPU management functions that return
 * a standard failure condition and are needed only to prevent linking errors.
 */
 
#include "libmy.h"
#include <sched.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

cpu_set_t *
__sched_cpualloc ( count )
	size_t count __attribute__((unused)) ;
{
	return NULL ;
}

void
__sched_cpufree ( set )
	cpu_set_t * set __attribute__((unused)) ;
{
	errno = ENOMEM ;
}

pid_t fork( void )
{
	errno = ENOSYS ;
	return -1 ;
}

int
execv( pathname, argv )
	const char *pathname __attribute__((unused)) ;
	char *const argv[] __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1 ;
}

pid_t
waitpid( pid, wstatus, options)
	pid_t pid __attribute__((unused)) ;
	int *wstatus __attribute__((unused)) ;
	int options __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return (pid_t) -1;
}

pid_t getpid() { return 1 ; }

__typeof( getpid ) getppid __attribute__(( weak , alias( "getpid" ) )) ;

int prctl(int option);

int
prctl ( option )
	int option __attribute__((unused)) ;
{
	errno = EINVAL ;
	return -1;
}

