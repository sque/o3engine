#ifndef O3ENGINE_RECTANGLE_HPP_INCLUDED
#define O3ENGINE_RECTANGLE_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./vector2.hpp"

namespace o3engine {
	//! [R5] Class representing a rectangle in 2d space
	/**
	 * This class is useful for representing any kind of rectangle in 2d space
	 * It is light and generally fast and contains a number of feature
	 * very useful when working with rectangles.
	 * @par Class Characteristics
	 * Rectangle is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 * @ingroup base_group
	 */
	class Rectangle {
	public:
		//! Lower left point of rectangle
		Vector2 lower_left;

		//! Upper right point of rectangle
		Vector2 upper_right;

		//! Default constructor
		/**
		 * It does @b NOT initialize member values
		 */
		inline Rectangle() {
		}

		//! Construct and initialize from Vector2 points
		/**
		 * @param ll Lower Left point
		 * @param ur Upper Right point
		 */
		inline Rectangle(const Vector2 & ll, const Vector2 & ur) :
				lower_left(ll), upper_right(ur) {
		}

		//! Construct and initialize from an array of 4 Real numbers
		/**
		 @remarks Two first numbers of the array are the lower left corner
		 and the two last numbers are the upper right corner of the array.
		 */
		inline Rectangle(const Real coords[]) :
				lower_left(coords[0], coords[1]), upper_right(coords[2], coords[3]) {
		}

		//! Construct and initialize from an array of 2 Vector2 objects
		/**
		 * @remarks The first Vector2 of the array will be used for the lower left
		 * corner and the second will be used for the upper right corner.
		 */
		inline Rectangle(const Vector2 points[]) :
				lower_left(points[0]), upper_right(points[1]) {
		}

		//! Construct and initialize from 4 Real numbers
		inline Rectangle(Real left, Real bottom, Real right, Real top) :
				lower_left(left, bottom), upper_right(right, top) {
		}

		//! Set values from 2 Vector2 objects
		inline void set(const Vector2 & ll, const Vector2 & ur) {
			lower_left = ll;
			upper_right = ur;
		}

		//! Set values from a C array of 2 Vector2 objects
		/**
		 * @remarks The first Vector2 of the array will be used for the lower left
		 * corner and the second will be used for the upper right corner.
		 */
		inline void set(const Vector2 points[]) {
			lower_left = points[0];
			upper_right = points[1];
		}

		//! Get the height of rectangle
		inline Real getHeight() const {
			return upper_right.y - lower_left.y;
		}

		//! Get the width of rectangle
		inline Real getWidth() const {
			return upper_right.x - lower_left.x;
		}

		//! Get the size of rectangle in a Vector2 object
		inline Vector2 getSize() const {
			return Vector2(getWidth(), getHeight());
		}

		//! Get the center of rectangle
		inline Vector2 getCenter() const {
			return Vector2((upper_right.x + lower_left.x) / 2,
					(upper_right.y + lower_left.y) / 2);
		}

		//! Repair corners of rectangle
		/**
		 * Repairing corners means that it will swap the corners if needed
		 * so that lower_left is really the lower_left and not the upper_right.
		 * @see hasValidCorners()
		 */
		inline void repairCorners() {
			if (lower_left.x > upper_right.x)
				std::swap(lower_left.x, upper_right.x);

			if (lower_left.y > upper_right.y)
				std::swap(lower_left.y, upper_right.y);

		}

		//! @name Math operations
		//! @{

		//! Move rectangle to a relative position
		inline Rectangle & translate(const Vector2 & trans) {
			lower_left += trans;
			upper_right += trans;
			return *this;
		}

		//! Scale rectangle based on a factor
		inline Rectangle & scale(Real factor) {
			lower_left *= factor;
			upper_right *= factor;
			return *this;
		}

		//! Calculate area that the rectangle covers
		inline Real area() const {
			return (upper_right - lower_left).length() * 2.0f;
		}

		//! Calculate a new interpolated rectangle
		inline Rectangle interpolated(const Rectangle & dst, Real factor) const {
			return Rectangle(lower_left.interpolated(dst.lower_left, factor),
					upper_right.interpolated(dst.upper_right, factor));
		}

		//! Check if a point is inside the rectangle
		inline bool containsPoint(const Vector2 & point) const {
			return (upper_right.x >= point.x && upper_right.y >= point.y
					&& lower_left.x <= point.x && lower_left.y <= point.y);
		}

		//! Check if a rectangle is inside this rectangle
		inline bool containsRectangle(const Rectangle & rect) const {
			return (upper_right.x >= rect.upper_right.x
					&& upper_right.y >= rect.upper_right.y
					&& lower_left.x <= rect.lower_left.x
					&& lower_left.y <= rect.lower_left.y);
		}

		//! Resize rectangle (if needed) to fit a specified point
		inline void resizeToFit(const Vector2 & point) {
			if (lower_left.x > point.x)
				lower_left.x = point.x;
			if (lower_left.y > point.y)
				lower_left.y = point.y;
			if (upper_right.x < point.x)
				upper_right.x = point.x;
			if (upper_right.y < point.y)
				upper_right.y = point.y;
		}

		//! Check if corners of rectangle are valid
		/**
		 * Corners are valid when the upper_right corner is
		 * trully in the upper right part of the lower_left corner.
		 @see repairCorners
		 */
		inline bool hasValidCorners() const {
			return (lower_left.x <= upper_right.x && lower_left.y <= upper_right.y);
		}

		//! Self-scale operator
		inline Rectangle & operator*=(Real factor) {
			lower_left *= factor;
			upper_right *= factor;
			return *this;
		}

		//! Scale operator
		inline Rectangle operator*(Real factor) const {
			return Rectangle(lower_left * factor, upper_right * factor);
		}

		//! @}

		//! @name Comparison operators
		//! @{

		inline bool operator==(const Rectangle & r) const {
			return (lower_left == r.lower_left && upper_right == r.upper_right);
		}

		inline bool operator!=(const Rectangle & r) const {
			return !operator==(r);
		}
		//! @}
	};
}

#endif
