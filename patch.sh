#!/bin/bash
##
## This file is part of UEFI fdisk.
##
## UEFI fdisk is a port of util-linux fdisk to UEFI/BIOS.
## UEFI fdisk est un portage de util-linux fdisk vers UEFI/BIOS.
## This file was created by Joseph Zeller in January 2023.
##
## All this work is copyleft Bernard Burette and Joseph Zeller.
## Gauche d'auteur Bernard Burette et Joseph Zeller.
##
## This program is distributed under the terms of the
## GNU General Public License version 2 or more.
## La diffusion de ce code est faite selon les termes de la
## licence publique générale GNU version 2 ou plus.

## Patching script to disable preprocessor directives for Linux
## zoned block device support found in util-linux version 2.38 and
## higher which are incompatible with the UEFI ioctl function.

version=$( grep PACKAGE_VERSION= ../configure | tr -d [:alpha:] | cut -c4- | rev | cut -c2- | rev )
if [ "$(printf '%s\n' "2.38" "$version" | sort -V | head -n1)" = "2.38" ]; then
	if grep HAVE_LINUX_BLKZONED_H ../include/blkdev.h >/dev/null 2>&1 ; then
		echo "Disable HAVE_LINUX_BLKZONED_H directives in ../include/blkdev.h"
		sed -i '/#ifdef HAVE_LINUX_BLKZONED_H/,/#endif/ s/#else//' ../include/blkdev.h
		sed -i 's/#ifdef HAVE_LINUX_BLKZONED_H/#if 0/' ../include/blkdev.h
	else
		echo "File ../include/blkdev.h is already patched."
	fi
	if grep HAVE_LINUX_BLKZONED_H ../lib/blkdev.c >/dev/null 2>&1 ; then
		echo "Disable HAVE_LINUX_BLKZONED_H directives in ./lib/blkdev.c"
		sed -i 's/#ifdef HAVE_LINUX_BLKZONED_H/#if 0/' ../lib/blkdev.c
	else
		echo "File ../lib/blkdev.c is already patched."
	fi
	if grep -E "HAVE_LINUX_BLKZONED_H|def BLKGETZONESZ" ../libblkid/src/probe.c >/dev/null 2>&1 ; then
		echo "Disable HAVE_LINUX_BLKZONED_H and BLKGETZONESZ directives in ../libblkid/src/probe.c"
		sed -Ei 's/#ifdef HAVE_LINUX_BLKZONED_H|# ifdef BLKGETZONESZ/#if 0/' ../libblkid/src/probe.c
	else
		echo "File ../libblkid/src/probe.c is already patched."
	fi
	if grep HAVE_LINUX_BLKZONED_H ../libblkid/src/superblocks/btrfs.c >/dev/null 2>&1 ; then
		echo "Disable HAVE_LINUX_BLKZONED_H directives in btrfs.c"
		sed -i 's/#ifdef HAVE_LINUX_BLKZONED_H/#if 0/' ../libblkid/src/superblocks/btrfs.c
	else
		echo "File ../libblkid/src/superblocks/btrfs.c is already patched."
	fi
else
	echo "Version" ${version} "of util-linux doesn't need patching."
fi
