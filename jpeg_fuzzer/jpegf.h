/* 
 * File:   jpegf.h
 * Author: serge
 *
 * Created on 13 липня 2011, 12:15
 */

#ifndef JPEGF_H
#define	JPEGF_H

class Marker
{
	public:
	Marker(char *);
	//~Marker();
	void WriteToFile();
	protected:
	char ID[2];
	char size[2];
};

class SOFx : public Marker
{
	public:
	SOFx(char *, char);
	//~SOFx();
	void DetSize()
	{
		int sz=2+1+2+2+1+(sizeof(comp_ID))*3;
		size[0]=0;
		size[1]=(char)sz;
	}
	void WriteToFile();
	private:
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
	//~DHT();
	void DetSize()
	{
		int sz=2+1+16+sizeof(HT_symb);
		size[0]=0;
		size[1]=(char)sz;
	}
	void WriteToFile();
	private:
	char HT_info;
	char HT_len[16];
	char *HT_symb;
};

class SOS : public Marker
{
	public:
	SOS(char *, char);
	//~SOS();
	void DetSize()
	{
		int sz=2+1+3+sizeof(comp_ID)+sizeof(tab_Huff);
		size[0]=0;
		size[1]=(char)sz;
	}
	void WriteToFile();
	private:
	char num_comps;
	char *comp_ID;
	char *tab_Huff;
	char ign[3];
};

class DQT : public Marker
{
	public:
	DQT(char *);
	//~DQT();
	void DetSize()
	{
                int inf;
                if(tab_inf<16) inf=1;
                else inf=2;
		int sz=2+1+64*inf;
		size[0]=0;
		size[1]=(char)sz;
	}
	void WriteToFile();
	private:
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
		int sz=2+2;
		size[0]=0;
		size[1]=(char)sz;
	}
	void WriteToFile();
	private:
	char RI[2];
};

class COM : public Marker
{
	public:
	COM(char *);
	//~COM();
	void DetSize()
	{
		int sz=2+sizeof(comment);
		size[0]=0;
		size[1]=(char)sz;
	}
	void WriteToFile();
	private:
	char *comment;
};

class APPx : public Marker
{
	public:
	APPx(char *, char *);
	//~APPx();
	void DetSize()
	{
		int sz=2+sizeof(app_ID)+2+1+2+2+1+1+sizeof(Preview);
		if(sz<256)
		{
			size[0]=0;
		    size[1]=(char)sz;
		}
		else
		{
			size[0]=(char)(sz/256);
			size[1]=(char)(sz%256);
		}
	}
	void WriteToFile();
	private:
	char *app_ID;
	char version[2];
	char unit;
	char Xdensity[2];
    char Ydensity[2];
    char xThumbnail;
    char yThumbnail;
    char* Preview;
};


#endif	/* JPEGF_H */

