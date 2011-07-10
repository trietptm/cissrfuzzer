#include "post_table.h"
void gener_post_table_v1_3(post_table &pt,uint32 ver){
           if(ver!=0x00010000&&ver!=0x00030000) ver=0x00030000;
           pt.version=ver;
           pt.italicAngle=0;
           pt.underlinePosition=(rand()%32)-16;
           pt.underlineThickness=(rand()%32)-16;
           //pt.isFixedPitch=rand()%2;
           pt.isFixedPitch=0;
           pt.minMemType42=pt.maxMemType42=pt.minMemType1=pt.maxMemType1=0;
           pt.num_new_glyph=0;
};
void gener_post_table_v2(post_table &pt, uint16 numGlyfs, uint16 new_glyfs_size,const char* Names){
           pt.version=0x00020000;
           pt.names=new char[new_glyfs_size];
           pt.numGlyphs=numGlyfs;
           pt.glyphNameIndex=new uint16[numGlyfs];
           for(uint16 i=0;i<numGlyfs;i++) pt.glyphNameIndex[i]=rand()%32768; 
           pt.num_new_glyph=new_glyfs_size;
           memcpy(pt.names,Names,new_glyfs_size); //new_glyfs_size=number of byte, correct copying       
};
uint32 post_table::getSize(){
       uint32 size;
       if(version!=0x20000) return 32;
       //for 'post' version 2
       size=34;//first 10 fields
       size+=numGlyphs*2; //+size of glyph index array
       size+=num_new_glyph;//+size of names, each symbol of 'names' string is a byte
       return size;
};
void gener_post_table_header(TableDirectoryNod &tdn, uint32 length,uint32 offSet){
      tdn.tag=0x706f7374;
      tdn.length=length;
      tdn.offset=offSet;
};
void post_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     cout<<"good file: "<<file.good()<<endl;
     file<<(char)(version>>24)<<(char)((version>>16)&255);
     file<<(char)((version>>8)&255)<<(char)(version%256);
     file<<(char)(italicAngle>>24)<<(char)((italicAngle>>16)&255);
     file<<(char)((italicAngle>>8)&255)<<(char)(italicAngle%256);  
     file<<(char)(underlinePosition>>8)<<(char)(underlinePosition%256);
     file<<(char)(underlineThickness>>8)<<(char)(underlineThickness%256);
     file<<(char)(isFixedPitch>>24)<<(char)((isFixedPitch>>16)&255);
     file<<(char)((isFixedPitch>>8)&255)<<(char)(isFixedPitch%256);
     //16 bytes of zeros follows
     for(uint16 i=0;i<16;i++){
                file<<(char)0;
     };
     if(version!=0x00010000&&version!=0x00030000){                                         
           file<<(char)(numGlyphs>>8)<<(char)(numGlyphs%256);
           for(uint16 i=0;i<numGlyphs;i++){
                file<<(char)(glyphNameIndex[i]>>8)<<(char)(glyphNameIndex[i]%256);
           };
           file<<names;
     }
     int ofs=getSize();
     if(ofs%4!=0){
          for(int i=0;i<4-ofs%4;i++) file<<(char)0;
     }
     //file<<(char)0<<(char)0;
     file.close();
};
