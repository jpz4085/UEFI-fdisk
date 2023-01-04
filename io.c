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
 * Entrée sortie console, disque ou fichier.
 *
 */


#include "uefi.h"
#include "debug.h"
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <linux/hdreg.h>
#include <linux/fd.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <poll.h>


/**
 * Les différents descripteurs manipulables.
 */
enum type_fd
{
	fd_libre = 0 , /* descripteur inutilisé */
	fd_console , /* console ConIn, ConOut ou StdErr */
	fd_disque , /* disque ou partition de disque */
	fd_dossier , /* dossier de fichiers */
	fd_fichier , /* fichier */
} ;


/**
 * La structure employée derrière un descripteur de fichier
 */
struct fd
{
	EFI_HANDLE handle ; /* handle UEFI du disque ou du fichier */
	unsigned long long position ; /* position en octets dans un disque */
	int mode ; /* mode d'ouverture */
	enum type_fd type ; /* type de ce descripteur */
} ;


/**
 * La première table des fichiers ouverts (car stdin, stdout et stderr sont
 * déjà ouverts).
 */
static struct fd table_init[ 8 ] = {
	{ .type = fd_console , } ,
	{ .type = fd_console , } ,
	{ .type = fd_console , .handle = (EFI_HANDLE) 1 , } ,
} ;


/**
 * La taille de la table en nombre d'index.
 */
static int table_max = sizeof( table_init ) / sizeof( struct fd ) ;


/**
 * La table des fichiers ouverts.
 * Cette table est accédée via l'index par fd.
 */
static struct fd * table = table_init ;


/**
 * Initialisation du module.
 */
static void init( void ) ;


/**
 * Le numéro d'un fichier ouvert d'après son fd.
 * @param fd Le numéro du descripteur à contrôler
 * @return Le numéro du fd (l'argument fd passé)
 *  ou -1 en cas d'erreur (errno=EBADF)
 */
static int numero( int fd )
{
	/* vérifie que le module est initialisé */
	init() ;
	/* contrôle du numéro */
	if ( fd < 0 || fd >= table_max ) {
		badf : ;
		errno = EBADF ;
		return -1 ;
	}
	/* contrôle que l'emplacement est utilisé */
	switch ( table[ fd ]. type ) {
		case fd_libre : goto badf ;
		case fd_console : break ;
		case fd_disque : break ;
		case fd_dossier : break ;
		case fd_fichier : break ;
	}
	return fd ;
}


/**
 * Construit le nom d'un disque d'après son handle UEFI.
 * @param handle Le EFI_HANDLE dont on souhaite obtenir une représentation
 * @return Un buffer "static" qui contient cela (ce code n'est pas
 *  multi-thread mais en UEFI ça ne sera pas un soucis)
 */
const char * UEFI_disk_name( EFI_HANDLE handle )
{
	static char txt[ 30 ] ;
	snprintf( txt , 30 , "EFI_HANDLE(%llx)" ,
		(unsigned long long) handle ) ;
	return txt ;
}


/**
 * Tests sur un fichier.
 * Ici tout est toujours autorisé.
 */
int access( const char *pathname __attribute__((unused)) ,
	int mode __attribute__((unused)) )
{
	return 0 ;
}
#if 0
int faccessat( dirfd , pathname , mode , flags )
	int dirfd __attribute__((unused)) ;
	const char *pathname __attribute__((unused)) ;
	int mode __attribute__((unused)) ;
	int flags __attribute__((unused)) ;
{
	return 0 ;
}
#endif


/**
 * Ouverture d'un fichier.
 * @param name Le cheminon du fichier/périphérique à ouvrir
 * @param mode Le mode d'ouverture (fcntl.h)
 * @return Le nouveau fd
 *  ou -1 en cas d'erreur (consulter errno)
 */
