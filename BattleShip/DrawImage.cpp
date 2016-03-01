#include "DrawImage.h"


void drawImage::lerp(unsigned int& _sourceARGB, unsigned int _destARGB, unsigned int _tempSourceA)
{
	int diff = (int)_sourceARGB - (int)_destARGB;
	_sourceARGB = (int)(diff*((float)_tempSourceA / 255.0f)) + _destARGB;
}

void drawImage::lerpFixPt(unsigned int& _sourceARGB, unsigned int _destARGB, unsigned int _tempSourceA)
{
	int diff = (int)_sourceARGB - (int)_destARGB;
	_sourceARGB = (diff*_tempSourceA + _destARGB * 255) / 255;
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

void  drawImage::transferARGB(unsigned int _source, unsigned int& _returnSource, int destIndex)
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
			unsigned int index = (destX + x) + (destY + y)*RS_HEIGHT;

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

