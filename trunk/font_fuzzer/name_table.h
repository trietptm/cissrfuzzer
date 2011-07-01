#include "header.h"
//table name consist of: format,count, stringOffset, nameRecord[], name
//description of they follows
struct nameRecord{
       uint16	platformID;	//Platform identifier code.
       //0: Unicode, 1: MAC, 2: reserved, 3:MS
       uint16	platformSpecificID;	//Platform-specific encoding identifier.
       //
       uint16	languageID;	//Language identifier. 0-150
       uint16	nameID;	//Name identifiers.
       //see spec of nameID here: http://developer.apple.com/fonts/TTRefMan/RM06/Chap6name.html
       uint16	length;	//Name string length in bytes.
       uint16	offset;	//Name string offset in bytes from stringOffset.
};
struct name_table{
       uint16	format;	//Format selector. Set to 0.
       uint16	count;	//The number of nameRecords in this name table.
       uint16	stringOffset;	//Offset in bytes to the beginning of the name character strings.
       //stringOffset calculates in next way: 12*count+6
       //12 - size of each nameRecord, 6 - size of 3 first fields
       nameRecord * records;	//The name records array. size of array equals to count
       std::string    name;	//character strings The character strings of the names. Note that these are not necessarily ASCII!
};
extern nameRecord gener_nameRecord(uint16 platf_ID, uint16 platf_SID, uint16 langID, uint16 nameid, uint16 strlen, uint16 offSet);                  
//in coded with ANSI file with address "path_to_records" each string is seperated name record
//each record not longer then 2^16
extern name_table gener_name_table(uint16 num_records, char* path_to_records);
extern uint32 name_table_size(name_table nt);
