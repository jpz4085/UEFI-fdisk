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
/* Pas de double inclusion. */
#ifndef libmy_h_INCLUDED
#define libmy_h_INCLUDED
#define __dietlibc__
/* for types like size_t */
#include <stdint.h>
#include <sys/types.h>
/* This file could be included by C++ source files */
#if defined(__cplusplus)
extern "C" {
#endif
extern void __fortify_fail( const char * msg ) __attribute__((noreturn)) ;
extern int __ltostr( char * s , size_t size , long i ,
	unsigned int base , char UpCase ) ;
extern int __lltostr( char * s , size_t size , long long i ,
	unsigned int base , char UpCase ) ;
extern void * __memset_chk( void* dstpp , int c , size_t len ,
	size_t dstlen ) ;
extern void * __memcpy_chk( void* dstpp , const void* srcpp , size_t len ,
	size_t dstlen ) ;
#if defined(__cplusplus)
}
#endif
/* Locale management imported from GNU stdlib uses a lot of these macros,
   we don't need them in our simple implementation */
#define __libc_rwlock_define(CLASS,NAME)
#define __libc_lock_lock(NAME)
#define __libc_rwlock_rdlock(NAME)
#define __libc_rwlock_wrlock(NAME)
#define __libc_lock_unlock(NAME)
#define __libc_rwlock_unlock(NAME)
#define compat_symbol( libc , name1 , name2 , version )
#define __SYMBOL_PREFIX
#define libc_hidden_proto(name, attrs...)
#define libc_hidden_def(name)
#define attribute_hidden
#define internal_function      /* empty */
#define attribute_tls_model_ie __attribute__ ((tls_model ("initial-exec")))
#define weak_extern(expr)
#endif /* libmy_h_INCLUDED */
#define link_warning(symbol,msg) \
  asm (".section .gnu.warning." symbol "\n\t.string \"" msg "\"\n\t.previous");
