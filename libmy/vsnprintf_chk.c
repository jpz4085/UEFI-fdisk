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
#include <string.h>
#include <stdio.h>
#include "dietstdio.h"
struct str_data {
	char* str;
	size_t len;
	size_t size;
};
static int swrite(void*ptr, size_t nmemb, struct str_data* sd) {
	size_t tmp=sd->size-sd->len;
	if (tmp>0) {
		size_t len=nmemb;
		if (len>tmp) len=tmp;
		if (sd->str) {
			memcpy(sd->str+sd->len,ptr,len);
			sd->str[sd->len+len]=0;
		}
		sd->len+=len;
	}
	return nmemb;
}
int __vsnprintf_chk(
	char * str ,
	size_t size ,
	int flag __attribute__((unused)) ,
	size_t real_size __attribute__((unused)) ,
	const char * format ,
	va_list arg_ptr )
{
	int n;
	struct str_data sd = { str, 0, size?size-1:0 };
	struct arg_printf ap = { &sd, (int(*)(void*,size_t,void*)) swrite };
	n=__v_printf(&ap,format,arg_ptr);
	if (str && size && n>=0) {
		if (size!=(size_t)-1 && ((size_t)n>=size)) str[size-1]=0;
		else str[n]=0;
	}
	return n;
}
