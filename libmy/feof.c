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
#define _GNU_SOURCE
#include "libmy.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dietstdio.h"
int feof_unlocked(stream)
	FILE*stream __attribute__((unused)) ;
{
	__fortify_fail( "feof()" ) ;
}
int feof(FILE*stream)
__attribute__((weak,alias("feof_unlocked")));