int open64( const char * name , int mode , ... )
{
	/*va_list args ;*/
	long long h ;
	EFI_HANDLE hand ;
	int n ;
	/* debug */
	UEFI_dprintf( D_BLKIO | D_DEBUG ,
		"Entre dans open64( \"%s\" , mode=%06x )\n" , name , mode ) ;
	/* vérifie que le module est initialisé */
	init() ;
	/* passe "EFI_HANDLE" et "(" */
	while ( * name && name[ 0 ] != '(' ) name ++ ;
	if ( * name ) name ++ ;
	if ( * name == 0 ) {
		errno = EINVAL ;
		return -1 ;
	}
	/* après c'est la valeur du handle en hexadécimal */
	n = 0 ;
	if ( sscanf( name , "%llx%n" , & h , & n ) != 1 ) {
		errno = EINVAL ;
		return -1 ;
	}
	hand = (EFI_HANDLE) h ;
	name += n ;
	/* après c'est la parenthèse fermante */
	if ( * name == ')' ) name ++ ;
	/* trouve un numéro libre */
	for(;;) {
		for ( n = 0 ; n < table_max ; n ++ ) {
			if ( table[ n ]. type == fd_libre ) {
				/* trouvé une place */
				table[ n ]. position = 0 ;
				table[ n ]. mode = mode ;
				break ;
			}
		}
		/* trouvé un numéro */
		if ( n < table_max ) break ;
		/* il faut agrandir la table */
		__fortify_fail( "open() table_max" ) ;
	}
	if ( * name ) {
		/* c'est un fichier à ouvrir */
		__fortify_fail( "open() file" ) ;
	} else {
#ifdef EFI_DEBUG
		/* debug */
		if ( uefi_debug_mask( D_BLKIO | D_DEBUG ) ) {
			CHAR16 * str ;
			EFI_BLOCK_IO * block_io ;
			char txt[ 100 ] ;
			str = DevicePathToStr( DevicePathFromHandle( hand ) ) ;
			uefi_dprint_str( " " ) ;
			while ( * str ) {
				char c[ 2 ] = { * str , '\0' } ;
				uefi_dprint_str( c ) ;
				++ str ;
			}
			FreePool( str ) ;
			UEFI_call( ST-> BootServices-> HandleProtocol ,
				hand , & BlockIoProtocol , & block_io ) ;
			snprintf( txt , 100 , "\n %ld blocs de chacun %d octets\n" ,
				block_io-> Media-> LastBlock + 1 ,
				block_io-> Media-> BlockSize ) ;
			uefi_dprint_str( txt ) ;
			uefi_dprint_str( "--> Touche : " ) ;
			UEFI_console_getchar() ;
			UEFI_console_putchar( '\n' , 1 ) ;
		}
#endif
		/* c'est un disque à ouvrir */
		table[ n ]. handle = hand ;
		table[ n ]. type = fd_disque ;
	}
	return n ;
}

/* Cette fonction sert en _FORTIFY_SOURCE */
extern int __open64_2( const char* name , int mode ) __attribute__((nonnull((1)))) ;
int __open64_2( const char* name , int mode )
{
	return open64( name , mode ) ;
}


#if 0
/**
 * Ouverture d'un fichier.
 * @param name Le cheminon du fichier/périphérique à ouvrir
 * @param mode Le mode d'ouverture (fcntl.h)
 * @return Le nouveau fd
 *  ou -1 en cas d'erreur (consulter errno)
 */
int openat64(
	int dirfd __attribute__((unused)) ,
	const char * name ,
	int mode ,
	... )
{
	/*va_list args ;*/
	return open64( name , mode ) ;
}
#endif


/**
 * Lit un caractère depuis la console.
 * @return le caractère lu (valeur unicode)
 *  ou -1 en cas d'erreur (consulter errno)
 * Note : pour simplifier ce code ne gère pas tout Unicode mais seulement
 *  la partie qui se code en un CHAR16 en UTF-16
 * Note : ce code est appelé par les macros de debug donc pour éviter
 *  une récursion infinie, il n'appelle aucun code de debug.
 */
long UEFI_console_getchar( void )
{
	EFI_INPUT_KEY k ;
	EFI_STATUS status ;
	/* récupère la prochaine touche */
	readkey : ;
	status = UEFI_call( ST-> ConIn-> ReadKeyStroke , ST-> ConIn , & k ) ;
	if ( status == EFI_NOT_READY ) {
		/* pas de touche disponible, attend */
		UINTN i ;
		UEFI_call( ST-> BootServices-> WaitForEvent , 1 ,
			& ST-> ConIn-> WaitForKey , & i ) ;
		/* recommence */
		goto readkey ;
	}
	if ( EFI_ERROR( status ) ) {
		/* pas de message de debug autorisé dans cette fonciton */
		errno = EIO ;
		return -1 ;
	}
	/* si le code unicode est 0, c'est une touche spéciale */
	if ( k. UnicodeChar == 0 ) {
		/* touche Échap. */
		if ( k. ScanCode == SCAN_ESC ) return '\033' ;
		goto readkey ;
	}
	/* retourne le code unicode */
	return k. UnicodeChar ;
}


