#include "header.h"
#include "font_directory_table.h"
//different applications and systems get the metric information from different places.
//Windows uses the 'OS/2' table as the basic source for ascent and descent for the font.
//his table calculates on the base of 'glyf' and 'hmtx' tables
struct hhea_table: public table{
     uint32 version;
     short ascend;  //Distance from baseline of highest ascender
     short descend;          //Distance from lowest of discender ascender    
     short lineGap;           //typographic line gap
     uint16 advanceWidthMax;     //Maximum advance width value in 'hmtx' table. 
     short minLeftSideBearing;	//Minimum left side bearing value in 'hmtx' table. 
     short minRightSideBearing;	//Minimum right side bearing value; 
     //calculated as Min(aw - lsb - (xMax - xMin)).
     //xMax & xMin from the 'glyf' table
     short xMaxExtent;	//Max(lsb + (xMax - xMin)).
     short caretSlopeRise;	//Used to calculate the slope of the cursor (rise/run); 1 for vertical.
     short caretSlopeRun;  
     short caretOffset;	//The amount by which a slanted highlight on a glyph needs 
     //to be shifted to produce the best appearance. Set to 0 for non-slanted fonts
     short reserved[4]; //zeros, reserved
     short metricDataFormat; //0 for current format
     uint16 numberOfHMetrics;	//Number of hMetric entries in 'hmtx' table
     virtual void printTable(char* path);
     virtual uint32 getSize();
};
//array param[9] in the following function is: ascend, descend, lineGap, 
//advanceWidthMax, minLeft(Right)Sidebearing, xMaxExtent, caretSlopeRise(Run) and carretOffset
extern void gener_hhea_table(hhea_table &hh, short param[9], uint16 hmetrixNum);
extern void gener_hhea_table_header(TableDirectoryNod &tdn,uint32 offSet);
