#include <time.h>
#include "cmap_table.h"
#include "font_directory_table.h"
#include "name_table.h"
#include "hmtx_table.h"
#include "hhea_table.h"
#include "head_table.h"
#include "post_table.h"
#include "glyf_table.h"
#include "maxp_table.h"
#include  "cvt_table.h"
#include "prep_table.h"
#include "fpgm_table.h"
#include "os_2_table.h"
#include "loca_table.h"
//for now checked writing and creating functions of:
//post,name,hmtx,hhea,head
void generate_tables(){
     srand ( time(NULL) );
     uint16 numGlyphs=rand()%512;//let it be: 1..513 glyphs
     //uint16 numGlyphs=10;
     cout<<"nuber of glyphs: "<<numGlyphs<<endl;
     //generating glyph table
     //there are 13 tables,so we have 13 table directory nods
     TableDirectoryNod * tdn=new TableDirectoryNod[13];
     for(int i=0;i<13;i++) tdn[i].checkSum=0;
     uint32 offset=13*16+12;
     //order of tables: table directory,glyf,cmap,head,maxp,post,hhea,hmtx,name,
     simpleGlyph *sg=new simpleGlyph[numGlyphs];
     gener_simpleGlyphArr(sg,numGlyphs);
     //generating glyf table
     glyf_table gt;
     gt.numGlyphs=gt.numSimpleGlyph=numGlyphs;
     gt.sg=sg;
     //generating table directory nod for 'glyf'
     tdn[0].tag=0x676c7966;
     tdn[0].offset=offset;
     tdn[0].length=gt.getSize();
     offset+=gt.getSize();
     //generating cmap table
     cmap_table ct;
     gener_cmap_table(ct);
     //generating table directory nod for 'cmap'
     tdn[1].tag=0x636d6170;
     tdn[1].offset=offset;
     tdn[1].length=ct.getSize();
     offset+=ct.getSize();
     //generating head table
     //indexToLocFormat=1, offsets in 'loca' are long! 
     head_table ht;
     gener_head_table(ht,gt.getxMin(),gt.getyMin(),gt.getxMax(),gt.getyMax());
     //generating table directory nod for 'head'
     tdn[2].tag=0x68656164;
     tdn[2].offset=offset;
     tdn[2].length=ht.getSize();
     offset+=ht.getSize();
     //generating maxp table
     maxp_table mt;
     short param[]={gt.maxPoints(),gt.maxContours(),0,0,rand()%128,rand()%128,rand()%128,rand()%128,rand()%128,gt.maxInstr(),rand()%128,0};
     //array param described in function gener_maxp_table(...)
     gener_maxp_table(mt,numGlyphs,param);
     //generating table directory nod for 'maxp'
     tdn[3].tag=0x6d617870;
     tdn[3].offset=offset;
     tdn[3].length=mt.getSize();
     offset+=mt.getSize();
     //generating post table
     post_table pt;
     gener_post_table_v1_3(pt,0x30000);
     //generating table directory nod for 'post'
     tdn[4].tag=0x706f7374;
     tdn[4].offset=offset;
     tdn[4].length=pt.getSize();
     offset+=pt.getSize();
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
     //generating table directory nod for 'hhea'
     tdn[5].tag=0x68686561;
     tdn[5].offset=offset;
     tdn[5].length=hh.getSize();
     offset+=hh.getSize();
     //hhea table not filled with marginal parametrs of lsb, rsb, xMaxExtend and some other
     //generating hmtx
     hmtx_table hmt;
     gener_hmtx_table(hmt,numOfLhm,numGlyphs);
     //generating table directory nod for 'hmtx'
     tdn[6].tag=0x686d7478;
     tdn[6].offset=offset;
     tdn[6].length=hmt.getSize();
     offset+=hmt.getSize();
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
     gener_name_table(nt,ct.numTables,"nameRecords.txt");
     //generating table directory nod for 'name'
     tdn[7].tag=0x6e616d65;
     tdn[7].offset=offset;
     tdn[7].length=nt.getSize();
     offset+=nt.getSize();
     //generating 'os/2' table
     os_2_table ot;
     gener_os_2_table(ot);
     //generating table directory nod for 'os/2'
     tdn[8].tag=0x4f532f32;
     tdn[8].offset=offset;
     tdn[8].length=ot.getSize();
     offset+=nt.getSize();
     //generating prep table
     prep_table prt;
     gener_prep_table(prt);
     ////generating table directory nod for 'prep'
     tdn[9].tag=0x70726570;
     tdn[9].offset=offset;
     tdn[9].length=prt.getSize();
     offset+=prt.getSize();
     //generating loca table
     loca_table lc;
     uint32 * offsets=new uint32[numGlyphs+1];
     offsets[0]=0;
     for(uint16 i=1;i<=numGlyphs;i++){
                offsets[i]=offsets[i-1]+sg[i-1].getSize();
     }
     gener_loca_table(lc,numGlyphs,offsets);
     //generating  table directory nod for 'loca'
     tdn[10].tag=0x6c6f6361;
     tdn[10].offset=offset;
     tdn[10].length=lc.getSize();
      offset+=lc.getSize();
     //generating 'cvt' table
     cvt_table cvt;
     gener_cvt_table(cvt);
     //generating  table directory nod for 'cvt'
     tdn[11].tag=0x63767420;
     tdn[11].offset=offset;
     tdn[11].length=cvt.getSize();
      offset+=cvt.getSize();
     //generating fpgm table
     fpgm_table fgt;
     gener_fpgm_table(fgt);
     //generating  table directory nod for 'fpgm'
     tdn[12].tag=0x6670676d;
     tdn[12].offset=offset;
     tdn[12].length=fgt.getSize();
      offset+=fgt.getSize();
     //generating font directory table
     font_directory_table fdt;
     gener_fdirectory_table(fdt,13,tdn);
     ///
     fdt.printTable("C:\\tab.ttf");
     gt.printTable("C:\\tab.ttf");
     ct.printTable("C:\\tab.ttf");
     ht.printTable("C:\\tab.ttf");
     mt.printTable("C:\\tab.ttf");
     pt.printTable("C:\\tab.ttf");
     hh.printTable("C:\\tab.ttf");
     hmt.printTable("C:\\tab.ttf");
     nt.printTable("C:\\tab.ttf");
     ot.printTable("C:\\tab.ttf");
     prt.printTable("C:\\tab.ttf");
     lc.printTable("C:\\tab.ttf");
     cvt.printTable("C:\\tab.ttf");
     fgt.printTable("C:\\tab.ttf");
     
     /*for(int i=0;i<nt.count;i++){
             cout<<"PId: "<<nt.records[i].platformID<<" PSId: "<<nt.records[i].platformSpecificID;
     }*/
}
int main(int argc, char *argv[])
{
    generate_tables();
    /*glyf_table gt;
    simpleGlyph * sg=new simpleGlyph[10];
    gener_simpleGlyphArr(sg,10);
    gt.sg=sg;
    gt.numSimpleGlyph=10;
    ofstream file;  
    char path[]="E:\\glf\\fontGlyphX.ttt";
    for(int i=0;i<10;i++){
              path[16]=(char)(i+69);
              printf(path);
              cout<<endl;
              file.open(path,ios::binary|ios::app);
              cout<<"good file: "<<file.good()<<" : "<<sg[i].getSize()<<endl;
             sg[i].printGlyph(file);
             file.close();
    }
    gt.printTable("E:\\glf\\glyfs.gg");*/
    system("PAUSE");
    return EXIT_SUCCESS;
}
