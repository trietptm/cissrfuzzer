#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "jpegf.h"
using namespace std;

void Marker::WriteToFile()
{
    vector <char> buf;
    FILE *filehandle;
    filehandle = fopen("test.jpg", "ab");
    buf.push_back(ID[0]);
    buf.push_back(ID[1]);
    for(int i=0;i<buf.size();i++)
    {
        fprintf (filehandle, "%c", buf[i]);
    }
    fclose(filehandle);
        buf.clear();
        //delete filehandle;
}

void APPx::WriteToFile()
{
    vector <char> buf;
    FILE *filehandle;
    filehandle = fopen("test.jpg", "ab");
    buf.push_back(ID[0]);
    buf.push_back(ID[1]);
    buf.push_back(size[0]);
    buf.push_back(size[1]);
    for(int i=0;i<sizeof(app_ID);i++)
    {
        buf.push_back(app_ID[i]);
    }
    buf.push_back(0);
    buf.push_back(version[0]);
    buf.push_back(version[1]);
    buf.push_back(unit);
    buf.push_back(Xdensity[0]);
    buf.push_back(Xdensity[1]);
    buf.push_back(Ydensity[0]);
    buf.push_back(Ydensity[1]);
    buf.push_back(xThumbnail);
    buf.push_back(yThumbnail);
    int length=3*(int)xThumbnail*(int)yThumbnail;
    for(int i=0;i<length;i++)
    {
    buf.push_back(Preview[i]);
    }
    for(int i=0;i<buf.size();i++)
    {
    fprintf (filehandle, "%c", buf[i]);
    }
    fclose(filehandle);
    buf.clear();
    //delete filehandle;
}

void SOFx::WriteToFile()
{
    vector <char> buf;
    FILE *filehandle;
    filehandle = fopen("test.jpg", "ab");
    buf.push_back(ID[0]);
    buf.push_back(ID[1]);
    buf.push_back(size[0]);
    buf.push_back(size[1]);
    buf.push_back(precision);
    buf.push_back(Y_image[0]);
    buf.push_back(Y_image[1]);
    buf.push_back(X_image[0]);
    buf.push_back(X_image[1]);
    buf.push_back(num_comps);
    for(int i=0;i<num_comps;i++)
    {
        buf.push_back(comp_ID[i]);
        buf.push_back(discr[i]);
        buf.push_back(num_quant_tab[i]);
    }
    for(int i=0;i<buf.size();i++)
    {
    fprintf (filehandle, "%c", buf[i]);
    }
    fclose(filehandle);
    buf.clear();
    //delete filehandle;
}

void DHT::WriteToFile()
{
    vector <char> buf;
    FILE *filehandle;
    filehandle = fopen("test.jpg", "ab");
    buf.push_back(ID[0]);
    buf.push_back(ID[1]);
    buf.push_back(size[0]);
    buf.push_back(size[1]);
    buf.push_back(HT_info);
    for(int i=0;i<16;i++)
    {
        buf.push_back(HT_len[i]);
    }
    for(int i=0;i<sizeof(HT_symb);i++)
    {
        buf.push_back(HT_symb[i]);
    }
    for(int i=0;i<buf.size();i++)
    {
    fprintf (filehandle, "%c", buf[i]);
    }
    fclose(filehandle);
    buf.clear();
    //delete filehandle;
}

void SOS::WriteToFile()
{
    vector <char> buf;
    FILE *filehandle;
    filehandle = fopen("test.jpg", "ab");
    buf.push_back(ID[0]);
    buf.push_back(ID[1]);
    buf.push_back(size[0]);
    buf.push_back(size[1]);
    buf.push_back(num_comps);
    for(int i=0;i<num_comps;i++)
    {
        buf.push_back(comp_ID[i]);
        buf.push_back(tab_Huff[i]);
    }
    for(int i=0;i<3;i++)
    {
        buf.push_back(ign[i]);
    }
    for(int i=0;i<buf.size();i++)
    {
    fprintf (filehandle, "%c", buf[i]);
    }
    fclose(filehandle);
    buf.clear();
    //delete filehandle;
}

void DQT::WriteToFile()
{
    vector <char> buf;
    FILE *filehandle;
    filehandle = fopen("test.jpg", "ab");
    buf.push_back(ID[0]);
    buf.push_back(ID[1]);
    buf.push_back(size[0]);
    buf.push_back(size[1]);
    buf.push_back(tab_inf);
    if(tab_inf<16)
    {
        for(int i=0;i<64;i++)
        {
            buf.push_back(qTable[i][0]);
        }
    }
    else
    {
        for(int i=0;i<64;i++)
        {
            buf.push_back(qTable[i][0]);
            buf.push_back(qTable[i][1]);
            
        }
    }
    for(int i=0;i<buf.size();i++)
    {
    fprintf (filehandle, "%c", buf[i]);
    }
    fclose(filehandle);
    buf.clear();
    //delete filehandle;
}

void DRI::WriteToFile()
{
    vector <char> buf;
    FILE *filehandle;
    filehandle = fopen("test.jpg", "ab");
    buf.push_back(ID[0]);
    buf.push_back(ID[1]);
    buf.push_back(size[0]);
    buf.push_back(size[1]);
    buf.push_back(RI[0]);
    buf.push_back(RI[1]);
    for(int i=0;i<buf.size();i++)
    {
    fprintf (filehandle, "%c", buf[i]);
    }
    fclose(filehandle);
    buf.clear();
    //delete filehandle;
}

void COM::WriteToFile()
{
    vector <char> buf;
    FILE *filehandle;
    filehandle = fopen("test.jpg", "ab");
    buf.push_back(ID[0]);
    buf.push_back(ID[1]);
    buf.push_back(size[0]);
    buf.push_back(size[1]);
    for(int i=0;i<len_com;i++)
    {
        buf.push_back(comment[i]);
    }
    for(int i=0;i<buf.size();i++)
    {
    fprintf (filehandle, "%c", buf[i]);
    }
    fclose(filehandle);
    buf.clear();
    //delete filehandle;
}

