
#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include "RasterSurface.h"
#include "tiles_12.h" // town
#include "fire_01.h"
#include "XTime.h"


#define RS_WIDTH 800
#define RS_HEIGHT 800
#define RS_NUMPIXELS RS_WIDTH*RS_HEIGHT

unsigned int BackBuffer[RS_NUMPIXELS];

#define fixPt 0
struct Matrix2D2
{
	float e_00, e_01, e_10, e_11;
	Matrix2D2()
	{
		e_00 = e_01 = e_10 = e_11 = 0.0f;
	}

	Matrix2D2(float _e_00,float _e_01,float _e_10, float _e_11)
	{
		e_00 = _e_00;
		e_01 = _e_01;
		e_10 = _e_10;
		e_11 = _e_11;
	}

	Matrix2D2(float _radian)
	{
		e_00 = cosf(_radian);
		e_01 = sinf(_radian);
		e_10 = cosf(_radian);
		e_11 = sinf(_radian);
	}
};

class drawImage
{
	struct position
	{
		int x, y;
	};
public:
	bool random = false;
	position m_position[10];
	void cleanBackGround(int w, int h);

	void transferARGB(unsigned int _source, unsigned int& _returnSource, int destIndex);

	//only render
	void BLIT(unsigned int* _buffer, int destX, int destY, const unsigned int* source, unsigned int sourceX, unsigned int sourceY, unsigned int sourceHeight, unsigned int sourceW, unsigned int sourceH);

	//render + rotate
	void BLIT(unsigned int* _buffer, int destX, int destY, const unsigned int* source, unsigned int sourceX, 
		unsigned int sourceY, unsigned int sourceHeight, unsigned int sourceW, unsigned int sourceH, float rotateRadian, int rotateX, int rotateY);

	//render + rotate
	void BLIT(unsigned int* _buffer, int destX, int destY, const unsigned int* source, unsigned int sourceX,
		unsigned int sourceY, unsigned int sourceHeight, unsigned int sourceW, unsigned int sourceH, const Matrix2D2& _matrix2D2, int rotateX, int rotateY);

	void makeRandomTree();

	void lerp(unsigned int& _sourceARGB, unsigned int _destARGB, unsigned int _tempSourceA);
	void lerpFixPt(unsigned int& _sourceARGB, unsigned int _destARGB, unsigned int _tempSourceA);
};
	
void drawImage::lerp(unsigned int& _sourceARGB, unsigned int _destARGB, unsigned int _tempSourceA)
{
	int diff = (int)_sourceARGB - (int)_destARGB;
	_sourceARGB = (int)(diff*((float)_tempSourceA / 255.0f)) + _destARGB;
}

void drawImage::lerpFixPt(unsigned int& _sourceARGB, unsigned int _destARGB, unsigned int _tempSourceA)
{
	int diff = (int)_sourceARGB - (int)_destARGB;
	_sourceARGB = (diff*_tempSourceA + _destARGB*255) / 255;
}
void drawImage::makeRandomTree()
{
	for (int i = 0; i < 10; i++)
	{
		m_position[i].x = rand() % RS_WIDTH;
		m_position[i].y = rand() % RS_HEIGHT;
	}
	
}
void drawImage::cleanBackGround(int w, int h)
{
	int index = 0;
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			//clean white screen
			BackBuffer[index] = 0xFFFFFFFF;

			index++;
		}
	}

}

void  drawImage::transferARGB(unsigned int _source, unsigned int& _returnSource,int destIndex)
{
	//BGRA to ARGB
	unsigned int b = (_source & 0xFF000000) >> 24;
	unsigned int g = (_source & 0x00FF0000) >> 16;
	unsigned int r = (_source & 0x0000FF00) >> 8;

	//get the _tempSourceA from source
	unsigned int _tempSourceA = _source & 0x000000FF;

#if fixPt
	//ARGB interpolation
	lerpFixPt(r, (BackBuffer[destIndex] & 0x00FF0000) >> 16, _tempSourceA);
	lerpFixPt(g, (BackBuffer[destIndex] & 0x0000FF00) >> 8, _tempSourceA);
	lerpFixPt(b, (BackBuffer[destIndex] & 0x000000FF), _tempSourceA);
	
#else if
	//ARGB interpolation
	lerp(r, (BackBuffer[destIndex] & 0x00FF0000) >> 16, _tempSourceA);
	lerp(g, (BackBuffer[destIndex] & 0x0000FF00) >> 8, _tempSourceA);
	lerp(b, (BackBuffer[destIndex] & 0x000000FF), _tempSourceA);
#endif
	//left shift cal A
	_returnSource = _tempSourceA << 24;

	//Add other RGB value
	_returnSource += r << 16;
	_returnSource += g << 8;
	_returnSource += b;

}


void  drawImage::BLIT(unsigned int* _buffer2D, int destX, int destY, const unsigned int* source, unsigned int sourceX,
	unsigned int sourceY, unsigned int sourceHeight, unsigned int sourceW, unsigned int sourceH, float rotateRadian, int rotateX, int rotateY)
{

	
	//source copy
	for (unsigned int x = 0; x < sourceW; x++)
	{
		for (unsigned int y = 0; y < sourceH; y++)
		{
			//origin
			unsigned int originX = destX + x;
			unsigned int originY = destY + y;

			//distance difference from rotate location to dest location
			float diffX = (float)originX - (float)rotateX;
			float diffY = (float)originY - (float)rotateY;

			int indexX = rotateX + (int)(diffX*cosf(rotateRadian) - diffY*sinf(rotateRadian));
			int indexY = rotateY + (int)(diffX*sinf(rotateRadian) + diffY*cosf(rotateRadian));
			 int index = indexX + indexY*RS_HEIGHT;

			//safe check
			if (index >= RS_NUMPIXELS || index<0)
				continue;
			
			
			//source index
			unsigned int sourceIndex = (sourceX + x) + (sourceY + y)*sourceHeight;

			unsigned int refine = 0;
			transferARGB(source[sourceIndex], refine, index);
			_buffer2D[index] = refine;
		}
	}
}


