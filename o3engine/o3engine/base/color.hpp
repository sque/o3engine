#ifndef O3ENGINE_COLOR_HPP_INCLUDED
#define O3ENGINE_COLOR_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include <stdint.h>

namespace o3engine {
	//! [R5] Definition of 32bit RGBA color
	/**
	 * @ingroup base_group
	 */
	union color_rgba_t {
		//! Default constructor ( @b NOT Initialized values)
		inline color_rgba_t() {
		}

		//! Construct and initialize from 4 values RGBA
		/**
		 * @param r The red channel of the pixel.
		 * @param g The green channel of the pixel.
		 * @param b The blue channel of the pixel
		 * @param a The alpha channel of the pixel
		 */
		inline color_rgba_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			channels.red = r;
			channels.green = g;
			channels.blue = b;
			channels.alpha = a;
		}

		//! Construct and initialize from 32bit full pixel
		/**
		 * @param rgba_pixel A 32bit length pixel containing 4channels of 8bit colors
		 * in RGBA format.
		 */
		inline color_rgba_t(uint32_t rgba_pixel) :
				full_pixel(rgba_pixel) {
		}

		//! The pixels divided in channels
		struct channels_t {
			uint8_t red;
			uint8_t green;
			uint8_t blue;
			uint8_t alpha;
		} channels;

