##
## This file is part of UEFI fdisk.
##
## UEFI fdisk is a port of util-linux fdisk to UEFI/BIOS.
## UEFI fdisk est un portage de util-linux fdisk vers UEFI/BIOS.
## Ce fichier a été initié par Bernard Burette en janvier 2014.
##
## All this work is copyleft Bernard Burette.
## Gauche d'auteur Bernard Burette.
##
## This program is distributed under the terms of the GNU General Public
##  License version 2 or more.
## La diffusion de ce code est faite selon les termes de la licence publique
##  générale GNU version 2 ou plus.
##

##
## Makefile to build a reduced replacement for the libc.
## This lib is built from bits taken from "dietlibc" but also
## bits of "glic" (mostly the locale bits because "dietlibc"
## doesn't have those bits). Not tried to support wchar_t here,
## all the code we use is only UTF-8.
##
## What a mess!
##


# Host/target identification
ARCH ?= $(shell uname -m|sed s,i[3-9]86,ia32,)
# FreeBSD (and possibly others) reports amd64 instead of x86_64
ifeq ($(ARCH),amd64)
  override ARCH = x86_64
endif

# Compiler switch for 32 or 64 bits.
ifeq ($(ARCH),ia32)
  # Build 32 bits binaries (not tested).
  CFLAGS += -m32 -mtune=i386
endif
ifeq ($(ARCH),x86_64)
  # Build 64 bits binaries.
  CFLAGS += -m64 -mno-red-zone
endif

# Access 64 bits for seek() et al.
CFLAGS += -D_FILE_OFFSET_BITS=64
# UEFI firmware doesn't initialize CPU for MMX et al (returning float or double
# using Linux x86_64 ABI is not possible: better break during compilation than
# crash during run).
#CFLAGS += -mno-mmx -mno-sse
# Optimize for size. We also need to use -fno-inline otherwise <stdlib.h> will
# try to define atof() as "inline" returning a "float" which is not available
# in UEFI using x86_64 ABI and is forbidden by -mno-mmx option.
CFLAGS += -Os -fno-inline
# Compile Position Independent Code and for foreign platform.
CFLAGS += -fPIC -DPIC -ffreestanding
# wchar_t for UEFI is 16 bits (we don't use UFT-16 here and standard libraries
# were built without this flag, so using this switch could be a problem).
CFLAGS += -fshort-wchar
# Code should be well debugged so don't need these.
CFLAGS += -fno-stack-protector -fno-stack-check -fomit-frame-pointer
# ?
CFLAGS += -fno-asynchronous-unwind-tables -fno-unwind-tables
# Alloue tout l'espace de pile d'une fonction (plus rapide).
CFLAGS += -maccumulate-outgoing-args
# Be thorough.
CFLAGS += -Wall -Wextra -Werror
# Pas besoin de _FORTIFY_SOURCE
CFLAGS += -U_FORTIFY_SOURCE
# Symboles
CFLAGS += -g

# List of object files required to link a nice fdisk.so.
OBJS += syscall.o sleep.o nanosleep.o errno.o pipe.o
OBJS += string.o explicit_bzero.o tolower.o toupper.o
OBJS += memory.o stdio.o setvbuf.o makedev.o colors.o
OBJS += fstat.o fstream.o fileman.o
OBJS += print.o putchar.o puts.o
OBJS += scan.o warnx.o errx.o clearerr.o
OBJS += C-ctype-data.o C-ctype.o ctype-info.o
OBJS += qsort.o isatty.o rpmatch.o signal.o identity.o
OBJS += stack_chk_fail.o assert_fail.o environ.o proc.o
OBJS += getopt.o gettimeofday.o random.o directory.o
OBJS += xpg_basename.o

# Build the library by default.
#
all: libmy.a


# Cleanup.
#
clean: #no prerequisites
	-rm -f core *.o *~ libmy.a


# Phony targets (build them every time).
#
.PHONY: all clean


# The library is made of all object files.
#
libmy.a: $(OBJS)
	ar -rs $@ $?
	-ranlib $@

