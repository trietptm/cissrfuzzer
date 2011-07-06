#include "header.h"
#include "font_directory_table.h"
struct glyph{
       short numberOfContours;
       short xMin;
       short yMin;
       short xMax;
       short yMax;
};
//it's simplified simple glyph, only short vectors allowed
struct simpleGlyph: public glyph{
       uint16 * endPtsOfContour;//array of last point of contour
       //elements of array - point indicies, size of array defines by number of contours
       uint16 instructionLength; //array of microcode of glyph
       char * instructions; //set of instructions
       char * flags; //size is variable, but i used simplified version. number of flags equals number of points
       /*bits of flag:
              0- on Curve:	
              1- x-Short Vector
              2- y-Short Vector	
              3- Repeat : deprecated, set to 0 at our version
              4- Positive x-Short Vector : 1 equalling positive and 0 negative.
              5- Positive y-Short Vector :	1 equalling positive and 0 negative.
              6-7 - reserved, 0                                   */
      char * xCordinates;
      char * yCordinates; 
      void printGlyph(ofstream &file); 
      uint32 getSize();      
};
struct compoundGlyph: public glyph{
       //will be defined later
};
struct glyf_table: public table{
       simpleGlyph * sg;
       compoundGlyph * cg;
       uint16 numGlyphs; //number of glyphs, defined for convinience, do not write into thte file
       uint16 numSimpleGlyph; //defined for convinience, do not write in file
       virtual void printTable(char* path);//pure virtual in base class had to be redefined
       virtual uint32 getSize();
       short getxMax();
       short getxMin();
       short getyMax();
       short getyMin();
       uint16 maxPoints();
       uint16 maxContours();
       uint16 maxInstr();
};
extern void gener_simpleGlyphArr(simpleGlyph* sg,uint16 numSimpleGlyph);
