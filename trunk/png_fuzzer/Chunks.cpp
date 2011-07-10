#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Chunks.h"

using namespace std;

char RandomNumbers(int range_max);

chunk::chunk()
{
	srand( (unsigned)time( NULL ) );

	char sign1[8]={137,80,78,71,13,10,26,10};
	char IHDRfield1 [8]={0,0,0,13,73,72,68,82};
	char sRGBfield1 [8]={0,0,0,1,115,82,71,66};
	char gAMAfield1 [8]={0,0,0,4,103,65,77,65};
	char pHYSfield1 [8]={0,0,0,9,112,72,89,115};
	char cHRMfield1 [8]={0,0,0,32,99,72,82,77};//new
	char sBITfield1 [8]={0,0,0,0,115,66,73,84};
	char bKGDfield1 [8]={0,0,0,0,98,75,71,68};
	char PLTEfield1 [8]={0,0,0,3,80,76,84,69};
	char hISTfield1 [8]={0,0,0,2,104,73,83,84};
	char IDATfield1 [8]={0,0,0,12,73,68,65,84};
	char IENDfield1 [8]={0,0,0,0,73,69,78,68};
//All fields (names) of chunks
	for (int i=0;i<8;i++)
	{
	sign[i]=sign1[i];
	IHDRfield[i]=IHDRfield1 [i];
	sRGBfield[i]=sRGBfield1 [i];
	gAMAfield[i]=gAMAfield1 [i];
	pHYSfield[i]=pHYSfield1 [i];
	cHRMfield[i]=cHRMfield1 [i];
	sBITfield[i]=sBITfield1 [i];
	bKGDfield[i]=bKGDfield1 [i];
	PLTEfield[i]=PLTEfield1 [i];
	hISTfield[i]=hISTfield1 [i];
	IDATfield[i]=IDATfield1 [i];
	IENDfield[i]=IENDfield1 [i];
	}

//Filling data
	IDATsize=2*RandomNumbers(128);
	IDATdata=new char[IDATsize];
	for (int i=0;i<IDATsize;i++)
	{
	IDATdata [i]=RandomNumbers(255);
	}
	IDATfield[3]=IDATsize;
	

	char IENDCRC1[4]={174,66,96,130};//CRC of IEND is constant

	for (int i=0;i<3;i++)
	{
		IHDRWidth[i]=0;
		IHDRHeight[i]=0;
	}
	
	for (int i=3;i<4;i++)
	{
		IHDRWidth[i]=RandomNumbers(256);
		IHDRHeight[i]=RandomNumbers(256);
		
		
	}

	for (int i=0;i<4;i++)
	{
		gAMAgamma[i]=RandomNumbers(256);
		pHYSX[i]=RandomNumbers(256);
		pHYSY[i]=RandomNumbers(256);	
		cHRMWhiteX[i]=RandomNumbers(256);
		cHRMWhiteY[i]=RandomNumbers(256);
		cHRMRedX[i]=RandomNumbers(256);
		cHRMRedY[i]=RandomNumbers(256);
		cHRMGreenX[i]=RandomNumbers(256);
		cHRMGreenY[i]=RandomNumbers(256);
		cHRMBlueX[i]=RandomNumbers(256);
		cHRMBlueY[i]=RandomNumbers(256);

		IHDRCRC[i]=RandomNumbers(256);
		sRGBCRC[i]=RandomNumbers(256);
		gAMACRC[i]=RandomNumbers(256);
		pHYSCRC[i]=RandomNumbers(256);
		cHRMCRC[i]=RandomNumbers(256);
		sBITCRC[i]=RandomNumbers(256);
		bKGDCRC[i]=RandomNumbers(256);
		PLTECRC[i]=RandomNumbers(256);
		hISTCRC[i]=RandomNumbers(256);
		IDATCRC[i]=RandomNumbers(256);
		IENDCRC[i]=IENDCRC1[i];
	}

//Filling one-byte fields
	hISTFreq[0]=RandomNumbers(256);
	hISTFreq[1]=RandomNumbers(256);
	IHDRCompression=0;//Defined in standart
	IHDRFilter=0;//Defined in standart

	IHDRColour=RandomNumbers(7);
	if (IHDRColour==1) IHDRColour=0;
	if (IHDRColour==5) IHDRColour=6;

	if(IHDRColour==2||IHDRColour==4||IHDRColour==6)
		IHDRDepth=(RandomNumbers(2)+1)*8;
	int temppow=RandomNumbers(6);
	if (IHDRColour==0) 
		IHDRDepth=pow((long double)2,(int)temppow);

	temppow=RandomNumbers(5);
	if (IHDRColour==3) 
		IHDRDepth=pow((long double)2,(int)temppow);

	if (IHDRColour==0) sBITfield[3]=1;
	if (IHDRColour==2||IHDRColour==3) sBITfield[3]=3;
	if (IHDRColour==4) sBITfield[3]=2;
	if (IHDRColour==6) sBITfield[3]=4;

		sBITGrey=1+RandomNumbers(IHDRDepth+1);
		sBITRed=1+RandomNumbers(IHDRDepth+1);
		sBITGreen=1+RandomNumbers(IHDRDepth+1);
		sBITBlue=1+RandomNumbers(IHDRDepth+1);
		sBITAlpha=1+RandomNumbers(IHDRDepth+1);

	int tempbKGD;
	if (IHDRColour==0||IHDRColour==4) 
	{
		bKGDfield [3]=2;
		tempbKGD=RandomNumbers(pow((long double)2,(int)IHDRDepth));
		bKGDgreyscale [0]=tempbKGD/256;
		bKGDgreyscale [1]=tempbKGD%256;
	}
	if (IHDRColour==2||IHDRColour==6)
	{
		bKGDfield [3]=6;
		tempbKGD=RandomNumbers(pow((long double)2,(int)IHDRDepth));
		bKGDred [0]=tempbKGD/256;
		bKGDred [1]=tempbKGD%256;
		tempbKGD=RandomNumbers(pow((long double)2,(int)IHDRDepth));
		bKGDgreen [0]=tempbKGD/256;
		bKGDgreen [1]=tempbKGD%256;
		tempbKGD=RandomNumbers(pow((long double)2,(int)IHDRDepth));
		bKGDblue [0]=tempbKGD/256;
		bKGDblue [1]=tempbKGD%256;
	}
	if (IHDRColour==3)
	{
		bKGDfield [3]=1;
		bKGDpalette=RandomNumbers(256);
	}


	IHDInterlace=RandomNumbers(2);
	sRGBRendering=RandomNumbers(4);
	pHYSspecifier=RandomNumbers(2);


	for (int i=0;i<3;i++)
	{
		PLTERedGreenBBlue[i]=RandomNumbers(256);
	}
	
}


char RandomNumbers(int range_max)
{
	return (rand()%range_max);
}
