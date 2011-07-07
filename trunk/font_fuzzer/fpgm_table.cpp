#include "fpgm_table.h"
uint32 fpgm_table::getSize(){
       return num;
};
void fpgm_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     cout<<"good file: "<<file.good()<<endl;
     for(uint16 i=0;i<num;i++){
           file<<instr[i];              
     };
     file.close();
};
void gener_fpgm_table(fpgm_table &ft){
     ft.num=rand()%255+1;
     ft.instr=new char[ft.num];
     for(uint16 i=0;i<ft.num;i++) ft.instr[i]=(char)rand()%256;
};
