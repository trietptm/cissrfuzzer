#include "header.h"
#include "font_directory_table.h"
struct fpgm_table: public table{
       char* instr;
       uint16 num; //non-documented parameter, only for convinience
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
extern void gener_fpgm_table(fpgm_table &ft);
