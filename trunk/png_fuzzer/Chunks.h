class PNG
{
private:
	const char sign[8]={137,80,78,71,13,10,26,10};

	const char IHDRfield [8]={0,0,0,13,73,72,68,82};//Image header
	char IHDRWidth [4];
	char IHDRHeight [4];
	char IHDRDepth;// watch allowed combs of Depth in Clour in specs
	char IHDRColour;
	const char IHDRCompression=0;
	const char IHDRFilter=0;
	char IHDInterlace;//1 or 0
	char IHDRCRC [4];

	const char sRGBfield [8]={0,0,0,1,115,82,71,66};//Standard RGB colour space
	char sRGBRendering;//only 0,1,2,3 allowed
	char sRGBCRC [4];

	const char gAMAfield [8]={0,0,0,4,103,65,77,65};//Image gamma
	char gAMAgamma [4];//random?
	char gAMACRC [4];

	const char pHYSfield [8]={0,0,0,9,112,72,89,115};//Physical pixel dimensions
	char pHYSX [4];//possibly 00 00 14 195
	char pHYSY [4];//same as X
	char pHYSspecifier;//1 or 0
	char pHYSCRC [4];

	const char IDATfield [8]={0,0,0,12,73,68,65,84};//Image data
	const char IDATdata[12]={24,87,99,248,255,255,63,0,5,254,2,254};//data from example file
	char IDATCRC [4];

	const char IENDfield [8]={0,0,0,0,73,69,78,68};
	const char IENDCRC[4]={174,66,96,130};
}