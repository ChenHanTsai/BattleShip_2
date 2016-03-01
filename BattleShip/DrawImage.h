#pragma once
#include <cmath>

#include <iostream>
#include "Factors.h"

#define fixPt 1

static unsigned int BackBuffer[RS_NUMPIXELS];
struct Matrix2D2
{
	float e_00, e_01, e_10, e_11;
	Matrix2D2()
	{
		e_00 = e_01 = e_10 = e_11 = 0.0f;
	}

	Matrix2D2(float _e_00, float _e_01, float _e_10, float _e_11)
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
	void lerpFixPt(unsigned int& _sourceARGB, unsigned int _destARGB, unsigned int _tempSourceA);
	void lerp(unsigned int& _sourceARGB, unsigned int _destARGB, unsigned int _tempSourceA);
	
};

