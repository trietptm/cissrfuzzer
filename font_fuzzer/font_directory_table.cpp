#include "font_directory_table.h"
OffsetSubtable generateOffsetSubtable(uint16 num_Tables){
                OffsetSubtable ost;
                ost.scalerType=(1<<8);
                ost.numTables=num_Tables;
                int n=0;
                while (num_Tables>0) {
                      num_Tables=num_Tables>>1;
                      n++;
                }
                n--;
                ost.entrySelector=n;
                ost.searchRange=16;
                for(int i=0;i<n;i++) ost.searchRange*=2;
                ost.rangeShift=ost.numTables*16-ost.searchRange;
                return ost;                      
};
//calculating checksum
uint32 CalcTableChecksum(uint32 *table, uint32 numberOfBytesInTable){
    uint32 sum = 0;
    uint32 nLongs = (numberOfBytesInTable + 3) / 4;
    while (nLongs-- > 0)
        //adding 4-bytes number!
        sum += *table++;
    return sum;
}