/**
 * L'espace dans lequel la ligne lue de la console est stocké.
 * La fonction lit_ligne() remplit ce buffer jusqu'à ce que l'utilisateur
 * presse la touche Entrée, si le buffer est trop petit alors le \n n'y sera
 * pas copié.
 */
static CHAR16 * ligne ;


/**
 * La position courante dans la ligne lue de la console.
 */
static CHAR16 * pos_ligne ;


/**
 * Libère le buffer de lecture de ligne en fin d'exécution.
 */
static void free_ligne()
{
	free( ligne ) ;
}


/**
 * Lit une ligne depuis la console.
 * Attend qu'une touche '\r' ou '\n' soit pressée pour retourner.
 * Gère l'effacement via les touches Ret. Arr. ou Échap.
 * Note : Si le buffer n'est pas assez grand, retourne quand même (mais le
 *  buffer ne contiendra pas le \n).
 */
static void lit_ligne()
{
	int pos = 0 ;
	/* tout premier appel */
	if ( ligne == NULL ) {
		ligne = malloc( 501 * sizeof( CHAR16 ) ) ;
		if ( ligne == NULL ) {
			__fortify_fail( "lit_ligne() ENOMEM" ) ;
		}
		atexit( free_ligne ) ;
	}
	/* initialise la position dans la ligne lue */
	pos_ligne = ligne ;
	/* lit jusqu'à un saut de ligne ou dépassement du buffer */
	while ( pos < 500 ) {
		long c ;
		c = UEFI_console_getchar() ;
		/* une erreur */
		if ( c == (long) -1 ) break ;
		/* le caractère Ret. Arr. ou Échap. efface */
		if ( c == '\b' || c == '\033' ) {
			while ( pos > 0 ) {
				UEFI_console_putchar( '\b' , 0 ) ;
				UEFI_console_putchar( ' ' , 0 ) ;
				UEFI_console_putchar( '\b' , 0 ) ;
				pos -- ;
				/* Ret. Arr. efface un seul caractère */
				if ( c == '\b' ) break ;
			}
			continue ;
		}
		/* affiche le caractère lu */
		UEFI_console_putchar( c , 0 ) ;
		/* fin de ligne ? */
		if ( c == '\r' ) UEFI_console_putchar( '\n' , 0 ) ;
		if ( c == '\n' || c == '\r' ) {
			ligne[ pos ++ ] = '\n' ;
			break ;
		}
		/* stocke le caractère lu */
		ligne[ pos ++ ] = (CHAR16) c ;
	}
	/* termine avec un \0 il reste toujours au moins une place */
	ligne[ pos ] = '\0' ;
}


/**
 * Lecture depuis la console.
 * @param buf L'adresse où déposer les caractères UTF-8 lus
 * @param n Le nombre maximum de caractères à lire
 * @return Le nombre de caractères effectivement lus
 */
static ssize_t read_console( void * buf , size_t n )
{
	size_t ret = 0 ;
	char * pos = (char *) buf ;
	/* copie les caractères depuis un buffer de ligne */
	copie : ;
	/* si il faut lire une nouvelle ligne depuis la console */
	if ( pos_ligne == NULL ) lit_ligne() ;
	/* copie le nombre de caractères demandés */
	while ( n && * pos_ligne ) {
#		if 0
		/* TODO: convertit UTF-16 vers UTF-8 ou pas ? */
#		endif
		char c = (char) * pos_ligne ;
		pos_ligne ++ ;
		* pos = c ;
		pos ++ ;
		n -- ;
		ret ++ ;
	}
	/* si il reste à copier c'est que la ligne lue a été finie */
	if ( n > 0 ) {
		/* il faut relire une ligne */
		pos_ligne = NULL ;
		goto copie ;
	}
	/* le nombre d'octets lus */
	return ret ;
}


