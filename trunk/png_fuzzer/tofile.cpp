#include "stdafx.h"
#include "Chunks.h"
#include <string>

using namespace std;

void chunk::tofile()
{
	FILE *f;
	char b [1024];
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
//sBIT
		for(temp=i;i<temp+8;i++)
			b[i]=sBITfield [i-temp];
		if (IHDRColour==0) 
			b[i++]=sBITGrey;
		if (IHDRColour==2||IHDRColour==3)
		{
			b[i++]=sBITRed;
			b[i++]=sBITGreen;
			b[i++]=sBITBlue;
		}	
		if (IHDRColour==4)
		{
			b[i++]=sBITGrey;
			b[i++]=sBITAlpha;
		}
		if (IHDRColour==6)
		{
			b[i++]=sBITRed;
			b[i++]=sBITGreen;
			b[i++]=sBITBlue;
			b[i++]=sBITAlpha;
		}
		for (temp=i;i<temp+4;i++)
			b[i]=sBITCRC[i-temp];
//bKGD
		for(temp=i;i<temp+8;i++)
			b[i]=bKGDfield [i-temp];
		if (IHDRColour==0||IHDRColour==4) 
		{
			b[i++]=bKGDgreyscale [0];
			b[i++]=bKGDgreyscale [1];
		}
		if (IHDRColour==2||IHDRColour==6)
		{
			b[i++]=bKGDred [0];
			b[i++]=bKGDred [1];
			b[i++]=bKGDgreen [0];
			b[i++]=bKGDgreen [1];
			b[i++]=bKGDblue [0];
			b[i++]=bKGDblue [1];
		}
		if (IHDRColour==3)
		{
			b[i++]=bKGDpalette;
		}			
		for (temp=i;i<temp+4;i++)
			b[i]=bKGDCRC[i-temp];
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
		for (temp=i;i<temp+IDATsize;i++)
			b[i]=IDATdata[i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=IDATCRC[i-temp];
//IEND		
		for(temp=i;i<temp+8;i++)
			b[i]=IENDfield [i-temp];
		for (temp=i;i<temp+4;i++)
			b[i]=IENDCRC[i-temp];
	
	
    //ofstream file("test1.png");
	f=_wfopen(L"d://2.png",L"wb+");
	fwrite(b,i*sizeof(char),1,f);
	
}
