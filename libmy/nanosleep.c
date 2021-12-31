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
#include <time.h>
#include <string.h>
#include <unistd.h>
/**
 * Dort un peu (ici ce sera le nombre de secondes + 1).
 */
int nanosleep( req , rem )
	const struct timespec *req ;
	struct timespec *rem ;
{
	memset( rem , 0 , sizeof( rem ) ) ;
	sleep( req-> tv_sec + 1 ) ;
	return 0 ;
}
