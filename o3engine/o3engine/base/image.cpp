#include "./image.hpp"

#include <FreeImage.h>

namespace o3engine {
	// Construct an empty image with unknown content
	Image::Image(size_type width, size_type height) :
			mp_pixels(NULL), m_data_size(width * height), m_width(width), m_height(
					height) {
		// Allocate space
		mp_pixels = new pixel_type[m_data_size];

	}

	// Construct with an empty image
	Image::Image(size_type width, size_type height, const Color & back_color) :
			mp_pixels(NULL), m_data_size(width * height), m_width(width), m_height(
					height) {
		// Allocate space
		mp_pixels = new pixel_type[m_data_size];

		// Add background color
		pixel_type back_pixel = back_color.castAsRGBA();
		for (size_type i = 0; i < m_data_size; i++) {
			mp_pixels[i] = back_pixel;
		}
	}

	Image::Image(const std::string & fname) :
			mp_pixels(NULL), m_data_size(0), m_width(0), m_height(0) {
		loadImage(fname);
	}

	// Copy operator
	Image & Image::operator=(const Image & r) {
		// Empty old data if any
		if (mp_pixels) {
			delete[] mp_pixels;
			mp_pixels = NULL;
		}

		// Copy variables
		m_data_size = r.m_data_size;
		m_width = r.m_width;
		m_height = r.m_height;

		// Copy data
		if (m_data_size > 0) {
			mp_pixels = new pixel_type[m_data_size];
			memcpy(mp_pixels, r.mp_pixels, m_data_size);
		}
		return *this;
	}

