#ifndef __PIXEL_SHADER_STATE_H
#define __PIXEL_SHADER_STATE_H

#include "LinearInterpolator.h"
#include "PixelShader.h"
#include "OutputBuffer.h"

const int kMaxParams = 16;

class PixelShaderState
{
public:
	PixelShaderState(OutputBuffer *buffer);
	
	// Coordinates are in screen space (-1.0 -> 1.0)
	void setUpTriangle(float x1, float y1, float z1, 
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		PixelShader *shader);
	void setUpParam(int paramIndex, float c1, float c2, float c3);
	
	// Shade a 4x4 set of pixels in parallel.  Left and top are
	// in pixel coordinates.
	void fillMasked(int left, int top, unsigned short mask);
	
private:
	LinearInterpolator fZInterpolator;
	LinearInterpolator fParamInterpolators[kMaxParams];
	int fNumParams;
	PixelShader *fShader;
	OutputBuffer *fOutputBuffer;
	float fX0;
	float fY0;
	float fZ0;
	float fX1;
	float fY1;
	float fZ1;
	float fX2;
	float fY2;
	float fZ2;
	vec16<float> fXStep;
	vec16<float> fYStep;
};

#endif