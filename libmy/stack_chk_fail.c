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
#define _GNU_SOURCE
#include "libmy.h"
#include <stdlib.h>
void __attribute__((noreturn)) __stack_chk_fail( void ) ;
__attribute__((noreturn))
void __stack_chk_fail()
{
	__fortify_fail( "stack smashing detected" ) ;
}
link_warning("__stack_chk_fail","your code has stack checking enabled!")
