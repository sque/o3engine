#ifndef O3ENGINE_SINGLETONMANAGER_HPP_INCLUDED
#define O3ENGINE_SINGLETONMANAGER_HPP_INCLUDED

#include "./prereqs.hpp"
#include <assert.h>
#include <map>

namespace o3engine {
	//! Manager of objects
	/**
	 * @par What is it
	 * A template class for managing any type of object with any type of name.\n
	 * It provides a <b>simple and extensible</b> API and a class interface for objects called ManagedObject.\n
	 * \n
	 * The great advantage is that a ManagedObject register itself at the time of creation and
	 * unregisters from manager at the time of destruction. You can always query for an object based on his
	 * name and get the pointer of it.\n
	 * \n
	 * The manager is also a singleton, which means that can be only one existence of it, and it provides
	 * assertations to alert you from by accident creating multiple objects. Providing a structured singleton
	 * form from the ground-base with the appropriate API unleashes the full power of singleton at derived
	 * classes.\n
	 * \n
	 * <b>The two classes are strictly binded between them and there is no way to use one type of objects with
	 * another type of manager.</b> Although it may be considered a draw-back, it gives us a more clean interface
	 * which is the most important for software developing.
	 *
	 * @par How to declare objects of these classes
	 * It consists of 2 parts. One is the declaration of manager and the other is the declaration of objects.
	 * We must decide the names of both classes and the type of names before declaring them.\n
	 * <i>e.g. We will create PeopleManager and People as an object.</i>
	 * @code
	 * // Declare People
	 * class People : ManagedObject<PeopleManager, string, People>
	 * {
	 * 	// Constructor
	 * 	People(const string & name)
	 * 	:ManagedObject<PeopleManager, string, People>(name) {
	 * 	}
	 *
	 * 	// Add your prefered API here
	 * };
	 *
	 * // Declare PeopleManager
	 * class PeopleManager :public SingletonManager<PeopleManager, string, People>
	 * {
	 * 	// Add your prefered API here
	 * }
	 * @endcode
	 * Finally for the manager to work you <b>must</b> define at its <b>.cpp</b> file the instance
	 * of static variable ms_Singleton. For our case this will be done this way:
	 * @code
	 * template<> PeopleManager* SingletonManager<PeopleManager, string, People>::ms_Singleton = 0;
	 * @endcode
	 *
	 * @par How to use objects
	 * You are now ready to create objects of classes <b>People</b> easily
	 * @code
	 * People * p_Maria = People("Maria");
	 * @endcode
	 * Maria is automatically registered at the <b>PeopleManager</b>, in any other part of your
	 * code without even needed to have <b>PeopleManager</b> pointer you can query for Maria's object.
	 * @code
	 * People * p_AtMaria = PeopleManager::getObjectPtr("Maria");
	 * @endcode
	 * Magic uh? You must have noticed that getObjectPtr() and getObject() are static functions which results
	 * in even more simple and clean code.
	 * */
	template<class T, class N, class O> class SingletonManager {
	public:

		//! Type definition for the type of objects
		typedef O object_type;

		//! Type definition for the type of names
		typedef N name_type;

	protected:
		//! A pointer to the instance of object
		static T* ms_singleton;

		//! List of managed objects
		std::map<name_type, object_type *> m_objects;

		//! Type definition of iterator
		typedef typename std::map<name_type, object_type *>::iterator ObjectIterator;

		//! Event triggered when a new object has been added
		virtual void onObjectAdded(const name_type & _name,
				object_type * _pobject) {
		}

		//! Event triggered when an object has been removed
		virtual void onObjectRemoved(const name_type & _name) {
		}

	public:
		//! Constructor of managed objects
		inline SingletonManager() {
			assert( !ms_singleton);
			ms_singleton = static_cast<T*>(this);
		}

		//! Destrcuctor of Manager
		inline virtual ~SingletonManager(void) {
			assert(ms_singleton);
			ms_singleton = 0;
		}

		//! Get singleton by reference
		inline static T& getSingleton(void) {
			assert( ms_singleton);
			return (*ms_singleton);
		}

		//! Get singleton's pointer
		inline static T* getSingletonPtr(void) {
			return ms_singleton;
		}

		//! Register a new object
		inline static bool registerObject(const name_type & name,
				object_type * pobject) {
			ObjectIterator it;

			if ((it = ms_singleton->m_objects.find(name))
					== ms_singleton->m_objects.end()) {
				ms_singleton->m_objects[name] = pobject;

				// Call event
				ms_singleton->onObjectAdded(name, pobject);
				return true;
			} else
				return false;
		}

		//! Unregister an object
		inline static bool unregisterObject(const name_type & name) {
			ObjectIterator it;

			if ((it = ms_singleton->m_objects.find(name))
					!= ms_singleton->m_objects.end()) {
				ms_singleton->m_objects.erase(it);

				// Call event
				ms_singleton->onObjectRemoved(name);
				return true;
			} else
				return false;
		}

		//! Get a managed object by reference
		inline static object_type & getObject(const name_type & name) {
			ObjectIterator it;

			if ((it = ms_singleton->m_objects.find(name))
					!= ms_singleton->m_objects.end())
				return *it->second;
			assert(0);
		}

		//! Get a managed object's pointer
		inline static object_type * getObjectPtr(const name_type & name) {
			ObjectIterator it;

			if ((it = ms_singleton->m_objects.find(name))
					!= ms_singleton->m_objects.end())
				return it->second;
			return nullptr;
		}
	};

	//! Class for creating managed objects
	/**
	 * For detailed explanation visit SingletonManager <b>details</b>.
	 */
	template<class Manager, class Name, class Object>
	class ManagedObject {
	public:

		//! Type of manager
		typedef Manager manager_type;

		//! Type of name
		typedef Name name_type;

		//! Final derived type of this object
		typedef Object object_type;

		//! Constructor of ManagedObjects always with a name
		inline ManagedObject(const name_type & name) {
			// Save name
			m_name = name;

			// Register object
			assert(manager_type::registerObject(name, (object_type*)this));
		}

		//! Destruct of ManagedObjects
		inline virtual ~ManagedObject() {
			// Unregister before deleting it
			assert(manager_type::unregisterObject(m_name));
		}

		//! Request for the name of object
		inline const name_type & getName() const {
			return m_name;
		}

	private:
		// We hide the name from derived class because it is illegal in logic
		// of this class to change the name
		name_type m_name;
	};
}

#endif
