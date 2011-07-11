#include "head_table.h"
void gener_head_table(head_table &ht,short xmin, short ymin, short xmax, short ymax){
           ht.version=0x00010000;
           ht.revision=0x00010000;
           ht.checkSum=0;
           ht.magicNumber=0x5F0F3CF5;
           //ht.flags=rand()%32768;
           ht.flags=0;
           ht.unitsPerEm=rand()%16384+16;
           ht.created=88888888;
           ht.modified=999999999;
           ht.xMax=xmax;
           ht.xMin=xmin;
           ht.yMax=ymax;
           ht.yMin=ymin;
           //ht.macStyle=rand()%7;//bold, italic and underline, other not supported in Windows, only for Mac
           ht.macStyle=0;
           ht.lowestRecPPEM=rand()%2048;
           ht.fontDirectionHint=2; //deprecated, set to 2
           ht.indexToLocFormat=1; //0 - for short offset,1 - for long
           ht.glyphDataFormat=0;
};
uint32 head_table::getSize(){return 54;}; //fixed-length table
void gener_head_table_header(TableDirectoryNod &tdn,head_table ht, uint32 offSet){
                  tdn.tag=0x68656164;
                  tdn.length=ht.getSize();
                  tdn.offset=offSet;
};
void head_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     //writting version
     file<<(char)0<<(char)1<<(char)0<<(char)0;//version set to 0x00010000
     //writting revision, which is set to 0x00010000
     file<<(char)0<<(char)1<<(char)0<<(char)0;
     //writting checksum(will be remade later)
     file<<(char)0<<(char)0<<(char)0<<(char)0;
     file<<(char)0x5f<<(char)0x0f<<(char)0x3c<<(char)0xf5;//magic number, const
     //writting flags
     file<<(char)(flags>>8)<<(char)(flags%256);
     //writting unitsPerEm
     file<<(char)(unitsPerEm>>8)<<(char)(unitsPerEm%256);
     //writting creation and mod modifying date(this params affects nothing)
     uint32 createdH=created>>32;
     file<<(char)(createdH>>24)<<(char)((createdH>>16)&255);
     file<<(char)((createdH>>8)&255)<<(char)(createdH%256);
     createdH=created&0xffffffff;
     file<<(char)(createdH>>24)<<(char)((createdH>>16)&255);
     file<<(char)((createdH>>8)&255)<<(char)(createdH%256);
     createdH=modified>>32;
     file<<(char)(createdH>>24)<<(char)((createdH>>16)&255);
     file<<(char)((createdH>>8)&255)<<(char)(createdH%256);
     createdH=modified&0xffffffff;
     file<<(char)(createdH>>24)<<(char)((createdH>>16)&255);
     file<<(char)((createdH>>8)&255)<<(char)(createdH%256);
     //writting bounding box data:
     file<<(char)(xMin>>8)<<(char)(xMin%256);
     file<<(char)(yMin>>8)<<(char)(yMin%256);
     file<<(char)(xMax>>8)<<(char)(xMax%256);
     file<<(char)(yMax>>8)<<(char)(yMax%256);
     //writting macStyle
     file<<(char)(macStyle>>8)<<(char)(macStyle%256);
     file<<(char)(lowestRecPPEM>>8)<<(char)(lowestRecPPEM%256);
     file<<(char)(fontDirectionHint>>8)<<(char)(fontDirectionHint%256);
     //writting indexToLocFormat and GlyphDataFormat, that are fixed    
     file<<(char)0<<(char)1;
     file<<(char)0<<(char)0;
     //2 bytes to 4-byte:
     file<<(char)0<<(char)0;
     file.close();
};
