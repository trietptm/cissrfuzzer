// bmp_fuzz.cpp : Defines the entry point for the application.


#include "stdafx.h"
#include <time.h>
#include <iostream>

void CreateBmp1 (char *fname);
void CreateBmp4 (char *fname);
void CreateBmp8 (char *fname);
void CreateBmp16 (char *fname);
void CreateBmp24 (char *fname);
void CreateBmp32 (char *fname);
int col16(int col_ind, int i);
int Padding1(int width);
int Padding4(int width);

BOOL Convert256To24 (char *fin, char *fout);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{	
	srand((unsigned)time(NULL));	
	int rnd_bmp = rand()%6; 
	switch(rnd_bmp){
	  case 0:
			CreateBmp1 ("bmp1bit.bmp");break;
      case 1: 
			CreateBmp4 ("bmp4bit.bmp");break;
	  case 2:
			CreateBmp8 ("bmp8bit.bmp");break;
      case 3:
			CreateBmp16 ("bmp16bit.bmp");break;
	  case 4:	
			CreateBmp24 ("bmp24bit.bmp");break;
	  case 5:
			CreateBmp32 ("bmp32bit.bmp");break;
	}
	
	MessageBox(NULL,(LPCWSTR)"ALL DONE", (LPCWSTR)"BMP Fuzzer", MB_OK | MB_ICONASTERISK); 
	return rnd_bmp;
}

// Генерация 16-цветной палитры
int col16(int i, int col_ind)
{
	int pal[16][3]={
		0,0,0,
		128,0,0,
		0,128,0,
		128,128,0,
		0,0,128,
		128,0,128,
		0,128,128,
		128,128,128,
		192,192,192,
		255,0,0,
		0,255,0,
		255,255,0,
		0,0,255,
		255,0,255,
		0,255,255,
		255,255,255
		};
	return pal[i][col_ind];
}

int Padding1(int width)
{ 
	while (width-32 > 0) width = width-32;
	int k=0;	

	if (width>0 ,width<8) k=4;
	else if (width>7 ,width<16)  k=3;
	else if (width>15 ,width<24) k=2;
	else if (width>23 ,width<32) k=1;
	else k=0;

	return k;
}

int Padding4(int width)
{ 
	while (width-8 > 0) width = width-8;
	int k=0;	

	if (width==1) k=4;
	else if	(width>1 ,width<4) k=3;
	else if (width>3 ,width<6) k=2;
	else if (width>5 ,width<8) k=1;
	else k=0;

	return k;
}

//	bmp 1 бит
void CreateBmp1 (char *fname)
{
	HANDLE hFile;
	DWORD RW;
	int i, j;

	srand((unsigned)time(NULL));

	// Объявим нужные структуры
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	RGBQUAD Palette [2];									// Палитра 2 цвета

	// Рандомно зададим размер картинки
	int Width = rand()%1000;
	int Height = rand()%1000;

	// Заполним их
	memset (&bfh, 0, sizeof(bfh));
	bfh.bfType = 0x4D42;									// Обозначим, что это bmp 'BM'
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih)+8;		
	bfh.bfSize = bfh.bfOffBits + 
				 Height *(Width/8-(Width%8)/8) + 
				 Height * Padding1(Width);					// Посчитаем размер конечного файла

	memset (&bih, 0, sizeof(bih));

	bih.biSize = sizeof(bih);								
	bih.biBitCount = 1;										// 1 бит на пиксель
	bih.biCompression = BI_RGB;								
	bih.biHeight = Height;
	bih.biWidth = Width;
	bih.biPlanes = 1;										

	hFile = CreateFile ((LPCWSTR)fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	// Запишем заголовки
	WriteFile (hFile, &bfh, sizeof (bfh), &RW, NULL);
	WriteFile (hFile, &bih, sizeof (bih), &RW, NULL);

	// Создадим и запишем палитру
	memset (&Palette[0], 0, sizeof (RGBQUAD));
		Palette[0].rgbRed = 0;
		Palette[0].rgbGreen = 0;
		Palette[0].rgbBlue = 0;
		Palette[0].rgbReserved = 0;
		Palette[1].rgbRed = 255;
		Palette[1].rgbGreen = 255;
		Palette[1].rgbBlue = 255;
		Palette[1].rgbReserved = 0;

	WriteFile (hFile, Palette, 2 * sizeof (RGBQUAD), &RW, NULL);

	// Сгенерируем и запишем случайное изображение		
	BYTE **color_matrix;
	color_matrix = new BYTE*[Height];
				
	for (i = 0; i < Height; i++) 
			color_matrix[i] = new BYTE[Width/8+1];

	for (i = 0; i < Height; i++) 
			for (j = 0; j < Width/8+1; j++) 
			color_matrix[i][j]=rand()%256;
	
	for (i = 0; i < Height; i++)
	{
		for (j = 0; j < (Width/8); j++)
		{
			WriteFile (hFile, &color_matrix[i][j], 1, &RW, NULL);
		}
	// Выровняем по границе
	WriteFile (hFile, &color_matrix[i][j+1], Padding1(Width), &RW, NULL);
	}
	CloseHandle(hFile);
}

