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
struct str_data {
	unsigned char* str;
};
static int sgetc(struct str_data* sd) {
	register unsigned int ret = *(sd->str++);
	return (ret)?(int)ret:-1;
}
static int sputc(int c, struct str_data* sd) {
	return (*(--sd->str)==c)?c:-1;
}
#ifdef __vsscanf
# undef __vsscanf
#endif
int __vsscanf(const char* str, const char* format, va_list arg_ptr)
{
	struct str_data fdat = { (unsigned char*)str };
	struct arg_scanf farg = { (void*)&fdat, (int(*)(void*))sgetc, (int(*)(int,void*))sputc };
	return __v_scanf(&farg,format,arg_ptr);
}
__typeof (__vsscanf) vsscanf __attribute__((weak, alias("__vsscanf"))) ;
__typeof (__vsscanf) __isoc99_vsscanf __attribute__((weak, alias("__vsscanf"))) ;
