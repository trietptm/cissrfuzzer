
findMemcpy IDA Pro Plugin
-------------------------

The plugin was developed for the book "Reverse Engineering with IDA Pro". 

Description:
Compilers will often replace memcpy() library calls with inlined assembly language equivalents. The plugin operates on ELF and PE IA-32 binaries and searches for inlined memcpy() calls.  

.text:0308912E     mov     ecx, edx    ; ecx == number bytes to copy
.text:03089130     mov     ebx, ecx    
.text:03089132     shr     ecx, 2      ; ecx == number dwords to copy
.text:03089135     rep movsd           ; copy (ecx) dwords
.text:03089137     mov     ecx, ebx
.text:03089139     and     ecx, 3      ; ecx == remaining bytes (0-3)
.text:0308913C     rep movsb           ; copy (ecx) bytes

finMemcpy looks for rep movsd and rep movsb instructions. The plugin will record:
1. matched sets of rep movsd/rep movsb and their distance in bytes
2. solo rep movsd instructions
3. solo rep movsb instructions

The results are presented in a list using the choose2() IDA SDK call.

Usage:
The plugin will have an entry under ( Edit | Plugins | findMemcpy). The plugin by default is not bound to a hotkey.

A list will be presented displaying memcpy() equivalents as well as solo rep movsd/rep movsb instructions.

Building:
The plugin builds with Visual Studio 2005/2008 including Express Editions. The project currently assumes the location of the SDK to be:
C:\SDK\idasdk52

If the SDK is in a different location a couple options need to be updated.
The options are located under the findMemcpy Property pages. Both of options listed below must be updated to reflect the location of the SDK.

 1.  C/C++  -> General -> Additional Include Directories
 2.  Linker -> General -> Additional Library Directories

NOTE: There is a bug in all versions of the SDK. One of the #includes in \include\intel.hpp needs to changed.
  from:  #include “../idaidp.hpp”
  to:    #include “../module/idaidp.hpp
 