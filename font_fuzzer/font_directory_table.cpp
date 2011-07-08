#include "font_directory_table.h"
void generateOffsetSubtable(OffsetSubtable &os, uint16 num_Tables){
                os.scalerType=(1<<8);
                os.numTables=num_Tables;
                int n=0;
                while (num_Tables>0) {
                      num_Tables=num_Tables>>1;
                      n++;
                }
                n--;
                os.entrySelector=n;
                os.searchRange=16;
                for(int i=0;i<n;i++) os.searchRange*=2;
                os.rangeShift=os.numTables*16-os.searchRange;                      
};
//writting into the file with address "path" font directory table
void font_directory_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     cout<<"good file: "<<file.good()<<endl;
     //before writing each elemental strucrure divides into bytes, then writing to file
     file<<(char)0<<(char)1<<(char)0<<(char)0;//os.scaller, default 0x00010000
     file<<(char)(os.numTables>>8)<<(char)(os.numTables%256);//number of tables
     file<<(char)(os.searchRange>>8)<<(char)(os.searchRange%256);
     file<<(char)(os.entrySelector>>8)<<(char)(os.entrySelector%256);
     file<<(char)(os.rangeShift>>8)<<(char)(os.rangeShift%256);
     //offset subtable have been written. Table directory nods writing follows
     for(uint16 i=0;i<os.numTables;i++){
                //writting tag
                file<<(char)(nods[i].tag>>24)<<(char)((nods[i].tag>>16)&255);
                file<<(char)((nods[i].tag>>8)&255)<<(char)(nods[i].tag%256);
                //writting checkSum
                file<<(char)(nods[i].checkSum>>24)<<(char)((nods[i].checkSum>>16)&255);
                file<<(char)((nods[i].checkSum>>8)&255)<<(char)(nods[i].checkSum%256);
                //writting offset
                file<<(char)(nods[i].offset>>24)<<(char)((nods[i].offset>>16)&255);
                file<<(char)((nods[i].offset>>8)&255)<<(char)(nods[i].offset%256);
                //writting length
                file<<(char)(nods[i].length>>24)<<(char)((nods[i].length>>16)&255);
                file<<(char)((nods[i].length>>8)&255)<<(char)(nods[i].length%256);
     };
     file.close();
};
uint32 font_directory_table::getSize(){
       return 12+os.numTables*16;
};
void gener_fdirectory_table(font_directory_table &fdt,uint16 numTables, TableDirectoryNod * nodes){
     generateOffsetSubtable(fdt.os ,numTables);
     fdt.nods=new TableDirectoryNod[numTables];
     for(uint16 i=0;i<numTables;i++) 
           fdt.nods[i]=nodes[i];//copying is legal, because all fields are simple types
};
