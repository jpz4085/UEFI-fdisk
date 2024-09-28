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
 
/*
 * This file contains all file stream functions needed for compilation/linking.
 */
 
#define _XOPEN_SOURCE 600
#define _GNU_SOURCE
#include "libmy.h"
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <errno.h>
#include "dietstdio.h"

#ifdef getc
# undef getc
#endif
#define GETC_UNGETC 0x100
#if GETC_UNGETC == _IO_EOF_SEEN
# error GETC_UNGETC == _IO_EOF_SEEN
#endif
#ifdef fwrite_unlocked
# undef fwrite_unlocked
#endif
#ifdef putc
# undef putc
#endif
#undef fopen

int feof_unlocked(stream)
	FILE*stream __attribute__((unused)) ;
{
	__fortify_fail( "feof()" ) ;
}
int feof(FILE*stream)
__attribute__((weak,alias("feof_unlocked")));

int
fcntl64( int fd __attribute__((unused)),
 	int cmd __attribute__((unused)),
 	... )
{
 	__fortify_fail( "fcntl64()" ) ;
}

int ungetc( c , stream )
	int c ;
	FILE * stream ;
{
	/* jamais de buffering ici */
	/* inutile setvbuf( stream , NULL , _IONBF , 0 ) ; */
	/* on ne relit pas EOF */
	if ( c == EOF ) return EOF ;
	/* si déjà un UNGET */
	if ( stream-> _flags2 & GETC_UNGETC ) {
		return EOF ;
	}
	/* note la valeur du caractère à relire */
	stream-> _shortbuf[ 0 ] = (char) c ;
	/* passe EOF dans flags2 et note la présence du caractère à relire */
	stream-> _flags2 |= ( GETC_UNGETC |
		( stream-> _flags & _IO_EOF_SEEN ) ) ;
	/* enlève erreur et fin de fichier du flux */
	stream-> _flags &= ~ ( _IO_ERR_SEEN | _IO_EOF_SEEN ) ;
	/* retourne le caractère remis dans le flux */
	return c ;
}

int fgetc( stream )
	FILE * stream __attribute__((unused)) ;
{
	char c ;
	/* jamais de buffering ici */
	setvbuf( stream , NULL , _IONBF , 0 ) ;
	/* s'il y a un caractère à relire en attente */
	if ( stream-> _flags2 & GETC_UNGETC ) {	
		/* récupère le caractère */
		c = stream -> _shortbuf[ 0 ] ;
		/* repasse l'indicateur EOF dans _flags */
		stream-> _flags |= stream-> _flags2 & _IO_EOF_SEEN ;
		/* remet flags2 en état normal */
		stream-> _flags2 &= ~ ( GETC_UNGETC | _IO_EOF_SEEN ) ;
	} else {
		int n ;
		n = read( stream-> _fileno , & c , 1 ) ;
		if ( n < 0 ) {
			/* note l'erreur */
			stream-> _flags |= _IO_ERR_SEEN ;
			return EOF ;
		}
		if ( n != 1 ) {
			/* note la fin de fichier */
			stream-> _flags |= _IO_EOF_SEEN ;
			return EOF ;
		}
	}
	return (unsigned char) c ;
}
__typeof( fgetc ) getc __attribute__((weak,alias("fgetc"))) ;

char *fgets_unlocked(char *s, int size, FILE *stream) {
	/* comme on ajoute toujours un \0 on lit un caractère de moins */
	size --;
	int l;
	for (l=0; l<size; ) {
		register int c;
			c=fgetc(stream);
			if (c==EOF) {
	if (!l) return NULL ;
	goto fini;
			}
		s[l]=c;
		++l;
		if (c=='\n'||l==size) {
fini:
			s[l]=0;
			return s;
		}
	}
	return NULL ;
}
char*fgets(char*s,int size,FILE*stream) __attribute__((weak,alias("fgets_unlocked")));

int
flock ( fd, operation)
 	int fd __attribute__(( unused )) ;
 	int operation __attribute__(( unused )) ;
{
 	return 0 ;
}

FILE *
fopen( name , mode )
	const char * name __attribute__((unused)) ;
	const char * mode __attribute__((unused)) ;
{
	/* TODO: ? */
	errno = EPERM ;
	return NULL ;
}

