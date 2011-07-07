#include "header.h"
#include "font_directory_table.h"
struct longHorMetric{
       uint16 advanceWidth;
       short lsb; //leftSideBearing       
};
//horizontal metrics table covered all glyphs
struct hmtx_table: public table{
       uint16 numOfLongHorMmetrics; //this variable duplicates numOfLongHorHetric from 
       //'hhea' table, i added it for convinient, 
       //Warning! this variable wouldn't be written into the font file
       uint16 numGlyfs; //duplicates maxp.numGlyph, also wouldn't be written
       //into the file and added for convinience!
       longHorMetric * hMetrics; //if font monospaced, 1 entry requierd.
       //last entry advanceWidth applies for all glyphs in the following array
       short * lsb; //left side bearing The number of entries in this array 
       //is derived from the total number of glyphs minus numOfLongHorMetrics.
       virtual void printTable(char* path);
       virtual uint32 getSize();
       
};
extern void gener_hmtx_table(hmtx_table &hmt,uint16 numOflhm, uint16 numGlyphs);
extern uint32 hmtx_table_size(hmtx_table hmt);
extern void gener_hmtx_table_header(TableDirectoryNod &tdn,hmtx_table hmt,uint32 offSet);
extern uint16 getMaxAdvance(hmtx_table &hmt);
extern short getMinlsb(hmtx_table &hmt);//returns minimal left side bearing
