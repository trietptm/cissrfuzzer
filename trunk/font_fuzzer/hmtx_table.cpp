#include "hmtx_table.h"
hmtx_table gener_hmtx_table(uint16 numOflhm, uint16 numGlyphs, longHorMetric* metrics , short* Lsb){
           hmtx_table hmt;
           hmt.numOfLongHorMmetrics=numOflhm;
           hmt.numGlyfs=numGlyphs;
           hmt.hMetrics=new longHorMetric[numOflhm];
           for(int i=0;i<numOflhm;i++) hmt.hMetrics[i]=metrics[i];//default copying - 
           //copying of the fieldsm that's why it correct
           hmt.lsb=new short[numGlyphs-numOflhm];
           memcpy(hmt.lsb, Lsb,(numGlyphs-numOflhm)*2);//2 bytes long short
           return hmt;
};
uint32 hmtx_table_size(hmtx_table hmt){
       return (2*hmt.numOfLongHorMmetrics-hmt.numGlyfs)*2;
};
TableDirectoryNod gener_hmtx_table_header(hmtx_table hmt,uint32 offSet){
                  TableDirectoryNod tdn;
                  tdn.tag=0x686d7478;
                  tdn.length=hmtx_table_size(hmt);
                  tdn.offset=offSet;
                  return tdn;
};
uint16 getMaxAdvance(hmtx_table hmt){
       uint16 max=0;
       for(uint16 i=0;i<hmt.numOfLongHorMmetrics;i++)
            if(hmt.hMetrics[i].advanceWidth>max) max=hmt.hMetrics[i].advanceWidth;
       return max;    
};
short getMinlsb(hmtx_table hmt){
       short min=hmt.hMetrics[0].lsb;
       for(uint16 i=0;i<hmt.numOfLongHorMmetrics;i++)
           if(hmt.hMetrics[i].lsb<min) min=hmt.hMetrics[i].lsb;
       for(uint16 i=0;i<hmt.numGlyfs-hmt.numOfLongHorMmetrics;i++)   
           if(hmt.lsb[i]<min) min=hmt.lsb[i];
       return min;
};
