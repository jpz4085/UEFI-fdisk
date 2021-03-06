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
 * Ce module contient la fonction efi_main() appellée depuis
 * _start du module <tt>start-"ARCH".S</tt>. Cette fonction est en charge
 * d'énumérer les périphériques bloc disponibles, de faire
 * choisir l'utilisateur et d'appeller la fonction main() avec
 * le chemin vers ce disque comme argument.
 *
 */


#define _GNU_SOURCE
#include "uefi.h"
#include "debug.h"
#include <unistd.h>

#include "../config.h"
#include "../include/strutils.h"


/**
 * La table de tous les périphériques disque.
 */
EFI_HANDLE * HandlePointer ;


/**
 * Le nombre d'entrées dans HandlePointer.
 */
UINTN HandleCount ;


/**
 * La table des disques utilisables.
 */
static EFI_HANDLE * table ;


/**
 * Le nombre d'entrées utiles dans "table".
 */
static int max_table ;


/**
 * Fait le ménage en fin d'exécution.
 */
static void fini( void )
{
	UINTN i ;
	EFI_STATUS status ;
	EFI_BLOCK_IO * block_io ;
	/* force la relecture des tables de partitions */
	for ( i = 0 ; i < HandleCount ; i ++ ) {
		status = UEFI_call( ST-> BootServices-> HandleProtocol ,
			HandlePointer[ i ] , & BlockIoProtocol , & block_io ) ;
		if ( EFI_ERROR( status ) ) continue ;
		UEFI_call( ST-> BootServices-> ReinstallProtocolInterface ,
			HandlePointer[ i ] , & BlockIoProtocol ,
			block_io , block_io ) ;
	}
	FreePool( HandlePointer ) ;
	free( table ) ;
}


/**
 * Détermine la liste des périphériques partitionnables.
 * @return EFI_SUCCESS si tout est bon, sinon une erreur.
 * Cette fonction est reprise du programme "diskpart" de
 * Intel.
 */
static EFI_STATUS FindPartitionableDevices( void )
{
    EFI_STATUS      status ;
    EFI_BLOCK_IO    *BlkIo;
    EFI_DEVICE_PATH *DevicePath;
    UINTN           PathSize;
    BOOLEAN         Partitionable;
    EFI_DEVICE_PATH *PathInstance;
    UINTN           i;

    /*
     Try to find all of the hard disks by finding all
     handles that support BlockIo protocol
    */
    status = LibLocateHandle(
        ByProtocol,
        &BlockIoProtocol,
        NULL,
        &HandleCount,
        &HandlePointer
        );

    if (EFI_ERROR(status)) {
        return status;
    }

    table = (EFI_HANDLE*) malloc( sizeof( EFI_HANDLE ) * HandleCount ) ;

    if (table == NULL) {
	FreePool( HandlePointer ) ;
        return EFI_OUT_OF_RESOURCES;
    }

    atexit( fini ) ;

    for (i = 0; i < HandleCount; i++) {
        Partitionable = TRUE;
        status = UEFI_call( ST-> BootServices-> HandleProtocol ,
		HandlePointer[ i ] , &BlockIoProtocol, &BlkIo);
        /* According to Windows GPT FAQ at
	   www.microsoft.com/hwdev/tech/storage/GPT_FAQ.ASP, Microsoft tools
	   will never partition removable media, whether it be floppy or
	   superfloppy.  */
        if (BlkIo->Media->RemovableMedia) {
            /* It's removable, it's not for us */
            Partitionable = FALSE;
        }
        if ( ! BlkIo->Media->MediaPresent) {
            /* It's still not for us */
            Partitionable = FALSE;
        }
        if (BlkIo->Media->ReadOnly) {
            /* Cannot partition a read-only device!  */
            Partitionable = FALSE;
        }
	/* OK, it seems to be a present, fixed, read/write, block device.
	   Now, make sure it's really the raw device by inspecting the
	   device path.  */
        DevicePath = DevicePathFromHandle(HandlePointer[i]);
        while (DevicePath != NULL) {
            PathInstance = DevicePathInstance(&DevicePath, &PathSize);

            while (!IsDevicePathEnd(PathInstance)) {
                if ((DevicePathType(PathInstance) == MEDIA_DEVICE_PATH)) {
                    Partitionable = FALSE;
                }

                PathInstance = NextDevicePathNode(PathInstance);
            }
        }

        if (Partitionable) {
		/* l'affiche */
		CHAR16 * str , * p ;
		EFI_BLOCK_IO * BlkIo ;
        	DevicePath = DevicePathFromHandle( HandlePointer[ i ] ) ;
		str = DevicePathToStr( DevicePath ) ;
		status = UEFI_call( ST-> BootServices-> HandleProtocol ,
			HandlePointer[ i ] , & BlockIoProtocol , & BlkIo ) ;
		printf( "  Disk %d: %s: %lld sectors, %s\n    " ,
			max_table + 1 , UEFI_disk_name( HandlePointer[ i ] ) ,
			BlkIo-> Media-> LastBlock + 1 ,
			size_to_human_string( SIZE_DECIMAL_2DIGITS
				| SIZE_SUFFIX_SPACE | SIZE_SUFFIX_3LETTER ,
				( BlkIo-> Media-> LastBlock + 1 )
					* BlkIo-> Media-> BlockSize ) ) ;
		/* pour convertir chaque CHAR16 en char */
		p = str ;
		while ( * p ) {
			char c = * p ;
			putchar( c ) ;
			p ++ ;
		}
		FreePool( str ) ;
		putchar( '\n' ) ;
		/* return this handle */
		table[ max_table ] = HandlePointer[ i ] ;
		max_table ++ ;
	}
    }
    return EFI_SUCCESS;
}


