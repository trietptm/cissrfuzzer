#include "cff_table.h"
uint16 getRandWord(){ //genearting 2 byte random according dict data specification
     srand ( time(NULL)+rand()%rand() );
     uint16 res=0;
     short sign=rand()%2;
     if(sign==0) return (rand()%4+247)*256+(rand()%256);
     return (rand()%4+251)*256+(rand()%256);
};
char getRandByte(){//generating 1 byte operand
     srand ( time(NULL)+rand() );
     return (char)(32+(rand()%215));
};
short toSpecW(short val){
    if(val<0) return (-(val>>8)+251-1)*256+(-108-(val%256));
    return (val%256-108)+256*(247+(val>>8));
}
uint32 toSpecLw(short val){
        uint32 res=0;
        res+=(28<<16);
        res+= (val>>8)*256+val%256;
        return res;
} 
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
void gener_topDict(stringId &td){
     td.count=1;
     td.offSize=(char)1;
     td.off1=new char[2];
     td.off1[0]=1;
     td.str=new string[1];
     string s="";
     s.append(3,(char)0);
     uint16 wrd=getRandWord();
     s[0]=wrd>>8;
     s[1]=wrd%256;
     s[2]=0; //version opcode
     s.append(3,0);
     wrd=getRandWord();
     s[3]=wrd>>8;
     s[4]=wrd%256;
     s[5]=1;//notice opcode
     s.append(4,0);
     wrd=getRandWord();
     s[6]=wrd>>8;
     s[7]=wrd%256;
     s[8]=12;//copyright opcode (h)
     s[9]=0;//copyright opcode(l)
     s.append(3,0);
     wrd=getRandWord();
     s[10]=wrd>>8;
     s[11]=wrd%256;
     s[12]=2;//full name opcode
     s.append(3,0);
     wrd=getRandWord();
     s[13]=wrd>>8;
     s[14]=wrd%256;
     s[15]=3;//family name opcode
     s.append(3,0);
     wrd=getRandWord();
     s[16]=wrd>>8;
     s[17]=wrd%256;
     s[18]=4;//weight opcode
     s.append(3,0);
     s[19]=0x8b;
     s[20]=12;//isFixedPitch opcode(h)
     s[21]=1;//isFixedPitch opcode (l)
     s.append(3,0);
     wrd=getRandWord();
     s[22]=0x8b;
     s[23]=12;//italicAngle opcode (h)
     s[24]=2;//italicAngle opcode (l)
     s.append(3,0);
     s[25]=0x27;
     s[26]=12;//underline position(h)
     s[27]=3;//underline position(l)
     s.append(3,0);
     s[28]=0xBD;
     s[29]=12;//underline thichness(h)
     s[30]=4;//underline thichness(l)
     s.append(3,0);
     wrd=getRandWord();
     s[31]=0x8b;
     s[32]=12;//paintType (h)
     s[33]=5;//paintType (l)
     s.append(3,0);
     wrd=getRandWord();
     s[34]=0x8d;
     s[35]=12;//charstring type
     s[36]=6;//charstring type
     s.append(3,0);
     wrd=getRandWord();
     s[37]=wrd>>8;
     s[38]=wrd%256;
     s[39]=13;//uniqueId opcode
     s.append(5,0);
     s[40]=89;
     s[41]=89;
     s[42]=189;
     s[43]=189;
     s[44]=5;//fontBBox opcode (-50 -50 50 50)
     s.append(3,0);
     s[45]=139;
     s[46]=12;
     s[47]=8;//stroke Width opcode
     s.append(3,0);
     s[48]=0;
     s[49]=0;
     s[50]=17;//charstring offset opcode
     s.append(4,0);
     s[51]=0; //length
     s[52]=0; //offset h
     s[53]=0; //offset l
     s[54]=18;//Private opcode
     td.off1[1]=s.length()+1;
     td.str[0]=s;
}
void gener_privateDict(string &s){
     s="";
     s.append(15,0);
     s[0]=139;
     s[1]=6; //blueValues op
     s[2]=139;
     s[3]=7; //otherBlues op
     s[4]=139;
     s[4]=8; //familyBlues op
     s[5]=139;
     s[6]=9; //familyOtherBlues op
     s[7]=169;
     s[8]=10; //stdHW op
     s[9]=169;
     s[10]=11; //stdVW op
     s[11]=159;
     s[12]=20; //defaultWidthX op
     s[13]=159;
     s[14]=21; //nominalWidthX op
};
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
     //generating string index:
     cft.strings.count=32; //more strings avaible, but they're unnecessary
     cft.strings.offSize=2;
     cft.strings.off2=new uint16[33];
     cft.strings.str=new string[32];
     ifstream fin;
     fin.open("strings.txt");
     if(!fin.good()) cout<<"bad file strings.txt!\n";
     else{
          for(int i=0;i<32;i++)
               getline(fin,cft.strings.str[i]);
     }
     fin.close();
     cft.strings.off2[0]=1;
     for(int i=1;i<33;i++){
             cft.strings.off2[i]=cft.strings.off2[i-1]+cft.strings.str[i-1].length();
     }
     //generating global subroutines index  
     cft.globalSubr.count=0;
     //uint16 numGlyph=rand()%254+1;//1..254 glyphs
     uint16 numGlyph=32;
     cft.charString.count=numGlyph;
     cft.charString.offSize=(char)1;//1 byte offst enough for demo
     cft.charString.off1=new char[numGlyph+1];
     for(int i=0;i<numGlyph+1;i++) cft.charString.off1[i]=(char)(i+1);
     cft.charString.data=new char[numGlyph];
     for(int i=0;i<numGlyph;i++)cft.charString.data[i]=0x0e;
     gener_topDict(cft.topDict);
     uint16 offset=4+cft.name.getSize()+cft.topDict.getSize()+cft.strings.getSize()+cft.globalSubr.getSize();
     cft.topDict.str[0][48]=toSpecW(offset)>>8;
     cft.topDict.str[0][49]=toSpecW(offset)%256;
     gener_privateDict(cft.privateDict);
     offset+=cft.charString.getSize();
     cft.topDict.str[0][51]=cft.privateDict.length()+139;
     cft.topDict.str[0][52]=toSpecW(offset)>>8;
     cft.topDict.str[0][53]=toSpecW(offset)%256;
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
     charString.printId(file);
     //writting privateDict
     file<<privateDict;
     if(getSize()%4!=0) for(int i=0;i<4-getSize()%4;i++) file<<(char)0;
     file.close();
};
uint32 cff_table::getSize(){
     uint32 res=4;
     res+=name.getSize();
     res+=topDict.getSize();
     //cout<<"before glabalsubr: "<<res<<endl;
     res+=globalSubr.getSize();
     //cout<<"strings: "<<strings.getSize()<<endl;
     res+=strings.getSize();
     //cout<<"charString: "<<charString.getSize()<<endl;
     res+=charString.getSize();
     res+=privateDict.length();
     return res;
}
