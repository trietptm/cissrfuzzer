#include "cff_table.h"
uint32 index::getSize(){
       uint32 res=2;
       if(count==0) return res;
       else{
           res++;//+= 1-byte offSize
           switch (offSize){
           case 1:
                 res+=count+1;//count+1 1-byte offsets
                 res+=off1[count]-1;
                 break;
            case 2:
                 res+=2*count+2;//count+1 2-byte offsets
                 res+=off2[count]-1;
                 break;
            case 3:
                 res+=3*count+3;//count+1 3-byte offsets
                 uint32 num;
                 num=off3[0][count]<<16+off3[1][count]<<8+off3[2][count]-1;
                 res+=num;
                 break;
            default:   //default offSize==4
                 res+=4*count+4;//count+1 4-byte offsets
                 res+=off4[count]-1;
                 break;
           }
       }
       return res;
};
uint32 stringId::getSize(){
       uint32 res=2;
       if(count==0) return res;
       else{
           res++;//+= 1-byte offSize
           switch (offSize){
           case 1:
                 res+=count+1;//count+1 1-byte offsets
                 break;
            case 2:
                 res+=2*count+2;//count+1 2-byte offsets
                 cout<<"res:"<<res<<endl;
                 break;
            case 3:
                 res+=3*count+3;//count+1 3-byte offsets
                 break;
            default:   //default offSize==4
                 res+=4*count+4;//count+1 4-byte offsets
                 break;
           }
       cout<<"local offset: "<<res<<endl;
       for(int i=0;i<count; i++) res+=str[i].length();
       }
       return res;
};
void index::printId(ofstream &file){
     file<<(char)(count>>8)<<(char)(count%256);
     if(count!=0){
     file<<offSize;
     switch (offSize){
            case 1:
                 for(int i=0;i<count+1 ;i++)
                     file<<off1[i];
                 for(int i=0;i<off1[count]-1;i++)
                     file<<data[i];
                 break;
            case 2:
                 for(int i=0;i<count+1 ;i++)
                     file<<(char)(off2[i]>>8)<<(char)(off2[i]%256);
                 for(int i=0;i<off2[count]-1;i++)
                     file<<data[i];
                 break;
            case 3:
                 for(int i=0;i<count+1 ;i++)
                     file<<off3[0][i]<<off3[1][i]<<off3[2][i];
                 uint32 num;
                 num=off3[0][count]<<16+off3[1][count]<<8+off3[2][count]-1;
                 for(int i=0;i<num;i++)
                     file<<data[i];
                 break;
            default:   //default offSize==4
                 for(int i=0;i<count+1 ;i++){
                     file<<(char)(off4[i]>>24)<<(char)((off4[i]>>16)&255);
                     file<<(char)((off4[i]>>8)&255)<<(char)(off4[i]%256);
                 }
                 for(int i=0;i<off4[count]-1;i++)
                     file<<data[i];
                 break;
     }
     }
};
void stringId::printId(ofstream &file){
     file<<(char)(count>>8)<<(char)(count%256);
     if(count!=0){ 
     file<<offSize;
     switch (offSize){
            case 1:
                 for(int i=0;i<count+1 ;i++)
                     file<<off1[i];
                 break;
            case 2:
                 for(int i=0;i<count+1 ;i++)
                     file<<(char)(off2[i]>>8)<<(char)(off2[i]%256);
                 break;
            case 3:
                 for(int i=0;i<count+1 ;i++)
                     file<<off3[0][i]<<off3[1][i]<<off3[2][i];
                 break;
            default:   //default offSize==4
                 for(int i=0;i<count+1 ;i++){
                     file<<(char)(off4[i]>>24)<<(char)((off4[i]>>16)&255);
                     file<<(char)((off4[i]>>8)&255)<<(char)(off4[i]%256);
                 }
                 break;
     }
     for(int i=0;i<count;i++) file<<str[i];
     }
}
void gener_cff_table(cff_table &cft){
     cft.major=(char)1;
     cft.minor=(char)0;
     cft.hdrsize=(char)4;
     cft.offsize=(char)1;
     //generating name: 
     //in our case name has only one entry(1 font)
     cft.name.count=1;
     cft.name.offSize=(char)1;
     cft.name.off1=new char[2];
     cft.name.off1[0]=(char)1;
     cft.name.off1[1]=(char)65;
     cft.name.data="0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";
     //generating top Dict index and data
     cft.topDict.count=1;//count must be same with count in name Index
     cft.topDict.offSize=1;
     cft.topDict.off1=new char[2];//for 1 entry required 2 offsets
     cft.topDict.off1[0]=(char)1;
     /*
     too much dependencies with other data, will be filled later
     some of depencies:
          - charstring type(opcode 12 6) affects charstring index and global/local subr index
          - 
     */
     srand ( time(NULL) );
     /*string s="";
     for(int i=0;i<256;i++)
             s.append(1,(char)(rand()%243+13));//excluding operators with codes 0..12
     s[2]=(char)0;//3rd byte - version opcode
     s[5]=(char)1;//6th byte - notice opcode
     s[8]=(char)12;s[9]=(char)0;//copyright opcode
     s[12]=(char)2;//fullName opcode
     s[15]=(char)3;//familyName opcode
     s[18]=(char)4;//weight opcode
     s[20]=(char)12;s[21]=(char)1;//isFixedPitch opcode
     s[22]=(char)0;s[23]=12;s[24]=(char)2;//italicAngle fixed=0;
     */
     //generating string index:
     cft.strings.count=2400; //more strings avaible, but they're unnecessary
     cft.strings.offSize=2;
     cft.strings.off2=new uint16[2401];
     cft.strings.str=new string[2400];
     ifstream fin;
     fin.open("strings.txt");
     if(!fin.good()) cout<<"bad file strings.txt!\n";
     else{
          for(int i=0;i<2400;i++)
               getline(fin,cft.strings.str[i]);
     }
     fin.close();
     cft.strings.off2[0]=1;
     for(int i=1;i<2401;i++){
             cft.strings.off2[i]=cft.strings.off2[i-1]+cft.strings.str[i-1].length();
     }
     //generating global subroutines index
     /*
     cft.globalSubr.count=rand()%65535;//we don't need too much subroutines, but we
     //had to cover all call graph
     0 subroutines, temporary
     */
     cft.globalSubr.count=0;
     uint16 numGlyph=rand()%254+1;//1..254 glyphs
     cft.charString.count=numGlyph;
     cft.charString.offSize=1;//1 byte offst enough for demo
     cft.charString.off1=new char[numGlyph+1];
     for(int i=0;i<numGlyph+1;i++) cft.charString.off1[i]=(char)i;
     
     //
};
void cff_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     //writting header
     file<<major<<minor<<hdrsize<<offsize;
     //writting Name section
     name.printId(file);
     //writting top dict index
     //just do it!
     //writting global subroutines
     globalSubr.printId(file);
     //writting string Index
     strings.printId(file);
     file.close();
};
uint32 cff_table::getSize(){
     uint32 res=4;
     res+=name.getSize();
     //res+=topDict.getSize();
     res+=globalSubr.getSize();
     cout<<"name+head+subr: "<<res<<endl;
     res+=strings.getSize();
     //res+=charString.getSize();
     return res;
}
