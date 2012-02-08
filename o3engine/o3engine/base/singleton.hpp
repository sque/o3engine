/* Original version Copyright (C) Scott Bilas, 2000.
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Scott Bilas, 2000"
 */
#ifndef O3ENGINE_SINGLETON_HPP_INCLUDED
#define O3ENGINE_SINGLETON_HPP_INCLUDED

#include <assert.h>

namespace o3engine
{
    //! [R5] Implementas all the basic features and security that a singleton must have
	/**
     @par Copyright Scott Bilas, 2000
        Main concept and implementation is work of Scott Bias, this class is
        little changed
        Template class for creating single-instance global classes.
     @ingroup base_group
     @par Class Characteristics
         Singleton is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	*/
	template <typename T> class Singleton
	{
    private:
        Singleton(const Singleton &);
        Singleton & operator=(const Singleton &);

	protected:
		//! A pointer to the instance of object
		static T* ms_singleton;

	public:

        //! General Constructor
		/**
            When an object is created, it checks if the internall
            pointer to NULL otherwise it asserts.
		 */
		inline Singleton( void )
		{
			assert( !ms_singleton );
			ms_singleton = static_cast< T* >( this );
		}

		//! Destructor
		inline virtual ~Singleton( void )
		{
			assert(ms_singleton);
			ms_singleton = 0;
		}

        //! Returns a pointer to the singleton
		/**
            If you want to check if the signleton is allocated check getSingletonPtr() which
            doesn't assert if the object is unallocated.
         @return An object by reference to the single-instance object if it is allocated,
            otherwise it asserts.
		 */
		inline static T& getSingleton( void )
		{
			assert( ms_singleton );
			return ( *ms_singleton );
		}

        //! Returns a pointer to the singleton
		/**
		 @return A pointer to the single-instance object.
		 */
		inline static T* getSingletonPtr( void )
		{return ms_singleton;}
	};
}

#endif
