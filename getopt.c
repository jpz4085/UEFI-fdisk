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

/* @file
 *
 * Gestion des options de la ligne de commande.
 *
 * Ce module ne fait rien, il sert juste à réussir le link.
 *
 */


#include "uefi.h"
#include "debug.h"
#include <getopt.h>

int optind = 1 ;
char * optarg = NULL ;

int getopt_long( argc , argv , optstring , longopts , longindex )
	int argc __attribute__((unused)) ;
	char *const argv[] __attribute__((unused)) ;
	const char *optstring __attribute__((unused)) ;
	const struct option *longopts __attribute__((unused)) ;
	int *longindex __attribute__((unused)) ;
{
	return -1 ;
}

