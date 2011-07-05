#include "header.h"
#include "font_directory_table.h"
struct maxp_table: public table{
     uint32 version;
     uint16 numGlyphs;
     uint16	maxPoints;//points in non-compound glyph
     uint16	maxContours;//contours in non-compound glyph
     uint16	maxComponentPoints;//points in compound glyph
     uint16	maxComponentContours;//contours in compound glyph
     uint16	maxZones;//set to 2
     uint16	maxTwilightPoints;//	points used in Twilight Zone (Z0)
     uint16	maxStorage;	//number of Storage Area locations
     uint16	maxFunctionDefs;//	number of FDEFs
     uint16	maxInstructionDefs;//	number of IDEFs
     uint16	maxStackElements;//	maximum stack depth
     uint16	maxSizeOfInstructions;//	byte count for glyph instructions
     uint16	maxComponentElements;//	number of glyphs referenced at top level
     uint16	maxComponentDepth;//	levels of recursion, set to 0 if font has only simple glyphs
     virtual void printTable(char* path);
     virtual uint32 getSize();
};
extern void gener_maxp_table(maxp_table &mt,uint16 numGlyphs, short param[12]);
extern void gener_maxp_table_header(TableDirectoryNod &tdn,uint32 offSet);
