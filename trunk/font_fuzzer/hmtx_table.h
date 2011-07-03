#include "header.h"
#include "font_directory_table.h"
struct longHorMetric{
       uint16 advanceWidth;
       short lsb; //leftSideBearing       
};
//horizontal metrics table covered all glyphs
struct hmtx_table{
       uint16 numOfLongHorMmetrics; //this variable duplicate numOfLongHorHetric from 
       //'hhea' table, i added it for convinient, 
       //Warning! this variable wouldn't be written into the font file
       uint16 numGlyfs; //duplicates maxp.numGlyph, also wouldn't be written
       //into the file and added for convinience!
       longHorMetric * hMetrics; //if font monospaced, 1 entry requierd.
       //last entry advanceWidth applies for all glyphs in the following array
       short * lsb; //left side bearing The number of entries in this array 
       //is derived from the total number of glyphs minus numOfLongHorMetrics.
       
};
extern hmtx_table gener_hmtx_table(uint16 numOflhm, uint16 numGlyphs, longHorMetric* metrics , short* Lsb);
extern uint32 hmtx_table_size(hmtx_table hmt);
extern TableDirectoryNod gener_hmtx_table_header(hmtx_table hmt,uint32 offSet);
extern uint16 getMaxAdvance(hmtx_table hmt);
extern short getMinlsb(hmtx_table hmt);
