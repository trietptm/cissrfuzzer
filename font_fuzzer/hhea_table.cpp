#include "hhea_table.h"
hhea_table gener_hhea_table(short param[9], uint16 hmetrixNum){
           hhea_table hh;
           //if exists 'OS/2' table parametrs 0-2 would be taken from there
           hh.ascend=param[0];
           hh.descend=param[1];
           hh.lineGap=param[2];
           //parameters 3-5 must be consistent with 'hmtx' table!
           hh.advanceWidthMax=(uint16)param[3];
           hh.minLeftSideBearing=param[4];
           hh.minRightSideBearing=param[5];
           hh.xMaxExtent=param[6];
           hh.caretSlopeRise=param[7];
           hh.caretSlopeRun=param[8];
           hh.caretOffset=param[9];
           for(int i=0;i<3;i++) hh.reserved[i]=0;
           hh.metricDataFormat=0;
           hh.numberOfHMetrics=hmetrixNum;
           return hh;
};
uint32 hhea_table_size(){return 36;}; //this table has fixed size
TableDirectoryNod gener_hhea_table_header(hhea_table hh,uint32 offSet){
                  TableDirectoryNod tdn;
                  tdn.tag=0x68686561;
                  tdn.length=hhea_table_size();
                  tdn.offset=offSet;
                  return tdn;
};

