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
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "dietstdio.h"
static int __fwrite(void*ptr, size_t nmemb, FILE* f) {
	return fwrite(ptr,1,nmemb,f);
}
int __vfprintf_chk(
	FILE * stream ,
	int flag __attribute__((unused)) ,
	const char *format ,
	va_list arg_ptr )
{
	struct arg_printf ap = {
		stream ,
		(int(*)(void*,size_t,void*)) __fwrite
	} ;
	return __v_printf(&ap,format,arg_ptr);
}
