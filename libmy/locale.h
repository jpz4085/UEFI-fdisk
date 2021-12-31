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
#ifndef	MY_LOCALE_H
#include <locale.h>
/*#include <xlocale.h>*/
extern locale_t uselocale (locale_t newloc) ;
#ifndef _ISOMAC
extern __typeof (uselocale) __uselocale;
libc_hidden_proto (setlocale)
libc_hidden_proto (__uselocale)
/* This has to be changed whenever a new locale is defined.  */
#define __LC_LAST	13
extern struct loaded_l10nfile *_nl_locale_file_list[] attribute_hidden;
/* Locale object for C locale.  */
extern const struct __locale_struct _nl_C_locobj attribute_hidden;
#define _nl_C_locobj_ptr ((struct __locale_struct *) &_nl_C_locobj)
/* Now define the internal interfaces.  */
extern struct lconv *__localeconv (void);
/* Fetch the name of the current locale set in the given category.  */
extern const char *__current_locale_name (int category) attribute_hidden;
#endif
#endif /* MY_LOCALE_H */
