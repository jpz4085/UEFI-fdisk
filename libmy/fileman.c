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
 * This file contains unused Linux file management functions that return a
 * standard failure condition and are needed only to prevent linking errors.
 */
 
#include "libmy.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
  
int
unlink( pathname )
	const char * pathname __attribute__((unused)) ;
{
	errno = ENOENT ;
	return -1 ;
}

int
link( oldpath, newpath )
	const char * oldpath __attribute__((unused)) ;
	const char * newpath __attribute__((unused)) ;
{
	errno = ENOENT ;
	return -1 ;
}

int
rename( oldpath, newpath )
	const char * oldpath __attribute__((unused)) ;
	const char * newpath __attribute__((unused)) ;
{
	errno = ENOENT ;
	return -1 ;
}

int
fchmod( fd, mode)
	int fd __attribute__((unused)) ;
	mode_t mode __attribute__((unused)) ;
{
	errno = ENOENT ;
	return -1 ;
}

ssize_t
sendfile64 ( out_fd, in_fd, offset, count )
	int out_fd __attribute__((unused)) ;
	int in_fd __attribute__((unused)) ;
	off_t *offset __attribute__((unused)) ;
	size_t count __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

mode_t umask( mask )
	mode_t mask __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

int
openat64 ( fd, file, oflag )
	int fd __attribute__((unused)) ;
	const char *file __attribute__((unused)) ;
	int oflag __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

int
dup ( fd )
	int fd __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

int
dup2 ( oldfd, newfd )
	int oldfd __attribute__((unused)) ;
	int newfd __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

ssize_t
readlink ( path, buf, len)
	const char *path __attribute__((unused)) ;
	char *buf __attribute__((unused)) ;
	size_t len __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

ssize_t
readlinkat ( fd, path, buf, len)
	int fd __attribute__((unused)) ;
	const char *path __attribute__((unused)) ;
	char *buf __attribute__((unused)) ;
	size_t len __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

int
mkostemp64 ( template, flags )
	char *template __attribute__((unused)) ;
	int flags __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

int
getdtablesize (void)
{
	errno = ENOSYS ;
	return -1;
}

int
faccessat ( fd, file, type, flag)
	int fd __attribute__((unused)) ;
	const char *file __attribute__((unused)) ;
	int type __attribute__((unused)) ;
	int flag __attribute__((unused)) ;
{
	errno = ENOSYS ;
	return -1;
}

char *
getcwd( buf, size)
	char *buf __attribute__((unused)) ;
	size_t size __attribute__((unused)) ;
{
	errno = ENOENT ;
	return NULL ;
}

char *
realpath( path, resolved_path)
	const char *path __attribute__((unused)) ;
	char *resolved_path __attribute__((unused)) ;
{
	errno = EINVAL ;
	return NULL ;
}

