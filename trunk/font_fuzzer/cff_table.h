//cff_table
#include "header.h"
#include "font_directory_table.h"
struct index{
       uint16 count;
       char offSize;//size of offset
       char * off1;//for 1-byte offsets
       uint16 * off2;//for 2-byte offsets
       char * off3[3];//for 3-byte offsets
       uint32 * off4;//for 4-byte offsets
       //only one of previous 4 arrays should be in each table;
       //size of arrays specifies by count+1
       char * data; //size determines by last offset-1
       virtual void printId(ofstream &file);
       virtual uint32 getSize();
};
struct stringId:public index{
       string * str;
       virtual void printId(ofstream &file);
       virtual uint32 getSize();
};
struct cff_table:public table{
       //
       char major;      //const=1
       char minor;      //const=0
       char hdrsize;    //header size, in bytes, const=4
       char offsize;    //1,2,3,4 - avaible offset size(in bytes)
       index name;      //name shouldn't contain next symbols: [ ] { } < > % /
       // (NUL) (space) \n \r \t max length - 63(127)
       index topDict;
       stringId strings;
       index globalSubr;
       index charString;
       char * privateDict; //temporary not avaible
       virtual void printTable(char* path);
       virtual uint32 getSize();
};
extern void gener_cff_table(cff_table &cft);
