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
#define _GNU_SOURCE
#include "libmy.h"
#include <sys/cdefs.h>
#include <stdlib.h>
static void exch(char* base,size_t size,size_t a,size_t b) {
	char* x=base+a*size;
	char* y=base+b*size;
	while (size) {
		char z=*x;
		*x=*y;
		*y=z;
		--size; ++x; ++y;
	}
}
typedef int (*fcompar)(const void*,const void*,void*) ;
#define MID
/* Quicksort with 3-way partitioning, ala Sedgewick */
/* Blame him for the scary variable names */
/* http://www.cs.princeton.edu/~rs/talks/QuicksortIsOptimal.pdf */
static void quicksort(char* base,size_t size,ssize_t l,ssize_t r,
	fcompar compar,
	void * d)
{
	ssize_t i=l-1, j=r, p=l-1, q=r, k;
	char* v=base+r*size;
	if (r<=l) return;
#ifdef RAND
	/*
	 We chose the rightmost element in the array to be sorted as pivot,
	 which is OK if the data is random, but which is horrible if the
	 data is already sorted.  Try to improve by exchanging it with a
	 random other pivot.
	 */
	exch(base,size,l+(rand_i()%(r-l)),r);
#elif defined MID
	/*
	 We chose the rightmost element in the array to be sorted as pivot,
	 which is OK if the data is random, but which is horrible if the
	 data is already sorted.  Try to improve by chosing the middle
	 element instead.
	 */
	exch(base,size,l+(r-l)/2,r);
#endif
	for (;;) {
		while (++i != r && compar(base+i*size,v,d)<0) ;
		while (compar(v,base+(--j)*size,d)<0) if (j == l) break;
		if (i >= j) break;
		exch(base,size,i,j);
		if (compar(base+i*size,v,d)==0) exch(base,size,++p,i);
		if (compar(v,base+j*size,d)==0) exch(base,size,j,--q);
	}
	exch(base,size,i,r); j = i-1; ++i;
	for (k=l; k<p; k++, j--) exch(base,size,k,j);
	for (k=r-1; k>q; k--, i++) exch(base,size,i,k);
	quicksort(base,size,l,j,compar,d);
	quicksort(base,size,i,r,compar,d);
}
void qsort_r(void* base,size_t nmemb,size_t size,
	int (*compar)(const void*,const void*,void *),
	void *data)
{
	/* check for integer overflows */
	if (nmemb >= (((size_t)-1)>>1) ||
		size >= (((size_t)-1)>>1)) return;
	if (nmemb>1)
		quicksort(base,size,0,nmemb-1,compar,data);
}
/* on va faire une conversion de type de fonction
 en faisant passer la fonction à deux arguments pour
 une fonction à trois arguments : avec l'ABI C ça
 se passe bien puisque c'est le dernier argument qui
 est empilé en premier */
#pragma GCC diagnostic ignored "-Wcast-function-type"
void qsort(void* base,size_t nmemb,size_t size,
	int (*compar)(const void*,const void*))
{
	/* check for integer overflows */
	if (nmemb >= (((size_t)-1)>>1) ||
		size >= (((size_t)-1)>>1)) return;
	if (nmemb>1)
		quicksort(base,size,0,nmemb-1,(fcompar)compar,NULL);
}
