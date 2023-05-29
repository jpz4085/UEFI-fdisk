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
 *
 * Gestion des couleurs.
 *
 * Ce module ne fait rien, il sert juste à réussir le link.
 *
 */

#include "libmy.h"
#include <stdio.h>
#include <unistd.h>

int colormode_or_err(const char *str __attribute__((unused)) , const char *errmsg __attribute__((unused)) ) { return 0 ; }

int colors_init(int mode __attribute__((unused)) , const char *util_name __attribute__((unused)) ) { return 0 ; }

int colors_wanted(void) { return 0 ; }

void color_scheme_fenable(const char *name __attribute__((unused)) , const char *dflt __attribute__((unused)) , FILE *f __attribute__((unused)) ) {}

const char *color_scheme_get_sequence(const char *name __attribute__((unused)) , const char *dflt __attribute__((unused)) ) { return NULL ; }

void color_fdisable(FILE *f __attribute__((unused)) ) {}

void *bsearch(const void *key __attribute__((unused)), const void *base __attribute__((unused)), size_t nmemb __attribute__((unused)), size_t size __attribute__((unused)), int (*compar)(const void *, const void *) __attribute__((unused))) { return NULL ; }

