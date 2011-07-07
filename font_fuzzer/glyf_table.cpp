#include "glyf_table.h"
void simpleGlyph::printGlyph(ofstream &file){
     //TODO: extend this function with other flags
     file<<(char)(numberOfContours>>8)<<(char)((numberOfContours)%256);
     file<<(char)(xMin>>8)<<(char)(xMin%256);
     file<<(char)(yMin>>8)<<(char)(yMin%256);
     file<<(char)(xMax>>8)<<(char)(xMax%256);
     file<<(char)(yMax>>8)<<(char)(yMax%256);
     for(int i=0;i<numberOfContours;i++){
             file<<(char)(endPtsOfContour[i]>>8)<<(char)(endPtsOfContour[i]%256);        
     }
     file<<(char)(instructionLength>>8)<<(char)(instructionLength%256);
     for(int i=0;i<instructionLength;i++){
             file<<instructions[i];        
     }
     for(int i=0;i<endPtsOfContour[numberOfContours-1];i++){
             file<<flags[i];
     }
     for(int i=0;i<endPtsOfContour[numberOfContours-1];i++){
             file<<xCordinates[i];
     }
     for(int i=0;i<endPtsOfContour[numberOfContours-1];i++){
             file<<yCordinates[i];
     }
}
uint32 simpleGlyph::getSize(){
       uint32 res=12; //all non-arrays
       res+=instructionLength;//length of 1-byte instructions
       res+=2*numberOfContours;//last points indecies of all contours
       res+=3*endPtsOfContour[numberOfContours-1];//x-y coordinates+flags
       return res;
};
//array of simple glyphs should be initialized
void gener_simpleGlyphArr(simpleGlyph* sg,uint16 numSimpleGlyph){
     for(uint16 i=0;i<numSimpleGlyph;i++){
              sg[i].numberOfContours=(rand()%3)+1;//number of contours
              //bounding box:
              sg[i].xMin=(rand()%256)-128;
              sg[i].yMin=(rand()%256)-128;
              sg[i].xMax=sg[i].xMin+(rand()%128);
              sg[i].yMax=sg[i].yMin+(rand()%128);
              //generating end points of contours. last element of array is number of points
              sg[i].endPtsOfContour=new uint16[sg[i].numberOfContours];
              uint16 numPts=sg[i].endPtsOfContour[sg[i].numberOfContours-1];
              sg[i].endPtsOfContour[0]=rand()%20+1;
              for(uint16 j=1;j<sg[i].numberOfContours;j++)
                     sg[i].endPtsOfContour[j]=sg[i].endPtsOfContour[j-1]+rand()%20;
              //generating instructions
              sg[i].instructionLength=rand()%64+1;
              sg[i].instructions=new char[sg[i].instructionLength];
              for(uint16 j=0;j<sg[i].instructionLength;j++)
                      sg[i].instructions[j]=(char)(rand()%256);
              //generating flags
              sg[i].flags=new char[numPts];
              for(uint16 j=0;j<numPts;j++)
                      sg[i].flags[j]=(char)((rand()%256)&236);//236=11101100b mask, that applies to flag,
                      //that guarantee correct simplification
              //generating x cordiates
              sg[i].xCordinates=new char[numPts];
              for(uint16 j=0;j<numPts;j++)
                      sg[i].xCordinates[j]=(char)(rand()%256);
              //generating y cordiates 
              sg[i].yCordinates=new char[numPts];
              for(uint16 j=0;j<numPts;j++) 
                      sg[i].xCordinates[j]=(char)(rand()%256);        
     }
};
short glyf_table::getxMax(){
       short xMax=sg[0].xMax;
       for(uint16 i=0; i<numSimpleGlyph;i++)
             if(xMax<sg[i].xMax) xMax=sg[i].xMax;
       return xMax;       
};
short glyf_table::getxMin(){
       short xMin=sg[0].xMin;
       for(uint16 i=0; i<numSimpleGlyph;i++)
             if(xMin>sg[i].xMin) xMin=sg[i].xMin;
       return xMin;       
};
short glyf_table::getyMax(){
       short yMax=sg[0].yMax;
       for(uint16 i=0; i<numSimpleGlyph;i++)
             if(yMax<sg[i].yMax) yMax=sg[i].yMax;
       return yMax;       
};
short glyf_table::getyMin(){
       short yMin=sg[0].yMin;
       for(uint16 i=0; i<numSimpleGlyph;i++)
             if(yMin>sg[i].yMin) yMin=sg[i].yMin;
       return yMin;       
};
uint16 glyf_table::maxContours(){
       uint16 num=sg[0].numberOfContours;
       for(uint16 i=0; i<numSimpleGlyph;i++)
                  if(num<sg[i].numberOfContours) num=sg[i].numberOfContours;
       return num;
              
};
uint16 glyf_table::maxPoints(){
       uint16 num=sg[0].endPtsOfContour[sg[0].numberOfContours-1];
       for(uint16 i=0; i<numSimpleGlyph;i++)
                  if(num<sg[i].endPtsOfContour[sg[i].numberOfContours-1]) num=sg[i].endPtsOfContour[sg[i].numberOfContours-1];
       return num+1;
              
};
uint16 glyf_table::maxInstr(){
       uint16 num=sg[0].instructionLength;
       for(uint16 i=0; i<numSimpleGlyph;i++)
                  if(num<sg[i].instructionLength) num=sg[i].instructionLength;
       return num;
};
void glyf_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     if(!file.good()) printf("output file corrupted!\n");
     for(uint16 i=0; i<numSimpleGlyph;i++){
           sg[i].printGlyph(file);
     }
     file.close();
};
uint32 glyf_table::getSize(){
     //todo: expand for compound glyphs
     uint32 size=0;
     for(uint16 i=0;i<numSimpleGlyph;i++) size+=sg[i].getSize();
     return size;
};
