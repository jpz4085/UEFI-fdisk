#!/bin/bash

# This file is part of UEFI fdisk.
#
# UEFI fdisk is a port of util-linux fdisk to UEFI/BIOS.
# UEFI fdisk est un portage de util-linux fdisk vers UEFI/BIOS.
# Ce fichier a été initié par Bernard Burette en janvier 2014.
#
# Original work is copyleft Bernard Burette.
# Modifications are copyleft Joseph Zeller.
#
# This program is distributed under the terms of the GNU General Public
#  License version 2 or more.
# La diffusion de ce code est faite selon les termes de la licence publique
#  générale GNU version 2 ou plus.

#
# Error messages and warnings are output to stderr by default which is not
# visible under the VirtualBox UEFI environment so we send these to stdout
# instead. This is not necessary when running fdisk on physical hardware.
#

if grep 'stderr' ../disk-utils/fdisk.c > /dev/null 2>&1 ; then
	echo "Patch ask_callback in fdisk.c so warnings are visible." 1>&2
	sed -i 's/stderr/stdout/' ../disk-utils/fdisk.c
else
	echo "File ../disk-utils/fdisk.c is already patched." 1>&2
fi
if grep 'fprintf(stderr, _("Try' ../include/c.h > /dev/null 2>&1 ; then
	echo "Patch errtryhelp in c.h so errors are visible." 1>&2
	sed -i 's/fprintf(stderr, _("Try/fprintf(stdout, _("Try/' ../include/c.h
else
	echo "File ../include/c.h is already patched." 1>&2
fi
