#include "prep_table.h"
uint32 prep_table::getSize(){
       return num;
};
void prep_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     for(uint16 i=0;i<num;i++){
           file<<instr[i];              
     };
     int ofs=getSize();
     if(ofs%4!=0){
          for(int i=0;i<4-ofs%4;i++) file<<(char)0;
     }
     file.close();
};
void gener_prep_table(prep_table &ft){
     ft.num=rand()%255+1;
     ft.instr=new char[ft.num];
     for(uint16 i=0;i<ft.num;i++) 
           //ft.instr[i]=(char)rand()%256;
           ft.instr[i]=(char)0x7a;
};