// bmp 4 бит
void CreateBmp4 (char *fname)
{
	HANDLE hFile;
	DWORD RW;
	int i, j;

	srand((unsigned)time(NULL));

	// Объявим нужные структуры
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	RGBQUAD Palette [16];									//Палитра 16 цветов

	// Рандомно зададим размер картинки
	int Width = rand()%1000;
	int Height = rand()%1000;

	// Заполним их
	memset (&bfh, 0, sizeof(bfh));
	bfh.bfType = 0x4D42;									// Обозначим, что это bmp 'BM'
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih) + 64;			
	bfh.bfSize = bfh.bfOffBits + 
				 Height*(Width/2-(Width%2)/2) + 
				 Height*Padding4(Width);					// Посчитаем размер конечного файла

	memset (&bih, 0, sizeof(bih));
	bih.biSize = sizeof(bih);							
	bih.biBitCount = 4;										// 4 бит на пиксель
	bih.biCompression = BI_RGB;								
	bih.biHeight = Height;
	bih.biWidth = Width;
	bih.biPlanes = 1;										

	hFile = CreateFile ((LPCWSTR)fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	// Запишем заголовки
	WriteFile (hFile, &bfh, sizeof (bfh), &RW, NULL);
	WriteFile (hFile, &bih, sizeof (bih), &RW, NULL);

	// Создадим и запишем палитру
	memset (&Palette[0], 0, sizeof (RGBQUAD));
	for (i = 1; i < 16; i++)
	{
		Palette[i].rgbRed = col16(i,0);
		Palette[i].rgbGreen = col16(i,1);
		Palette[i].rgbBlue = col16(i,2);
		Palette[i].rgbReserved = 0;
	}

	WriteFile (hFile, Palette, 16 * sizeof (RGBQUAD), &RW, NULL);

	// Сгенерируем и запишем случайное изображение
	BYTE **color_matrix;
	color_matrix = new BYTE*[Height];
				
	for (i = 0; i < Height; i++) 
			color_matrix[i] = new BYTE[Width/2+1];

	for (i = 0; i < Height; i++) 
			for (j = 0; j < Width/2+1; j++) 
			color_matrix[i][j]=rand()%256;

	for (i = 0; i < Height; i++)
	{
		for (j = 0; j < Width/2; j++)
		{
			WriteFile (hFile, &color_matrix[i][j], 1, &RW, NULL);
		}
		// Выровняем по границе
		WriteFile (hFile, &color_matrix[i][j+1], Padding4(Width), &RW, NULL);
	}
	CloseHandle(hFile);
}

