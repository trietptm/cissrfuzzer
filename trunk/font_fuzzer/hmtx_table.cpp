#include "hmtx_table.h"
void gener_hmtx_table(hmtx_table &hmt,uint16 numOflhm, uint16 numGlyphs, longHorMetric* metrics , short* Lsb){
           hmt.numOfLongHorMmetrics=numOflhm;
           hmt.numGlyfs=numGlyphs;
           hmt.hMetrics=new longHorMetric[numOflhm];
           for(int i=0;i<numOflhm;i++) hmt.hMetrics[i]=metrics[i];//default copying - 
           //copying of the fieldsm that's why it correct
           hmt.lsb=new short[numGlyphs-numOflhm];
           memcpy(hmt.lsb, Lsb,(numGlyphs-numOflhm)*2);//2 bytes long short
};
uint32 hmtx_table::getSize(){
       return (2*numOfLongHorMmetrics-numGlyfs)*2;
};
void gener_hmtx_table_header(TableDirectoryNod &tdn,hmtx_table hmt,uint32 offSet){
                  tdn.tag=0x686d7478;
                  tdn.length=hmt.getSize();
                  tdn.offset=offSet;
};
uint16 getMaxAdvance(hmtx_table hmt){
       uint16 max=0;
       for(uint16 i=0;i<hmt.numOfLongHorMmetrics;i++)
            if(hmt.hMetrics[i].advanceWidth>max) max=hmt.hMetrics[i].advanceWidth;
       return max;    
};
short getMinlsb(hmtx_table hmt){ //finding minimal left side bearing
       short min=hmt.hMetrics[0].lsb;
       for(uint16 i=0;i<hmt.numOfLongHorMmetrics;i++)
           if(hmt.hMetrics[i].lsb<min) min=hmt.hMetrics[i].lsb;
       for(uint16 i=0;i<hmt.numGlyfs-hmt.numOfLongHorMmetrics;i++)   
           if(hmt.lsb[i]<min) min=hmt.lsb[i];
       return min;
};
void hmtx_table::printTable(char* path){
     ofstream file;
     file.open("C:\\txt.ttx",ios::binary|ios::app);
     cout<<"good file: "<<file.good()<<endl;
     for(uint16 i=0;i<numOfLongHorMmetrics;i++){
                //writting longHorMetric info
                file<<(char)(hMetrics[i].advanceWidth>>8)<<(char)(hMetrics[i].advanceWidth%255);
                file<<(char)(hMetrics[i].lsb>>8)<<(char)(hMetrics[i].lsb%255);                
     };
     for(uint16 i=0;i<numGlyfs-numOfLongHorMmetrics;i++){
                //writting lsb info
                file<<(char)(lsb[i]>>8)<<(char)(lsb[i]%255);              
     };
     file.close();
};
