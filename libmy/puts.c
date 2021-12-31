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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
static int __stdio_outs(const char *s,size_t len) ;
static int __stdio_outs(const char *s,size_t len) {
	return (write(1,s,len)==(ssize_t)len)?1:0;
}
int puts(const char *s) {
	return (__stdio_outs(s,strlen(s)) && __stdio_outs("\n",1))?0:-1;
}
