#if !defined(chunk_H)
	#define chunk_H


class chunk
{
public:
	chunk();
	~chunk(){delete [] IDATdata;}
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

	char cHRMfield [8];//Primary chromaticities and white point
	char cHRMWhiteX [4];
	char cHRMWhiteY [4];
	char cHRMRedX [4];
	char cHRMRedY [4];
	char cHRMGreenX [4];
	char cHRMGreenY [4];
	char cHRMBlueX [4];
	char cHRMBlueY [4];
	char cHRMCRC [4];

	char sBITfield [8];//Significant bits
	char sBITGrey; 
	char sBITRed; 
	char sBITGreen; 
	char sBITBlue; 
	char sBITAlpha; 
	char sBITCRC [4];

	char bKGDfield [8];//Background colour
	char bKGDgreyscale [2];
	char bKGDred [2];
	char bKGDgreen [2];
	char bKGDblue [2];
	char bKGDpalette;
	char bKGDCRC [4];

	char PLTEfield [8];//Palette
	char PLTERedGreenBBlue[3];//from 1 to 256
	char PLTECRC [4];

	char tRNSfield [8];
	char tRNSgrey [2];
	char tRNSred [2];
	char tRNSgreen [2];
	char tRNSblue [2];
	char tRNSone;
	char tRNStwo;
	char tRNSCRC [4];

	char hISTfield [8];//Image histogram
	char hISTFreq[2];
	char hISTCRC [4];

	char IDATfield [8];//Image data
	char * IDATdata;//data from example file
	int IDATsize;
	char IDATCRC [4];

	char IENDfield [8];
	char IENDCRC[4];


};


#endif