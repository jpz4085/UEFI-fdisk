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
/*
 * Entrée sortie FILE de stdio.
 * Définition de stdin, stdout, stderr.
 * Les trois sont définis dans un seul fichier comme glibc
 * Ce fichier définit également _IO_stdin pour stdin, etc...
 */
/* en premier */
#include "libmy.h"
#include <stdio.h>
/**
 * Le flux stdin.
 */
#ifdef stdin
#undef stdin
#endif
#ifdef _IO_stdin
#undef _IO_stdin
#endif
static struct _IO_FILE
my_stdin = { ._fileno = 0 } ;
struct _IO_FILE *
stdin = & my_stdin ;
extern struct _IO_FILE *
_IO_stdin __attribute__(( alias("stdin") )) ;
/**
 * Le flux stdout.
 */
#ifdef stdout
#undef stdout
#endif
#ifdef _IO_stdout
#undef _IO_stdout
#endif
static struct _IO_FILE
my_stdout = { ._fileno = 1 } ;
struct _IO_FILE *
stdout = & my_stdout ;
extern struct _IO_FILE *
_IO_stdout __attribute__(( alias("stdout") )) ;
/**
 * Le flux stderr.
 */
#ifdef stderr
#undef stderr
#endif
#ifdef _IO_stderr
#undef _IO_stderr
#endif
static struct _IO_FILE
my_stderr = { ._fileno = 2 } ;
struct _IO_FILE *
stderr = & my_stderr ;
extern struct _IO_FILE *
_IO_stderr __attribute__(( alias("stderr") )) ;
