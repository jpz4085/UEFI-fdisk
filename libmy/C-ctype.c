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
#include "libmy.h"
#include "locale.h"
/* Copyright (C) 1995-2013 Free Software Foundation, Inc.
 This file is part of the GNU C Library.
 Contributed by Ulrich Drepper <drepper@cygnus.com>, 1995.
 The GNU C Library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 The GNU C Library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public
 License along with the GNU C Library; if not, see
 <http://www.gnu.org/licenses/>.  */
#include "localeinfo.h"
/*#include "C-translit.h"*/
#define NTRANSLIT 13
static const uint32_t translit_from_idx[] = {} ;
static const uint32_t translit_from_tbl[] = {} ;
static const uint32_t translit_to_idx[] = {} ;
static const uint32_t translit_to_tbl[] = {} ;
/* This table's entries are taken from POSIX.2 Table 2-6
 ``LC_CTYPE Category Definition in the POSIX Locale''.
 The `_nl_C_LC_CTYPE_width' array is a GNU extension.
 In the `_nl_C_LC_CTYPE_class' array the value for EOF (== -1)
 is set to always return 0 and the conversion arrays return EOF.  */
const char _nl_C_LC_CTYPE_class32[1024] attribute_hidden =
 /* 0x00 */ "\000\000\002\000" "\000\000\002\000" "\000\000\002\000"
 /* 0x03 */ "\000\000\002\000" "\000\000\002\000" "\000\000\002\000"
 /* 0x06 */ "\000\000\002\000" "\000\000\002\000" "\000\000\002\000"
 /* 0x09 */ "\000\000\003\040" "\000\000\002\040" "\000\000\002\040"
 /* 0x0c */ "\000\000\002\040" "\000\000\002\040" "\000\000\002\000"
 /* 0x0f */ "\000\000\002\000" "\000\000\002\000" "\000\000\002\000"
 /* 0x12 */ "\000\000\002\000" "\000\000\002\000" "\000\000\002\000"
 /* 0x15 */ "\000\000\002\000" "\000\000\002\000" "\000\000\002\000"
 /* 0x18 */ "\000\000\002\000" "\000\000\002\000" "\000\000\002\000"
 /* 0x1b */ "\000\000\002\000" "\000\000\002\000" "\000\000\002\000"
 /* 0x1e */ "\000\000\002\000" "\000\000\002\000" "\000\000\001\140"
 /* 0x21 */ "\000\000\004\300" "\000\000\004\300" "\000\000\004\300"
 /* 0x24 */ "\000\000\004\300" "\000\000\004\300" "\000\000\004\300"
 /* 0x27 */ "\000\000\004\300" "\000\000\004\300" "\000\000\004\300"
 /* 0x2a */ "\000\000\004\300" "\000\000\004\300" "\000\000\004\300"
 /* 0x2d */ "\000\000\004\300" "\000\000\004\300" "\000\000\004\300"
 /* 0x30 */ "\000\000\010\330" "\000\000\010\330" "\000\000\010\330"
 /* 0x33 */ "\000\000\010\330" "\000\000\010\330" "\000\000\010\330"
 /* 0x36 */ "\000\000\010\330" "\000\000\010\330" "\000\000\010\330"
 /* 0x39 */ "\000\000\010\330" "\000\000\004\300" "\000\000\004\300"
 /* 0x3c */ "\000\000\004\300" "\000\000\004\300" "\000\000\004\300"
 /* 0x3f */ "\000\000\004\300" "\000\000\004\300" "\000\000\010\325"
 /* 0x42 */ "\000\000\010\325" "\000\000\010\325" "\000\000\010\325"
 /* 0x45 */ "\000\000\010\325" "\000\000\010\325" "\000\000\010\305"
 /* 0x48 */ "\000\000\010\305" "\000\000\010\305" "\000\000\010\305"
 /* 0x4b */ "\000\000\010\305" "\000\000\010\305" "\000\000\010\305"
 /* 0x4e */ "\000\000\010\305" "\000\000\010\305" "\000\000\010\305"
 /* 0x51 */ "\000\000\010\305" "\000\000\010\305" "\000\000\010\305"
 /* 0x54 */ "\000\000\010\305" "\000\000\010\305" "\000\000\010\305"
 /* 0x57 */ "\000\000\010\305" "\000\000\010\305" "\000\000\010\305"
 /* 0x5a */ "\000\000\010\305" "\000\000\004\300" "\000\000\004\300"
 /* 0x5d */ "\000\000\004\300" "\000\000\004\300" "\000\000\004\300"
 /* 0x60 */ "\000\000\004\300" "\000\000\010\326" "\000\000\010\326"
 /* 0x63 */ "\000\000\010\326" "\000\000\010\326" "\000\000\010\326"
 /* 0x66 */ "\000\000\010\326" "\000\000\010\306" "\000\000\010\306"
 /* 0x69 */ "\000\000\010\306" "\000\000\010\306" "\000\000\010\306"
 /* 0x6c */ "\000\000\010\306" "\000\000\010\306" "\000\000\010\306"
 /* 0x6f */ "\000\000\010\306" "\000\000\010\306" "\000\000\010\306"
 /* 0x72 */ "\000\000\010\306" "\000\000\010\306" "\000\000\010\306"
 /* 0x75 */ "\000\000\010\306" "\000\000\010\306" "\000\000\010\306"
 /* 0x78 */ "\000\000\010\306" "\000\000\010\306" "\000\000\010\306"
 /* 0x7b */ "\000\000\004\300" "\000\000\004\300" "\000\000\004\300"
 /* 0x7e */ "\000\000\004\300" "\000\000\002\000" "\000\000\000\000"
 /* 0x81 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x84 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x87 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x8a */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x8d */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x90 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x93 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x96 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x99 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x9c */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0x9f */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xa2 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xa5 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xa8 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xab */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xae */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xb1 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xb4 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xb7 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xba */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xbd */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xc0 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xc3 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xc6 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xc9 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xcc */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xcf */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xd2 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xd5 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xd8 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xdb */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xde */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xe1 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xe4 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xe7 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xea */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xed */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xf0 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xf3 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xf6 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xf9 */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xfc */ "\000\000\000\000" "\000\000\000\000" "\000\000\000\000"
 /* 0xff */ "\000\000\000\000"