/**
 * Lecture depuis un disque.
 * @param f La structure du disque ouvert
 * @param buf L'adresse où stocker les octets lus
 * @param n Le nombre maximum d'octets à lire
 * @return Le nombre d'octets lus ou -1 en cas d'erreur (consulter errno)
 */
static ssize_t read_disque( struct fd * f , void * buf , size_t n )
{
	EFI_STATUS status ;
	EFI_DISK_IO * disk_io ;
	EFI_BLOCK_IO * block_io ;
	/* récupère les fonctions d'accès */
	status = UEFI_call( ST-> BootServices-> HandleProtocol ,
		f-> handle , & DiskIoProtocol , & disk_io ) ;
	if ( EFI_ERROR( status ) ) {
		errno = EIO ;
		return -1 ;
	}
	/* récupère les informations sur le disque */
	status = UEFI_call( ST-> BootServices-> HandleProtocol ,
		f-> handle , & BlockIoProtocol , & block_io ) ;
	if ( EFI_ERROR( status ) ) {
		errno = EIO ;
		return -1 ;
	}
	/* lit sur le disque */
	status = UEFI_call( disk_io-> ReadDisk , disk_io ,
		block_io-> Media-> MediaId , f-> position , n , buf ) ;
	if ( EFI_ERROR( status ) ) {
		errno = EIO ;
		return -1 ;
	}
	/* avance sur le disque */
	f-> position += n ;
	/* le nombre d'octets lus */
	return n ;
}


/**
 * Lecture.
 * @param fd Le numéro du descripteur
 * @param buf L'espace où stocker ce qui est lu
 * @param n Le nombre d'octets maximum à lire
 * @return Le nombre d'octets lus ou -1 en cas d'erreur (consulter errno)
 */
ssize_t read( int fd , void * buf , size_t n )
{
	ssize_t ret = -1 ;
	UEFI_dprintf( D_BLKIO | D_INFO ,
		"Entre dans read( fd=%d , buf=%p , n=%ld )\n" ,
		fd , buf , n ) ;
	/* contrôle du numéro */
	if ( numero( fd ) < 0 ) return -1 ;
	/* selon le type de descripteur */
	switch( table[ fd ]. type ) {
		case fd_libre : {
			errno = EBADF ;
			return -1 ;
		}
		case fd_console : {
			ret = read_console( buf , n ) ;
			break ;
		}
		case fd_disque : {
			ret = read_disque( table + fd , buf , n ) ;
			break ;
		}
		default : {
			__fortify_fail( "read()" ) ;
			break ;
		}
	}
	UEFI_dprintf( D_BLKIO | D_INFO , "Quitte read() : %d\n" ,
		(int) ret ) ;
	return ret ;
}


/**
 * Écrit un caractère sur la console.
 * Note : ce code est appelé par les macros de debug donc pour éviter
 *  une récursion infinie, il n'appelle aucun code de debug.
 * @param c Le caractère Unicode à écrire
 * @param e Écrire sur StdErr plutôt que ConOut
 * @return Le caractère Unicode écrit convertit en int
 *  ou -1 en cas d'erreur (consulter errno)
 */
int UEFI_console_putchar( long c , char e )
{
	/* le firmware UEFI demande du UTF-16 */
	UINT16 lo ;
	CHAR16 s[ 2 ] ;
	SIMPLE_TEXT_OUTPUT_INTERFACE * h ;
	EFI_STATUS status ;
	lo = (UINT16) c ;
#	if 0
	/* TODO: ne gère pas tout Unicode */
	if ( c >= 0x10000 ) {
		/* ce caractère Unicode s'écrit en deux UTF-16 */
		int ret ;
		ret = UEFI_console_putchar( ( c >> 10 ) | 0xd800 , e ) ;
		if ( ret < 0 ) return ret ;
		lo = ( lo & 0x3ff ) | 0xdc00 ;
	}
#	endif
	s[ 0 ] = lo ;
	s[ 1 ] = '\0' ;
	h = e ? ST-> StdErr : ST-> ConOut ;
	status = UEFI_call( h-> OutputString , h , s ) ;
	if ( EFI_ERROR( status ) ) {
		errno = EIO ;
		return -1 ;
	}
	/* saut de ligne */
	if ( lo == '\n' ) {
		/* ajoute le retour chariot */
		if ( UEFI_console_putchar( '\r' , e ) == -1 ) {
			return -1 ;
		}
	}
	return (int) c ;
}


