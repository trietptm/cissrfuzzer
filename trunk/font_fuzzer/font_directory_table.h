#include "header.h"
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
extern OffsetSubtable generateOffsetSubtable(uint16 num_Tables);
// CalcTableChecksum(...) function from .TTF specification
//http://developer.apple.com/fonts/TTRefMan/RM06/Chap6.html#Overview
uint32 CalcTableChecksum(uint32 *table, uint32 numberOfBytesInTable);
//each of subtable in font must have an etry in font directory table
//this entry structure described below
struct TableDirectoryNod{
       uint32 tag;       //name of subtable
       uint32 checkSum;  //checksum, calculates by appropriate function
       uint32 offset;    //offset from the beginning of the file
       uint32 length;    //length of subtable  
};
