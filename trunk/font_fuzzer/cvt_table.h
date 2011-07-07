#include "header.h"
#include "font_directory_table.h"
//control value table. data from this table accessible by instructions in glyphs
struct cvt_table: public table{
       uint16* instr;
       uint16 num; //non-documented parameter, only for convinience
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
extern void gener_cvt_table(cvt_table &ft);
