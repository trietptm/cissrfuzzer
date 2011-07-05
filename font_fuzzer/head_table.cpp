#include "head_table.h"
void gener_head_table(head_table &ht,short xmin, short ymin, short xmax, short ymax){
           ht.version=0x00010000;
           ht.revision=0x00010000;
           ht.checkSum=0;
           ht.magicNumber=0x5F0F3CF5;
           ht.flags=rand()%32768;
           ht.unitsPerEm=rand()%16384+16;
           ht.created=0x1111111;
           ht.modified=0x1000100;
           ht.xMax=xmax;
           ht.xMin=xmin;
           ht.yMax=ymax;
           ht.yMin=ymin;
           ht.macStyle=rand()%7;//bold, italic and underline, other not supported in Windows, only for Mac
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
     cout<<"good file: "<<file.good()<<endl;
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
     file<<(char)1<<(char)1<<(char)1<<(char)1;
     file<<(char)1<<(char)1<<(char)1<<(char)1;
     file<<(char)0<<(char)1<<(char)0<<(char)1;
     file<<(char)1<<(char)0<<(char)1<<(char)0;
     //writting bounding box data:
     file<<(char)(xMin>>8)<<(char)(xMin%256);
     file<<(char)(yMin>>8)<<(char)(yMin%256);
     file<<(char)(xMax>>8)<<(char)(xMax%256);
     file<<(char)(yMax>>8)<<(char)(yMax%256);
     //writting macStyle(constant value)
     file<<(char)0<<(char)7;
     file<<(char)(lowestRecPPEM>>8)<<(char)(lowestRecPPEM%256);
     file<<(char)(fontDirectionHint>>8)<<(char)(fontDirectionHint%256);
     //writting indexToLocFormat and GlyphDataFormat, that are fixed    
     file<<(char)0<<(char)1;
     file<<(char)0<<(char)0;
     file.close();
};
