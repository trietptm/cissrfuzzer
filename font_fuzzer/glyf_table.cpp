#include "glyf_table.h"
void simpleGlyph::printGlyph(ofstream &file){
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
     for(int i=0;i<=endPtsOfContour[numberOfContours-1];i++){
             file<<flags[i];
     }
     for(int i=0;i<=endPtsOfContour[numberOfContours-1];i++){
             file<<xCordinates[i];
     }
     for(int i=0;i<=endPtsOfContour[numberOfContours-1];i++){
             file<<yCordinates[i];
     }
}
uint32 simpleGlyph::getSize(){
       uint32 res=12; //all non-arrays
       res+=instructionLength;//length of 1-byte instructions
       res+=2*numberOfContours;//last points indecies of all contours
       res+=3*endPtsOfContour[numberOfContours-1]+3;//x-y coordinates+flags
       return res;
};
//array of simple glyphs should be initialized
void gener_simpleGlyphArr(simpleGlyph* sg,uint16 numSimpleGlyph){
     srand ( time(NULL) );
     for(uint16 i=0;i<numSimpleGlyph;i++){
             sg[i].numberOfContours=(rand()%3)+1;//number of contours
              //bounding box:
              //sg[i].xMin=(rand()%256)-128;
              //sg[i].yMin=(rand()%256)-128;
              //sg[i].xMax=sg[i].xMin+(rand()%128);
              //sg[i].yMax=sg[i].yMin+(rand()%128);
              sg[i].xMin=-100+(rand()%100);
              sg[i].yMin=-100+(rand()%100);
              sg[i].xMax=100+(rand()%100);
              sg[i].yMax=100+(rand()%100);
              //generating end points of contours. last element of array is number of points
              sg[i].endPtsOfContour=new uint16[sg[i].numberOfContours];
              uint16 numPts=sg[i].endPtsOfContour[sg[i].numberOfContours-1]+1;
              sg[i].endPtsOfContour[0]=rand()%20+2;
              for(uint16 j=1;j<sg[i].numberOfContours;j++)
                     sg[i].endPtsOfContour[j]=sg[i].endPtsOfContour[j-1]+rand()%10+4;
              //generating instructions
              //sg[i].instructionLength=rand()%64+1;
              sg[i].instructionLength=1;
              sg[i].instructions=new char[sg[i].instructionLength];
              for(uint16 j=0;j<sg[i].instructionLength;j++)
                      //sg[i].instructions[j]=(char)(rand()%256);
                      sg[i].instructions[j]=(char)0x7a;
              //generating flags
              sg[i].flags=new char[numPts];
              for(uint16 j=0;j<numPts;j++)
                      //sg[i].flags[j]=(char)(((rand()%256)|96)&236);//236=11101100b mask, that applies to flags,
                      sg[i].flags[j]=236;
                      //that guarantee correct simplification
              sg[i].yCordinates=new char[numPts];
              sg[i].xCordinates=new char[numPts];
              //generating x cordiates
              for(uint16 j=0;j<numPts;j++)
                      //sg[i].xCordinates[j]=(char)(rand()%(sg[i].xMax-sg[i].xMin)+sg[i].xMin);  
                      sg[i].xCordinates[j]=(char)(rand()%256);  
              //generating y cordiates 
              for(uint16 j=0;j<numPts;j++) 
                      //sg[i].yCordinates[j]=(char)(rand()%(sg[i].yMax-sg[i].yMin)+sg[i].yMin);   
                       sg[i].yCordinates[j]=(char)(rand()%256);    
              int k=0;
              int start=0;//ordinal number of  point in new contour             
              for(uint16 j=0;j<numPts-1;j++){
                    if(j==sg[i].endPtsOfContour[k]){
                         sg[i].xCordinates[j]=sg[i].xCordinates[start];
                         sg[i].yCordinates[j]=sg[i].yCordinates[start];
                         start=j+1;
                         k++;
                    }
              }
              sg[i].xCordinates[numPts-1]=sg[i].xCordinates[sg[i].endPtsOfContour[sg[i].numberOfContours-2]+1];
              sg[i].yCordinates[numPts-1]=sg[i].yCordinates[sg[i].endPtsOfContour[sg[i].numberOfContours-2]+1];
              
              /*
              sg[i].numberOfContours=1;
              sg[i].xMin=-300;
              sg[i].yMin=-300;
              sg[i].xMax=300;
              sg[i].yMax=300;
              sg[i].endPtsOfContour=new uint16[1];
              sg[i].endPtsOfContour[0]=4+1;
              uint16 numPts=sg[i].endPtsOfContour[0]+1;
              sg[i].instructionLength=1;
              sg[i].instructions=new char[1];
              sg[i].instructions[0]=0x7a;
              sg[i].flags=new char[numPts];
              sg[i].yCordinates=new char[numPts];
              sg[i].xCordinates=new char[numPts];
              sg[i].yCordinates[5]=0;
              sg[i].xCordinates[5]=0;
              sg[i].flags[5]=236;
              sg[i].yCordinates[4]=0;
              sg[i].xCordinates[4]=20;
              sg[i].flags[4]=236;
              sg[i].yCordinates[3]=0;
              sg[i].xCordinates[3]=20;
              sg[i].flags[3]=236;
              sg[i].yCordinates[2]=20;
              sg[i].xCordinates[2]=100;
              sg[i].flags[2]=228;
              sg[i].yCordinates[1]=20;
              sg[i].xCordinates[1]=20;
              sg[i].flags[1]=232;
              sg[i].yCordinates[0]=0;
              sg[i].xCordinates[0]=100;
              sg[i].flags[0]=224;
              */
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
     int ofs=getSize();
     if(ofs%4!=0){
          for(int i=0;i<4-ofs%4;i++) file<<(char)0;
     }
     file.close();
};
uint32 glyf_table::getSize(){
     //todo: expand for compound glyphs
     uint32 size=0;
     for(uint16 i=0;i<numSimpleGlyph;i++) size+=sg[i].getSize();
     return size;
};
