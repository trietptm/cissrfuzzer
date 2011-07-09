#include "stdafx.h"
#include "Chunks.h"

using namespace std;

chunk::chunk()
{
	char sign1[8]={137,80,78,71,13,10,26,10};
	char IHDRfield1 [8]={0,0,0,13,73,72,68,82};
	char sRGBfield1 [8]={0,0,0,1,115,82,71,66};
	char gAMAfield1 [8]={0,0,0,4,103,65,77,65};
	char pHYSfield1 [8]={0,0,0,9,112,72,89,115};
	char cHRMfield1 [8]={0,0,0,32,99,72,82,77};//new
	char PLTEfield1 [8]={0,0,0,3,80,76,84,69};
	char hISTfield1 [8]={0,0,0,2,104,73,83,84};
	char IDATfield1 [8]={0,0,0,12,73,68,65,84};
	char IDATdata1 [12]={24,87,99,248,255,255,63,0,5,254,2,254};
	char IENDfield1 [8]={0,0,0,0,73,69,78,68};
//All fields (names) of chunks
	for (int i=0;i<8;i++)
	{
	sign[i]=sign1[i];
	IHDRfield[i]=IHDRfield1 [i];
	sRGBfield[i]=sRGBfield1 [i];
	gAMAfield[i]=gAMAfield1 [i];
	pHYSfield[i]=pHYSfield1 [i];
	cHRMfield[i]=cHRMfield1[i];
	PLTEfield[i]=PLTEfield1 [i];
	hISTfield[i]=hISTfield1 [i];
	IDATfield[i]=IDATfield1 [i];
	IENDfield[i]=IENDfield1 [i];
	}
//Filling data
	for (int i=0;i<12;i++)
	{
	IDATdata [i]=IDATdata1 [i];
	}

	char IENDCRC1[4]={174,66,96,130};//CRC of IEND is constant

	char IHDRWidth1[4]={0,0,0,1};
	char IHDRHeight1[4]={0,0,0,1};
	//
	char gAMAgamma1[4]={0,0,0,1};
	//
	char pHYSX1[4]={0,0,14,195};
	char pHYSY1[4]={0,0,14,195};
	//
	char cHRMWhiteX1 [4]={0,0,0,1};
	char cHRMWhiteY1 [4]={0,0,0,1};
	char cHRMRedX1 [4]={0,0,0,1};
	char cHRMRedY1 [4]={0,0,0,1};
	char cHRMGreenX1 [4]={0,0,0,1};
	char cHRMGreenY1 [4]={0,0,0,1};
	char cHRMBlueX1 [4]={0,0,0,1};
	char cHRMBlueY1 [4]={0,0,0,1};
//Filling CRC's
	char IHDRCRC1[4]={0,0,0,1};
	char sRGBCRC1[4]={0,0,0,1};
	char gAMACRC1[4]={0,0,0,1};
	char cHRMCRC1[4]={0,0,0,1};
	char PLTECRC1[4]={0,0,0,1};
	char hISTCRC1[4]={0,0,0,1};
	char pHYSCRC1[4]={0,0,0,1};
	char IDATCRC1[4]={0,0,0,1};



	for (int i=0;i<4;i++)
	{
		IHDRWidth[i]=IHDRWidth1[i];
		IHDRHeight[i]=IHDRHeight1[i];
		gAMAgamma[i]=gAMAgamma1[i];
		pHYSX[i]=pHYSX1[i];
		pHYSY[i]=pHYSY1[i];
		IHDRCRC[i]=IHDRCRC1[i];
		sRGBCRC[i]=sRGBCRC1[i];
		gAMACRC[i]=gAMACRC1[i];
		pHYSCRC[i]=pHYSCRC1[i];
		cHRMWhiteX[i]=cHRMWhiteX1[i];
		cHRMWhiteY[i]=cHRMWhiteY1[i];
		cHRMRedX[i]=cHRMRedX1[i];
		cHRMRedY[i]=cHRMRedY1[i];
		cHRMGreenX[i]=cHRMGreenX1[i];
		cHRMGreenY[i]=cHRMGreenY1[i];
		cHRMBlueX[i]=cHRMBlueX1[i];
		cHRMBlueY[i]=cHRMBlueY1[i];
		cHRMCRC[i]=cHRMCRC1[i];
		PLTECRC[i]=PLTECRC1[i];
		hISTCRC[i]=hISTCRC1 [i];
		IDATCRC[i]=IDATCRC1[i];
		IENDCRC[i]=IENDCRC1[i];
	}
//Filling one-byte fields
	hISTFreq[0]=0;
	hISTFreq[1]=1;
	IHDRCompression=0;
	IHDRFilter=0;
	IHDRColour=0;
	IHDRDepth=1;
	IHDInterlace=0;
	sRGBRendering=0;
	pHYSspecifier=0;
	char PLTERedGreenBBlue1[3]={0,0,0};

	for (int i=0;i<3;i++)
	{
		PLTERedGreenBBlue[i]=PLTERedGreenBBlue1[i];
	}
	
}
