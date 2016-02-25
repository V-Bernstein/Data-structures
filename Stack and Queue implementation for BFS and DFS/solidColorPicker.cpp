#include "solidColorPicker.h"

/**
 * Constructs a new solidColorPicker.
 * 
 * @param fillColor The color for this color picker.
 */
solidColorPicker::solidColorPicker(RGBAPixel fillColor)
{
	/**
	 * @todo Initialize a new solidColorPicker here!
	 */

  color = fillColor;
  
}

/**
 * Picks the color for pixel (x, y).
 *
 * Simply returns the same color (used to construct the picker) all of the
 * time.
 */
RGBAPixel solidColorPicker::operator()(int x, int y)
{
	/**
	 * @todo Return the appropriate color here! */

  RGBAPixel retVal;
  retVal.red = color.red;
  retVal.green = color.green;
  retVal.blue = color.blue;
  retVal.alpha = color.alpha;

  return retVal;
}