// bmp 8 бит
void CreateBmp8 (char *fname)
{
	HANDLE hFile;
	DWORD RW;
	int i, j;

	srand((unsigned)time(NULL));

	// Объявим нужные структуры
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	RGBQUAD Palette [256];									// Палитра 256 цветов 

	// Рандомно зададим размер картинки
	int Width = rand()%1000;
	int Height = rand()%1000;

	// Заполним их
	memset (&bfh, 0, sizeof(bfh));
	bfh.bfType = 0x4D42;									// Обозначим, что это bmp 'BM'
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih) + 1024;		
	bfh.bfSize = bfh.bfOffBits + 
				 Width * Height + 
				 Height * ((3*Width) % 4);					// Посчитаем размер конечного файла

	memset (&bih, 0, sizeof(bih));
	bih.biSize = sizeof(bih);								
	bih.biBitCount = 8;										// 8 бит на пиксель
	bih.biCompression = BI_RGB;								
	bih.biHeight = Height;
	bih.biWidth = Width;
	bih.biPlanes = 1;										

	hFile = CreateFile ((LPCWSTR)fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	// Запишем заголовки
	WriteFile (hFile, &bfh, sizeof (bfh), &RW, NULL);
	WriteFile (hFile, &bih, sizeof (bih), &RW, NULL);

	// Создадим и запишем палитру
	memset (&Palette[0], 0, sizeof (RGBQUAD));
	for (i = 1; i < 256; i++)
	{
		Palette[i].rgbBlue = Palette[i-1].rgbBlue + 20;
		Palette[i].rgbGreen = Palette[i-1].rgbGreen + 30;
		Palette[i].rgbRed = Palette[i-1].rgbRed + 10;
		Palette[i].rgbReserved = 0;
	}
	WriteFile (hFile, Palette, 256 * sizeof (RGBQUAD), &RW, NULL);

	// Сгенерируем и запишем случайное изображение
	BYTE **color_matrix;
	color_matrix = new BYTE*[Height];
				
	for (i = 0; i < Height; i++) 
			color_matrix[i] = new BYTE[Width];

	for (i = 0; i < Height; i++) 
			for (j = 0; j < Width; j++) 
			color_matrix[i][j]=rand()%256;

	for (i = 0; i < Height; i++)
	{
		for (j = 0; j < Width; j++)
		{
			WriteFile (hFile, &color_matrix[i][j], 1, &RW, NULL);
		}
		// Выровняем по границе
		WriteFile (hFile, Palette, (3 * Width) % 4, &RW, NULL);
	}

	CloseHandle(hFile);
}

// bmp 16 бит типа 5-5-5
void CreateBmp16 (char *fname)
{
	HANDLE hFile;
	DWORD RW;
	int i, j;

	srand((unsigned)time(NULL));
	
	// Объявим нужные структуры
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	BYTE Palette [1024];									// Палитра

	// Рандомно зададим размер картинки
	int Width = rand()%1000;
	int Height = rand()%1000;

	memset (Palette, 0, 1024);								// В палитре у нас нули

	// Заполним их
	memset (&bfh, 0, sizeof(bfh));
	bfh.bfType = 0x4D42;									// Обозначим, что это bmp 'BM'
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih) + 1024;		
	bfh.bfSize = bfh.bfOffBits + 
				 2 * Width * Height + 
				 Height * (2*Width % 4);					// Посчитаем размер конечного файла

	memset (&bih, 0, sizeof(bih));
	bih.biSize = sizeof(bih);								
	bih.biBitCount = 16;									// 16 бит на пиксель
	bih.biClrUsed = 32768;									// Используем формат 5-5-5
	bih.biCompression = BI_RGB;								
	bih.biHeight = Height;
	bih.biWidth = Width;
	bih.biPlanes = 1;										

	hFile = CreateFile ((LPCWSTR)fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	// Запишем заголовки
	WriteFile (hFile, &bfh, sizeof (bfh), &RW, NULL);
	WriteFile (hFile, &bih, sizeof (bih), &RW, NULL);

	// Запишем палитру
	WriteFile (hFile, Palette, 1024, &RW, NULL);

	// Сгенерируем и запишем случайное изображение
	WORD **color_matrix;
	color_matrix = new WORD*[Height];
				
	for (i = 0; i < Height; i++) 
		color_matrix[i] = new WORD[Width];

	for (i = 0; i < Height; i++) 
		for (j = 0; j < Width; j++) 
			color_matrix[i][j]=rand()%32768;

	for (i = 0; i < Height; i++)
	{
		for (j = 0; j < Width; j++)
		{
			WriteFile (hFile, &color_matrix[i][j], 2, &RW, NULL);
		}
		// Выровняем по границе
		WriteFile (hFile, Palette, (2*Width) % 4, &RW, NULL);
	}

	CloseHandle(hFile);
}

