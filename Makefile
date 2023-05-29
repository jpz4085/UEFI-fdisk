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
## Makefile to build an UEFI version of fdisk.
##
## Not tried any 32 bits compilation.
## Not tried support of wchar_t here, all the code we use is only UTF-8.
##
## We build a reduced version of the libc that we use for final link.
## This "libmy.a" is built from bits taken from "dietlibc" but also bits of
## "glic" (mostly the "locale" bits because "dietlibc" doesn't have them and
## GNU stdlibc++ seems fond of gnulibc implementation).
## What a mess!
##


# Debug this code. This should make the code be verbose or not depending
# on the value of the UEFI firmware variable EFIDebug.
# Note: you still need -O for _FORTIFY_SOURCE to work
#EFI_DEBUG_FLAGS = -DEFI_DEBUG -fstack-protector -O -D_FORTIFY_SOURCE=2

# Architecture for target EFI.
# Note: 32 bits code does not build.
#ARCH = ia32
ARCH = x86_64


## End of the changeable section of this Makefile.


# Name of the directory where GNU EFI is built.
GNUEFI = $(wildcard gnu-efi-*)

# Compiler switch for 32 or 64 bits.
ifeq ($(ARCH),ia32)
  # Build 32 bits binaries.
  CFLAGS += -m32
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
# wchar_t for UEFI is 16 bits (we don't use UFT-16 here but standard libraries
# were built without this flag, so using this switch could be a problem).
CFLAGS += -fshort-wchar
# Code should be well debugged so don't need these.
CFLAGS += -fno-stack-protector -fno-stack-check -fomit-frame-pointer
# Code should be well debugged so don't need asserts.
CFLAGS += -DNDEBUG
# Code should be well debugged so don't need fortified source.
CFLAGS += -U_FORTIFY_SOURCE
# ?
CFLAGS += -fno-unwind-tables -fno-asynchronous-unwind-tables
# Alloue tout l'espace de pile d'une fonction (plus rapide).
CFLAGS += -maccumulate-outgoing-args
# Be thorough.
CFLAGS += -Wall -Wextra
# Debug UEFI code flag.
CFLAGS += -g $(EFI_DEBUG_FLAGS)

# Same flags for assembler files.
ASFLAGS += $(CFLAGS)

# Our UEFI glue will need additional includes from GNU EFI.
CFLAGS += -I$(GNUEFI)/inc/$(ARCH) -I$(GNUEFI)/inc

# We want to build a standalone executable (no dynamic link available with
# UEFI) but just using "-static" removes all relocation information in the
# resulting file but we need them when loading the UEFI image.
# Note that we use the -Bxx format because these options are also used with
# "g++" who wouldn't send them to "ld" otherwise and we also use additional
# link options for the Linux binary "fdisk".
LDFLAGS += -Bshareable -Bsymbolic -Bstatic
# Very important otherwise the relocation section will be emptied by ld.
LDFLAGS += -znocombreloc
# We don't use the .data.rel.ro magic here (make a segment read-only after
# relocation entries have been applied to it).
LDFLAGS += -zrelro

# Object files to be built for our glue with UEFI.
GLUE_OBJS = start-$(ARCH).o relocate-$(ARCH).o initfini.o \
	efi_main.o io.o alloc.o time.o debug.o thread.o

# Module names for fdisk (copied from util-linux Makefile).
MODULES += ../disk-utils/fdisk-fdisk \
	../disk-utils/fdisk-fdisk-menu ../disk-utils/fdisk-fdisk-list

# Object files names derived from module names.
OBJS = $(MODULES:=.o)

# Extra object files replacing libraries.
OBJS += uuid.o


# Build only the UEFI version by default.
# Need to "make fdisk" to build the Linux one.
#
all: fdisk.efi


# Cleanup.
#
clean: #no prerequisites
	-$(MAKE) -C $(GNUEFI) clean
	-rm -f core *.o *~ fdisk.efi fdisk.so.s fdisk.so fdisk fdisk.map test


# Big big Cleanup.
#
distclean: clean
	-$(MAKE) -C .. distclean
	-$(MAKE) -C libmy clean


# Build object files from util-linux fdisk.
#
../disk-utils/fdisk-fdisk.o: ../Makefile
	$(MAKE) -C .. -j fdisk


