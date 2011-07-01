#include "header.h"
extern uint16 cmap_version;
extern uint16 cmap_numberSubtables;
struct enc_subtable{
       uint16	platformID;	//Platform identifier
       uint16	platformSpecificID;	//Platform-specific encoding identifier
       uint32	offset; //offset of the mapping table
};
//each of subtable has 1 of the 7 possible formats:
//Format 0: Byte encoding table
//This is the Apple standard character to glyph index mapping table.
struct format_0_table{
       uint16 format;               //format=0
       uint16 length;               //length of subtable
       uint16 language;             //language id
       char glyphIdArray[256];      //1 to 1 mapping char-glyph
       //glyph_id=(int)glyphIdArray[number_of_symbol]
};
//procedure of generating format_0_table
extern format_0_table gener_format_0_table( char GlyphIdArray[256], unsigned short lang);
//Format 2: High-byte mapping through table
//This subtable is useful for the national character code standards used for
//Japanese, Chinese, and Korean characters.
//That's why i've skipped it. 
//I planned to build this table later
struct format_2_table{      
};
//Format 4: Segment mapping to delta values
//this format uses when characters isn't forming contiguous range
struct format_4_table{
       static const uint16 format=4;//format #4
       uint16 length;               //length of subtable
       uint16 language;             //language ID
       uint16 segCountX2;           //number of segments of characters, multiplied by 2
       uint16 searchRange;          //2 * (2^FLOOR(log2(segCount))) 
       uint16 rangeShift;           //segCountX2 - searchRange
       uint16 endCode[];            //size:segCountX2/2, Ending character code for each segment
                                    //last element - 0xFFFF
       static const uint16 reversePad=0;    
       uint16 startCode[];          //size:segCountX2/2, Starting character code for each segment
       short idDelta[];              //size:segCountX2/2, Delta (shifting) for all character codes in segment
       uint16 idRangeOffset[];       //size:segCountX2/2, Offset in bytes for glyph indexArray, or 0
       uint16 glyphIndxArray[];        //array of glyph index
};
//Format 6: Trimmed table mapping
//It should be used when character codes for a font fall into a single contiguous range
//if range isn't contigious, we should use format #4
struct format_6_table{
       static const uint16	format=6;	//Format number is set to 6
       uint16	length;	        //Length in bytes of subtable
       uint16	language;	    //Language code for this encoding subtable, or zero if language-independent
       uint16	firstCode;	    //First character code of subrange
       uint16	entryCount;	    //Number of character codes in subrange
       uint16	glyphIndexArray[];	//Array of glyph index values for character codes in the range 
       //glyphIndexArray[entryCount]   
};
