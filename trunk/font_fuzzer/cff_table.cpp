#include "cff_table.h"
void gener_cff_table(cff_table &cft){
     cft.major=(char)1;
     cft.minor=(char)0;
     cft.hdrsize=(char)4;
     cft.offsize=(char)1;
     //generating name: 
     //in our case name has only one entry(1 font)
     cft.name.count=1;
     cft.name.offSize=(char)1;
     cft.name.off1=new char[2];
     cft.name.off1[0]=(char)1;
     cft.name.off1[1]=(char)65;
     cft.name.data="0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";
     //generating top Dict index and data
     cft.topDict.count=1;//count must be same with count in name Index
     cft.topDict.offSize=11111;
     //...
     //generating string index:
     cft.strings.count=2400; //more strings avaible, but they're unnecessary
     cft.strings.offSize=2;
     cft.strings.off2=new uint16[2401];
     cft.strings.str=new string[2400];
     ifstream fin;
     fin.open("strings.txt");
     if(!fin.good()) cout<<"bad file strings.txt!\n";
     else{
          for(int i=0;i<2400;i++)
               getline(fin,cft.strings.str[i]);
     }
     fin.close();
     cft.strings.off2[0]=1;
     for(int i=1;i<2401;i++){
             cft.strings.off2[i]=cft.strings.off2[i-1]+cft.strings.str[i-1].length();
     }
     
};
void cff_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     //writting header
     file<<major<<minor<<hdrsize<<offsize;
     //writting Name section
     file<<(char)(name.count>>8)<<(char)(name.count%256);
     file<<name.offSize;
     file<<name.off1[0]<<name.off1[1];
     for(int i=0;i<name.off1[1]-1;i++) file<<name.data[i];
     //writting top dict index
     //just do it!
     
     //writting string Index
     file<<(char)(strings.count>>8)<<(char)(strings.count%256);
     file<<strings.offSize;
     //all offsetes are 2 bytes long;total number of offsets : 2401
     for(int i=0;i<2401;i++)
         file<<(char)(strings.off2[i]>>8)<<(char)(strings.off2[i]%256);
     for(int i=0;i<2400;i++)
         file<<strings.str[i];
     file.close();
};
uint32 cff_table::getSize(){
     return 0;
}