;
#define STRUCT_CTYPE_CLASS(p, q) \
 struct \
  { \
   uint32_t isctype_data[8]; \
   uint32_t header[5]; \
   uint32_t level1[1]; \
   uint32_t level2[1 << q]; \
   uint32_t level3[1 << p]; \
  }
const STRUCT_CTYPE_CLASS(1, 1) _nl_C_LC_CTYPE_class_upper attribute_hidden =
{
 { 0x00000000, 0x00000000, 0x07fffffe, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 7, 1, 6, 1, 1 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 0, 8 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x07fffffe, 0x00000000 }
};
const STRUCT_CTYPE_CLASS(1, 1) _nl_C_LC_CTYPE_class_lower attribute_hidden =
{
 { 0x00000000, 0x00000000, 0x00000000, 0x07fffffe,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 7, 1, 6, 1, 1 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 0, 8 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x00000000, 0x07fffffe }
};
const STRUCT_CTYPE_CLASS(1, 1) _nl_C_LC_CTYPE_class_alpha attribute_hidden =
{
 { 0x00000000, 0x00000000, 0x07fffffe, 0x07fffffe,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 7, 1, 6, 1, 1 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 0, 8 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x07fffffe, 0x07fffffe }
};
const STRUCT_CTYPE_CLASS(1, 0) _nl_C_LC_CTYPE_class_digit attribute_hidden =
{
 { 0x00000000, 0x03ff0000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 6, 1, 6, 0, 1 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 7 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x00000000, 0x03ff0000 }
};
const STRUCT_CTYPE_CLASS(2, 0) _nl_C_LC_CTYPE_class_xdigit attribute_hidden =
{
 { 0x00000000, 0x03ff0000, 0x0000007e, 0x0000007e,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 7, 1, 7, 0, 3 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 7 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x00000000, 0x03ff0000, 0x0000007e, 0x0000007e }
};
const STRUCT_CTYPE_CLASS(1, 0) _nl_C_LC_CTYPE_class_space attribute_hidden =
{
 { 0x00003e00, 0x00000001, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 6, 1, 6, 0, 1 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 7 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x00003e00, 0x00000001 }
};
const STRUCT_CTYPE_CLASS(2, 0) _nl_C_LC_CTYPE_class_print attribute_hidden =
{
 { 0x00000000, 0xffffffff, 0xffffffff, 0x7fffffff,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 7, 1, 7, 0, 3 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 7 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x00000000, 0xffffffff, 0xffffffff, 0x7fffffff }
};
const STRUCT_CTYPE_CLASS(2, 0) _nl_C_LC_CTYPE_class_graph attribute_hidden =
{
 { 0x00000000, 0xfffffffe, 0xffffffff, 0x7fffffff,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 7, 1, 7, 0, 3 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 7 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x00000000, 0xfffffffe, 0xffffffff, 0x7fffffff }
};
const STRUCT_CTYPE_CLASS(1, 0) _nl_C_LC_CTYPE_class_blank attribute_hidden =
{
 { 0x00000200, 0x00000001, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 6, 1, 6, 0, 1 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 7 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x00000200, 0x00000001 }
};
const STRUCT_CTYPE_CLASS(2, 0) _nl_C_LC_CTYPE_class_cntrl attribute_hidden =
{
 { 0xffffffff, 0x00000000, 0x00000000, 0x80000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 7, 1, 7, 0, 3 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 7 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0xffffffff, 0x00000000, 0x00000000, 0x80000000 }
};
const STRUCT_CTYPE_CLASS(2, 0) _nl_C_LC_CTYPE_class_punct attribute_hidden =
{
 { 0x00000000, 0xfc00fffe, 0xf8000001, 0x78000001,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 7, 1, 7, 0, 3 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 7 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x00000000, 0xfc00fffe, 0xf8000001, 0x78000001 }
};
const STRUCT_CTYPE_CLASS(2, 0) _nl_C_LC_CTYPE_class_alnum attribute_hidden =
{
 { 0x00000000, 0x03ff0000, 0x07fffffe, 0x07fffffe,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 },
 { 7, 1, 7, 0, 3 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 7 * sizeof (uint32_t) },
 /* 3rd-level table */
 { 0x00000000, 0x03ff0000, 0x07fffffe, 0x07fffffe }
};
const struct
{
 uint32_t header[5];
 uint32_t level1[1];
 uint32_t level2[4];
 int32_t level3[32];
}
_nl_C_LC_CTYPE_map_toupper attribute_hidden =
{
 { 7, 1, 5, 3, 31 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 0, 0, 0, 10 * sizeof (uint32_t) },
 /* 3rd-level table */
 {
  0x00000000, 0xffffffe0, 0xffffffe0, 0xffffffe0,
  0xffffffe0, 0xffffffe0, 0xffffffe0, 0xffffffe0,
  0xffffffe0, 0xffffffe0, 0xffffffe0, 0xffffffe0,
  0xffffffe0, 0xffffffe0, 0xffffffe0, 0xffffffe0,
  0xffffffe0, 0xffffffe0, 0xffffffe0, 0xffffffe0,
  0xffffffe0, 0xffffffe0, 0xffffffe0, 0xffffffe0,
  0xffffffe0, 0xffffffe0, 0xffffffe0, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 }
},
_nl_C_LC_CTYPE_map_tolower attribute_hidden =
{
 { 7, 1, 5, 3, 31 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 { 0, 0, 10 * sizeof (uint32_t), 0 },
 /* 3rd-level table */
 {
  0x00000000, 0x00000020, 0x00000020, 0x00000020,
  0x00000020, 0x00000020, 0x00000020, 0x00000020,
  0x00000020, 0x00000020, 0x00000020, 0x00000020,
  0x00000020, 0x00000020, 0x00000020, 0x00000020,
  0x00000020, 0x00000020, 0x00000020, 0x00000020,
  0x00000020, 0x00000020, 0x00000020, 0x00000020,
  0x00000020, 0x00000020, 0x00000020, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000
 }
};
const struct
{
 uint32_t header[5];
 uint32_t level1[1];
 uint32_t level2[8];
 int8_t level3[33];
}
_nl_C_LC_CTYPE_width attribute_hidden =
{
 { 7, 1, 4, 7, 15 },
 /* 1st-level table */
 { 6 * sizeof (uint32_t) },
 /* 2nd-level table */
 {
  14 * sizeof (uint32_t) +  0, 0,
  14 * sizeof (uint32_t) + 16, 14 * sizeof (uint32_t) + 16,
  14 * sizeof (uint32_t) + 16, 14 * sizeof (uint32_t) + 16,
  14 * sizeof (uint32_t) + 16, 14 * sizeof (uint32_t) + 17
 },
 /* 3rd-level table */
 {
   0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
   -1
 }
};
/* Number of fields with fixed meanings, starting at 0.  */
#define NR_FIXED 72
/* Number of class fields, starting at CLASS_OFFSET.  */
#define NR_CLASSES 12
/* Number of map fields, starting at MAP_OFFSET.  */
#define NR_MAPS 2
/* Compile time verification of
  NR_FIXED == _NL_ITEM_INDEX (_NL_CTYPE_EXTRA_MAP_1). */
typedef int assertion1[1 - 2 * (NR_FIXED != _NL_ITEM_INDEX (_NL_CTYPE_EXTRA_MAP_1))];
extern const char _nl_C_LC_CTYPE_class[] ;
extern const uint32_t _nl_C_LC_CTYPE_toupper[] ;
extern const uint32_t _nl_C_LC_CTYPE_tolower[] ;
const struct __locale_data _nl_C_LC_CTYPE =
{
 _nl_C_name,
 NULL, 0, 0,			/* no file mapped */
 { NULL, },			/* no cached data */
 UNDELETABLE,
 1,		/* Enable transliteration by default.  */
 NR_FIXED + NR_CLASSES + NR_MAPS,
 {
  /* _NL_CTYPE_CLASS */
  { .string = _nl_C_LC_CTYPE_class },
  /* _NL_CTYPE_TOUPPER */
  { .string = (const char *) _nl_C_LC_CTYPE_toupper },
  /* _NL_CTYPE_GAP1 */
  { .string = NULL },
  /* _NL_CTYPE_TOLOWER */
  { .string = (const char *) _nl_C_LC_CTYPE_tolower },
  /* _NL_CTYPE_GAP2 */
  { .string = NULL },
  /* _NL_CTYPE_CLASS32 */
  { .string = NULL },
  /* _NL_CTYPE_GAP3 */
  { .string = NULL },
  /* _NL_CTYPE_GAP4 */
  { .string = NULL },
  /* _NL_CTYPE_GAP5 */
  { .string = NULL },
  /* _NL_CTYPE_GAP6 */
  { .string = NULL },
  /* _NL_CTYPE_CLASS_NAMES */
  { .string = "upper\0" "lower\0" "alpha\0" "digit\0" "xdigit\0" "space\0"
   "print\0" "graph\0" "blank\0" "cntrl\0" "punct\0"  "alnum\0"
#ifdef PREDEFINED_CLASSES
   "left_to_right\0" "right_to_left\0" "num_terminator\0"
   "num_separator\0" "segment_separator\0" "block_separator\0"
   "direction_control\0" "sym_swap_layout\0" "char_shape_selector\0"
   "num_shape_selector\0" "non_spacing\0" "non_spacing_level3\0"
   "r_connect\0" "no_connect\0" "no_connect-space\0"
   "vowel_connect\0"
#endif
  },
  /* _NL_CTYPE_MAP_NAMES */
  { .string = "toupper\0" "tolower\0"
#ifdef PREDEFINED_CLASSES
   "tosymmetric\0"
#endif
  },
  /* _NL_CTYPE_WIDTH */
  { .string = (const char *) _nl_C_LC_CTYPE_width.header },
  /* _NL_CTYPE_MB_CUR_MAX */
  { .word = 1 },
  /* _NL_CTYPE_CODESET_NAME */
  { .string = _nl_C_codeset },
  /* _NL_CTYPE_TOUPPER32 */
  { .string = (const char *) &_nl_C_LC_CTYPE_toupper[128] },
  /* _NL_CTYPE_TOLOWER32 */
  { .string = (const char *) &_nl_C_LC_CTYPE_tolower[128] },
  /* _NL_CTYPE_CLASS_OFFSET */
  { .word = NR_FIXED },
  /* _NL_CTYPE_MAP_OFFSET */
  { .word = NR_FIXED + NR_CLASSES },
  /* _NL_CTYPE_INDIGITS_MB_LEN */
  { .word = 1 },
  /* _NL_CTYPE_INDIGITS0_MB .. _NL_CTYPE_INDIGITS9_MB */
  { .string = "0" },
  { .string = "1" },
  { .string = "2" },
  { .string = "3" },
  { .string = "4" },
  { .string = "5" },
  { .string = "6" },
  { .string = "7" },
  { .string = "8" },
  { .string = "9" },
  /* _NL_CTYPE_INDIGITS_WC_LEN */
  { .word = 1 },
  /* _NL_CTYPE_INDIGITS0_WC .. _NL_CTYPE_INDIGITS9_WC */
  { .wstr = (uint32_t *) L"0" },
  { .wstr = (uint32_t *) L"1" },
  { .wstr = (uint32_t *) L"2" },
  { .wstr = (uint32_t *) L"3" },
  { .wstr = (uint32_t *) L"4" },
  { .wstr = (uint32_t *) L"5" },
  { .wstr = (uint32_t *) L"6" },
  { .wstr = (uint32_t *) L"7" },
  { .wstr = (uint32_t *) L"8" },
  { .wstr = (uint32_t *) L"9" },
  /* _NL_CTYPE_OUTDIGIT0_MB .. _NL_CTYPE_OUTDIGIT9_MB */
  { .string = "0" },
  { .string = "1" },
  { .string = "2" },
  { .string = "3" },
  { .string = "4" },
  { .string = "5" },
  { .string = "6" },
  { .string = "7" },
  { .string = "8" },
  { .string = "9" },
  /* _NL_CTYPE_OUTDIGIT0_WC .. _NL_CTYPE_OUTDIGIT9_WC */
  { .word = L'0' },
  { .word = L'1' },
  { .word = L'2' },
  { .word = L'3' },
  { .word = L'4' },
  { .word = L'5' },
  { .word = L'6' },
  { .word = L'7' },
  { .word = L'8' },
  { .word = L'9' },
  /* _NL_CTYPE_TRANSLIT_TAB_SIZE */
  { .word = NTRANSLIT },
  /* _NL_CTYPE_TRANSLIT_FROM_IDX */
  { .wstr = translit_from_idx },
  /* _NL_CTYPE_TRANSLIT_FROM_TBL */
  { .wstr = (uint32_t *) translit_from_tbl },
  /* _NL_CTYPE_TRANSLIT_TO_IDX */
  { .wstr = translit_to_idx },
  /* _NL_CTYPE_TRANSLIT_TO_TBL */
  { .wstr = (uint32_t *) translit_to_tbl },
  /* _NL_CTYPE_TRANSLIT_DEFAULT_MISSING_LEN */
  { .word = 1 },
  /* _NL_CTYPE_TRANSLIT_DEFAULT_MISSING */
  { .wstr = (uint32_t *) L"?" },
  /* _NL_CTYPE_TRANSLIT_IGNORE_LEN */
  { .word = 0 },
  /* _NL_CTYPE_TRANSLIT_IGNORE */
  { .wstr = NULL },
  /* _NL_CTYPE_MAP_TO_NONASCII */
  { .word = 0 },
  /* _NL_CTYPE_NONASCII_CASE */
  { .word = 0 },
  /* NR_CLASSES wctype_tables */
  { .string = (const char *) _nl_C_LC_CTYPE_class_upper.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_lower.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_alpha.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_digit.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_xdigit.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_space.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_print.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_graph.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_blank.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_cntrl.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_punct.header },
  { .string = (const char *) _nl_C_LC_CTYPE_class_alnum.header },
  /* NR_MAPS wctrans_tables */
  { .string = (const char *) _nl_C_LC_CTYPE_map_toupper.header },
  { .string = (const char *) _nl_C_LC_CTYPE_map_tolower.header }
 }
};
