#include "name_table.h"
nameRecord gener_nameRecord(uint16 platf_ID, uint16 platf_SID, uint16 langID,uint16 nameid, uint16 strlen, uint16 offSet){
           nameRecord nr;
           nr.platformID=platf_ID;
           nr.platformSpecificID=platf_SID;
           nr.languageID=langID;
           nr.nameID=nameid;
           nr.length=strlen;  
           nr.offset=offSet;        
};
//todo: the NameRecords are sorted by platform ID, then platform-specific ID, then language ID, and then by name ID.
name_table gener_name_table(uint16 num_records, char* path_to_records){
           name_table n_t;
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
                return n_t;
           }else{
                 for(int i=0;i<n_t.count;i++){
                         fgets(buff,65535,stream);
                         tmp=std::string(buff);
                         if(i!=n_t.count-1)tmp=tmp.substr(0,tmp.length()-1);
                         text=text+tmp;
                         //i need something to do with PID,PSID and LID!
                         n_t.records[i].platformID=rand()%4;
                         n_t.records[i].platformSpecificID=rand()%7;//%13 if PID=1, but nobody cares, it's just a name!
                         n_t.records[i].languageID=rand()%151;
                         n_t.records[i].nameID=(rand()%(20-i))+i;//nameID were set randomly
                         n_t.records[i].length=tmp.length();
                         n_t.records[i].offset=offset;
                         offset+=(uint16)tmp.length();
                 }
                 fclose(stream);
           }
           
           n_t.name = text;
           return n_t;
};
uint32 name_table_size(name_table nt){return nt.stringOffset+nt.name.length(); }
//no need checksum!
uint32 name_table_checksum(name_table nt){
       uint32 sum=0;
       //first uint32 follows
       sum+=((nt.format)<<16)+nt.count;
       if(nt.count==0) return sum+((nt.stringOffset)<<16);
       else{
       
       }
       return sum;
};
TableDirectoryNod gener_name_table_header(name_table nt, uint32 offSet){
                  TableDirectoryNod tdn;
                  tdn.tag=0x6e616d65;
                  tdn.length=name_table_size(nt);
                  tdn.offset=offSet;
                  return tdn;
};
