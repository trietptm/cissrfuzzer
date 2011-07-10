#include "cmap_table.h"
void gener_format_0_table(format_0_table &f0, uint16 numGlyphs){
               //random substitution on a glyph array
               for(int i=0;i<256;i++) f0.glyphIdArray[i]=rand()%numGlyphs;
                       //f0.glyphIdArray[i]=i;
               f0.format=0;
               f0.length=262;
               //f0.language=rand()%151;
               f0.language=0;
};

//generation simplyfied, offset array set to 0, GlyphIndexArray to one element - 0
//segments(and number of them) generated randomly
void gener_format_4_table(format_4_table &f4,uint16 numGlyphs){
               f4.format=4;
               //f4.language=rand()%151;
               f4.language=0;
               uint16 segNum=rand()%4+1;//1..4, other number of segments also legal
               f4.endCode=new uint16[segNum];
               f4.reversePad=0; //const
               f4.startCode=new uint16[segNum];
               f4.idDelta=new short[segNum];
               f4.idRangeOffset=new uint16[segNum];
               for(int i=0;i<segNum; i++)f4.idRangeOffset[i]=0;//simplification, will be fixed in next versions
               f4.segCountX2=segNum*2;
               //REDO this!!!111
               f4.startCode[0]=rand()%numGlyphs/8;//
               f4.endCode[0]=f4.startCode[0]+1+rand()%numGlyphs/8;
               for(int i=1;i<segNum-1;i++){
                       f4.startCode[i]=f4.endCode[i-1]+1+rand()%numGlyphs/8;//offset from previous segment
                       f4.endCode[i]=f4.startCode[i]+1+rand()%numGlyphs/8;//length of segment
               }
               f4.startCode[segNum-1]=f4.endCode[segNum-1]=0xffff;
               f4.idDelta[0]=f4.endCode[0]-f4.startCode[0]+1;
               for(int i=1;i<segNum;i++){
                       f4.idDelta[i]=rand()%numGlyphs/8-numGlyphs/16;//
               }
               f4.idDelta[segNum]=1;
               f4.segCountX2=segNum*2;    
               f4.glyphIndxArray=new uint16[1];
               f4.glyphIndxArray[0]=0;
               f4.length=14+8*segNum+2; //+2: reverse pad+ 1 element of glypd id array  
               //14 - single fields, 4 arrays,2 bytes etries,with size of segNum +1 element of glyphIndxArray
               int pow=0;
               int i=1;
               while(i<segNum) {i*=2;pow++;}
               f4.searchRange=i;
               f4.entrySelector=pow-1;
               f4.rangeShift=segNum*2-i;
};
void gener_format_6_table(format_6_table &f6, uint16 numGlyphs){
     f6.firstCode=rand()%256; 
     f6.entryCount=rand()%numGlyphs+1;//number of entries
     f6.length=10+f6.entryCount*2;
     f6.format=6;
     //f6.language=rand()%151;
     f6.language=0;
     f6.glyphIndexArray=new uint16[f6.entryCount];
     for(int i=0;i<f6.entryCount;i++){
             f6.glyphIndexArray[i]=rand()%numGlyphs;//consistence with number of glyphs
     }
};
void format_0_table::Print(ofstream &file){
     file<<(char)0<<(char)0;//format 0
     file<<(char)(length>>8)<<(char)(length%256);
     file<<(char)(language>>8)<<(char)(language%256);
     for( uint16 i=0;i<256;i++){//writting endCode
          file<<glyphIdArray[i];
     }
};
void format_4_table::Print(ofstream &file){
     file<<(char)0<<(char)4;//format 4
     file<<(char)(length>>8)<<(char)(length%256);
     file<<(char)(language>>8)<<(char)(language%256);
     file<<(char)(segCountX2>>8)<<(char)(segCountX2%256);
     file<<(char)(searchRange>>8)<<(char)(searchRange%256);
     file<<(char)(entrySelector>>8)<<(char)(entrySelector%256);
     file<<(char)(rangeShift>>8)<<(char)(rangeShift%256);
     for( uint16 i=0;i<segCountX2/2;i++){//writting endCode
          file<<(char)(endCode[i]>>8)<<(char)(endCode[i]%256);
     }
     file<<(char)0<<(char)0;//reversePad, 0
     for( uint16 i=0;i<segCountX2/2;i++){//writting startCode
          file<<(char)(startCode[i]>>8)<<(char)(startCode[i]%256);
     }
     for( uint16 i=0;i<segCountX2/2;i++){//writting idDelta
          file<<(char)(idDelta[i]>>8)<<(char)(idDelta[i]%256);
     }
     for( uint16 i=0;i<segCountX2/2+1;i++){//writting 0ffset, 0 by simplification
     //+1 element of glyph index array, which is zero
          file<<(char)0<<(char)0;
     }   
};
void format_6_table::Print(ofstream &file){
     file<<(char)0<<(char)6;//format 6
     file<<(char)(length>>8)<<(char)(length%256);
     file<<(char)(language>>8)<<(char)(language%256);
     file<<(char)(firstCode>>8)<<(char)(firstCode%256);
     file<<(char)(entryCount>>8)<<(char)(entryCount%256);
     for( uint16 i=0;i<entryCount;i++){
          file<<(char)(glyphIndexArray[i]>>8)<<(char)(glyphIndexArray[i]%256);
     }
};
string format_0_table::toString(){
       string str="";
       stringstream ss;
       ss<<(char)0<<(char)0;//format 0
       ss<<(char)(length>>8)<<(char)(length%256);
       ss<<(char)(language>>8)<<(char)(language%256);
       for( uint16 i=0;i<256;i++){//writting endCode
          ss<<glyphIdArray[i];
       }
       str=ss.str();
       return str;
};
string format_4_table::toString(){
     string str="";
     stringstream file;
     file<<(char)0<<(char)4;//format 4
     file<<(char)(length>>8)<<(char)(length%256);
     file<<(char)(language>>8)<<(char)(language%256);
     file<<(char)(segCountX2>>8)<<(char)(segCountX2%256);
     file<<(char)(searchRange>>8)<<(char)(searchRange%256);
     file<<(char)(entrySelector>>8)<<(char)(entrySelector%256);
     file<<(char)(rangeShift>>8)<<(char)(rangeShift%256);
     for( uint16 i=0;i<segCountX2/2;i++){//writting endCode
          file<<(char)(endCode[i]>>8)<<(char)(endCode[i]%256);
     }
     file<<(char)0<<(char)0;//reversePad, 0
     for( uint16 i=0;i<segCountX2/2;i++){//writting startCode
          file<<(char)(startCode[i]>>8)<<(char)(startCode[i]%256);
     }
     for( uint16 i=0;i<segCountX2/2;i++){//writting idDelta
          file<<(char)(idDelta[i]>>8)<<(char)(idDelta[i]%256);
     }
     for( uint16 i=0;i<segCountX2/2+1;i++){//writting 0ffset, 0 by simplification
     //+1 element of glyph index array, which is zero
          file<<(char)0<<(char)0;
     }   
       str=file.str();
       return str;
};
string format_6_table::toString(){
     string str="";
     stringstream file;
     file<<(char)0<<(char)6;//format 6
     file<<(char)(length>>8)<<(char)(length%256);
     file<<(char)(language>>8)<<(char)(language%256);
     file<<(char)(firstCode>>8)<<(char)(firstCode%256);
     file<<(char)(entryCount>>8)<<(char)(entryCount%256);
     for( uint16 i=0;i<entryCount;i++){
          file<<(char)(glyphIndexArray[i]>>8)<<(char)(glyphIndexArray[i]%256);
     }
     str=file.str();
     return str;
};
void cmap_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     cout<<"good file: "<<file.good()<<endl;
     file<<(char)0<<(char)0;
     file<<(char)(numTables>>8)<<(char)(numTables%256);
     //writting encoding records
     for( uint16 i=0;i<numTables;i++){
          file<<((char)(encodingRecords[i].platformID>>8));
          file<<(char)(encodingRecords[i].platformID%256);
          file<<(char)(encodingRecords[i].platformSpecificID>8);
          file<<(char)(encodingRecords[i].platformSpecificID%256);           
          file<<(char)(encodingRecords[i].offset>>24)<<(char)((encodingRecords[i].offset>>16)&255);
          file<<(char)((encodingRecords[i].offset>>8)&255)<<(char)(encodingRecords[i].offset%256);
     };
     for( uint16 i=0;i<numTables;i++){
          file<<subTables[i];            
     }
     int ofs=getSize();
     if(ofs%4!=0){
          for(int i=0;i<4-ofs%4;i++) file<<(char)0;
     }
     file.close();
}
uint32 format_0_table::getLength(){return 262;}
uint32 format_4_table::getLength(){
       uint32 size=14;//7 first field
       size+=segCountX2/2*4;//endCode,startCode,idDelta,rangeOffset added
       size+=4;//reversePad+1 element in glyphIndxArray
       return size;
}
uint32 format_6_table::getLength(){
       return 10+entryCount*2;
}
uint32 cmap_table::getSize(){
       uint32 size=4+8*numTables;//numTables+verson size+size of records
       for(int i=0;i<numTables;i++) size+=subTables[i].length();
       return size;
};
void gener_cmap_table(cmap_table &cmt, uint16 numGlyphs){
     cmt.version=0;
     cmt.numTables=rand()%3+1;//1..4 tables
     //cmt.numTables=2;
     cmt.encodingRecords=new cmap_encoding_record[cmt.numTables];
     cmt.subTables=new string[cmt.numTables];
     uint32 offset=4+8*cmt.numTables;
     for(uint16 i=0;i<cmt.numTables;i++){
                int type=rand()%3;
                //int type=0;
                if (type==0) {
                   format_0_table f0;
                   gener_format_0_table(f0,numGlyphs);
                   cmt.subTables[i]=f0.toString();
                }
                else if (type==1) {
                     format_4_table f4;
                     gener_format_4_table(f4,numGlyphs);
                     cmt.subTables[i]=f4.toString();
                }
                else {
                     format_6_table f6;
                     gener_format_6_table(f6,numGlyphs);
                     cmt.subTables[i]=f6.toString();
                }
                //encoding records must be sorted by PID then - by PSID
                cmt.encodingRecords[i].platformID=3;//platform - Win
                cmt.encodingRecords[i].platformSpecificID=i;
                cmt.encodingRecords[i].offset=offset;
                offset+=cmt.subTables[i].length();
     }
};
