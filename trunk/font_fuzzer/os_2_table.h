#include "header.h"
#include "font_directory_table.h"
//we shall use simplified version of os/2 table version 0, other
//versions will be commited later
struct os_2_table:public table{
       uint16 version;// table version number (set to 0)   
       short xAvgCharWidth;// average weighted advance width of lower case letters and space   
       uint16 usWeightClass;// visual weight (degree of blackness or thickness) of stroke in glyphs   
       uint16 usWidthClass;//relative change from the normal aspect ratio (width to height ratio) as specified by a font designer for the glyphs in the font  
       short fsType;// characteristics and properties of this font (set undefined bits to zero)   
       short ySubscriptXSize; //recommended horizontal size in pixels for subscripts   
       short ySubscriptYSize; //recommended vertical size in pixels for subscripts   
       short ySubscriptXOffset; //recommended horizontal offset for subscripts   
       short ySubscriptYOffset; //recommended vertical offset form the baseline for subscripts   
       short ySuperscriptXSize; //recommended horizontal size in pixels for superscripts   
       short ySuperscriptYSize; //recommended vertical size in pixels for superscripts   
       short ySuperscriptXOffset; //recommended horizontal offset for superscripts   
       short ySuperscriptYOffset; //recommended vertical offset from the baseline for superscripts   
       short yStrikeoutSize; //width of the strikeout stroke   
       short yStrikeoutPosition;// position of the strikeout stroke relative to the baseline   
       short sFamilyClass;// classification of font-family design.   
       char panose[10];// 10 byte series of number used to describe the visual characteristics of a given typeface   
       uint32 ulCharRange[4]; //Field is split into two bit fields of 96 and 36 bits each. The low 96 bits are used to specify the Unicode blocks encompassed by the font file. The high 32 bits are used to specify the character or script sets covered by the font file. Bit assignments are pending. Set to 0   
       char achVendID[4]; //four character identifier for the font vendor   
       uint16 fsSelection; //2-byte bit field containing information concerning the nature of the font patterns   
       uint16 fsFirstCharIndex; //The minimum Unicode index in this font.   
       uint16 fsLastCharIndex; //The maximum Unicode index in this font.
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
extern void gener_os_2_table(os_2_table &ost);
