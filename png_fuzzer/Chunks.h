#if !defined(chunk_H)
	#define chunk_H


class chunk
{
public:
	chunk();
	~chunk()
	{
		delete [] IDATdata;
		delete [] sPLTname;
		delete [] iTXtkey;
		delete [] iTXtlang;
		delete [] iTXttrans;
		delete [] iTXttext;
		delete [] tEXtkey;
		delete [] tEXttext;
		delete [] zTXtkey;
		delete [] zTXtdata;
	}
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

	char tRNSfield [8];//Transparency
	char tRNSgrey [2];
	char tRNSred [2];
	char tRNSgreen [2];
	char tRNSblue [2];
	char tRNSone;
	char tRNStwo;
	char tRNSCRC [4];

	char sPLTfield [8];//Suggested palette
	char * sPLTname;
	int sPLTsize;
	char sPLTnull;
	char sPLTdepth;
	char sPLTred[2];
	char sPLTgreen[2];
	char sPLTblue[2];
	char sPLTalpha[2];
	char sPLTfreq[2];
	char sPLTCRC [4];


	char hISTfield [8];//Image histogram
	char hISTFreq[2];
	char hISTCRC [4];

	char IDATfield [8];//Image data
	char * IDATdata;
	int IDATsize;
	char IDATCRC [4];

	char tIMEfield [8];//Image last-modification time
	char tIMEyear[2];
	char tIMEmonth;
	char tIMEday;
	char tIMEhour;
	char tIMEminute;
	char tIMEsecond;
	char tIMECRC [4];

	char iTXtfield [8];//International textual data
	char * iTXtkey;
	int iTXtsize;
	char iTXtnull;
	char iTXtcomp;
	char iTXtmethod;
	char * iTXtlang;
	int iTXtsizel;
	char iTXtlangnull;
	char * iTXttrans;
	int iTXtsizet;
	char iTXtnulltr;
	char * iTXttext;
	int iTXtsizete;
	char iTXtCRC [4];

	char tEXtfield [8];//Textual data
	char * tEXtkey;
	int tEXtkeysize;
	char tEXtnull;
	char * tEXttext;
	int tEXttextsize;
	char tEXtCRC [4];

	char zTXtfield [8];//Compressed textual data
	char * zTXtkey;
	int zTXtkeysize;
	char zTXtnull;
	char zTXtcomp;
	char * zTXtdata;
	int zTXtdatasize;
	char zTXtCRC [4];

	char IENDfield [8];//Image trailer
	char IENDCRC[4];


};


#endif