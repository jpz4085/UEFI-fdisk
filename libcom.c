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
 * Fonctions bidon en remplacement le libcommon/sysfs et libcommon/path
 * qui requiert plein de trucs impossibles en UEFI.
 *
 * Ce module ne fait rien, il sert juste à réussir le link.
 *
 */


#include "uefi.h"
#include "debug.h"
#include <efi.h>
#include <efilib.h>
#include <stdlib.h>

/* c'est pas trop bien fait, l'include en inclut un autre qui en inclut un 
   autre qui contient une fonction inline qui a besoin de ça */
#define HAVE_NANOSLEEP
#include "../include/sysfs.h"
#include "../include/path.h"
#include "../include/blkdev.h"
/*#include "../libblkid/src/topology/topology.h"*/
/*#include "../libblkid/src/blkidP.h"*/

__attribute__((noreturn))
dev_t sysfs_devname_to_devno(const char *name ) ;
__attribute__((noreturn))
dev_t sysfs_devname_to_devno(const char *name __attribute__((unused))) {
__fortify_fail( "sysfs_devname_to_devno()\n" ) ; }

int sysfs_devno_is_dm_private(dev_t devno , char **uuid ) ;
int sysfs_devno_is_dm_private(dev_t devno __attribute__((unused)), char **uuid __attribute__((unused)))
{
	/* en UEFI il n'y a pas de gestion DM */
	return 0 ;
}

__attribute__((noreturn))
int sysfs_devno_is_wholedisk( dev_t dev __attribute((unused)) )
{
__fortify_fail( "sysfs_devno_is_wholedisk()\n" ) ;
}

__attribute__((noreturn))
char * sysfs_devno_to_devpath(dev_t devno , char *buf , size_t bufsiz ) ;
__attribute__((noreturn))
char * sysfs_devno_to_devpath(dev_t devno __attribute__((unused)), char *buf __attribute__((unused)), size_t bufsiz __attribute__((unused))) { 
__fortify_fail("sysfs_devno_to_devpath()\n" ); }

char *canonicalize_path(const char *path ) ;
char *canonicalize_path(const char *path __attribute__((unused)) ) { return NULL ; }

char *canonicalize_path_restricted(const char *path ) ;
char *canonicalize_path_restricted(const char *path __attribute__((unused)) ) { return NULL ; }

char *canonicalize_dm_name(const char *ptname ) ;
char *canonicalize_dm_name(const char *ptname __attribute__((unused)) ) { return NULL ; }

char *absolute_path(const char *path ) ;
char *absolute_path(const char *path __attribute__((unused)) ) { return NULL ; }

int is_dm_device(dev_t devno ) ;
int is_dm_device(dev_t devno __attribute__((unused)) )
{ return 0 ; }

__attribute__((noreturn))
struct path_cxt *ul_new_sysfs_path(dev_t devno __attribute__((unused)), struct path_cxt *parent __attribute__((unused)), const char *prefix __attribute__((unused)))
{
	__fortify_fail( "ul_new_sysfs_path()\n" ) ;
}

__attribute__((noreturn))
void ul_unref_path(struct path_cxt *pc ) ;
__attribute__((noreturn))
void ul_unref_path(struct path_cxt *pc __attribute__((unused)))
{
	__fortify_fail( "ul_unref_path()\n" ) ;
}

__attribute__((noreturn))
int ul_path_read_string(struct path_cxt *pc __attribute__((unused)), char **str __attribute__((unused)), const char *path __attribute__((unused)))
{
	__fortify_fail( "ul_path_read_string()\n" ) ;
}

__attribute__((noreturn))
int ul_path_access(struct path_cxt *pc __attribute__((unused)), int mode __attribute__((unused)), const char *path __attribute__((unused)))
{
	__fortify_fail( "ul_path_access()\n" ) ;
}

__attribute__((noreturn))
int ul_path_read_s32(struct path_cxt *pc , int32_t *res , const char *path ) ;
__attribute__((noreturn))
int ul_path_read_s32(struct path_cxt *pc __attribute__((unused)), int32_t *res __attribute__((unused)), const char *path __attribute__((unused)))
{
	__fortify_fail( "ul_path_read_s32()\n" ) ;
}

__attribute__((noreturn))
int ul_path_readf_s32(struct path_cxt *pc , int32_t *res , const char *path , ...) ;
__attribute__((noreturn))
int ul_path_readf_s32(struct path_cxt *pc __attribute__((unused)), int32_t *res __attribute__((unused)), const char *path __attribute__((unused)), ...)
{
	__fortify_fail( "ul_path_readf_s32()\n" ) ;
}

__attribute__((noreturn))
int ul_path_read_s64(struct path_cxt *pc , int64_t *res , const char *path ) ;
__attribute__((noreturn))
int ul_path_read_s64(struct path_cxt *pc __attribute__((unused)), int64_t *res __attribute__((unused)), const char *path __attribute__((unused)))
{
	__fortify_fail( "ul_path_read_s64()\n" ) ;
}

__attribute__((noreturn))
int ul_path_read_u64(struct path_cxt *pc ,uint64_t *res , const char *path ) ;
__attribute__((noreturn))
int ul_path_read_u64(struct path_cxt *pc __attribute__((unused)), uint64_t *res __attribute__((unused)), const char *path __attribute__((unused)))
{
	__fortify_fail( "ul_path_read_u64()\n" ) ;
}

