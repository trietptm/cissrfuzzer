/* 
 * File:   jpegf.h
 * Author: serge
 *
 * Created on 13 липня 2011, 12:15
 */

#ifndef JPEGF_H
#define    JPEGF_H

class Marker
{
    public:
    Marker(char *);
    //~Marker();
    void WriteToFile();
    protected:
    char ID[2];
};

class SOFx : public Marker
{
    public:
    SOFx(char *, char);
    ~SOFx()
        {
            delete[] comp_ID;
            delete[] discr;
            delete[] num_quant_tab;
        }
    void DetSize()
    {
            size[0]=(char)(size_int/256);
            size[1]=(char)(size_int%256);
    }
    void WriteToFile();
    private:
        char size[2];
        int size_int;
    char precision;
    char Y_image[2];
    char X_image[2];
    char num_comps;
    char *comp_ID;
    char *discr;
    char *num_quant_tab;
};

class DHT : public Marker
{
    public:
    DHT(char *, char, char);
    ~DHT()
        {
            delete[] HT_symb;
        }
    void DetSize()
    {
            size[0]=(char)(size_int/256);
            size[1]=(char)(size_int%256);
    }
    void WriteToFile();
    private:
        char size[2];
        int size_int;
    char HT_info;
    char HT_len[16];
    char *HT_symb;
};

class SOS : public Marker
{
    public:
    SOS(char *, char);
    ~SOS()
        {
            delete[] comp_ID;
            delete[] tab_Huff;
        }
    void DetSize()
    {
            size[0]=(char)(size_int/256);
            size[1]=(char)(size_int%256);
    }
    void WriteToFile();
    private:
        char size[2];
        int size_int;
    char num_comps;
    char *comp_ID;
    char *tab_Huff;
    char ign[3];
};

class DQT : public Marker
{
    public:
    DQT(char *);
    ~DQT()
        {
            for(int i=0;i<64;i++)
            {
                delete[]  qTable[i];
            }
        }
    void DetSize()
    {
            size[0]=(char)(size_int/256);
            size[1]=(char)(size_int%256);
    }
    void WriteToFile();
    private:
        char size[2];
        int size_int;
    char tab_inf;
    char *qTable[64];
};

class DRI : public Marker
{
    public:
    DRI(char *);
    //~DRI();
    void DetSize()
    {
            size[0]=(char)(size_int/256);
            size[1]=(char)(size_int%256);
    }
    void WriteToFile();
    private:
        char size[2];
        int size_int;
    char RI[2];
};

class COM : public Marker
{
    public:
    COM(char *);
    ~COM()
        {
            delete[] comment;
        }
    void DetSize()
    {
            size[0]=(char)(size_int/256);
            size[1]=(char)(size_int%256);
    }
    void WriteToFile();
    private:
        char size[2];
        int size_int;
    char *comment;
        int len_com;
};

class APPx : public Marker
{
    public:
    APPx(char *, char *);
    ~APPx()
        {
            delete[] app_ID;
            delete[] Preview;
        }
    void DetSize()
    {
            size[0]=(char)(size_int/256);
            size[1]=(char)(size_int%256);
    }
    void WriteToFile();
    private:
        char size[2];
        int size_int;
    char *app_ID;
    char version[2];
    char unit;
    char Xdensity[2];
        char Ydensity[2];
        char xThumbnail;
        char yThumbnail;
        char* Preview;
};


#endif    /* JPEGF_H */

