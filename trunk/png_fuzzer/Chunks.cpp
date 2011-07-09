#include "stdafx.h"
#include "Chunks.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

chunk::chunk()
{
	char sign1[8]={137,80,78,71,13,10,26,10};
	char IHDRfield1 [8]={0,0,0,13,73,72,68,82};
	char sRGBfield1 [8]={0,0,0,1,115,82,71,66};
	char gAMAfield1 [8]={0,0,0,4,103,65,77,65};
	char pHYSfield1 [8]={0,0,0,9,112,72,89,115};
	char PLTEfield1 [8]={0,0,0,3,80,76,84,69};
	char IDATfield1 [8]={0,0,0,12,73,68,65,84};
	char IDATdata1 [12]={24,87,99,248,255,255,63,0,5,254,2,254};
	char IENDfield1 [8]={0,0,0,0,73,69,78,68};
	for (int i=0;i<8;i++)
	{
	sign[i]=sign1[i];
	IHDRfield[i]=IHDRfield1 [i];
	sRGBfield[i]=sRGBfield1 [i];
	gAMAfield[i]=gAMAfield1 [i];
	pHYSfield[i]=pHYSfield1 [i];
	PLTEfield[i]=PLTEfield1 [i];
	IDATfield[i]=IDATfield1 [i];
	IENDfield[i]=IENDfield1 [i];

	}
	for (int i=0;i<12;i++)
	{
	IDATdata [i]=IDATdata1 [i];
	}

	char IENDCRC1[4]={174,66,96,130};
	IHDRCompression=0;
	IHDRFilter=0;
	char IHDRWidth1[4]={0,0,0,1};
	char IHDRHeight1[4]={0,0,0,1};
	char gAMAgamma1[4]={0,0,0,1};
	char pHYSX1[4]={0,0,14,195};
	char pHYSY1[4]={0,0,14,195};

	char IHDRCRC1[4]={0,0,0,1};
	char sRGBCRC1[4]={0,0,0,1};
	char gAMACRC1[4]={0,0,0,1};
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
		IDATCRC[i]=IDATCRC1[i];
		IENDCRC[i]=IENDCRC1[i];
	}

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


void chunk::tofile()
{
	FILE *f;
	char b [256];
	int i;
	int temp;

	for (i=0;i<8;i++)
		b[i]=sign[i];

	for (i=8;i<16;i++)
		b[i]=IHDRfield[i-8];
	for (i=16;i<20;i++)
		b[i]=IHDRWidth[i-16];
	for (i=20;i<24;i++)
		b[i]=IHDRHeight[i-20];
		b[i++]=IHDRDepth;
		b[i++]=IHDRColour;
		b[i++]=IHDRCompression;
		b[i++]=IHDRFilter;
		b[i++]=IHDInterlace;
		for (temp=i;i<temp+4;i++)
			b[i]=IHDRCRC[i-temp];

		for(temp=i;i<temp+8;i++)
			b[i]=sRGBfield [i-temp];
		b[i++]=sRGBRendering;
		for (temp=i;i<temp+4;i++)
			b[i]=sRGBCRC[i-temp];

		for(temp=i;i<temp+8;i++)
			b[i]=gAMAfield [i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=gAMAgamma[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=gAMACRC[i-temp];

		for(temp=i;i<temp+8;i++)
			b[i]=pHYSfield [i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=pHYSX[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=pHYSY[i-temp];
		b[i++]=pHYSspecifier;
		for (temp=i;i<temp+4;i++)
			b[i]=pHYSCRC[i-temp];

		for(temp=i;i<temp+8;i++)
			b[i]=PLTEfield [i-temp];
		for (temp=i;i<temp+3;i++)
			b[i]=PLTERedGreenBBlue[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=PLTECRC[i-temp];

		for(temp=i;i<temp+8;i++)
			b[i]=IDATfield [i-temp];
		for (temp=i;i<temp+12;i++)
			b[i]=IDATdata[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=IDATCRC[i-temp];
		
		for(temp=i;i<temp+8;i++)
			b[i]=IENDfield [i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=IENDCRC[i-temp];
	
	//a=a+IHDRfield;
	//a=sign+(string)IHDRfield;
	//cout<<sign;
	cin.get();
    ofstream file("test1.png");
	f=fopen("d://2.png","rb+");
	fwrite(b,i*sizeof(char),1,f);
	//for(i=0;i<8;i++)
	//char c=a[5];
	//file<<c;
}