void  drawImage::BLIT(unsigned int* _buffer2D, int destX, int destY, const unsigned int* source, unsigned int sourceX,
	unsigned int sourceY, unsigned int sourceHeight, unsigned int sourceW, unsigned int sourceH, const Matrix2D2& _matrix2D2, int rotateX, int rotateY)
{


	//source copy
	for (unsigned int x = 0; x < sourceW; x++)
	{
		for (unsigned int y = 0; y < sourceH; y++)
		{
			//origin
			unsigned int originX = destX + x;
			unsigned int originY = destY + y;

			//distance difference from rotate location to dest location
			float diffX = (float)originX - (float)rotateX;
			float diffY = (float)originY - (float)rotateY;

			int indexX = rotateX + (int)(diffX*_matrix2D2.e_00 - diffY*_matrix2D2.e_01);
			int indexY = rotateY + (int)(diffX*_matrix2D2.e_10 + diffY*_matrix2D2.e_11);
			int index = indexX + indexY*RS_HEIGHT;

			//safe check
			if (index >= RS_NUMPIXELS || index<0)
				continue;


			//source index
			unsigned int sourceIndex = (sourceX + x) + (sourceY + y)*sourceHeight;

			unsigned int refine = 0;
			transferARGB(source[sourceIndex], refine, index);
			_buffer2D[index] = refine;
		}
	}
}
void  drawImage::BLIT(unsigned int* _buffer2D, int destX, int destY, const unsigned int* source, unsigned int sourceX, 
	unsigned int sourceY, unsigned int sourceHeight, unsigned int sourceW, unsigned int sourceH)
{
	//source copy
	for (unsigned int x = 0; x < sourceW; x++)
	{
		for (unsigned int y = 0; y < sourceH; y++)
		{
			//int destIndex
			unsigned int index = (destX+x) + (destY+y)*RS_HEIGHT;

			//safe check
			if (index >= RS_NUMPIXELS || index<0)
				continue;

			//source index
			unsigned int sourceIndex = (sourceX+x) + (sourceY+y)*sourceHeight;

			unsigned int refine = 0;
			transferARGB(source[sourceIndex], refine,index);
			_buffer2D[index] = refine;		
		}
	}
}

int main(void)
{
	drawImage m_drawImage;
	XTime m_XTime;
	m_XTime.Restart();

	m_drawImage.makeRandomTree();

	RS_Initialize(RS_WIDTH, RS_HEIGHT);

	Matrix2D2 m_matrix2D2((float)M_PI_4);
	int animationCounter = 0;
	do
	{
		m_XTime.Signal();
		
		m_drawImage.cleanBackGround(RS_WIDTH, RS_HEIGHT);
		
		//draw back ground
		for (int x = 0; x < RS_WIDTH; x+=29)
		{
			for (int y = 0; y < RS_HEIGHT; y+=29)
			{
				m_drawImage.BLIT(BackBuffer, x, y, tiles_12_pixels, 290, 129, tiles_12_width, 29, 29);
			}
		}
		
		//draw tree
		for (int i = 0;i <5; i++)
		{		
			m_drawImage.BLIT(BackBuffer, m_drawImage.m_position[i].x, m_drawImage.m_position[i].y, tiles_12_pixels, 321, 14, tiles_12_width, 64, 85);	
		}
		for (int i = 6; i < 10; i++)
		{
		//	m_drawImage.BLIT(BackBuffer, m_drawImage.m_position[i].x, m_drawImage.m_position[i].y, tiles_12_pixels, 321,
			//	14, tiles_12_width, 64, 85, (float)M_PI, m_drawImage.m_position[i].x + 64 / 2, m_drawImage.m_position[i].y + 85 / 2);

			m_drawImage.BLIT(BackBuffer, m_drawImage.m_position[i].x, m_drawImage.m_position[i].y, tiles_12_pixels, 321,
				14, tiles_12_width, 64, 85, (float)M_PI, m_drawImage.m_position[i].x + 64 / 2, m_drawImage.m_position[i].y + 85 / 2);
		}

		int sourceX = 0;
		int sourceY = 0;
		
		sourceX = animationCounter % 8 * 128;
		sourceY = animationCounter / 8 * 128;
		m_drawImage.BLIT(BackBuffer, 250, 250, fire_01_pixels, sourceX, sourceY, fire_01_height, 128, 128, m_matrix2D2, 250 + 128 / 2, 250 + 128 / 2);

		if (m_XTime.TotalTimeExact() >= 1.0f / 30.0f)
		{			
			animationCounter++;
			
			if (animationCounter >= 64)
				animationCounter = 0;

			m_XTime.Restart();
		}
		
	
	} while (RS_Update(BackBuffer, RS_NUMPIXELS));

	RS_Shutdown();

	return 0;
}

