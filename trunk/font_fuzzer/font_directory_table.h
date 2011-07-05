#include "header.h"
#pragma once //only once this file will be included
//all tables are inherits this table
struct table{
       virtual void printTable(char* path)=0;
       virtual uint32 getSize()=0;
};
//structure of Offset subtable of Font Directory
struct OffsetSubtable{
       uint32 scalerType; //constant value , 0x00010000
       uint16 numTables;
       uint16 searchRange; //generates from numTables
       uint16 entrySelector;//generates from numTables
       uint16 rangeShift;//generates from numTables
};
//first part of Font Directory table
//function, that generates Offset subtable on the basic of number of tables follows
extern void generateOffsetSubtable(OffsetSubtable &os, uint16 num_Tables);
//each of subtable in font must have an etry in font directory table
//this entry structure described below
struct TableDirectoryNod{
       uint32 tag;       //name of subtable
       uint32 checkSum;  //checksum, calculates by appropriate function
       uint32 offset;    //offset from the beginning of the file
       uint32 length;    //length of subtable  
};
struct font_directory_table:public table{
       OffsetSubtable os;
       TableDirectoryNod * nods; //number of nodes specifies by os.numTables value
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
extern void gener_fdirectory_table(font_directory_table &fdt,uint16 numTables, TableDirectoryNod * nodes);
