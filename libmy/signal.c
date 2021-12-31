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
/** @file
 * Gestion des signaux.
 * Ce module ne fait rien, il sert juste à réussir le link.
 */
/* en premier */
#include "libmy.h"
#include <signal.h>
int sigaction( signum , act , oldact )
	int signum __attribute__((unused)) ;
	const struct sigaction *act __attribute__((unused)) ;
	struct sigaction *oldact __attribute__((unused)) ;
{
	return 0 ;
}
int sigemptyset( set )
	sigset_t *set __attribute__((unused)) ;
{
	return 0 ;
}
