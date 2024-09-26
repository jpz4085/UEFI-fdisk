#!/bin/bash

# This file is part of UEFI fdisk.
#
# UEFI fdisk is a port of util-linux fdisk to UEFI/BIOS.
# UEFI fdisk est un portage de util-linux fdisk vers UEFI/BIOS.
# Ce fichier a été initié par Bernard Burette en janvier 2014.
#
# All this work is copyleft Bernard Burette.
# Gauche d'auteur Bernard Burette.
#
# This program is distributed under the terms of the GNU General Public
#  License version 2 or more.
# La diffusion de ce code est faite selon les termes de la licence publique
#  générale GNU version 2 ou plus.

#
# Error messages and warnings are colored red by default which is not visible
# under the UEFI environment so we patch do_vprint to always use plain text.
#

if ! grep 'type = FDISK_ASKTYPE_INFO;' ../libfdisk/src/ask.c > /dev/null 2>&1 ; then
	echo "Patch do_vprint in ask.c so warnings are visible." 1>&2
	sed -i $'/fdisk_ask_set_type(ask, type);/i#ifdef EFI\\n\\ttype = FDISK_ASKTYPE_INFO;\\n#endif\\n' ../libfdisk/src/ask.c
else
	echo "File ../libfdisk/src/ask.c is already patched." 1>&2
fi