/**
 * Bricolage pour afficher la bannière de début d'exécution une seule fois.
 */

static int cacher_ligne ;

void hush_next_line( void )
{
	cacher_ligne = 2 ;
}


/**
 * Écrit sur la console.
 * @param e Valeur 0 pour ConOut et !=0 pour StdErr
 * @param msg Pointeur vers le texte UTF-8 à écrire
 * @param n Le nombre d'octets à écrire
 * @return Le nombre d'octets effectivement écrits
 *  ou -1 en cas d'erreur (consulter errno).
 */
static ssize_t write_console( char e , const char * msg , size_t n )
{
	size_t i ;
	int err = 0 ;
	for ( i = 0 ; i < n ; ) {
		uint32_t uni ;
		uint8_t cp = (uint8_t) msg[ i ++ ] ;
		int todo ;
		/* convert to unicode */
		if ( cp < 0x80 ) {
			uni = cp == '\t' ? ' ' : cp ;
			/* le caractère "tab" est moche */
			if ( cp == '\t' ) uni = ' ' ;
			/* le caractère "bell" n'existe pas */
			if ( cp == '\a' ) continue ;
			todo = 0 ;
		}
		else if ( cp < 0xc0 || cp > 0xf7 ) {
			/* invalid byte, msg broken */
			err = EILSEQ ;
			break ;
		}
		else if ( cp < 0xe0 ) {
			uni = cp & 0x1f ;
			todo = 1 ;
		}
		else if ( cp < 0xf0 ) {
			uni = cp & 0x0f ;
			todo = 2 ;
		}
		else {
			uni = cp & 0x7 ;
			todo = 3 ;
		}
		while ( todo > 0 ) {
			if ( i >= n ) {
				/* missing continuation byte, msg broken */
				err = EILSEQ ;
				goto break_converter ;
			}
			cp = (uint8_t) msg[ i ++ ] ;
			if ( cp > 0xbf || cp < 0x80 ) {
				/* invalid continuation byte, msg broken */
				err = EILSEQ ;
				goto break_converter ;
			}
			uni <<= 6 ;
			uni |= cp & 0x3f ;
			todo -- ;
		}
		/* masquer la ligne suivante ? */
		if ( cacher_ligne ) {
			/* arrête de cacher en fin de ligne */
			if ( uni == '\n' ) cacher_ligne -- ;
			continue ;
		}
		/* then send to console */
		if ( UEFI_console_putchar( uni , e ) == -1 ) {
			/* output error */
			err = errno ;
			break ;
		}
	}
	break_converter : ;
	if ( i == 0 && err ) {
		/* aucun octet écrit mais une erreur */
		errno = err ;
		return -1 ;
	}
	return (ssize_t) i ;
}


/**
 * Écriture sur un disque.
 * @param f La structure du disque ouvert
 * @param buf L'adresse où sont stockés les octets à écrire
 * @param n Le nombre maximum d'octets à à écrire
 * @return Le nombre d'octets écrits ou -1 en cas d'erreur (consulter errno)
 */
static ssize_t write_disque( struct fd * f , const void * buf , size_t n )
{
	EFI_STATUS status ;
	EFI_DISK_IO * disk_io ;
	EFI_BLOCK_IO * block_io ;

	/* récupère les fonctions d'accès */
	status = UEFI_call( ST-> BootServices-> HandleProtocol ,
		f-> handle , & DiskIoProtocol , & disk_io ) ;
	if ( EFI_ERROR( status ) ) {
		errno = EIO ;
		return -1 ;
	}
	/* récupère les informations sur le disque */
	status = UEFI_call( ST-> BootServices-> HandleProtocol ,
		f-> handle , & BlockIoProtocol , & block_io ) ;
	if ( EFI_ERROR( status ) ) {
		errno = EIO ;
		return -1 ;
	}
	/* écrit sur le disque */
	status = UEFI_call( disk_io-> WriteDisk , disk_io ,
		block_io-> Media-> MediaId , f-> position , n , buf ) ;
	if ( EFI_ERROR( status ) ) {
		errno = EIO ;
		return -1 ;
	}
	/* avance sur le disque */
	f-> position += n ;
	/* le nombre d'octets écrits */
	return n ;
}


