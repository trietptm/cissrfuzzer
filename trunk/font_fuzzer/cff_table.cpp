#include "cff_table.h"
uint16 getRandWord(){ //genearting 2 byte random according dict data specification
     srand ( time(NULL) );
     uint16 res=0;
     short sign=rand()%2;
     if(sign==0) return (rand()%4+247)*256+(rand()%256);
     return (rand()%4+251)*256+(rand()%256);
};
char getRandByte(){//generating 1 byte operand
     srand ( time(NULL)+rand() );
     return (char)(32+(rand()%215));
};
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
                 break;
            case 3:
                 res+=3*count+3;//count+1 3-byte offsets
                 break;
            default:   //default offSize==4
                 res+=4*count+4;//count+1 4-byte offsets
                 break;
           }
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
     cft.topDict.str=new string[1];
     //////////////////////////////////////
     string s="";
     s.append(43,0);
     uint16 rnd=getRandWord();
     s[0]=(char)(rnd>>8);
     s[1]=(char)(rnd%256);
     s[2]=(char)0;//3rd byte - version opcode
     rnd=getRandWord();
     s[3]=(char)(rnd>>8);
     s[4]=(char)(rnd%256);
     s[5]=(char)1;//6th byte - notice opcode
     rnd=getRandWord();
     s[6]=(char)(rnd>>8);
     s[7]=(char)(rnd%256);
     s[8]=(char)12;s[9]=(char)0;//copyright opcode
     rnd=getRandWord();
     s[10]=(char)(rnd>>8);
     s[11]=(char)(rnd%256);
     s[12]=(char)2;//fullName opcode
     rnd=getRandWord();
     s[13]=(char)(rnd>>8);
     s[14]=(char)(rnd%256);
     s[15]=(char)3;//familyName opcode
     rnd=getRandWord();
     s[16]=(char)(rnd>>8);
     s[17]=(char)(rnd%256);
     s[18]=(char)4;//weight opcode
     char brnd=getRandByte();
     s[19]=brnd;
     s[20]=(char)12;s[21]=(char)1;//isFixedPitch opcode
     s[22]=(char)0;s[23]=12;s[24]=(char)2;//italicAngle fixed=0
     brnd=getRandByte();
     s[25]=brnd;
     s[26]=(char)12;s[27]=(char)3;//1-byte underlinePosition 
     brnd=getRandByte();
     s[28]=brnd;
     s[29]=(char)12;s[30]=(char)4;//1-byte underline thickness
     brnd=getRandByte();
     s[31]=brnd;
     s[32]=(char)12;s[33]=(char)5;//1-byte Paint type
     s[34]=(char)2;s[35]=(char)12;s[36]=(char)6;//1-byte fixed charstring type
     rnd=getRandWord();
     s[37]=(char)(rnd>>8);
     s[38]=(char)(rnd%256);
     s[39]=(char)13; //unique id opcode
     brnd=getRandByte();
     s[40]=brnd;
     s[41]=(char)12;s[42]=(char)8;//stroke width opcode
     //skipped next instructionsL font metrix, fontB Box, xuid, and all after xuid
     cft.topDict.str[0]=s;
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
     topDict.printId(file);
     globalSubr.printId(file);
     //writting string Index
     strings.printId(file);
     file.close();
};
uint32 cff_table::getSize(){
     uint32 res=4;
     res+=name.getSize();
     res+=topDict.getSize();
     res+=globalSubr.getSize();
     cout<<"name+head+subr: "<<res<<endl;
     res+=strings.getSize();
     //res+=charString.getSize();
     return res;
}