int fputc( c , stream )
	int c ;
	FILE * stream ;
{
	unsigned char bc ;
	bc = (unsigned char) c ;
	/* jamais de buffering ici */
	setvbuf( stream , NULL , _IONBF , 0 ) ;
	if ( write( stream-> _fileno , & bc , 1 ) != 1 ) {
		stream-> _flags |= _IO_ERR_SEEN ;
		return EOF ;
	}
	return bc ;
}
__typeof( fputc ) putc __attribute__((weak,alias("fputc"))) ;

int fputs_unlocked(const char*s,FILE*stream) {
	return fwrite(s,strlen(s),1,stream);
}
int fputs(const char*s,FILE*stream) __attribute__((weak,alias("fputs_unlocked")));

size_t fread_unlocked( ptr , size , count , stream )
	void * ptr ;
	size_t size ;
	size_t count ;
	FILE * stream ;
{
	char * p ; /* l'adresse où stocker ce qui est lu */
	size_t n ; /* le nombre d'items lus */
	char premier = 1 ; /* la première lecture */
	/* jamais de buffering ici */
	setvbuf( stream , NULL , _IONBF , 0 ) ;
	p = (char *) ptr ;
	n = 0 ;
	while ( count ) {
		ssize_t s ; /* la taille de cet item */
		s = size ;
		while ( s ) {
			ssize_t r ;
			if ( premier ) {
				/* gestion du ungetc() */
				char c = fgetc( stream ) ;
				/* fin de fichier ou erreur */
				if ( c == EOF ) goto ret ;
				/* stocke l'octet et avance */
				* p = c ;
				p ++ ;
				s -- ;
				premier = 0 ;
			}
			/* lit un item */
			r = read( stream-> _fileno , p , s ) ;
			if ( r < 0 ) {
				/* note l'erreur */
				stream-> _flags |= _IO_ERR_SEEN ;
				goto ret ;
			}
			if ( r < s ) {
				/* note la fin de fichier */
				stream-> _flags |= _IO_EOF_SEEN ;
				goto ret ;
			}
			p += r ;
			s -= r ;
		}
		count -- ;
		n ++ ;
	}
	ret : ;
	return n ;
}
__typeof( fread_unlocked ) fread __attribute__((weak,alias("fread_unlocked"))) ;

int fclose(FILE *stream) {
	int res;
	res = close( stream-> _fileno ) ;
	
	if ( res < 0 ) res = EOF ;
	
	if ( stream != stdin && stream != stdout && stream != stderr ) {
		free(stream);
	}
	return res;
}

FILE *
fdopen( fd , mode )
	int fd __attribute__((unused)) ;
	const char * mode __attribute__((unused)) ;
{
	__fortify_fail( "fdopen()" ) ;
}

int ferror( FILE * f )
{
	return f-> _flags & _IO_ERR_SEEN ;
}

int fflush_unlocked( stream )
	FILE * stream ;
{
	/* no buffers */
	setvbuf( stream , NULL , _IONBF , 0 ) ;
	/* we dit it ! */
	return 0 ;
}
int fflush(FILE *stream) __attribute__((weak,alias("fflush_unlocked")));

int fileno( stream )
	FILE * stream ;
{
	return stream-> _fileno ;
}

size_t fwrite_unlocked( ptr , size , count , stream )
	const void * ptr ;
	size_t size ;
	size_t count ;
	FILE * stream ;
{
	const char * p ;
	size_t n ;
	/* jamais de buffering ici */
	setvbuf( stream , NULL , _IONBF , 0 ) ;
	p = (const char *) ptr ;
	n = 0 ;
	while ( count ) {
	        if ( write( stream-> _fileno , p , size ) != (ssize_t) size ) {
			stream-> _flags |= _IO_ERR_SEEN ;
			break ;
	        }
	        p += size ;
	        count -- ;
	        n ++ ;
	}
	return n ;
}
__typeof( fwrite_unlocked ) fwrite __attribute__((weak,alias("fwrite_unlocked"))) ;

size_t
__fpending ( fp )
	FILE * fp __attribute__((unused)) ;
{
	__fortify_fail( "__fpending()" ) ;
}

ssize_t writev( fd , iov , iovcnt )
	int fd ;
	const struct iovec * iov ;
	int iovcnt ;
{
	int count ;
	ssize_t total = 0 ;
	for ( count = 0 ; count < iovcnt ; count ++ ) {
		const struct iovec v = iov[ count ] ;
		ssize_t l = write( fd , v.iov_base , v.iov_len ) ;
		if ( l < 0 ) return l ;
		total += l ;
		if ( (size_t) l != v.iov_len ) {
			break ;
		}
	}
	return total ;
}

