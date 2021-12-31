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
#include <string.h>
int __ltostr( s , size , i , base , UpCase )
	char * s ;
	size_t size ;
	long i ;
	unsigned int base ;
	char UpCase ;
{
	char *tmp;
	unsigned int j=0;
	s[--size]=0;
	tmp=s+size;
	if ((base==0)||(base>36)) base=10;
	j=0;
	if (!i)
	{
		*(--tmp)='0';
		j=1;
	}
	while((tmp>s)&&(i))
	{
		tmp--;
		if ((*tmp=i%base+'0')>'9') *tmp+=(UpCase?'A':'a')-'9'-1;
		i=i/base;
		j++;
	}
	memmove(s,tmp,j+1);
	return j;
}
__typeof( __ltostr ) ltostr __attribute__((weak,alias("__ltostr"))) ;
