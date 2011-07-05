
#include "cmap_table.h"
#include "font_directory_table.h"
#include "name_table.h"
#include "hmtx_table.h"
#include "hhea_table.h"
#include "head_table.h"
#include "post_table.h"
//for now checked writing and creating functions of:
//post,name,hmtx,hhea,head
int main(int argc, char *argv[])
{
    cmap_table ct;
    rand();
    gener_cmap_table(ct);
    cout<<"number of tables: "<<ct.numTables<<endl;
    ct.printTable("C:\\cmap.ttt");
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
