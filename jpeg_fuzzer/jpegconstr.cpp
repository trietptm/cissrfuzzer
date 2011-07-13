#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <time.h>
#include <vector>
#include "jpegf.h"

using namespace std;


char Random(int max)
{
	return (rand()%max);
}


Marker::Marker(char *id)
{
	strcpy(Marker::ID, id);
	size[0]=0;
	size[1]=2;
}

SOFx::SOFx(char *id, char num) : Marker(id)
{
    srand( (unsigned)time( NULL ) );
	SOFx::precision = 8;
	SOFx::Y_image[0] = Random(255);
	SOFx::Y_image[1] = Random(255);
	SOFx::X_image[0] = Random(255);
	SOFx::X_image[1] = Random(255);
	SOFx::num_comps = num;
	if(SOFx::num_comps==1)
	{
		SOFx::comp_ID = new char[1];
		SOFx::discr = new char[1];
		SOFx::num_quant_tab = new char[1];
		SOFx::comp_ID[0] = 1;
		SOFx::discr[0] = Random(255);
		SOFx::num_quant_tab[0] = Random(2);
	}
	else
	{
		SOFx::comp_ID = new char[3];
		SOFx::discr = new char[3];
		SOFx::num_quant_tab = new char[3];
		SOFx::comp_ID[0] = 1;
		SOFx::comp_ID[1] = 2;
		SOFx::comp_ID[2] = 3;
		SOFx::discr[0] = (Random(2))*17;
		SOFx::discr[1] = (Random(2))*17;
		SOFx::discr[2] = (Random(2))*17;
		SOFx::num_quant_tab[0] = Random(2);
		SOFx::num_quant_tab[1] = Random(2);
		SOFx::num_quant_tab[2] = Random(2);
	}
        SOFx::DetSize();
}

DHT::DHT(char *id, char tab_type, char tab_id) : Marker(id)
{
    srand( (unsigned)time( NULL ) );
	int length=0;
	DHT::HT_info = 16*tab_type+tab_id;
	for(int i=0;i<16;i++)
	{
		DHT::HT_len[i] = Random(6);
		length+=DHT::HT_len[i];
	}
	DHT::HT_symb = new char[length];
	for(int i=0;i<length;i++)
	{
		DHT::HT_symb[i] = Random(255);
	}
        DHT::DetSize();
}

SOS::SOS(char *id, char num) : Marker(id)
{
    srand( (unsigned)time( NULL ) );
	SOS::num_comps = num;
	if(SOS::num_comps==1)
	{
		SOS::comp_ID = new char[1];
		SOS::comp_ID[0] = 1;
		SOS::tab_Huff = new char[1];
		SOS::tab_Huff[0] = 16*Random(2)+Random(2);
	}
	else
	{
		SOS::comp_ID = new char[3];
		SOS::tab_Huff = new char[3];
		SOS::comp_ID[0] = 1;
		SOS::comp_ID[1] = 2;
		SOS::comp_ID[2] = 3;
		SOS::tab_Huff[0] = 16*Random(2)+Random(2);
		SOS::tab_Huff[1] = 16*Random(2)+Random(2);
		SOS::tab_Huff[2] = 16*Random(2)+Random(2);
	}
	for(int i=0;i<3;i++)
	{
	    SOS::ign[i]=0;
	}
        SOS::DetSize();
}

DQT::DQT(char *id) : Marker(id)
{
    srand( (unsigned)time( NULL ) );
	DQT::tab_inf = 16*Random(2)+Random(2);
	if(DQT::tab_inf<16)
	{
	    for(int i=0;i<64;i++)
	    {
		    DQT::qTable[i] = new char[1];
		    DQT::qTable[i][0] = Random(255);
	    }
	}
	else
	{
		for(int i=0;i<64;i++)
		{
			DQT::qTable[i] = new char[2];
			DQT::qTable[i][0] = Random(255);
			DQT::qTable[i][1] = Random(255);
		}
	}
        DQT::DetSize();
}

DRI::DRI(char *id) : Marker(id)
{
    srand( (unsigned)time( NULL ) );
	DRI::RI[0]=0;
	DRI::RI[1]=10;
        DRI::DetSize();
}

COM::COM(char *id) : Marker(id)
{
    srand( (unsigned)time( NULL ) );
	int length = Random(250);
	COM::comment = new char[length];
	for(int i=0;i<length;i++)
	{
		COM::comment[i] = Random(255);
	}
        COM::DetSize();
}

APPx::APPx(char *id, char* appid) : Marker(id)
{
    srand( (unsigned)time( NULL ) );
	APPx::app_ID = appid;
	APPx::version[0] = 1;
	APPx::version[1] = 2;
	APPx::unit = Random(3);
	APPx::Xdensity[0] = 0;
	APPx::Xdensity[1] = Random(255);
	APPx::Ydensity[0] = 0;
	APPx::Ydensity[1] = Random(255);
	APPx::xThumbnail = Random(255);
	APPx::yThumbnail = Random(255);
	APPx::Preview = new char[3*(int)xThumbnail*(int)yThumbnail];
	for(int i=0;i<sizeof(APPx::Preview);i++)
	{
		APPx::Preview[i] = Random(255);
	}
        APPx::DetSize();
}


vector <string> Order() 
{
	vector <string> vec;
	vector<string>::iterator cur;
	int counter;
	vec.push_back("DQT");
        for(int i=0;i<4;i++)
        {
	    vec.push_back("DHT");
        } 
	vec.push_back("SOFx");
	int SOS_num;
	SOS_num = Random(21);
	for(int i=0;i<SOS_num;i++) 
        {
		vec.push_back("SOS");
	}
	int insert_COM;
	insert_COM = Random(6+SOS_num);
	counter=0;
	for (cur=vec.begin();cur<vec.end();cur++) 
        {
		if(counter==insert_COM) vec.insert (cur, "COM");
		counter++;
	}
	return vec;
}


