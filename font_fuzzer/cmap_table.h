#include "header.h"
#include "font_directory_table.h"
struct cmap_encoding_record{
       uint16	platformID;	//Platform identifier
       uint16	platformSpecificID;	//Platform-specific encoding identifier
       uint32	offset; //offset of the mapping table
};
struct cmap_base{
       uint16 format;    //format
       uint16 length;    //length of subtable
       uint16 language;  //language ID
       virtual uint32 getLength()=0;  //return length in byte of subtable
       virtual void Print(ofstream &of)=0;//for printing
       virtual string toString()=0;
};
//each of subtable has 1 of the 7 possible formats
//Windows uses only 0,4 and 6 format 
//often number of subtables is few (1-3)
//Format 0: Byte encoding table
struct format_0_table : public cmap_base{
       char glyphIdArray[256];      //1 to 1 mapping char-glyph, it's some kind of permutation
       //glyph_id=(int)glyphIdArray[number_of_symbol]
       virtual uint32 getLength();
       virtual void Print(ofstream &of);
       virtual string toString();//warning! string contain hex vvalues, it's not readable
};
//Format 4: Segment mapping to delta values
//this format uses when characters isn't forming contiguous range
struct format_4_table : public cmap_base{
       uint16 segCountX2;           //number of segments of characters, multiplied by 2
       uint16 searchRange;          //2 * (2^FLOOR(log2(segCount))) 
       uint16 entrySelector;
       uint16 rangeShift;           //segCountX2 - searchRange
       uint16 * endCode;            //size:segCountX2/2, Ending character code for each segment
                                    //last element - 0xFFFF
       uint16 reversePad;           //set to 0
       uint16 * startCode;          //size:segCountX2/2, Starting character code for each segment
       short * idDelta;              //size:segCountX2/2, Delta (shifting) for all character codes in segment
       uint16 * idRangeOffset;       //size:segCountX2/2, Offset in bytes for glyph indexArray, or 0
       uint16 * glyphIndxArray;      //array of glyph indecies
       virtual uint32 getLength();
       virtual void Print(ofstream &of);
       virtual string toString();
};
//Format 6: Trimmed table mapping
//It should be used when character codes for a font fall into a single contiguous range
//if range isn't contigious, we should use format #4
struct format_6_table : public cmap_base{
       uint16	firstCode;	    //First character code of subrange
       uint16	entryCount;	    //Number of character codes in subrange
       uint16 * glyphIndexArray;	//Array of glyph index values for character codes in the range
       //glyphIndexArray[entryCount]
       virtual uint32 getLength(); 
       virtual void Print(ofstream &of); 
       virtual string toString(); 
};
struct cmap_table: public table{
       uint16 version;
       uint16 numTables;
       cmap_encoding_record * encodingRecords;//number of records equals numTables
       string * subTables; //number of subtables equals numTables
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
//procedure of generating different format subtables
//warning! before generating subtable cmap_base had to be generated!
//functions don't set language Id
extern void gener_cmap_table(cmap_table &cmt);
extern void gener_format_0_table(format_0_table &f0);
extern void gener_format_4_table(format_4_table &f4);
extern void gener_format_6_table(format_6_table &f6);