/**
 * Écriture.
 * @param fd Le numéro du descripteur
 * @param buf L'adresse où sont stockés les octets à écrire
 * @param n Le nombre maximum d'octets à à écrire
 * @return Le nombre d'octets écrits
 *  ou -1 en cas d'erreur (consulter errno)
 */
ssize_t write( int fd , const void * buf , size_t n )
{
	ssize_t ret = -1 ;
	/* contrôle du numéro */
	if ( numero( fd ) < 0 ) return -1 ;
	/* selon le type de descripteur */
	switch( table[ fd ]. type ) {
		case fd_libre : {
			errno = EBADF ;
			return -1 ;
		}
		case fd_console : {
			ret = write_console(
				(char) (long long) table[ fd ]. handle ,
				buf , n ) ;
			break ;
		}
		case fd_disque : {
			ret = write_disque( table + fd , buf , n ) ;
			break ;
		}
		default : {
			__fortify_fail( "write()" ) ;
			break ;
		}
	}
	return ret ;
}


/**
 * Positionnement.
 * @param fd le numéro du descripteur
 * @param offset La nouvelle position ou le déplacement selon le paramètre
 *  whence
 * @param whence Le mode de décalage SEEK_* (unistd.h)
 * @return La nouvelle position ou -1 en cas d'erreur (consulter errno)
 */
off64_t lseek64( int fd , off64_t offset , int whence )
{
	/* contrôle du numéro */
	if ( numero( fd ) < 0 ) return -1 ;
	switch ( whence ) {
		case SEEK_SET : {
			table[ fd ]. position = offset ;
			break ;
		}
		case SEEK_CUR : {
			table[ fd ]. position += offset ;
			break ;
		}
		case SEEK_END : {
			__fortify_fail( "lseek64() SEEK_END" ) ;
		}
	}
	/* c'est bon, retourne la nouvelle position >= 0 */
	return table[ fd ]. position ;
}


/**
 * Information et commandes diverses.
 * @param fd Le numéro du descripteur
 * @param request Le code de l'information demandée sur ce descripteur
 * @param ... Donnée à écrire ou l'emplacement pour stocker le résultat selon
 *  la valeur du paramètre request
 */
