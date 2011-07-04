#include "header.h"

struct cmap_encoding_record{
       uint16	platformID;	//Platform identifier
       uint16	platformSpecificID;	//Platform-specific encoding identifier
       uint32	offset; //offset of the mapping table
};
struct cmap_base{
       uint16 format;    //format
       uint16 length;    //length of subtable
       uint16 language;  //language ID   
};
//each of subtable has 1 of the 7 possible formats
//Windows uses only 0,4 and 6 format 
//often number of subtables is few (1-3)
//Format 0: Byte encoding table
struct format_0_table : public cmap_base{
       char glyphIdArray[256];      //1 to 1 mapping char-glyph, it's some kind of permutation
       //glyph_id=(int)glyphIdArray[number_of_symbol]
};
//Format 4: Segment mapping to delta values
//this format uses when characters isn't forming contiguous range
struct format_4_table : public cmap_base{
       uint16 format;//format #4
       uint16 length;               //length of subtable
       uint16 language;             //language ID
       uint16 segCountX2;           //number of segments of characters, multiplied by 2
       uint16 searchRange;          //2 * (2^FLOOR(log2(segCount))) 
       uint16 rangeShift;           //segCountX2 - searchRange
       uint16 * endCode;            //size:segCountX2/2, Ending character code for each segment
                                    //last element - 0xFFFF
       uint16 reversePad;           //set to 0
       uint16 * startCode;          //size:segCountX2/2, Starting character code for each segment
       short * idDelta;              //size:segCountX2/2, Delta (shifting) for all character codes in segment
       uint16 * idRangeOffset;       //size:segCountX2/2, Offset in bytes for glyph indexArray, or 0
       uint16 * glyphIndxArray;      //array of glyph indecies
};
//Format 6: Trimmed table mapping
//It should be used when character codes for a font fall into a single contiguous range
//if range isn't contigious, we should use format #4
struct format_6_table : public cmap_base{
       static const uint16	format=6;	//Format number is set to 6
       uint16	length;	        //Length in bytes of subtable
       uint16	language;	    //Language code for this encoding subtable, or zero if language-independent
       uint16	firstCode;	    //First character code of subrange
       uint16	entryCount;	    //Number of character codes in subrange
       uint16	glyphIndexArray[];	//Array of glyph index values for character codes in the range 
       //glyphIndexArray[entryCount]   
};
struct cmap_table:public table{
       uint16 version;
       uint16 numTables;
       cmap_encoding_record * encodingRecords;//number of records equals numTables
       cmap_base * subTables; //number of subtables equals numTables
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
//procedure of generating format_0_table
extern format_0_table gener_format_0_table( char GlyphIdArray[256], unsigned short lang);
extern format_6_table gener_format_6_table(uint16 segNum, uint16 *startSeg, uint16 *endSeg, short *delta, uint16 *rangeOffset, uint16 *glyfId);


