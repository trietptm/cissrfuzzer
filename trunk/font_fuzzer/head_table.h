#include "header.h"
//#include "font_directory_table.h"
struct head_table{
       uint32 version; //any version 0x00010000 for 0.1
       uint32 revision; //any revision
       uint32 checkSum; 
       //To compute: set it to 0, calculate the checksum for the 'head' 
       //table and put it in the table directory, sum the entire font as 
       //uint32, then store B1B0AFBA - sum. The checksum for the 'head' 
       //table will not be wrong. That is OK.
       uint32 magicNumber; //set to 0x5F0F3CF5
       uint16 flags;
       /*Bit 0: Baseline for font at y=0;
       Bit 1: Left sidebearing point at x=0;
       Bit 2: Instructions may depend on point size; 
       Bit 3: Force ppem to integer values for all internal scaler math; may
        use fractional ppem sizes if this bit is clear; 
       Bit 4: Instructions may alter advance width (the advance widths might not scale linearly); 
       Bits 5-10: These should be set according to  Apple's specification .
        However, they are not implemented in OpenType. 
       Bit 11: Font data is 'lossless,' as a result of having been compressed
        and decompressed with the Agfa MicroType Express engine.
       Bit 12: Font converted (produce compatible metrics)
       Bit 13: Font optimized for ClearType™. Note, fonts that rely on 
        embedded bitmaps (EBDT) for rendering should not be considered optimized
        for ClearType, and therefore should keep this bit cleared.
       Bit 14: Last Resort font. If set, indicates that the glyphs 
        encoded in the cmap subtables are simply generic symbolic representations
        of code point ranges and don’t truly represent support for those 
        code points. If unset, indicates that the glyphs encoded in the cmap 
        subtables represent proper support for those code points.
       Bit 15: Reserved, set to 0
       */
       uint16 unitsPerEm; //Valid range is from 16 to 16384. This value should 
       //be a power of 2 for fonts that have TrueType outlines.
       unsigned __int64 created; //Number of seconds since 12:00 midnight, January 1, 1904. 64-bit integern
       unsigned __int64 modified;// see prev. comment
       //next 4 for all glyph bounding boxes.
       short xMin;
       short yMin;
       short xMax;
       short yMax;
       uint16 macStyle;
       /*Bit 0: Bold (if set to 1); 
       Bit 1: Italic (if set to 1) 
       Bit 2: Underline (if set to 1) 
       Bit 3: Outline (if set to 1) 
       Bit 4: Shadow (if set to 1) 
       Bit 5: Condensed (if set to 1) 
       Bit 6: Extended (if set to 1) 
       Bits 7-15: Reserved (set to 0).
       */
       //set this value for fuzzing like rand()%64
       uint16 lowestRecPPEM; //Smallest readable size in pixels.
       short fontDirectionHint; //deprecated, set to 2
       uint16 indexToLocFormat; //0 for short offsets, 1 for long
       uint16 glyphDataFormat; //reserved as 0      
};
extern head_table gener_head_table(short xmin, short ymin, short xmax, short ymax,uint16 unitsperEm, uint16 lowestRecPix);
extern uint32 head_table_size();
extern TableDirectoryNod gener_head_table_header(head_table ht,uint32 offSet);