int ioctl( int fd , unsigned long int request , ... )
{
	va_list arg_ptr ;
	EFI_STATUS status ;
	EFI_BLOCK_IO * block_io ;
	UEFI_dprintf( D_BLKIO | D_INFO ,
		"Entre dans ioctl( fd=%d , req=%lu )\n" , fd , request ) ;
	/* contrôle du numéro */
	if ( numero( fd ) < 0 ) return -1 ;
	/* argument */
	va_start( arg_ptr , request ) ;
	/* selon le code */
	switch ( request ) {
		case BLKGETSIZE : {
			/* taille du disque en nombre de blocs de 512 oct */
			UINT64 n , s ;
			status = UEFI_call( ST-> BootServices->
				HandleProtocol , table[ fd ]. handle ,
				& BlockIoProtocol , & block_io ) ;
			if ( EFI_ERROR( status ) ) {
				errno = EIO ;
				return -1 ;
			}
			/* le nombre de blocs et leur taille en octets */
			n = block_io-> Media-> LastBlock + 1 ;
			s = block_io-> Media-> BlockSize ;
			/* ajuste en nombre de blocs de 512 octets */
			while ( s < 512 ) {
				n >>= 1 ;
				s <<= 1 ;
			}
			while ( s > 512 ) {
				n <<= 1 ;
				s >>= 1 ;
			}
			UEFI_dprintf( D_BLKIO | D_INFO ,
				"BLKGETSIZE : %p %lu\n" ,
				table[ fd ]. handle , (long unsigned) n ) ;
			/* l'argument est un "long unsigned" */
			* va_arg( arg_ptr , unsigned long * ) = n ;
			break ;
		}
		case BLKGETSIZE64 : {
			/* taille du disque en nombre d'octets */
			UINT64 n , s ;
			status = UEFI_call( ST-> BootServices->
				HandleProtocol , table[ fd ]. handle ,
				& BlockIoProtocol , & block_io ) ;
			if ( EFI_ERROR( status ) ) {
				errno = EIO ;
				return -1 ;
			}
			/* le nombre de blocs et leur taille en octets */
			n = block_io-> Media-> LastBlock + 1 ;
			s = block_io-> Media-> BlockSize ;
			/* ajuste en nombre d'octets */
			while ( s > 1 ) {
				s >>= 1 ;
				n <<= 1 ;
			}
			UEFI_dprintf( D_BLKIO | D_INFO ,
				"BLKGETSIZE64 : %p %llu\n" ,
				table[ fd ]. handle , n ) ;
			/* l'argument est 64 bits */
			* va_arg( arg_ptr , uint64_t * ) = n ;
			break ;
		}
		case BLKIOMIN :
		case BLKSSZGET :
		case BLKPBSZGET : {
			/* taille d'un bloc en octets */
			UINT64 s ;
			status = UEFI_call( ST-> BootServices->
				HandleProtocol , table[ fd ]. handle ,
				& BlockIoProtocol , & block_io ) ;
			if ( EFI_ERROR( status ) ) {
				errno = EIO ;
				return -1 ;
			}
			/* taille d'un bloc en octets */
			s = block_io-> Media-> BlockSize ;
			UEFI_dprintf( D_BLKIO | D_INFO ,
				"BLKSSZGET : %p %u\n" ,
				table[ fd ]. handle , (unsigned) s ) ;
			/* l'argument est "unsigned" */
			* va_arg( arg_ptr , unsigned * ) = s ;
			break ;
		}
		case BLKRRPART : {
			/* relire la table des partitions */
			break ;
		}
		case HDIO_GETGEO : {
			/* retourner toute la géométrie du disque dans une
			 structure spéciale */
			UINT64 n ;
			struct hd_geometry * p_geom ;
			status = UEFI_call( ST-> BootServices->
				HandleProtocol , table[ fd ]. handle ,
				& BlockIoProtocol , & block_io ) ;
			if ( EFI_ERROR( status ) ) {
				errno = EIO ;
				return -1 ;
			}
			/* le nombre de blocs */
			n = block_io-> Media-> LastBlock + 1 ;
			/* renseigne la structure */
			p_geom = va_arg( arg_ptr , struct hd_geometry * ) ;
			memset( p_geom , 0 , sizeof( struct hd_geometry ) ) ;
			p_geom-> heads = 255 ;
			p_geom-> sectors = 63 ;
			p_geom-> cylinders = n / 63 / 255 ;
			break ;
		}
		case BLKALIGNOFF : {
			/* alignement (je ne sais pas à quoi ça sert ?) */
			UINT64 s ;
#if 1
			s = 0 ;
#else
			status = UEFI_call( ST-> BootServices->
				HandleProtocol , table[ fd ]. handle ,
				& BlockIoProtocol , & block_io ) ;
			if ( EFI_ERROR( status ) ) {
				errno = EIO ;
				return -1 ;
			}
			/* alignement */
			s = block_io-> Media-> IoAlign
				* block_io-> Media-> BlockSize ;
			UEFI_dprintf( D_BLKIO | D_INFO ,
				"BLKALIGNOFF : %p %llu\n" ,
				table[ fd ]. handle , s ) ;
#endif
			/* l'argument est "unsigned" */
			* va_arg( arg_ptr , unsigned * ) = s ;
			break ;
		}
		case BLKIOOPT : {
			/* l'argument est "unsigned" */
			* va_arg( arg_ptr , unsigned * ) = 1024 * 1024 ;
			break ;
		}
		case FDGETFDCSTAT : {
			/* Return invalid for floppy status */
			errno = EINVAL ;
			return -1 ;
		}
		default : {
			/* TODO! */
			__fortify_fail( "ioctl()" ) ;
#		if 0
			fprintf( stderr , "** ioctl(%d) inconnu **\n" , request ) ;
			errno = EINVAL ;
			/* argument */
			va_end( arg_ptr ) ;
			return -1 ;
#		endif
		}
	}
	/* argument */
	va_end( arg_ptr ) ;
	UEFI_dprintf( D_INFO , "Quitte ioctl() : 0\n" ) ;
	return 0 ;
}


/**
 * Informations.
 * @param fd Le numéro du descripteur
 * @param stat_buf L'emplacement où stocker les informations lues
 * Modified from __fxstat64 for GCC11 compatibility.
 */