__attribute__((noreturn))
int ul_path_readf_majmin(struct path_cxt *pc , dev_t *res , const char *path , ...);
__attribute__((noreturn))
int ul_path_readf_majmin(struct path_cxt *pc __attribute__((unused)), dev_t *res __attribute__((unused)), const char *path __attribute__((unused)), ...)
{
	__fortify_fail( "ul_path_readf_majmin()\n" ) ;
}

__attribute__((noreturn))
void ul_ref_path(struct path_cxt *pc __attribute__((unused)))
{
	__fortify_fail( "ul_ref_path()\n" ) ;
}

__attribute__((noreturn))
int ul_path_set_prefix(struct path_cxt *pc __attribute__((unused)), const char *prefix __attribute__((unused)))
{
	__fortify_fail( "ul_path_set_prefix()\n" ) ;
}

__attribute__((noreturn))
const char *ul_path_get_prefix(struct path_cxt *pc __attribute__((unused)))
{
	__fortify_fail( "ul_path_get_prefix()\n" ) ;
}

__attribute__((noreturn))
int ul_path_set_dir(struct path_cxt *pc __attribute__((unused)), const char *dir __attribute__((unused)))
{
	__fortify_fail( "ul_path_set_dir()\n" ) ;
}

__attribute__((noreturn))
int ul_path_set_dialect(struct path_cxt *pc __attribute__((unused)), void *data __attribute__((unused)), void free_data(struct path_cxt *) __attribute__((unused)))
{
	__fortify_fail( "ul_path_set_dialect()\n" ) ;
}

__attribute__((noreturn))
void *ul_path_get_dialect(struct path_cxt *pc __attribute__((unused)))
{
	__fortify_fail( "ul_path_get_dialect()\n" ) ;
}

__attribute__((noreturn))
int ul_path_set_enoent_redirect(struct path_cxt *pc __attribute__((unused)), int (*func)(struct path_cxt *, const char *, int *) __attribute__((unused)))
{
	__fortify_fail( "ul_path_set_enoent_redirect()\n" ) ;
}

__attribute__((noreturn))
int ul_path_get_dirfd(struct path_cxt *pc __attribute__((unused)))
{
	__fortify_fail( "ul_path_get_dirfd()\n" ) ;
}

__attribute__((noreturn))
struct path_cxt *ul_new_path(const char *dir __attribute__((unused)), ...)
{
	__fortify_fail( "ul_new_path()\n" ) ;
}

__attribute__((noreturn))
DIR *ul_path_opendir(struct path_cxt *pc __attribute__((unused)), const char *path __attribute__((unused)))
{
	__fortify_fail( "ul_path_opendir()\n" ) ;
}

__attribute__((noreturn))
ssize_t ul_path_readlink(struct path_cxt *pc __attribute__((unused)), char *buf __attribute__((unused)), size_t bufsiz __attribute__((unused)), const char *path __attribute__((unused)))
{
	__fortify_fail( "ul_path_readlink()\n" ) ;
}

__attribute__((noreturn))
int dup_fd_cloexec(int oldfd , int lowfd ) ;
__attribute__((noreturn))
int dup_fd_cloexec(int oldfd __attribute__((unused)), int lowfd __attribute__((unused)))
{
	__fortify_fail( "dup_fd_cloexec()\n" ) ;
}

__attribute__((noreturn))
int sysfs_blkdev_set_parent(struct path_cxt *pc , struct path_cxt *parent ) ;
__attribute__((noreturn))
int sysfs_blkdev_set_parent(struct path_cxt *pc __attribute__((unused)), struct path_cxt *parent __attribute__((unused)))
{
	__fortify_fail( "sysfs_blkdev_set_parent()\n" ) ;
}

__attribute__((noreturn))
extern char * blkid_devno_to_devname( dev_t ) ;
__attribute__((noreturn))
char * blkid_devno_to_devname( dev_t dev __attribute__((unused)) )
{
	__fortify_fail( "blkid_devno_to_devname()\n" ) ;
}

extern int blkid_devno_to_wholedisk( dev_t , char* , size_t , dev_t* ) ;
int blkid_devno_to_wholedisk( dev_t dev __attribute__((unused)) ,
	char* diskname __attribute__((unused)) ,
	size_t len __attribute__((unused)) ,
	dev_t* diskdevno __attribute__((unused)) )
{
	errno = EINVAL ;
	return -1 ;
	/*<<>>*/
	/*__fortify_fail( "blkid_devno_to_wholedisk()\n" ) ;*/
}

__attribute__((noreturn))
int blkid_driver_has_major( const char* , int ) ;
__attribute__((noreturn))
int blkid_driver_has_major( const char* drvname __attribute((unused)) ,
	int major __attribute((unused)) )
{
	__fortify_fail( "blkid_driver_has_major()\n" ) ;
}

/* récupéré la taille dans libblkidP.h */
struct blkid_idinfo {
	char name[ 64 ] ;
} ;

extern const struct blkid_idinfo dm_tp_idinfo;
const struct blkid_idinfo dm_tp_idinfo =
{
	.name		= "dm",
} ;

extern const struct blkid_idinfo lvm_tp_idinfo;
const struct blkid_idinfo lvm_tp_idinfo =
{
	.name		= "lvm",
} ;