// bmp 24 бит
void CreateBmp24 (char *fname)
{
	HANDLE hFile;
	DWORD RW;
	int i, j;

	srand((unsigned)time(NULL));

	// Объявим нужные структуры
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	BYTE Palette [1024];									// Палитра

	// Рандомно зададим размер картинки
	int Width = rand()%1000;
	int Height = rand()%1000;

	memset (Palette, 0, 1024);								// В палитре у нас нули

	// Заполним их
	memset (&bfh, 0, sizeof(bfh));
	bfh.bfType = 0x4D42;									// Обозначим, что это bmp 'BM'
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih) + 1024;		
	bfh.bfSize = bfh.bfOffBits + 
				 3 * Width * Height + 
				 Height * (Width % 4);						// Посчитаем размер конечного файла

	memset (&bih, 0, sizeof(bih));
	bih.biSize = sizeof(bih);								
	bih.biBitCount = 24;									// 24 бит на пиксель
	bih.biCompression = BI_RGB;								
	bih.biHeight = Height;
	bih.biWidth = Width;
	bih.biPlanes = 1;										
	hFile = CreateFile ((LPCWSTR)fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	// Запишем заголовки
	WriteFile (hFile, &bfh, sizeof (bfh), &RW, NULL);
	WriteFile (hFile, &bih, sizeof (bih), &RW, NULL);
	
	// Запишем палитру
	WriteFile (hFile, Palette, 1024, &RW, NULL);

	// Сгенерируем и запишем случайное изображение
	RGBTRIPLE **color_matrix;
	color_matrix = new RGBTRIPLE*[Height];
				
	for (i = 0; i < Height; i++) 
		color_matrix[i] = new RGBTRIPLE[Width];

	for (i = 0; i < Height; i++) 
		for (j = 0; j < Width; j++) {
			color_matrix[i][j].rgbtRed=rand()%256;
			color_matrix[i][j].rgbtGreen=rand()%256;
			color_matrix[i][j].rgbtBlue=rand()%256;
		}

	for (i = 0; i < Height; i++)
	{
		for (j = 0; j < Width; j++)
		{
			WriteFile (hFile, &color_matrix[i][j], 3, &RW, NULL);
		}
		// Выровняем по границе
		WriteFile (hFile, Palette, Width % 4, &RW, NULL);
	}

	CloseHandle(hFile);
}

// bmp 32 бит
void CreateBmp32 (char *fname)
{
	HANDLE hFile;
	DWORD RW;
	int i, j;

	srand((unsigned)time(NULL));

	// Объявим нужные структуры
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	BYTE Palette [1024];									// Палитра

	// Рандомно зададим размер картинки
	int Width = rand()%1000;
	int Height = rand()%1000;

	memset (Palette, 0, 1024);								// В палитре нули

	// Заполним их
	memset (&bfh, 0, sizeof(bfh));
	bfh.bfType = 0x4D42;									// Обозначим, что это bmp 'BM'
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih) + 1024;		
	bfh.bfSize = bfh.bfOffBits + 
				 4 * Width * Height;						// Посчитаем размер конечного файла

	memset (&bih, 0, sizeof(bih));
	bih.biSize = sizeof(bih);								
	bih.biBitCount = 32;									// 32 бит на пиксель
	bih.biCompression = BI_RGB;								
	bih.biHeight = Height;
	bih.biWidth = Width;
	bih.biPlanes = 1;										

	hFile = CreateFile ((LPCWSTR)fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	// Запишем заголовки
	WriteFile (hFile, &bfh, sizeof (bfh), &RW, NULL);
	WriteFile (hFile, &bih, sizeof (bih), &RW, NULL);
	
	// Запишем палитру
	WriteFile (hFile, Palette, 1024, &RW, NULL);

	// Сгенерируем и запишем случайное изображение
	RGBQUAD **color_matrix;
	color_matrix = new RGBQUAD*[Height];
				
	for (i = 0; i < Height; i++) 
		color_matrix[i] = new RGBQUAD[Width];

	for (i = 0; i < Height; i++) 
		for (j = 0; j < Width; j++) {
			color_matrix[i][j].rgbRed=rand()%256;
			color_matrix[i][j].rgbGreen=rand()%256;
			color_matrix[i][j].rgbBlue=rand()%256;
			color_matrix[i][j].rgbReserved = 0; //4-й байт не используется, но его можно отдать 
												//для альфа-канала (прозрачности)
		}

	for (i = 0; i < Height; i++)
	{
		for (j = 0; j < Width; j++)
		{
			WriteFile (hFile, &color_matrix[i][j], 4, &RW, NULL);
		}
	}
	CloseHandle(hFile);
}
