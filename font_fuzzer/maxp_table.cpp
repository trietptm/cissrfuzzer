#include "maxp_table.h"
void gener_maxp_table(maxp_table &mt,uint16 numGlyfs, short param[12]){
     mt.version=0x00010000;
     mt.numGlyphs=numGlyfs;
     mt.maxPoints=param[0];
     mt.maxContours=param[1];
     mt.maxComponentPoints=param[2];
     mt.maxComponentContours=param[3];
     mt.maxZones=2;
     mt.maxTwilightPoints=param[4];
     mt.maxStorage=param[5];  
     mt.maxFunctionDefs=param[6];
     mt.maxInstructionDefs=param[7];
     mt.maxStackElements=param[8];
     mt.maxSizeOfInstructions=param[9];
     //mt.maxComponentElements=param[10];
     mt.maxComponentElements=0;
     mt.maxComponentDepth=param[11];   
};
void gener_maxp_table_header(TableDirectoryNod &tdn,uint32 offSet){
     tdn.tag=0x6d617870;
     tdn.length=32;
     tdn.offset=offSet;     
};
void maxp_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     file<<(char)0<<(char)1<<(char)0<<(char)0;//default 0x00010000
     file<<(char)(numGlyphs>>8)<<(char)(numGlyphs%256);
     file<<(char)(maxPoints>>8)<<(char)(maxPoints%256);
     file<<(char)(maxContours>>8)<<(char)(maxContours%256);
     file<<(char)(maxComponentPoints>>8)<<(char)(maxComponentPoints%256);
     file<<(char)(maxComponentContours>>8)<<(char)(maxComponentContours%256);
     file<<(char)0<<(char)2;//default value
     file<<(char)(maxTwilightPoints>>8)<<(char)(maxTwilightPoints%256);
     file<<(char)(maxStorage>>8)<<(char)(maxStorage%256);
     file<<(char)(maxFunctionDefs>>8)<<(char)(maxFunctionDefs%256);
     file<<(char)(maxInstructionDefs>>8)<<(char)(maxInstructionDefs%256);
     file<<(char)(maxStackElements>>8)<<(char)(maxStackElements%256);
     file<<(char)(maxSizeOfInstructions>>8)<<(char)(maxSizeOfInstructions%256);
     file<<(char)(maxComponentElements>>8)<<(char)(maxComponentElements%256);
     file<<(char)(maxComponentDepth>>8)<<(char)(maxComponentDepth%256);
     file.close();     
};
uint32 maxp_table::getSize(){
       return 32;
};
