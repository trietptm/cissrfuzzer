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
    delete[] id;
}

void CreateEOI()
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xD9;
    Marker EOI(id);
    EOI.WriteToFile();
    delete[] id;
}

void CreateAPP0()
{
    char *id, *appid;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xE0;
    appid = new char[4];
    strcpy(appid, "JFIF");
    APPx APP0(id, appid);
    APP0.DetSize();
    APP0.WriteToFile();
    delete[] id;
}

void CreateSOF0(char num)
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xC0;
    SOFx SOF0(id, num);
    SOF0.DetSize();
    SOF0.WriteToFile();
    delete[] id;
}

void CreateDHT(char t_t, char t_i)
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xC4;
    DHT dht(id, t_t, t_i);
    dht.DetSize();
    dht.WriteToFile();
    delete[] id;
}

void CreateSOS(char num)
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xDA;
    SOS sos(id, num);
    sos.DetSize();
    sos.WriteToFile();
    delete[] id;
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
    dqt.DetSize();
    dqt.WriteToFile();
    delete[] id;
}

void CreateDRI()
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xDD;
    DRI dri(id);
    dri.DetSize();
    dri.WriteToFile();
    delete[] id;
}

void CreateCOM()
{
    char *id;
    id = new char[2];
    id[0] = 0xFF;
    id[1] = 0xFE;
    COM com(id);
    com.DetSize();
    com.WriteToFile();
    delete[] id;
}



int main()
{
    char counterDHT=0;
    char num=3;
    int numMCU = (511+(int)(Random(127)))*num;
    vector <string> ord;
    vector <string>::iterator cur;
    CreateSOI(); cout<<"SOI is good\n";
    CreateAPP0(); cout<<"APP0 is good\n";
    ord = Order();
    for (cur=ord.begin();cur<ord.end();cur++)
    {
        cout<<*cur<<endl;
    }
    cur=ord.begin();
    while(cur!=ord.end())
    {
        if(*cur=="DQT") { CreateDQT(); cout<<"DQT is good\n"; }
        if(*cur=="DHT")
        {
            if(counterDHT==0) { CreateDHT(0, 0); cout<<"DHT1 is good\n"; }
            if(counterDHT==1) { CreateDHT(0, 1); cout<<"DHT2 is good\n"; }
            if(counterDHT==2) { CreateDHT(1, 0); cout<<"DHT3 is good\n"; }
            if(counterDHT==3) { CreateDHT(1, 1); cout<<"DHT4 is good\n"; }
            counterDHT++;
        }
        if(*cur=="SOFx") { CreateSOF0(num); cout<<"SOFx is good\n"; }
        if(*cur=="SOS") { CreateSOS(num); Fill(numMCU); cout<<"SOS is good\n"; }
        if(*cur=="COM") { CreateCOM(); cout<<"COM is good\n"; }
        cur++;
    }
    CreateEOI(); cout<<"EOI is good\n";
    ord.clear();
    return 0;
}