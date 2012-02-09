#ifndef O3ENGINE_IMAGE_HPP_INCLUDED
#define O3ENGINE_IMAGE_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./color.hpp"
#include "./vector2.hpp"

namespace o3engine
{
    //! [R5] A class for handling 32bit RGBA images.
    /**
        Class for handling images with 32bit RGBA channels. Images
        can be constructed dynamically or can be loaded from the filesystem.

     @ingroup base_group
     @par Class Characteristics
         Image is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
     */
	class Image
	{
    public:
        //! Definition of type used for measuring size
        typedef unsigned long size_type;
        //! Definition of the pixel type
        typedef color_rgba_t pixel_type;

	protected:
		pixel_type * mp_pixels;     //!< Pointer array of pixels
		size_type m_data_size;      //!< Size of data in bytes
		size_type m_width;          //!< Width of image in pixels
		size_type m_height;         //!< Height of image in pixels

	public:

		//! Construct with no data
		inline Image()
            :mp_pixels(NULL),
            m_data_size(0),
            m_width(0),
            m_height(0)
        {}

        //! Construct an empty image with unknown content
        /**
        @param width The width of image in pixels
        @param height The height of image in pixels
        @remarks This constructor only allocates memory space
            and does not initialize image content, so image
            will be typically random noisy.
        */
        Image(size_type width, size_type height);

		//! Construct an empty image and fill with a background color
		/**
        @param width The width of image in pixels
        @param height The height of image in pixels
        @param back_color The color to use to fill the image with after allocation.
        */
		Image(size_type width, size_type height, const Color & back_color);

		//! Construct by loading an image from file
		/**
        @param fname The file name of file to load the image from.
        */
		Image(const std::string & fname);

		//! Copy constructor
		inline Image(const Image & r)
            :mp_pixels(NULL)
        {   operator=(r);      }

		//! Assignment operator
		Image & operator=(const Image & r);

		//! Destructor
		inline ~Image()
        {   if (mp_pixels)
                delete [] mp_pixels;
        }

        //! @name Access Image attributes
        //! @{

		//! Get data pointer on image pixels
		inline const unsigned char * getDataPtr() const
		{   return (unsigned char *)mp_pixels;    }

		//! Get data size
		inline size_type getDataSize() const
		{   return m_data_size * sizeof(pixel_type); }

		//! Get width in pixels
		inline size_type getWidth() const
		{   return m_width;     }

		//! Get height in pixels
		inline size_type getHeight() const
		{   return m_height;    }

        //! Get width and height in a Vector2 object.
        inline Vector2 getSize() const
        {   return Vector2(m_width, m_height);  }

        //! Get the aspect ratio of image
        inline Real getAspectRatio() const
        {   return (Real)m_width/(Real)m_height;    }

        //! Get reference to a specific pixel (@b no-range-check )
        inline pixel_type & pixel(Vector2 & point)
        {   return pixel((size_type)point.x, (size_type)point.y);   }

        //! Get const reference to a specific pixel (@b no-range-check )
        inline const pixel_type & pixel(Vector2 & point) const
        {   return pixel((size_type)point.x, (size_type)point.y);   }

        //! Get reference to a specific pixel (@b no-range-check )
        inline pixel_type & pixel(size_type x, size_type y)
        {   return *(((pixel_type*)mp_pixels) + y *m_width + x);  }

        //! Get const reference to a specific pixel (@b no-range-check )
        inline const pixel_type & pixel(size_type x, size_type y) const
        {   return *(((pixel_type*)mp_pixels) + y *m_width + x);  }

        //! @}

        //! Check if two images are equal by size
        /**
         If both @b width and @b height of lv are equal by size
         with those of rv it will return true, else it will return false.
         */
        inline bool equalSize(const Image & rv)
        {   if ((getHeight() == rv.getHeight()) && (getWidth() == rv.getWidth()))
            return true;
            return false;
        }

        //! Load image from file
		bool loadImage(const std::string & fname);

        //! Save image to png file
        bool saveImageAsPNG(const std::string & fname);

        //! @name Image maniputalation functions
        //! @{

		//! Blend this picture with another one
		bool blend(const Image & other, Real factor, const Vector2 & lower_left = Vector2::ZERO);

		//! Slide image toward right direction
        void shiftRight(size_type pixels);

        //! Slide image toward left direction
        void shiftLeft(size_type pixels);

        //! Slide image toward down direction
        void shiftDown(size_type pixels);

        //! Slide image toward up direction
        void shiftUp(size_type pixels);

        //! Resize the canvas of the image
        /**
            Resizing the canvas will not scale the content of the image
            but only the canvas of it. If the canvas is enlarged the
            new area will have random pixels, if the canvas is shrinked
            the image will be clipped.
        @return @b True if it resized successfully, @b false in any error.
        */
        bool resizeCanvas(size_type new_width, size_type new_height);

        //! @}
	};
}
#endif
