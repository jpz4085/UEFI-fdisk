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
 * Fonctions d'allocation mémoire, libération et réallocation.
 *
 */


#include "uefi.h"
#include "debug.h"
#include <errno.h>
#include <string.h>


/**
 * Alloue un nouveau bloc de mémoire.
 * @param count Le nombre d'octets à allouer.
 * @return L'adresse de début du bloc ou NULL en cas d'impossibilité.
 */
void * malloc( size_t count )
{
	size_t s ;
	EFI_STATUS status ;
	size_t * q ;
	/* debug */
	UEFI_dprintf( D_POOL , "--> malloc(%u) " , (unsigned) count ) ;
	/* pour enregistrer la taille du bloc juste avant le bloc */
	s = count + sizeof( size_t ) ;
	/* appelle UEFI pour obtenir un bloc */
	status = UEFI_call( ST-> BootServices-> AllocatePool , EfiLoaderData ,
		s , & q ) ;
	/* vérifie que tout s'est bien passé */
	if ( EFI_ERROR( status ) ) {
		/* aie ! que faire ? */
		errno = ENOMEM ;
		/* affiche un message */
		UEFI_dprintf( D_ERROR , "**ERROR** malloc(%u) status=%d\n" ,
			(unsigned) count , (int) ( status & 0x7fffffff ) ) ;
		/* et retourne NULL, mais un plantage est proche */
		return NULL ;
	}
	/* debug */
	UEFI_dprintf( D_POOL , "addr=%p\n" , q ) ;
	/* enregistre la taille du bloc juste avant */
	q[ 0 ] = count ;
	/* le bloc retourné commence juste après */
	q ++ ;
	/* debug */
	UEFI_dprintf( D_POOL , "<-- malloc() : %p\n" , q ) ;
	/* retourne le pointeur incrémenté */
	return (void *) q ;
}

/**
 * Alloue un bloc plein de zéros.
 * @param nelem Nombre d'éléments
 * @param elsize Taille d'un élément
 * @return L'adresse de début du bloc ou NULL en cas d'erreur (consulter errno).
 */
void * calloc( size_t nelem , size_t elsize )
{
	register void* ptr;
	if ( nelem == 0 || elsize == 0 )
		nelem = elsize = 1 ;
	ptr = malloc( nelem * elsize ) ;
	if ( ptr ) memset( ptr , 0 , nelem * elsize ) ;
	return ptr ;
}

/**
 * Réalloue un bloc de mémoire.
 * @param block L'adresse de début du bloc.
 * @param count La nouvelle taille.
 * @return L'adresse de début du bloc ou NULL en cas d'impossibilité.
 */
void * realloc( void * block , size_t count )
{
	void * p ;
	/* alloue toujours un nouveau bloc */
	p = malloc( count ) ;
	/* vérifie que tout s'est bien passé */
	if ( p == NULL ) {
		/* retourne NULL, errno est positionné */
		return NULL ;
	}
	if ( block ) {
		size_t * q ;
		size_t s ;
		/* l'adresse du bloc actuel */
		q = (size_t *) block ;
		/* la taille du bloc actuel */
		s = q[ -1 ] ;
		/* copie le plus petit des deux */
		if ( count > s ) count = s ;
		memcpy( p , block , count ) ;
		/* libère l'ancien bloc */
		free( block ) ;
	}
	/* l'adresse de début du nouveau bloc si tout est bon */
	return p ;
}

/**
 * Libère un bloc alloué.
 * @param block L'adresse de début du bloc à libérer.
 */
void free( void * block )
{
	size_t * q ;
	EFI_STATUS status ;
	/* debug */
	UEFI_dprintf( D_POOL , "--> free(%p) " , block ) ;
	/* si le pointeur passé est NULL ne fait rien */
	if ( block == NULL ) return ;
	/* l'adresse passée à UEFI */
	q = (size_t *) block ;
	q -- ;
	status = UEFI_call( ST-> BootServices-> FreePool , q ) ;
	if ( EFI_ERROR( status ) ) {
		/* aie ! */
		UEFI_dprintf( D_ERROR ,
			"**ERROR** free(%p) size=%u status=%d\n" ,
			block , q[ 0 ] , (int) ( status & 0x7fffffff ) ) ;
		/* TODO: there is a bug in the code: then what ? */
	}
	/* debug */
	UEFI_dprintf( D_POOL , "\n<-- free()\n" ) ;
}

