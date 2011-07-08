#include "header.h"
#include "font_directory_table.h"
struct loca_table: public table{
       uint32* offset;
       uint16 numGlyph; //non-documented parameter, only for convinience
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
extern void gener_loca_table(loca_table &ft, uint16 num_glyphs, uint32 *offset);