		//! The 32bit full pixel containing all channels in RGBA format.
		uint32_t full_pixel;
	};

	//! [R5] Definition of 32bit BGRA color
	/**
	 * @ingroup base_group
	 */
	union color_bgra_t {
		//! Default constructor ( @b NOT Initialized values)
		inline color_bgra_t() {
		}

		//! Construct and initialize from 4 values BGRA
		/**
		 * @param b The blue channel of the pixel
		 * @param g The green channel of the pixel.
		 * @param r The red channel of the pixel.
		 * @param a The alpha channel of the pixel
		 */
		inline color_bgra_t(uint8_t b, uint8_t g, uint8_t r, uint8_t a) {
			channels.red = r;
			channels.green = g;
			channels.blue = b;
			channels.alpha = a;
		}

		//! Construct and initialize from 32bit full pixel
		/**
		 * @param bgra_pixel A 32bit length pixel containing 4channels of 8bit colors
		 * in BGRA format.
		 */
		inline color_bgra_t(uint32_t bgra_pixel) :
				full_pixel(bgra_pixel) {
		}

		//! The pixels divided in channels
		struct channels_t {
			uint8_t blue;
			uint8_t green;
			uint8_t red;
			uint8_t alpha;
		} channels;

		//! The 32bit full pixel containing all channels in RGBA format.
		uint32_t full_pixel;
	};

	//! [R5] Definition of 32bit ABGR color
	/**
	 * @ingroup base_group
	 */
	union color_abgr_t {
		//! Default constructor ( @b NOT Initialized values)
		inline color_abgr_t() {
		}

		//! Construct and initialize from 4 values ABGR
		/**
		 @param a The alpha channel of the pixel
		 @param b The blue channel of the pixel
		 @param g The green channel of the pixel.
		 @param r The red channel of the pixel.
		 */
		inline color_abgr_t(uint8_t a, uint8_t b, uint8_t g, uint8_t r) {
			channels.red = r;
			channels.green = g;
			channels.blue = b;
			channels.alpha = a;
		}

		//! Construct and initialize from 32bit full pixel
		/**
		 * @param abgr_pixel A 32bit length pixel containing 4channels of 8bit colors
		 * in ABGR format.
		 */
		inline color_abgr_t(uint32_t abgr_pixel) :
				full_pixel(abgr_pixel) {
		}

		//! The pixels divided in channels
		struct channels_t {
			uint8_t alpha;
			uint8_t blue;
			uint8_t green;
			uint8_t red;
		} channels;

		//! The 32bit full pixel containing all channels in RGBA format.
		uint32_t full_pixel;
	};

	//! [R5] Definition of 32bit ARGB color
	/**
	 * @ingroup base_group
	 */
	union color_argb_t {
		//! Default constructor ( @b NOT Initialized values)
		inline color_argb_t() {
		}

		//! Construct and initialize from 4 values ARGB
		/**
		 @param a The alpha channel of the pixel
		 @param b The blue channel of the pixel
		 @param g The green channel of the pixel.
		 @param r The red channel of the pixel.
		 */
		inline color_argb_t(uint8_t a, uint8_t r, uint8_t b, uint8_t g) {
			channels.red = r;
			channels.green = g;
			channels.blue = b;
			channels.alpha = a;
		}

		//! Construct and initialize from 32bit full pixel
		/**
		 @param argb_pixel A 32bit length pixel containing 4channels of 8bit colors
		 in ARGB format.
		 */
		inline color_argb_t(uint32_t argb_pixel) :
				full_pixel(argb_pixel) {
		}

		//! The pixels divided in channels
		struct channels_t {
			uint8_t alpha;
			uint8_t red;
			uint8_t green;
			uint8_t blue;
		} channels;

		//! The 32bit full pixel containing all channels in RGBA format.
		uint32_t full_pixel;
	};

	//! [R5] Convert low level colors
	/**
	 * This function can work with all @b color_XXXX_t data types.
	 * @remarks The conversion is decided automatically by the types
	 * of the @b source and @b destination values.
	 * @param src The color that will be converted
	 * @param dst The destination storage of the converted
	 * @ingroup base_group
	 */
	template<class C1, class C2>
	void convertColor(C1 & dst, const C2 & src) {
		dst.channels.red = src.channels.red;
		dst.channels.green = src.channels.green;
		dst.channels.blue = src.channels.blue;
		dst.channels.alpha = src.channels.alpha;
	}

	//! [R5] Class for handling and representing a color
	/**
	 * This class is able to handle RGBA colors. All color values are
	 * floating point and meaningful values are in range [0.0, 1.0]
	 *
	 * @par Class Characteristics
	 * Color is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 * @ingroup base_group
	 */
	class Color {
	public:
		//! Constant black and with zero opacity color
		static const Color ZERO;
		//! Constant black color
		static const Color BLACK;
		//! Constant white color
		static const Color WHITE;
		//! Constant red color
		static const Color RED;
		//! Constant green color
		static const Color GREEN;
		//! Constant blue color
		static const Color BLUE;
		//! Constant yellow color
		static const Color YELLOW;
		//! Constant cyan color
		static const Color CYAN;
		//! Constant magenta color
		static const Color MAGENTA;

		//! Value of red channel (Normal values are in range [0, 1] )
		Real red;
		//! Value of green channel (Normal values are in range [0, 1] )
		Real green;
		//! Value of blue channel (Normal values are in range [0, 1] )
		Real blue;
		//! Value of alpha channel (Normal values are in range [0, 1] )
		Real alpha;

		//! Default constructor (@b Not @b initialized )
		/**
		 * Creates a new color object with unitialized values for better
		 * performance.
		 */
		inline Color() {
		}

		//! Construct from 3 float color channels
		/**
		 * Initializes RGBA color with color channels passed by user and full opacity
		 * @param r Red color channel (0.0 to 1.0)
		 * @param g Green color channel (0.0 to 1.0)
		 * @param b Blue color channel (0.0 to 1.0)
		 * @param a Alpha color channel (0.0 to 1.0)
		 */
		inline Color(Real r, Real g, Real b, Real a = 1.0) :
				red(r), green(g), blue(b), alpha(a) {
		}

		//! Construct from 32 bit pixel
		/**
		 * Initializes RGBA color with color and alpha channel passed in an array of bytes.
		 * Each byte represents a channel and its values are between 0 to 255.
		 * @param rgba Array of 4 bytes representing channels Red Green Blue Alpha
		 * @see assignAsRGBA
		 */
		explicit inline Color(const color_rgba_t & rgba) {
			assignAsRGBA(rgba);
		}

		//! @name To/From raw color formats
		//! @{

		//! Assign color value from color_rgba_t
		/**
		 * @param color The r-value of assignment in @b RGBA format
		 */
		inline void assignAsRGBA(const color_rgba_t & color) {
			red = (Real) color.channels.red / (Real) 255;
			green = (Real) color.channels.green / (Real) 255;
			blue = (Real) color.channels.blue / (Real) 255;
			alpha = (Real) color.channels.alpha / (Real) 255;
		}

		//! Assign color value from color_bgra_t
		/**
		 * @param color The r-value of assignment in @b BGRA format
		 */
		inline void assignAsBGRA(const color_bgra_t & color) {
			red = (Real) color.channels.red / (Real) 255;
			green = (Real) color.channels.green / (Real) 255;
			blue = (Real) color.channels.blue / (Real) 255;
			alpha = (Real) color.channels.alpha / (Real) 255;
		}

		//! Assign color value from color_abgr_t
		/**
		 * @param color The r-value of assignment in @b ABGR format
		 */
		inline void assignAsABGR(const color_abgr_t & color) {
			red = (Real) color.channels.red / (Real) 255;
			green = (Real) color.channels.green / (Real) 255;
			blue = (Real) color.channels.blue / (Real) 255;
			alpha = (Real) color.channels.alpha / (Real) 255;
		}

		//! Assign color value from color_argb_t
		/**
		 * @param color The r-value of assignment in @b ARGB format
		 */
		inline void assignAsARGB(const color_argb_t & color) {
			red = (Real) color.channels.red / (Real) 255;
			green = (Real) color.channels.green / (Real) 255;
			blue = (Real) color.channels.blue / (Real) 255;
			alpha = (Real) color.channels.alpha / (Real) 255;
		}

		//! Cast color to color_rgba_t
		inline color_rgba_t castAsRGBA() const {
			color_rgba_t rgba;
			rgba.channels.red = (uint8_t) (red * 255.0);
			rgba.channels.green = (uint8_t) (green * 255.0);
			rgba.channels.blue = (uint8_t) (blue * 255.0);
			rgba.channels.alpha = (uint8_t) (alpha * 255.0);
			return rgba;
		}

		//! Cast color to color_bgra_t
		inline color_bgra_t castAsBGRA() const {
			return color_bgra_t((uint8_t) (blue * 255.0), (uint8_t) (green * 255.0),
					(uint8_t) (red * 255.0), (uint8_t) (alpha * 255.0));
		}

		//! Cast color to color_abgr_t
		inline color_abgr_t castAsABGR() const {
			return color_abgr_t((uint8_t) (alpha * 255.0), (uint8_t) (blue * 255.0),
					(uint8_t) (green * 255.0), (uint8_t) (red * 255.0));
		}

		//! Cast color to color_argb_t
		inline color_argb_t castAsARGB() const {
			return color_argb_t((uint8_t) (alpha * 255.0), (uint8_t) (red * 255.0),
					(uint8_t) (green * 255.0), (uint8_t) (blue * 255.0));
		}

		//! @}

		//! @name Math operators
		//! @{
		inline Color operator+(const Color & r) const {
			return Color(red + r.red, green + r.green, blue + r.blue,
					alpha + r.alpha);
		}

		inline Color operator*(const Color & r) const {
			return Color(red * r.red, green * r.green, blue * r.blue,
					alpha * r.alpha);
		}

		inline Color operator*(Real factor) const {
			return Color(red * factor, green * factor, blue * factor,
					alpha * factor);
		}

		inline Color & operator+=(const Color & r) {
			red += r.red;
			green += r.green;
			blue += r.blue;
			alpha += r.alpha;
			return *this;
		}

		inline Color & operator*=(const Color & r) {
			red *= r.red;
			green *= r.green;
			blue *= r.blue;
			alpha *= r.alpha;
			return *this;
		}

		inline Color & operator*=(Real factor) {
			red *= factor;
			green *= factor;
			blue *= factor;
			alpha *= factor;
			return *this;
		}
		//! @}

		//! Check if color is full opaque
		/**
		 @return It will return true if the alpha channel is 1 (full opaque).
		 */
		inline bool isOpaque() const {
			return (alpha == 1.0);
		}

		//! Check if color is transparent
		/**
		 * @return It will return true if alpha channel is less than 1.
		 * @note Semi-transparent colors will return true here.
		 */
		inline bool isTransperant() const {
			return (alpha < 1.0);
		}

		//! Get the middle point of a gradient from this color to the target, step is from 0 to 1
		/**
		 * It will calculate the color of a middle point from a gradient. The gradient will begin from this color
		 * and ends at the target color. By defining the step parameter you define the place of the middle point
		 * inside gradient.
		 * @param target Destination color of gradient
		 * @param step The place of the middle point. Acceptable range is [0.0, 1.0]. By defining 0 you mean this
		 * color and 1.0 means target color, all other values means a color inside the gradient.
		 * @return The color of the point at the defined place inside the gradient.
		 */
		inline Color gradientLinear(const Color & target, Real step) const {
			return Color(red + ((target.red - red) * step),
					blue + ((target.blue - blue) * step),
					green + ((target.green - green) * step),
					alpha + ((target.alpha - alpha) * step));
		}

		//! @name Comparison operators
		//! @{

		//! Check equality operator
		/**
		 Classical object comparison operator. It will compare all channels with those of r-value
		 @return It will return true if all channels are the same.
		 */
		inline bool operator==(const Color & r) const {
			return (red == r.red) && (blue == r.blue) && (red == r.red)
					&& (alpha == r.alpha);
		}

		//! Different comparison
		inline bool operator!=(const Color & r) const {
			return (!operator==(r));
		}

		//! @}
	};
}
#endif
