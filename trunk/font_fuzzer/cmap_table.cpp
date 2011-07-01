#include "cmap_table.h"
uint16 cmap_version=0;
format_0_table gener_format_0_table( char GlyphIdArray[256], unsigned short lang)
{
               format_0_table res;
               for(int i=0;i<256;i++) res.glyphIdArray[i]=GlyphIdArray[i];
               res.length=262;
               res.language=lang;
               res.format=0;
               return res; 
};

