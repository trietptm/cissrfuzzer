#include "name_table.h"
nameRecord gener_nameRecord(uint16 nameid, uint16 strlen, uint16 offSet){
           nameRecord nr;
           nr.platformID=3*(rand()%2);//unicode or MS
           nr.platformSpecificID=rand()%33;
           nr.languageID=rand()%151;
           nr.nameID=nameid;
           nr.length=strlen;  
           nr.offset=offSet;        
};
//todo: the NameRecords are sorted by platform ID, then platform-specific ID, then language ID, and then by name ID.
void gener_name_table(name_table &n_t,uint16 num_records, char* path_to_records){
           n_t.format=0;
           n_t.count=num_records;
           n_t.stringOffset=12*n_t.count+6;
           n_t.records = new nameRecord[n_t.count];
           FILE *stream;
           char buff[65535]; //64k memory requiered    
           std::string text;
           std::string tmp; 
           uint16 offset=0;
           if((stream=fopen(path_to_records, "r"))==NULL){
                printf("file open error.\n");
           }else{
                 for(int i=0;i<n_t.count;i++){
                         fgets(buff,65535,stream);
                         tmp=std::string(buff);
                         if(i!=n_t.count-1)tmp=tmp.substr(0,tmp.length()-1);
                         text=text+tmp;
                         //PID,PSID&NID set randomly, generating windows symbols
                         //todo: consistent with 'cmap' table!!
                         /*n_t.records[i].platformID=3*(rand()%2);
                         if(n_t.records[i].platformID==2) n_t.records[i].platformID=3;*/
                         n_t.records[i].platformID=3;
                         //n_t.records[i].platformSpecificID=rand()%7;//%13 if PID=1, but nobody cares, it's just a name!
                         n_t.records[i].platformSpecificID=0;
                         //n_t.records[i].languageID=rand()%151;
                         n_t.records[i].languageID=0;
                         n_t.records[i].nameID=i;//
                         n_t.records[i].length=tmp.length();
                         n_t.records[i].offset=offset;
                         offset+=(uint16)tmp.length();
                 }
                 fclose(stream);
           }
           
           n_t.name = text;
};
uint32 name_table::getSize(){return stringOffset+name.length(); }
//parametr length calulating in the previous function
void gener_name_table_header(TableDirectoryNod &tdn,uint32 length, uint32 offSet){
                  tdn.tag=0x6e616d65;
                  tdn.length=length;
                  tdn.offset=offSet;
};
void name_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     file<<(char)0<<(char)0;//format default 0x00000000
     file<<(char)(count>>8)<<(char)(count%256);//number of records
     file<<(char)(stringOffset>>8)<<(char)(stringOffset%256);//number of records    
     for(uint16 i=0;i<count;i++){
                file<<(char)(records[i].platformID>>8)<<(char)((records[i].platformID)%256);
                file<<(char)(records[i].platformSpecificID>>8)<<(char)(records[i].platformSpecificID%256);
                file<<(char)(records[i].languageID>>8)<<(char)((records[i].languageID)%256);
                file<<(char)(records[i].nameID>>8)<<(char)((records[i].nameID)%256);
                file<<(char)(records[i].length>>8)<<(char)((records[i].length)%256);
                file<<(char)(records[i].offset>>8)<<(char)((records[i].offset)%256);
     };
     file<<name.c_str(); //last symbol is '\n', that's why conversion to char* here
     int ofs=getSize();
     if(ofs%4!=0){
          for(int i=0;i<4-ofs%4;i++) file<<(char)0;
     }
     file.close();
};
