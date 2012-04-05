#ifndef OGL_UTILS_DEBUG_HPP_INCLUDED
#define OGL_UTILS_DEBUG_HPP_INCLUDED

#include "../base.hpp"
#include "../context.hpp"

namespace ogl {

namespace utils {

	template<class E>
	class bitflags {
	public:

		typedef E opt;

		typedef unsigned base_type;

		bitflags() = default;

		bitflags (E val):
			m_val(val) {
		}

		bitflags(std::initializer_list<E> flags) :
			m_val(E(0)){
			for(auto f : flags) {
				m_val = E((base_type)m_val | (base_type)f);
			}
		}

		base_type get_base() const{
			return (base_type)m_val;
		}

		bitflags operator~() const {
			base_type inter = ~get_base();
			return bitflags((E)inter);
		}

		bitflags operator&(const bitflags & r) const {
			return bitflags(E(get_base() & r.get_base()));
		}

		bitflags operator|(const bitflags & r) const {
			return bitflags(E(get_base() | r.get_base()));
		}

		bool has_flag(E val) const {
			return (base_type(m_val) & base_type(val)) != 0;
		}

		operator E () {
			return m_val;
		}

		static bitflags _and(E lv, E rv) {
			return bitflags(lv) & bitflags(rv);
		}

	protected:
		E m_val;
	};

	enum class info_filter : unsigned{
		NONE = 0,
		LIMITS = 1,
		EXTENSIONS = 2,
		COMPRESSED_FORMATS = 4,
		BINARY_FORMATS = 8,
		ALL = BINARY_FORMATS | COMPRESSED_FORMATS | EXTENSIONS | LIMITS
	};

	//! Get information about a context
	extern std::string info(context & ctx, bitflags<info_filter> filter = info_filter::ALL);
}
}


#endif
