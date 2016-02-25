#include <stdlib.h>
#include "gradientColorPicker.h"

/**
 * Constructs a new gradientColorPicker.
 *
 * @param fadeColor1 The first color to start the gradient at.
 * @param fadeColor2 The second color to end the gradient with.
 * @param radius How quickly to transition to fadeColor2.
 * @param centerX X coordinate for the center of the gradient.
 * @param centerY Y coordinate for the center of the gradient.
 */
gradientColorPicker::gradientColorPicker( RGBAPixel fadeColor1, 
		RGBAPixel fadeColor2, int radius, int centerX, int centerY ) {
	/** 
	 * @todo Construct your gradientColorPicker here! You may find it
	 *	helpful to create additional member variables to store things.
	 */
  color1 = fadeColor1;
  color2 = fadeColor2;
  cX = centerX;
  cY = centerY;
  rad = radius;  
}

/**
 * Picks the color for pixel (x, y).
 *
 * The first color fades into the second color as you move from the initial
 * fill point, the center, to the radius. Beyond the radius, all pixels
 * should be just color2. 
 *
 * You should calculate the distance between two points using the standard
 * Manhattan distance formula, 
 * 
 * \f$d = |center\_x - given\_x| + |center\_y - given\_y|\f$
 *
 * Then, scale each of the three channels (R, G, and B) from fadeColor1 to
 * fadeColor2 linearly from d = 0 to d = radius. 
 *
 * For example, the red color at distance d where d is less than the radius
 * must be
 *
 * \f$ redFill = fadeColor1.red - \left\lfloor
   \frac{d*fadeColor1.red}{radius}\right\rfloor +
   \left\lfloor\frac{d*fadeColor2.red}{radius}\right\rfloor\f$
 *
 * Note that all values are integers. If you do not follow this formula,
 * your colors may be very close but round differently than ours.
 *
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinate to pick a color for.
 * @return The color selected for (x, y).
 */
RGBAPixel gradientColorPicker::operator()(int x, int y)
{
	RGBAPixel color;
	int distance = abs(cX - x) + abs(cY - y);
	if(distance > rad){
	  color.red = color2.red;
	  color.green = color2.green;
	  color.blue = color2.blue;
	  color.alpha = color2.alpha;
	}else{
	  int redFill = color1.red - floor(distance * color1.red / rad) + floor(distance * color2.red / rad);
	  int greenFill = color1.green - floor(distance * color1.green / rad) + floor(distance * color2.green / rad);
	  int blueFill = color1.blue - floor(distance * color1.blue / rad) + floor(distance * color2.blue / rad);
	  int alphaFill = color1.alpha - floor(distance * color1.alpha / rad) + floor(distance * color2.alpha / rad);
	  color.red = redFill;
	  color.green = greenFill;
	  color.blue = blueFill;
	  color.alpha = alphaFill;
	}
	return color;
}
