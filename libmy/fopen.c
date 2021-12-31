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
/*
 * Entrée sortie FILE de stdio.
 */
#include "libmy.h"
#include <stdio.h>
#include <errno.h>
/**
 * fopen : ouverture d'un flux.
 */
#undef fopen
FILE *
fopen( name , mode )
	const char * name __attribute__((unused)) ;
	const char * mode __attribute__((unused)) ;
{
	/* TODO: ? */
	errno = EPERM ;
	return NULL ;
}
//__typeof( fopen ) fopen64 __attribute__(( weak , alias( "fopen" ) )) ;
