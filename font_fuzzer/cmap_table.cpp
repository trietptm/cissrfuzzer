#include "cmap_table.h"
format_0_table gener_format_0_table( char GlyphIdArray[256], unsigned short lang)
{
               format_0_table res;
               for(int i=0;i<256;i++) res.glyphIdArray[i]=GlyphIdArray[i];
               res.length=262;
               res.language=lang;
               res.format=0;
               return res; 
};
format_6_table gener_format_6_table( uint16 segNum, uint16 *startSeg, uint16 *endSeg, short *delta, uint16 *rangeOffset, uint16 *glyfId){
                      
};