	bool Image::loadImage(const std::string & fname) {
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP * dibUnknown, *dib32;
		size_type scan_pitch;

		// check the file signature and deduce its format
		// (the second argument is currently not used by FreeImage)
		fif = FreeImage_GetFileType(fname.c_str(), 0);

		if (fif == FIF_UNKNOWN) {
			// no signature ?
			// try to guess the file format from the file extension
			fif = FreeImage_GetFIFFromFilename(fname.c_str());
		}

		// check that the plugin has reading capabilities ...
		if ((fif == FIF_UNKNOWN) || (!FreeImage_FIFSupportsReading(fif))) {
			printf(">> ERROR Image: cannot open image: %s\n", fname.c_str());
			return false;
		}

		// Free old image if any
		if (mp_pixels) {
			delete mp_pixels;
			mp_pixels = NULL;
			m_data_size = 0;
		}

		// ok, let's load the file
		dibUnknown = FreeImage_Load(fif, fname.c_str());

		// Convert to 32 bits
		dib32 = FreeImage_ConvertTo32Bits(dibUnknown);
		FreeImage_Unload(dibUnknown);

		// Get info of image
		m_width = FreeImage_GetWidth(dib32);
		m_height = FreeImage_GetHeight(dib32);
		scan_pitch = FreeImage_GetPitch(dib32);
		m_data_size = m_height * m_width * sizeof(pixel_type);

		// Allocate enough space
		mp_pixels = new pixel_type[m_height * m_width];

		// Get data in BRG[A] mode
		FreeImage_ConvertToRawBits((unsigned char *) mp_pixels, dib32, scan_pitch,
				32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

		// Convert to RGB[A]
		size_type pixel_count = m_width * m_height;
		unsigned char tmp_color;
		for (size_type i = 0; i < pixel_count; i++) {
			tmp_color = mp_pixels[i].channels.red;
			mp_pixels[i].channels.red = mp_pixels[i].channels.blue;
			mp_pixels[i].channels.blue = tmp_color;
		}

		// Empty things
		FreeImage_Unload(dib32);

		printf(">> LOAD image: %s\n", fname.c_str());
		return true;
	}

	// Save image to jpeg file
	bool Image::saveImageAsPNG(const std::string & fname) {
		// Assert that we have data
		assert(mp_pixels);

		// Allocate space
		FIBITMAP *bitmap = FreeImage_Allocate(m_width, m_height, 32);

		// Copy image
		for (size_type x = 0; x < m_width; x++)
			for (size_type y = 0; y < m_height; y++) {
				FreeImage_SetPixelColor(bitmap, x, y, (RGBQUAD *) &pixel(x, y));
			}

		// Save image
		bool ret_code = FreeImage_Save(FIF_PNG, bitmap, fname.c_str());

		// Close image
		FreeImage_Unload(bitmap);

		return ret_code;
	}

	bool Image::resizeCanvas(size_type new_width, size_type new_height) {
		// Check for wrong parameters
		if ((new_width == 0) || (new_height == 0))
			return false; // Wrong resizing

		// Check if there is no image
		if (!mp_pixels) {
			m_width = new_width;
			m_height = new_height;
			m_data_size = m_width * m_height * sizeof(pixel_type);
			mp_pixels = new pixel_type[m_width * m_height];
			return true;
		}

		// Allocate new space
		pixel_type * p_newdata = new pixel_type[new_width * new_height];

		// Calculate the movements
		size_type max_width_move = (m_width < new_width) ? m_width : new_width;
		size_type max_height_move = (m_height < new_height) ? m_width : new_height;

		// Do the actual movements
		for (size_type y = 0; y < max_height_move; y++)
			memcpy(p_newdata + (y * new_width), mp_pixels + (y * m_width),
					max_width_move * sizeof(pixel_type));

		// Deallocate old
		delete mp_pixels;

		// Store new values
		m_width = new_width;
		m_height = new_height;
		m_data_size = m_width * m_height * sizeof(pixel_type);
		mp_pixels = p_newdata;
		return true;
	}

	// Shift image on right and pad with a new color
	void Image::shiftRight(size_type pixels) {
		pixel_type * p_row_start;

		// For each row
		for (size_type row = 0; row < m_height; row++) {
			p_row_start = mp_pixels + (row * m_width);
			// Move this row shift_pixels left
			memmove(p_row_start + pixels, p_row_start,
					(m_width - pixels) * sizeof(pixel_type));
		}
	}

	// Shift image on left
	void Image::shiftLeft(size_type pixels) {
		pixel_type * p_row_start;

		// For each row
		for (size_type row = 0; row < m_height; row++) {
			p_row_start = mp_pixels + (row * m_width);
			// Move this row shift_pixels left
			memmove(p_row_start, p_row_start + pixels,
					(m_width - pixels) * sizeof(pixel_type));
		}
	}

	// Slide image toward down direction
	void Image::shiftDown(size_type pixels) {
		// shifting can be done with a memmove
		size_type total_move_bytes = m_data_size
				- (pixels * m_width * sizeof(pixel_type));
		memmove(mp_pixels, mp_pixels + pixels * m_width, total_move_bytes);
	}

	// Slide image toward up direction
	void Image::shiftUp(size_type pixels) {
		// shifting can be done with a memmove
		size_type total_move_bytes = m_data_size
				- (pixels * m_width * sizeof(pixel_type));
		memmove(mp_pixels + pixels * m_width, mp_pixels, total_move_bytes);
	}

	bool Image::blend(const Image & other, Real factor,
			const Vector2 & lower_left) {
		// Check if there is no image
		if (!mp_pixels)
			return false;

		// Check size
		if ((lower_left.x + other.m_width > m_width)
				|| (lower_left.y + other.m_height > m_height))
			return false;

		// Blend pictures
		for (size_type y = 0; y < other.m_height; y++)
			for (size_type x = 0; x < other.m_width; x++) {
				pixel_type & this_pixel = pixel(lower_left.x + x, lower_left.y + y);
				const pixel_type & other_pixel = other.pixel(x, y);
				this_pixel.channels.red += (Real) (((Real) other_pixel.channels.red
						- (Real) this_pixel.channels.red) * factor);

				this_pixel.channels.green +=
						(Real) ((Real) other_pixel.channels.green
								- (Real) this_pixel.channels.green) * factor;

				this_pixel.channels.blue += (Real) ((Real) other_pixel.channels.blue
						- (Real) this_pixel.channels.blue) * factor;

				this_pixel.channels.alpha +=
						(Real) ((Real) other_pixel.channels.alpha
								- (Real) this_pixel.channels.alpha) * factor;
			}

		return true;
	}
}