int fstat64( int fd , struct stat64 * stat_buf )
{
	/* contrôle du numéro */
	if ( numero( fd ) < 0 ) return -1 ;
	/* initialise tout à 0 */
	memset( stat_buf , 0 , sizeof( struct stat64 ) ) ;
	/* positionne le mode en fonction du type du fd */
	switch ( table[ fd ]. type ) {
		case fd_libre /* n'arrive jamais */ :
			break ;
		case fd_console /* console ConIn, ConOut ou StdErr */ :
			stat_buf-> st_mode = S_IFCHR ;
			break ;
		case fd_disque /* disque ou partition de disque */ :
			stat_buf-> st_mode = S_IFBLK ;
			break ;
		case fd_dossier /* dossier de fichiers */ :
			stat_buf-> st_mode = S_IFDIR ;
			break ;
		case fd_fichier /* fichier */ :
			stat_buf-> st_mode = S_IFREG ;
			break ;
	}
	stat_buf-> st_mode |= 0777 ;
	/* TODO: le reste ? */
	return 0 ;
}


/**
 * poll : TODO: utile ?
 */
int poll( struct pollfd * fds __attribute__((unused)) ,
	nfds_t nfds __attribute__((unused)) ,
	int timeout __attribute__((unused)) )
{
	/* TODO! */
	return 0 ;
}


/**
 * fsync : flush d'un descripteur, inutile ici.
 * @param fd Le numéro du descripteur
 * @return 0 ou -1 en cas d'erreur (consulter errno)
 */
int fsync( int fd __attribute__((unused)) )
{
	return 0 ;
}


/**
 * sync : flush des buffers, inutile ici.
 */
void sync()
{
}


/**
 * close : fermeture.
 * @param fd Le numéro du descripteur
 * @return 0 ; -1 en cas d'erreur (consulter errno)
 */
int close( int fd )
{
	/* contrôle du numéro */
	if ( numero( fd ) < 0 ) return -1 ;
	/* ferme le descripteur */
	switch ( table[ fd ]. type ) {
		case fd_libre :
		case fd_console :
		case fd_disque : break ;
		case fd_dossier :
		case fd_fichier : {
			/* flush + ferme */
			/* TODO! */
			__fortify_fail( "close() file" ) ;
		}
	}
	/* note que l'emplacement est libre */
	table[ fd ]. type = fd_libre ;
	return 0 ;
}


/**
 * Ferme tous les fichiers ouverts.
 */
static void fini()
{
	/* ferme tous les fichiers */
	while ( table_max != 0 ) {
		table_max -- ;
		close( table_max ) ;
	}
}


/**
 * Initialisation du module.
 */
static void init()
{
	/* une seule fois */
	static char done = 0 ;
	if ( ! done ) {
		/* fermera les fichiers en fin d'exécution */
		atexit( fini ) ;
	}
}


/**
 * Retourne les dimensions de l'écran.
 */
int get_terminal_dimension(int *cols, int *lines) ;
int get_terminal_dimension(int *cols, int *lines)
{
	EFI_STATUS status ;
	UINTN r , c ;

	status = UEFI_call( ST-> ConOut-> QueryMode , ST-> ConOut ,
		ST-> ConOut-> Mode-> Mode , & c , & r ) ;
	if ( status ) { c = r = 0 ; }
	if ( cols ) *cols = c ;
	if ( lines ) *lines = r ;
	return 0 ;
}

/**
 * Largeur de l'écran.
 */
int get_terminal_width( void ) ;
int get_terminal_width( void )
{
	int r , c ;
	r = get_terminal_dimension( & c , NULL ) ;
	if ( r ) c = 0 ;
	return c ;
}


/**
 * Pour afficher en plusieurs écrans avec un pagineur.
 */

void pager_open( void ) ;
void pager_open() { }

void pager_close( void ) ;
void pager_close() { }


/**
 * Mineur et majeur d'un périphérique : ne servent pas ici.
 */

unsigned int gnu_dev_major( dev_t t )
{
	return ( ( t >> 8 ) & 0xfff ) | ( (unsigned int) ( t >> 32) & ~0xfff ) ;
}

unsigned int gnu_dev_minor( dev_t t )
{
	return ( t & 0xff ) | ( (unsigned int) ( t >> 12 ) & ~0xff ) ;
}

