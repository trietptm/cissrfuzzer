#include "cmap_table.h"
#include "font_directory_table.h"
#include "name_table.h"
#include "hmtx_table.h"
#include "hhea_table.h"
#include "head_table.h"
#include "post_table.h"
#include "glyf_table.h"
#include "maxp_table.h"
//for now checked writing and creating functions of:
//post,name,hmtx,hhea,head
void generate_tables(){
     uint16 numGlyphs=rand()%512+1;//let it be: 1..513 glyphs
     //generating glyph table
     simpleGlyph *sg=new simpleGlyph[numGlyphs];
     gener_simpleGlyphArr(sg,numGlyphs);
     glyf_table gt;
     gt.numGlyphs=gt.numSimpleGlyph=numGlyphs;
     gt.sg=sg;
     //generating cmap table
     cmap_table ct;
     gener_cmap_table(ct);
     //generating head table
     //indexToLocFormat=1, offsets in 'loca' are long! 
     head_table ht;
     gener_head_table(ht,gt.getxMin(),gt.getyMin(),gt.getxMax(),gt.getyMax());
     //generating maxp table
     maxp_table mt;
     short param[]={gt.maxPoints(),gt.maxContours(),0,0,rand()%128,rand()%128,rand()%128,rand()%128,rand()%128,gt.maxInstr(),rand()%128,0};
     //array param described in function gener_maxp_table(...)
     gener_maxp_table(mt,numGlyphs,param);
     //generating post table
     post_table pt;
     gener_post_table_v1_3(pt,0x30000);
     //later we will generate version 2 table
     /*
     char names="assdghghui....qw..q.w.wq.qw.q.wee..qweqe.e.q.eq....AAAA11!!!!!!!0x...000xff'''";
     uint16 num_new_glyphs=98;
     uint16 num=rand()%90+8;
     uint16 * glyphIndex=new uint16[num];
     ...
     */
     //generating hhea table
     uint16 numOfLhm=rand()%(numGlyphs-1);
     hhea_table hh;
     gener_hhea_table(hh,numOfLhm);
     //hhea table not filled with marginal parametrs of lsb, rsb, xMaxExtend and some other
     //generating hmtx
     hmtx_table hmt;
     gener_hmtx_table(hmt,numOfLhm,numGlyphs);
     //filling hhea with appropriate values
     hh.minLeftSideBearing=getMinlsb(hmt);
     hh.advanceWidthMax=getMaxAdvance(hmt);
     //calculating xMaxExtent for hhea
     uint16 xMaxExtent=0;
     for(uint16 i=0;i<numOfLhm;i++)
          if(hmt.hMetrics[i].lsb+gt.sg[i].xMax-+gt.sg[i].xMin>xMaxExtent)
               xMaxExtent=hmt.hMetrics[i].lsb+gt.sg[i].xMax-+gt.sg[i].xMin;
     for(uint16 i=numOfLhm;i<numGlyphs;i++)
                if(hmt.lsb[i-numOfLhm]+gt.sg[i].xMax-+gt.sg[i].xMin>xMaxExtent)
                     xMaxExtent=hmt.lsb[i-numOfLhm]+gt.sg[i].xMax-+gt.sg[i].xMin;
     hh.xMaxExtent=xMaxExtent;
     //calculating minRsb for hhea
     uint16 minRsb=xMaxExtent;
     for(uint16 i=0;i<numOfLhm;i++)
          if(hmt.hMetrics[i].advanceWidth-(hmt.hMetrics[i].lsb+gt.sg[i].xMax-+gt.sg[i].xMin)<minRsb)
               minRsb=hmt.hMetrics[i].advanceWidth-(hmt.hMetrics[i].lsb+gt.sg[i].xMax-gt.sg[i].xMin);
     for(uint16 i=numOfLhm;i<numGlyphs;i++)
          if(hmt.hMetrics[numOfLhm-1].advanceWidth-(hmt.lsb[i-numOfLhm]+gt.sg[i].xMax-gt.sg[i].xMin)<minRsb)
               minRsb=hmt.lsb[i-numOfLhm]+gt.sg[i].xMax-gt.sg[i].xMin;
     hh.minRightSideBearing=minRsb;
     //generating name table
     name_table nt;
     //nameRecords.txt should have 20+ records, and all of them should be in ANSI encoding;
     gener_name_table(nt,rand()%20+1,"C:\\nameRecords.txt");
     
}
int main(int argc, char *argv[])
{
    /*
    uint16 numGlyphs=rand()%32+1;//let it be: 1..513 glyphs
     //generating glyph table
     simpleGlyph *sg=new simpleGlyph[numGlyphs];
     gener_simpleGlyphArr(sg,numGlyphs);
     glyf_table gt;
     gt.numGlyphs=gt.numSimpleGlyph=numGlyphs;
     gt.sg=sg;
     gt.printTable("C:\\glyf_table.ttt");
    cmap_table ct;
    rand();
    gener_cmap_table(ct);
    cout<<"number of tables: "<<ct.numTables<<endl;
    ct.printTable("C:\\cmap.ttt");*/
    /*head_table ht;
    gener_head_table(ht,-5,-3,5,3);
    ht.printTable("C:\\head.ttt");
    short param[]={-1,1,-2,2,-1024,1024,-32768,32767,0,136};
    hhea_table hht;
    gener_hhea_table(hht,param,5);
    hht.printTable("C:\\hhea.ttt");
    longHorMetric * lhm=new longHorMetric[5];
    for(int i=0;i<5;i++){
    lhm[i].advanceWidth=i;
    lhm[i].lsb=-i;
    }
    short lsb[]={1,2,3};
    hmtx_table hmt;
    gener_hmtx_table(hmt,5,8,lhm,lsb);
    hmt.printTable("C:\\hmtx.ttt");
    post_table pt;
    name_table nt;
    gener_name_table(nt,5,"C:\\records.rec");
    //gener_post_table_v1_3(pt,1,2,3,4,5);
    nt.printTable("C:\\name.ttt");*/
    system("PAUSE");
    return EXIT_SUCCESS;
}
