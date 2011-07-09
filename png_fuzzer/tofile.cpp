#include "stdafx.h"
#include "Chunks.h"
#include <string>
#include <fstream>
//#include <iostream>

using namespace std;

void chunk::tofile()
{
	FILE *f;
	char b [512];
	int i;
	int temp;
// Signature
	for (i=0;i<8;i++)
		b[i]=sign[i];
//IHDR
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
//sRGB
		for(temp=i;i<temp+8;i++)
			b[i]=sRGBfield [i-temp];
		b[i++]=sRGBRendering;
		for (temp=i;i<temp+4;i++)
			b[i]=sRGBCRC[i-temp];
//gAMA
		for(temp=i;i<temp+8;i++)
			b[i]=gAMAfield [i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=gAMAgamma[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=gAMACRC[i-temp];
//pHYS
		for(temp=i;i<temp+8;i++)
			b[i]=pHYSfield [i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=pHYSX[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=pHYSY[i-temp];
		b[i++]=pHYSspecifier;
		for (temp=i;i<temp+4;i++)
			b[i]=pHYSCRC[i-temp];
//cHRM
		for(temp=i;i<temp+8;i++)
			b[i]=cHRMfield [i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=cHRMWhiteX[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=cHRMWhiteY[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=cHRMRedX[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=cHRMRedY[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=cHRMGreenX[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=cHRMGreenY[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=cHRMBlueX[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=cHRMBlueY[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=cHRMCRC[i-temp];
//PLTE
		for(temp=i;i<temp+8;i++)
			b[i]=PLTEfield [i-temp];
		for (temp=i;i<temp+3;i++)
			b[i]=PLTERedGreenBBlue[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=PLTECRC[i-temp];
//hIST
		for(temp=i;i<temp+8;i++)
			b[i]=hISTfield [i-temp];
		b[i++]=hISTFreq[0];
		b[i++]=hISTFreq[1];
		for (temp=i;i<temp+4;i++)
			b[i]=hISTCRC[i-temp];
//IDAT
		for(temp=i;i<temp+8;i++)
			b[i]=IDATfield [i-temp];
		for (temp=i;i<temp+12;i++)
			b[i]=IDATdata[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=IDATCRC[i-temp];
//IEND		
		for(temp=i;i<temp+8;i++)
			b[i]=IENDfield [i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=IENDCRC[i-temp];
	
	//a=a+IHDRfield;
	//a=sign+(string)IHDRfield;
	//cout<<sign;
	//cin.get();
    ofstream file("test1.png");
	f=fopen("d://2.png","rb+");
	fwrite(b,i*sizeof(char),1,f);
	//for(i=0;i<8;i++)
	//char c=a[5];
	//file<<c;
}
