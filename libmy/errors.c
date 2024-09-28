/*
 *
 * This file is part of UEFI fdisk.
 *
 * UEFI fdisk is a port of util-linux fdisk to UEFI/BIOS.
 * UEFI fdisk est un portage de util-linux fdisk vers UEFI/BIOS.
 * Ce fichier a été initié par Bernard Burette en janvier 2014.
 *
 * Original work is copyleft Bernard Burette.
 * Modifications are copyleft Joseph Zeller.
 *
 * This program is distributed under the terms of the GNU General Public
 *  License version 2 or more.
 * La diffusion de ce code est faite selon les termes de la licence publique
 *  générale GNU version 2 ou plus.
 *
 */
#include "libmy.h"
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "dietstdio.h"

extern char *program_invocation_short_name;

void errx (int eval, const char *fmt, ...)
{
	va_list ap;
	va_start (ap, fmt);
	printf("%s: ", program_invocation_short_name);
	if (fmt != NULL)
		__vfprintf_chk(stdout , 0 , fmt, ap);
	printf("\n");
	va_end (ap);
	exit (eval);
}

void err (int status, const char *format, ...)
{
	va_list ap;
	va_start (ap, format);
	printf("%s: ", program_invocation_short_name);
	if (format != NULL)
		__vfprintf_chk(stdout , 0 , format, ap);
	printf(": %m\n");
	va_end (ap);
	exit (status);
}

void warnx (const char* format, ...)
{
	va_list ap;
	va_start (ap, format);
	printf("%s: ", program_invocation_short_name);
	if (format != NULL)
		__vfprintf_chk(stdout , 0 , format, ap);
	printf("\n");
	va_end (ap);
}

void warn (const char *format, ...)
{
	va_list ap;
	va_start (ap, format);
	printf("%s: ", program_invocation_short_name);
	if (format != NULL)
		__vfprintf_chk(stdout , 0 , format, ap);
	printf(": %m\n");
	va_end (ap);
}
