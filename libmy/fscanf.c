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
#include <stdio.h>
#include "dietstdio.h"
#ifdef __fscanf
# undef __fscanf
#endif
int __fscanf(FILE *stream, const char *format, ...) ;
int __fscanf(FILE *stream, const char *format, ...) {
	int n;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	n=vfscanf(stream,format,arg_ptr);
	va_end (arg_ptr);
	return n;
}
__typeof (__fscanf) fscanf __attribute__((weak, alias("__fscanf"))) ;
__typeof (__fscanf) __isoc99_fscanf __attribute__((weak, alias("__fscanf"))) ;