# Use the configure script of util-linux to create its Makefile.
#
../Makefile: #no prerequisites
	# ajoute -D__SANITIZE_ADDRESS__ pour include/closestream.h
	cd .. ; ./configure CFLAGS="-D__SANITIZE_ADDRESS__ $(CFLAGS)" \
		--without-slang --without-ncursesw --with-ncurses \
		--disable-widechar --without-tinfo --without-readline \
		--without-python --disable-nls \
		--disable-fs-paths-default --disable-fs-paths-extra \
		--disable-colors-default --disable-libblkid \
		--enable-libuuid --enable-libuuid-force-uuidd \
		--enable-libfdisk --enable-fdisks \
		--enable-static --enable-static-programs=fdisk \
		--disable-shared \
		--disable-silent-rules --enable-libtool-lock
	#enlève certains trucs du config.h
	echo "#undef HAVE_LOCALE_H" >>../config.h
	echo "#undef HAVE_OPEN_MEMSTREAM" >>../config.h
	echo "#undef HAVE_POSIX_FADVISE" >>../config.h
	#désactive le debug
	echo "#undef __UL_INIT_DEBUG_FROM_STRING" >>../include/debug.h
	echo "#define __UL_INIT_DEBUG_FROM_STRING(l,p,m,e)" >>../include/debug.h
	echo "#undef __UL_INIT_DEBUG_FROM_ENV" >>../include/debug.h
	echo "#define __UL_INIT_DEBUG_FROM_ENV(l,p,m,e)" >>../include/debug.h
	echo "#undef __UL_DBG" >>../include/debug.h
	echo "#define __UL_DBG(l,p,m,x) do{}while(0)" >>../include/debug.h
	echo "#undef __UL_DBG_CALL" >>../include/debug.h
	echo "#define __UL_DBG_CALL(l,p,m,x) do{}while(0)" >>../include/debug.h


# For some reason all files from util-fdisk libcommon also end up in
# every other library, let's rince that off.
#
rinse: ../Makefile
	$(MAKE) -C .. -j fdisk
	cd ../.libs;ar d libuuid.a $$(ar t libuuid.a|grep ^libcommon)
	cd ../.libs;ar d libfdisk.a $$(ar t libfdisk.a|grep ^libcommon)
	cd ../.libs;ar d libtcolors.a $$(ar t libtcolors.a|grep ^libcommon)
	cd ../.libs;ar d libsmartcols.a $$(ar t libsmartcols.a|grep ^libcommon)


# Make a map of the link for debugging, delete fdisk.so if it exists then
# rebuild it with "-M" flag.
#
map: #no prerequisites
	-rm -f fdisk.so
	$(MAKE) MAPOPT="--cref -Map=fdisk.map" fdisk.so
	-rm -f fdisk.so


# Build the GNU UEFI library.
#
libefi.a: #no prerequisites
	$(MAKE) -C $(GNUEFI) ARCH="$(ARCH)" \
		EFI_DEBUG_FLAGS="$(EFI_DEBUG_FLAGS)" lib


# Build our extras replacing libc for the target architecture.
#
libmy.a: #no prerequisites
	$(MAKE) -C libmy -j ARCH="$(ARCH)" libmy.a


# Build fdisk.so as static ELF image by combining all bits.
# We carefully avoid linking against libc.a which has Linux system calls.
# We use a custom link script because the script from GNU EFI misses bits to
# successfully link a C++ program.
# Since version 3.0.2 of GNU EFI, libraries directories have moved so let's
# use both locations here.
#
fdisk.so: libefi.a libmy.a $(OBJS) $(GLUE_OBJS) rinse
	$(LD) -nostdlib --no-undefined -Telf-$(ARCH).lds \
		$(OBJS) $(GLUE_OBJS) $(LDFLAGS) \
		-L../.libs -lfdisk -luuid -lsmartcols \
		-L$(GNUEFI)/$(ARCH)/lib -L$(GNUEFI)/lib -lefi \
		-Llibmy -lmy -lcommon -lmy \
		--entry=_start $(MAPOPT) -o $@


# Build .EFI from .SO by first removing symbols (otherwise .EFI will say he
# has symbols in its PE header when he doesn't), then copy the required
# sections from image file.
#
%.so.s: %.so
	strip -s -o $@ $<
#
%.efi: %.so.s
	objcopy -j .reloc -j .dynamic -j .rela -j .dynsym -j .text \
		-j .rdata -j .data -j .bss \
		--set-section-flags .dynamic=alloc,load,readonly,data \
		--target=efi-app-$(ARCH) $< $@


# For testing purposes, build this program for the Linux platform with our
# libmy.a but then link with standard libc library for system calls like
# write()/read()... for Linux and not from our glue modules.
# This program is good for debugging with the symbols et al.
#
fdisk: libmy.a $(OBJS) rinse
	$(CC) -g $(OBJS) $(LDFLAGS) -Wl,-u,__ctype_init \
		-L../.libs -lfdisk -luuid -lsmartcols \
		-Llibmy -lmy -lcommon -lmy \
		-flto -static $(MAPOPT) -o $@


# Fichiers qui peuvent être supprimés
#
.INTERMEDIATE: fdisk.so


# Phoney targets (build them every time).
#
.PHONY: all clean libefi.a libmy.a map