/**
 * Le nom de ce programme.
 */
static const char proginvoshrtname[] = "fdisk.efi" ;
char * program_invocation_short_name = (char*) proginvoshrtname ;


/**
 * Les arguments passés à la fonction main().
 */
static const char* argv[] = { proginvoshrtname , NULL , NULL } ;
static const char* envp[] = { NULL } ;


/**
 * La définition de la fonction main().
 */
extern int main( int , const char ** , const char ** ) ;


/**
 * La fonction principale appelée depuis _start du module start-$(ARCH).
 * @param ImageHandle Le EFI_HANDLE de ce programme.
 * @param SystemTable La table des HANDLE et fonction UEFI.
 * @return Un EFI_STATUS de fin d'exécution.
 *
 * Cette fonction est le point d'entrée dans le programme (appellée depuis
 * le module start-$(ARCH)). Elle fait des trucs EFI pour récupérer la
 * liste des disques puis appelle la fonction main() du fdisk classique.
 */
EFI_STATUS
efi_main( EFI_HANDLE ImageHandle , EFI_SYSTEM_TABLE * SystemTable ) ;

EFI_STATUS
efi_main( EFI_HANDLE ImageHandle , EFI_SYSTEM_TABLE * SystemTable )
{
	EFI_STATUS status ;
	EFI_HANDLE Disk ;
	/* initialise la librairie GNU */
	InitializeLib( ImageHandle , SystemTable ) ;
#if 0
	/* les information sur moi-même */
	EFI_LOADED_IMAGE * loaded_image = NULL ;
	EFI_GUID my_LoadedImageProtocol = LOADED_IMAGE_PROTOCOL ;
	status = UEFI_call( SystemTable-> BootServices-> HandleProtocol ,
		ImageHandle , & my_LoadedImageProtocol ,
		(void **) & loaded_image ) ;
	if ( EFI_ERROR( status ) ) {
		__fortify_fail( "handleprotocol" ) ;
	}
	UEFI_dprintf( D_INFO , "Hello, world!\n" ) ;
	UEFI_dprintf( D_INFO , "Image base            : %p\n" ,
		loaded_image-> ImageBase ) ;
	UEFI_dprintf( D_INFO , "Image size            : %ld\n" ,
		loaded_image-> ImageSize ) ;
	UEFI_dprintf( D_INFO , "efi_main              : %p\n" , efi_main ) ;
	UEFI_dprintf( D_INFO , "Fin des initialisations, appel de main()\n" ) ;
#endif
	printf( "\nWelcome to UEFI fdisk (%s) version " VERSION "\n\n"
		"List of hard disks found:\n" ,
		program_invocation_short_name ) ;
	FindPartitionableDevices() ;
	putchar( '\n' ) ;

	/* si un seul disque, le sélectionne, sinon... */
	if ( max_table == 1 ) {
		Disk = table[ 0 ] ;
		printf( "Using Disk 1\n" ) ;
	} else {
		for(;;) {
			char str[ 10 ] ;
			int n ;
			printf( "Disk number (1-%d): " , max_table ) ;
			/* lit une ligne */
			if ( fgets( str , sizeof( str ) , stdin ) == NULL ) {
				/* fin de fichier ou erreur */
				exit( 5 ) ;
			}
			/* si la fin de ligne n'a pas été lue */
			if ( str[ strlen( str ) - 1 ] != '\n' ) {
				while ( fgetc( stdin ) != '\n' ) {}
			}
			/* trouve le nombre saisi */
			if ( sscanf( str , "%d" , & n ) != 1 ) {
				/* erreur dans la ligne lue ? */
				n = 0 ;
			}
			if ( n >= 1 && n <= max_table ) {
				Disk = table[ n - 1 ] ;
				break ;
			}
		}
	}
	putchar( '\n' ) ;

	hush_next_line() ;

	argv[ 1 ] = UEFI_disk_name( Disk ) ;
	status = main( 2 , argv , envp ) ;

	if ( status != EFI_SUCCESS ) status = EFI_ABORTED ;
	return status ;
}

