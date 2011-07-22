#include <time.h>
#include <sys/stat.h>
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
#include "cff_table.h"
//for now checked writing and creating functions of:
//post,name,hmtx,hhea,head
uint32 CalcTableChecksum(uint32 *table, uint32 numberOfBytesInTable){
    uint32 sum = 0;
    //uint32 nLongs = (numberOfBytesInTable + 3) / 4;
    uint32 *Endptr = table+((numberOfBytesInTable+3) & ~3) / sizeof(uint32);
    while (table < Endptr)
	sum += *table++;
    //while (nLongs-- > 0)
        //sum += *table++;
    return sum;
};
uint32 checkSum(table &t){
    t.printTable("tmp.tmp");
    struct stat results;
    if (stat("tmp.tmp", &results) == 0) {1;}
    char * buff =new char[results.st_size]; 
    ifstream myFile ("tmp.tmp", ios::in | ios::binary);
    myFile.read(buff, results.st_size);
    myFile.close();
    uint32 * table=new uint32[results.st_size/4];
    for( uint32 i=0;i<results.st_size/4;i++){
         table[i]=(((uint32)buff[i*4])<<24)+(((uint32)buff[i*4+1])<<16)+(((uint32)buff[i*4+2])<<8)+((uint32)buff[i*4+3]);
    }
    uint32 result=CalcTableChecksum( table, results.st_size);
    remove("tmp.tmp");
    delete[] buff;
    delete[] table;
    return result;       
}
void generate_tables(char * path){
     srand ( time(NULL) );
     uint16 numGlyphs=rand()%512+1;//let it be: 1..513 glyphs
     //uint16 numGlyphs=10;
     cout<<"nuber of glyphs: "<<numGlyphs<<endl;
     //generating glyph table
     //there are 13 tables,so we have 13 table directory nods
     TableDirectoryNod * tdn=new TableDirectoryNod[13];
     for(int i=0;i<13;i++) tdn[i].checkSum=0;
     uint32 offset=13*16+12;
     simpleGlyph *sg=new simpleGlyph[numGlyphs];
     gener_simpleGlyphArr(sg,numGlyphs);
     //generating glyf table
     glyf_table gt;
     gt.numGlyphs=gt.numSimpleGlyph=numGlyphs;
     gt.sg=sg;
     //generating cmap table
     cmap_table ct;
     gener_cmap_table(ct,numGlyphs);
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
     string names=".aaa.aab.wtf.omg.dffd.sdfsdfsdf.sdfsdfs.sdfsdfsd.fsd.werwer.werewrw.erere.";
     uint16 num_new_glyphs=names.length();
     //gener_post_table_v2(pt,numGlyphs,names.length(),names.c_str());
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
     gener_name_table(nt,20,"nameRecords.txt");
     //generating 'os/2' table
     os_2_table ot;
     gener_os_2_table(ot);
     //generating prep table
     prep_table prt;
     gener_prep_table(prt);
     //generating loca table
     loca_table lc;
     uint32 * offsets=new uint32[numGlyphs+1];
     offsets[0]=0;
     for(uint16 i=1;i<=numGlyphs;i++){
                offsets[i]=offsets[i-1]+sg[i-1].getSize();
     }
     gener_loca_table(lc,numGlyphs,offsets);
     //generating 'cvt' table
     cvt_table cvt;
     gener_cvt_table(cvt);
     //generating fpgm table
     fpgm_table fgt;
     gener_fpgm_table(fgt);
     //generating font directory table
     //-----------------------------------------------//
     font_directory_table fdt;
     //generating table directory nod for 'os/2'
     tdn[0].tag=0x4f532f32;
     tdn[0].offset=offset;
     tdn[0].length=ot.getSize();
     //tdn[0].checkSum=checkSum(ot);
     offset+=ot.getSize();
     //generating table directory nod for 'cmap'
     tdn[1].tag=0x636d6170;
     tdn[1].offset=offset;
     tdn[1].length=ct.getSize();
     //tdn[1].checkSum=checkSum(ct);
     offset+=ct.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating  table directory nod for 'cvt'
     tdn[2].tag=0x63767420;
     tdn[2].offset=offset;
     tdn[2].length=cvt.getSize();
     //tdn[2].checkSum=checkSum(cvt);
      offset+=cvt.getSize();
      //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating  table directory nod for 'fpgm'
     tdn[3].tag=0x6670676d;
     tdn[3].offset=offset;
     tdn[3].length=fgt.getSize();
     //tdn[3].checkSum=checkSum(ot);
      offset+=fgt.getSize();
      //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'glyf'
     tdn[4].tag=0x676c7966;
     tdn[4].offset=offset;
     tdn[4].length=gt.getSize();
     //tdn[4].checkSum=checkSum(gt);
     offset+=gt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));  
     //generating table directory nod for 'head'
     tdn[5].tag=0x68656164;
     tdn[5].offset=offset;
     tdn[5].length=ht.getSize();
     //tdn[5].checkSum=checkSum(ht);
     offset+=ht.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'hhea'
     tdn[6].tag=0x68686561;
     tdn[6].offset=offset;
     tdn[6].length=hh.getSize();
     //tdn[6].checkSum=checkSum(hh);
     offset+=hh.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
      //generating table directory nod for 'hmtx'
     tdn[7].tag=0x686d7478;
     tdn[7].offset=offset;
     tdn[7].length=hmt.getSize();
     //tdn[7].checkSum=checkSum(hmt);
     offset+=hmt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating  table directory nod for 'loca'
     tdn[8].tag=0x6c6f6361;
     tdn[8].offset=offset;
     tdn[8].length=lc.getSize();
     //tdn[8].checkSum=checkSum(lc);
      offset+=lc.getSize();
      //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'maxp'
     tdn[9].tag=0x6d617870;
     tdn[9].offset=offset;
     tdn[9].length=mt.getSize();
     //tdn[9].checkSum=checkSum(mt);
     offset+=mt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'name'
     tdn[10].tag=0x6e616d65;
     tdn[10].offset=offset;
     tdn[10].length=nt.getSize();
     //tdn[10].checkSum=checkSum(nt);
     offset+=nt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'post'
     tdn[11].tag=0x706f7374;
     tdn[11].offset=offset;
     tdn[11].length=pt.getSize();
     //tdn[11].checkSum=checkSum(pt);
     offset+=pt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));   
      ////generating table directory nod for 'prep'
     tdn[12].tag=0x70726570;
     tdn[12].offset=offset;
     tdn[12].length=prt.getSize();
     //tdn[12].checkSum=checkSum(prt);
     offset+=prt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     ///
     gener_fdirectory_table(fdt,13,tdn);
     ///
     fdt.printTable(path);
     /*fdt.printTable("tmp.tmp");
     ifstream file;
     file.open("tmp.tmp", ios::in | ios::binary);
     */
     ot.printTable(path);
     ct.printTable(path);
     cvt.printTable(path);
     fgt.printTable(path); 
     gt.printTable(path);
     ht.printTable(path);
     hh.printTable(path);
     hmt.printTable(path);
     lc.printTable(path);
     mt.printTable(path);
     nt.printTable(path);
     pt.printTable(path);
     prt.printTable(path);
     
};
void gener_otf( char* path){
     //tables: cff,os/2,cmap,head,hhea,hmtx,maxp,name,post  
     //order of tables matches with definition order below:
     cff_table cft;//*
     os_2_table ost;//+
     cmap_table ct;//+
     head_table ht;//+
     hhea_table hh;//+
     hmtx_table hmt;//*
     maxp_table mt;//*
     name_table nt;//*
     post_table pt;//+
     uint32 offset=9*16+12;
     //generating tables
     gener_cff_table(cft);
     uint16 numGlyphs=cft.charString.count;
     gener_os_2_table(ost);
     gener_cmap_table(ct,numGlyphs);
     gener_head_table(ht,-50,-50,50,50);
     uint16 numOfLhm=rand()%(numGlyphs-2)+1;
     gener_hhea_table(hh,numOfLhm);
     gener_os_2_table(ost);
     gener_hmtx_table(hmt,numOfLhm,numGlyphs);
     /*   hhea generation   */
     //filling hhea with appropriate values
     hh.minLeftSideBearing=getMinlsb(hmt);
     hh.advanceWidthMax=getMaxAdvance(hmt);
     //calculating xMaxExtent for hhea
     uint16 xMaxExtent=20;
     hh.xMaxExtent=xMaxExtent;
     //calculating minRsb for hhea
     uint16 minRsb=5;
     hh.minRightSideBearing=minRsb;
     /*end of hhea generation*/
     short param[]={100,5,0,0,rand()%128,rand()%128,rand()%128,rand()%128,rand()%128,20,rand()%128,0};
     gener_maxp_table(mt,numGlyphs,param);
     mt.version=0x00005000;
     gener_name_table(nt,20,"nameRecords.txt");
     gener_post_table_v1_3(pt,0x30000);
     //later we will generate version 2 table
     /*   
          generation tables is over
                                        */
     TableDirectoryNod * tdn=new TableDirectoryNod[9];
     font_directory_table fdt;
     for(int i=0;i<9;i++) tdn[i].checkSum=0;
     //generating table directory nod for 'cff'
     tdn[0].tag=0x43464620;
     tdn[0].offset=offset;
     tdn[0].length=cft.getSize();
     offset+=cft.getSize();
     cout<<cft.getSize()<<endl;
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'os/2'
     tdn[1].tag=0x4f532f32;
     tdn[1].offset=offset;
     tdn[1].length=ost.getSize();
     //tdn[0].checkSum=checkSum(ot);
     offset+=ost.getSize();
     //generating table directory nod for 'cmap'
     tdn[2].tag=0x636d6170;
     tdn[2].offset=offset;
     tdn[2].length=ct.getSize();
     //tdn[1].checkSum=checkSum(ct);
     offset+=ct.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'head'
     tdn[3].tag=0x68656164;
     tdn[3].offset=offset;
     tdn[3].length=ht.getSize();;
     offset+=ht.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'hhea'
     tdn[4].tag=0x68686561;
     tdn[4].offset=offset;
     tdn[4].length=hh.getSize();
     offset+=hh.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
      //generating table directory nod for 'hmtx'
     tdn[5].tag=0x686d7478;
     tdn[5].offset=offset;
     tdn[5].length=hmt.getSize();
     offset+=hmt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'maxp'
     tdn[6].tag=0x6d617870;
     tdn[6].offset=offset;
     tdn[6].length=mt.getSize();
     offset+=mt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'name'
     tdn[7].tag=0x6e616d65;
     tdn[7].offset=offset;
     tdn[7].length=nt.getSize();
     offset+=nt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));
     //generating table directory nod for 'post'
     tdn[8].tag=0x706f7374;
     tdn[8].offset=offset;
     tdn[8].length=pt.getSize();
     offset+=pt.getSize();
     //padding offset with 0 to full 4 bytes
     if(offset%4!=0) offset+=(4-(offset%4));   
     gener_fdirectory_table(fdt,9,tdn);
     fdt.os.scalerType=0x4f54544f;
     fdt.printTable(path);
     cft.printTable(path);
     ost.printTable(path);
     ct.printTable(path);
     ht.printTable(path);
     hh.printTable(path);
     hmt.printTable(path);
     mt.printTable(path);
     nt.printTable(path);
     pt.printTable(path);     
};
int main(int argc, char *argv[])
{
    char path[]="fnt.otf";
    //gener_otf("fntX.otf");
    //generate_tables(path);
    cff_table cft;
    gener_cff_table(cft);
    cft.printTable(path);  
    /*cout<<cft.getSize();*/
    //cout<<hex<<toSpec(1000)<<endl;
    //cout<<hex<<toSpecW(1131)<<endl;   
    //cout<<hex<<toSpecLw(10000)<<endl; 
    system("PAUSE");
    return EXIT_SUCCESS;
}
