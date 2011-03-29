#pragma once

/*
 larger, lower frequency, farther repetition = farther from viewer (black)
 smaller, higher frequency, closer repetition = closer to viewer (white)
 
 linear interpolation causes there to be less obvious 'stepping' effects in the 3d image
 */

#define USE_LINEAR_INTERPOLATION

class ofxAutostereogram {
public:
	/*
	 makeAutostereogram() expects the resultImage's width to be equal to the depthImage plus tileImage widths
	 */
	static void makeAutostereogram(ofImage& tileImage, ofImage& depthImage, float depthMultiplier, ofImage& resultImage) {
		int width = depthImage.getWidth();
		int height = depthImage.getHeight();
		int tileWidth = tileImage.getWidth();
		int tileHeight = tileImage.getHeight();
		int targetWidth = width + tileWidth;
		
		unsigned char* result = resultImage.getPixels();
		unsigned char* tile = tileImage.getPixels();
		unsigned char* depth = depthImage.getPixels();
		
		depthMultiplier *= tileWidth / 255.;
		
		// fill in the first strip
		for(int ty = 0; ty < height; ty++) {
			for(int tx = 0; tx < tileWidth; tx++) {
				int ti = ty * targetWidth + tx;
				int sy = ty % tileHeight;
				int si = sy * tileWidth + tx;
				memcpy(&result[ti * 3], &tile[si * 3], 3);
			}
		}
		
		// fill in remaining strips
		int di = 0;
		for(int ty = 0; ty < height; ty++) {
			int ti = ty * targetWidth + tileWidth;
			for(int tx = 0; tx < width; tx++) {
#ifdef USE_LINEAR_INTERPOLATION
				float si = ty * targetWidth + tx + depth[di] * depthMultiplier;
				int lefti = (int) si;
				int righti = lefti + 1;
				float leftAmount = (float) righti - si;
				float rightAmount =  si - (float) lefti;
				unsigned char* resultPixel = &result[ti * 3];
				unsigned char* leftPixel = &result[lefti * 3];
				unsigned char* rightPixel = &result[righti * 3];
				resultPixel[0] = (unsigned char) (leftPixel[0] * leftAmount + rightPixel[0] * rightAmount);
				resultPixel[1] = (unsigned char) (leftPixel[1] * leftAmount + rightPixel[1] * rightAmount);
				resultPixel[2] = (unsigned char) (leftPixel[2] * leftAmount + rightPixel[2] * rightAmount);
#else
				int si = ty * targetWidth + tx + depth[di] * depthMultiplier;
				memcpy(&result[ti * 3], &result[si * 3], 3);
#endif
				di++;
				ti++;
			}
		}
	}
};