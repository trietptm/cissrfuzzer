#include "header.h"
#include "font_directory_table.h"
//Pre program for glyphs
//this table is identical to  fpgm. creation of this table explaining by
//attempt to create program, that will be as far as possible close to specification 
struct prep_table: public table{
       char* instr;
       uint16 num; //non-documented parameter, only for convinience
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
extern void gener_prep_table(prep_table &ft);
