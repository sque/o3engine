#ifndef O3ENGINE_NODMATERIAL_STORAGE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_STORAGE_HPP_INCLUDED

#include "constantvaluenode.hpp"
#include "texturenode.hpp"
#include "mathnode.hpp"
#include "geometrynode.hpp"
#include "shadingnode.hpp"
#include "../texturemanager.hpp"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

namespace o3engine {
namespace nodmaterial {


	template <class Type>
	std::string pack_param(const Type & r) {
		return boost::lexical_cast<std::string>("%1%");
	}

	inline std::string pack_param(const Vector2 & r) {
		return (boost::format("vec2(%1%,%2%)") % r.x % r.y).str();
	}

	inline std::string pack_param(const Vector3 & r) {
		return (boost::format("vec3(%1%,%2%,%3%)") % r.x % r.y % r.z).str();
	}

	inline std::string pack_param(const Vector4 & r) {
		return (boost::format("vec4(%1%,%2%,%3%,%4%)") % r.x % r.y % r.z % r.w).str();
	}

	inline std::string pack_param(const Color & r) {
		return (boost::format("color(%1%,%2%,%3%,%4%)") % r.red % r.green % r.blue % r.alpha).str();
	}

	template <class Type>
	void unpack_param(const std::string & s, Type & dst) {
		dst = boost::lexical_cast<Type>(s);
	}

	void unpack_param(const std::string & s, Color & dst);

	void unpack_param(const std::string & s, Vector4 & dst);

	void unpack_param(const std::string & s, Vector3 & dst);

	void unpack_param(const std::string & s, Vector2 & dst);

	//! Pack/Unpack parameters functor that returns a map of strings
	template<class NodeType>
	struct parameters_serialization;

	//! Parameters map
	typedef std::map<std::string, std::string> parameters_map_type;

	//! TextureNode implementation
	template< >
	struct parameters_serialization<TextureNode> {

		static parameters_map_type pack(const TextureNode & texnode) {
			parameters_map_type param_map;
			param_map["texture"] = pack_param(texnode.getTexture());
			return param_map;
		}

		static void unpack(const parameters_map_type & params_map, TextureNode & dst ) {
			TextureManager::getSingleton().getObjectPtr(params_map.at("texture"));
		}
	};

	//! ShadingNode implementation
	template< >
	struct parameters_serialization<ShadingNode> {

		typedef ShadingNode node_type;

		static parameters_map_type pack(const node_type & texnode) {
			parameters_map_type param_map;
			return param_map;
		}

		static void unpack(const parameters_map_type & params_map, node_type & dst ) {

		}
	};

	//! Constant value implementation
	template< class Type, Socket::ValueType SocketValueType, const Type & DefaultValue >
	struct parameters_serialization< ConstantValueNode<Type, SocketValueType, DefaultValue> > {

		typedef ConstantValueNode<Type, SocketValueType, DefaultValue> node_type;

		static parameters_map_type pack(const node_type & texnode) {
			parameters_map_type param_map;
			param_map["value"] = pack_param(texnode.getValue());
			return param_map;
		}

		static void unpack(const parameters_map_type & params_map, node_type & dst ) {
			typename node_type::value_type value;
			unpack_param(params_map.at("value"), value);
			dst.setValue(value);
		}
	};


	void import_xml(const std::string & fname);

}}


#endif
