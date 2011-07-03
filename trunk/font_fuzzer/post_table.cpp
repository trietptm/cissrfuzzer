#include "post_table.h"
post_table gener_post_table_v1_3(uint32 ver, uint32 Angle, short underPos, short underThick, uint32 FixedPitch){
           if(ver!=0x10000&&ver!=0x30000) ver=0x10000;
           post_table pt;
           pt.version=ver;
           pt.italicAngle=Angle;
           pt.underlinePosition=underPos;
           pt.underlineThickness=underThick;
           pt.isFixedPitch=FixedPitch;
           pt.minMemType42=pt.maxMemType42=pt.minMemType1=pt.maxMemType1=0;
           pt.numGlyphs=pt.num_new_glyph=0;
           pt.glyphNameIndex=0;
           pt.names=0;
           return pt;
};
post_table gener_post_table_v2(post_table pt, uint16 numGlyfs, uint16 new_glyfs_size, uint16* glyphIndex, char* Names){
           pt.names=new char[new_glyfs_size];
           pt.numGlyphs=numGlyfs;
           pt.glyphNameIndex=new uint16[numGlyfs];
           memcpy(pt.glyphNameIndex,glyphIndex,numGlyfs*2); //each glyphIndex 2 bytes long
           pt.num_new_glyph=new_glyfs_size;
           memcpy(pt.names,Names,new_glyfs_size); //new_glyfs_size=number of byte, correct copying
           return pt;        
};
uint32 post_table_size(post_table pt){
       uint32 size;
       if(pt.version!=0x20000) return 32;
       //for 'post' version 2
       size=36;//first 10 fields
       size+=pt.numGlyphs*2; //+size of glyph index array
       size+=pt.num_new_glyph;//+size of names, each symbol of names string is a byte
       return size;
};
TableDirectoryNod gener_post_table_header(post_table pt,uint32 offSet){
      TableDirectoryNod tdn;
      tdn.tag=0x706f7374;
      tdn.length=post_table_size(pt);
      tdn.offset=offSet;
};
