# UEFI-fdisk

This is a port of the util-linux fdisk partitioning tool for use in a UEFI environment. It can be added as an option to the firmware boot menu like an operating system or run as an application from the UEFI Shell. When running from the shell it will accept all valid command line arguments including a block device. If run without arguments or as a firmware boot option the program will display a list of internal disks for selection. The original library can be found on SourceForge at [UEFI fdisk](https://sourceforge.net/projects/uefi-fdisk/) by bub75.

<img align="left" src="https://raw.githubusercontent.com/jpz4085/UEFI-fdisk/main/.github/images/fdisk_help.png" width=396 height=452/>

<img align="right" src="https://raw.githubusercontent.com/jpz4085/UEFI-fdisk/main/.github/images/fdisk_create.png" width=437 height=452/>

Figure 1: Display fdisk usage information. &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;
Figure 2: Create partitions and set types.

<img align="center" src="https://raw.githubusercontent.com/jpz4085/UEFI-fdisk/main/.github/images/fdisk_details.png"/>

Figure 3: Display detailed partition information.

## Requirements

Download from Releases or clone the repository.
```
git clone https://github.com/jpz4085/UEFI-fdisk.git
```
Download or clone the current [GNU-EFI](https://github.com/ncroxon/gnu-efi) library.
```
git clone https://github.com/ncroxon/gnu-efi.git
```
Download the official util-linux source code.
```
https://mirrors.edge.kernel.org/pub/linux/utils/util-linux/
```

## Build Instructions

1. Extract the util-linux source files to a temporary location.
2. Move the GNU-EFI folder inside the UEFI-fdisk folder.
3. Move the UEFI-fdisk folder inside the util-linux folder.
4. Now open a terminal at the UEFI-fdisk subdirectory.
5. Enter "make" at the prompt to build the executable.

## Addendum

The only functions not available are the commands to save or load the partition layout to disk and the ability to display colorized text. The former may be addressed in a future release. Apart from that all features should operate as expected. Refer to the fdisk manual for more information on how to use the program. Additional information about source code used in this project is provided below.

- A private "libc" library called "libmy.a" is built in the "libmy" subdirectory and is mostly built from bits imported from "dietlibc" but contains some code imported from "glibc" as well as OpenBSD.
- EFI is UTF-16 while util-linux fdisk uses UTF-8 internally and the original glue functions hand code conversions from UTF-8 to UTF-16. This process has been extended with Davipb's [UTF-8/UTF-16 converter](https://github.com/Davipb/utf8-utf16-converter) when processing command line arguments.
- For all the system calls from the standard libray we build EFI versions of functions like write(), read() and so on, all these functions are in the ".c" source files in this "." directory, not in the "libmy" subdirectory.
- If you change options in the Makefile (like enable asserts or stack checking or _FORTIFY_SOURCE or EFI_DEBUG debugging) the link should warn you that you're adding bloat to the program.
