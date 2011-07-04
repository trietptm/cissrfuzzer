#include "header.h"
#include "font_directory_table.h"
struct post_table: public table{
       uint32 version; //0x00010000 for version 1.0  0x00020000 for version 2.0 
                      //0x00025000 for version 2.5 (deprecated) 0x00030000 for version 3.0
       uint32 italicAngle;
       //Italic angle in counter-clockwise degrees from the vertical. Zero for upright text,
       short underlinePosition;//This is the suggested distance of the top of the underline
       //from the baseline (negative values indicate below baseline)
       short underlineThickness; //Suggested values for the underline thickness.
       uint32 isFixedPitch; // non-zero if the font is not proportionally spaced
       uint32 minMemType42; //isn't in use now, 0
       uint32 maxMemType42; //isn't in use now,0
       uint32 minMemType1;  //isn't in use now,0
       uint32 maxMemType1;  //isn't in use now,0
       //32 b length of header till now
       //if version not 2.0, table ends here
       //next field for v2.0 only!      p.s. v2.0 used in windows
       uint16 numGlyphs;     //same with numGlyphs in 'maxp' table!111
       uint16 * glyphNameIndex; //size=numGlyphs, ordinal number of the glyph in 'post' string tables.
       uint16 num_new_glyph;    //this is not specification variable! defined for convinience
       //Warning! it's not a number of new glyphs! it's length of names[]!
       char * names; //	Glyph names with length bytes [variable] (a Pascal string)
       //pattern of string chunk: .{1,16}[^0-9a-zA-Z]. 
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
//generating v1 and v3 tables
extern void gener_post_table_v1_3(post_table &pt,uint16 numGlyfs,uint32 ver,uint32 Angle, short underlinePos, short underlineThick, uint32 FixedPitch);
extern void gener_post_table_v2(post_table &pt,uint16 numGlyfs, uint16 new_glyfs_size, uint16* glyphIndex ,char* names);
extern void gener_post_table_header(TableDirectoryNod &tdn, uint32 length,uint32 offSet);
