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


#include "uefi.h"
#include "debug.h"
#include <unistd.h>


/*
 * Copyright (C) 2012 Ondrej Oprala <ooprala@redhat.com>
 * Copyright (C) 2012-2014 Karel Zak <kzak@redhat.com>
 *
 * This file may be distributed under the terms of the
 * GNU Lesser General Public License.
 */


/* --color[=WHEN] */
enum colortmode {
	UL_COLORMODE_AUTO = 0,
	UL_COLORMODE_NEVER,
	UL_COLORMODE_ALWAYS,
	UL_COLORMODE_UNDEF,

	__UL_NCOLORMODES	/* last */
};

#ifdef USE_COLORS_BY_DEFAULT
# define USAGE_COLORS_DEFAULT	_("colors are enabled by default")
#else
# define USAGE_COLORS_DEFAULT   _("colors are disabled by default")
#endif

/* Maintains human readable color names */
const char *color_sequence_from_colorname(const char *str ) ;
const char *color_sequence_from_colorname(const char *str __attribute__((unused)) )
{ return NULL ; }

int colormode_from_string(const char *str ) ;
int colormode_from_string(const char *str __attribute__((unused)) )
{ return 0 ; }

int colormode_or_err(const char *str , const char *errmsg ) ;
int colormode_or_err(const char *str __attribute__((unused)) , const char *errmsg __attribute__((unused)) )
{ return 0 ; }

/* Initialize the global variable UL_COLOR_TERM_OK */
int colors_init(int mode , const char *util_name ) ;
int colors_init(int mode __attribute__((unused)) , const char *util_name __attribute__((unused)) )
{
	return 0 ;
}

/* Returns 1 or 0 */
int colors_wanted(void) ;
int colors_wanted(void) { return 0 ; }

/* Returns UL_COLORMODE_* */
int colors_mode(void) ;
int colors_mode(void) { return 0 ; }

/* temporary enable/disable colors */
void colors_off(void) ;
void colors_off(void) {}
void colors_on(void) ;
void colors_on(void) {}


/* Set the color */
void color_fenable(const char *seq , FILE *f ) ;
void color_fenable(const char *seq __attribute__((unused)) , FILE *f __attribute__((unused)) ) {}

void color_scheme_fenable(const char *name , const char *dflt , FILE *f ) ;
void color_scheme_fenable(const char *name __attribute__((unused)) , const char *dflt __attribute__((unused)) , FILE *f __attribute__((unused)) ) {}

const char *color_scheme_get_sequence(const char *name , const char *dflt ) ;
const char *color_scheme_get_sequence(const char *name __attribute__((unused)) , const char *dflt __attribute__((unused)) ) { return NULL ; }

/* Reset colors to default */
void color_fdisable(FILE *f ) ;
void color_fdisable(FILE *f __attribute__((unused)) )
{
}

