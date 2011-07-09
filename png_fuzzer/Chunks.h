#if !defined(chunk_H)
	#define chunk_H


class chunk
{
public:
	chunk();
	void tofile();
private:
	char sign[8];
	char IHDRfield[8];//Image header
	char IHDRWidth [4];
	char IHDRHeight [4];
	char IHDRDepth;// watch allowed combs of Depth in Clour in specs
	char IHDRColour;
	char IHDRCompression;
	char IHDRFilter;
	char IHDInterlace;//1 or 0
	char IHDRCRC [4];

	char sRGBfield [8];//Standard RGB colour space
	char sRGBRendering;//only 0,1,2,3 allowed
	char sRGBCRC [4];

	char gAMAfield [8];//Image gamma
	char gAMAgamma [4];//random?
	char gAMACRC [4];

	char pHYSfield [8];//Physical pixel dimensions
	char pHYSX [4];//possibly 00 00 14 195
	char pHYSY [4];//same as X
	char pHYSspecifier;//1 or 0
	char pHYSCRC [4];

	char PLTEfield [8];//Palette
	char PLTERedGreenBBlue[3];//from 1 to 256
	char PLTECRC [4];

	char IDATfield [8];//Image data
	char IDATdata[12];//data from example file
	char IDATCRC [4];

	char IENDfield [8];
	char IENDCRC[4];


};


#endif