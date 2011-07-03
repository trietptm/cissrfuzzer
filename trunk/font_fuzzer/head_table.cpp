#include "head_table.h"

head_table gener_head_table(short xmin, short ymin, short xmax, short ymax,uint16 unitsperEm, uint16 lowestRecPix){
           head_table ht;
           ht.version=0x00010000;
           ht.revision=100500;
           ht.checkSum=0;
           ht.magicNumber=0x5F0F3CF5;
           ht.flags=0;///?????????????
           ht.unitsPerEm=unitsperEm;
           ht.created=0x1111111;
           ht.modified=0x1000100;
           ht.xMax=xmax;
           ht.xMin=xmin;
           ht.yMax=ymax;
           ht.yMin=ymin;
           ht.macStyle=3;//bold, italic and underline, other not supported in Windows, only for Mac
           ht.lowestRecPPEM=lowestRecPix;
           ht.fontDirectionHint=2; //deprecated, set to 2
           ht.indexToLocFormat=1; //0 - for short offset
           ht.glyphDataFormat=0;
           return ht;
};
uint32 head_table_size(){return 54;}; //fixed-length table
TableDirectoryNod gener_head_table_header(head_table ht, uint32 offSet){
                  TableDirectoryNod tdn;
                  tdn.tag=0x68656164;
                  tdn.length=head_table_size();
                  tdn.offset=offSet;
                  return tdn;
};
