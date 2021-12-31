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
#define _XOPEN_SOURCE 600
#include "libmy.h"
#include <stdarg.h>
#include <sys/types.h>
#include <stdio.h>
#include "dietstdio.h"
int __snprintf_chk(char * str, size_t maxlen, int flag, size_t strlen, const char * format , ...)
{
	int n;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	n=__vsnprintf_chk(str , maxlen , flag , strlen , format,arg_ptr);
	va_end (arg_ptr);
	return n;
}
