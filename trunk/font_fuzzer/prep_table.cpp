#include "prep_table.h"
uint32 prep_table::getSize(){
       return num;
};
void prep_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     cout<<"good file:(prep) "<<file.good()<<endl;
     for(uint16 i=0;i<num;i++){
           file<<instr[i];              
     };
     file.close();
};
void gener_prep_table(prep_table &ft){
     ft.num=rand()%255+1;
     ft.instr=new char[ft.num];
     for(uint16 i=0;i<ft.num;i++) ft.instr[i]=(char)rand()%256;
};
