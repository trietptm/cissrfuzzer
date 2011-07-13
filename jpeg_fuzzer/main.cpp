#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "jpegf.h"
using namespace std;

vector <string> Order();
char Random(int);

void CreateSOI()
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xD8;
    Marker SOI(id);
    SOI.WriteToFile();
}

void CreateEOI()
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xD9;
    Marker EOI(id);
    EOI.WriteToFile();
}

void CreateAPP0()
{
    char *id, *appid;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xE0;
    appid = new char[5];
    strcpy(appid, "JFIF");
    APPx APP0(id, appid);
    APP0.WriteToFile();
}

void CreateSOF0(char num)
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xC0;
    SOFx SOF0(id, num);
    SOF0.WriteToFile();
}

void CreateDHT(char t_t, char t_i)
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xC4;
    DHT dht(id, t_t, t_i);
    dht.WriteToFile();
}

void CreateSOS(char num)
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xDA;
    SOS sos(id, num);
    sos.WriteToFile();
}

void Fill(int num_mcu)
{
    vector <char> buf;
    FILE *filehandle;
    filehandle = fopen("test.jpg", "ab");
    for(int i=0;i<num_mcu;i++)
    {
        buf.push_back(Random(255));
    }
    for(int i=0;i<buf.size();i++)
    {
	fprintf (filehandle, "%c", buf[i]);
    }
    fclose(filehandle);
    buf.clear();
}

void CreateDQT()
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xDB;
    DQT dqt(id);
    dqt.WriteToFile();
}

void CreateDRI()
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xDD;
    DRI dri(id);
    dri.WriteToFile();
}

void CreateCOM()
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xFE;
    COM com(id);
    com.WriteToFile();
}



int main()
{
    char counterDHT=0;
    char num=1;
    int numMCU = (127+(char)(Random(127)))*num;
    vector <string> ord;
    vector <string>::iterator cur;
    CreateSOI();
    CreateAPP0();
    ord = Order();
    for (cur=ord.begin();cur<ord.end();cur++)
    {
        cout<<*cur<<endl;
    }
    cur=ord.begin();
    while(cur!=ord.end())
    {
        if(*cur=="DQT") CreateDQT();
        if(*cur=="DHT")
        {
            if(counterDHT==0) CreateDHT(0, 0); counterDHT++;
            if(counterDHT==1) CreateDHT(0, 1); counterDHT++;
            if(counterDHT==2) CreateDHT(1, 0); counterDHT++;
            if(counterDHT==3) CreateDHT(1, 1);
        }
        if(*cur=="SOFx") CreateSOF0(num);
        if(*cur=="SOS") CreateSOS(num); Fill(numMCU);
        if(*cur=="COM") CreateCOM();
        cur++;
    }
    CreateEOI();
    return 0;
}