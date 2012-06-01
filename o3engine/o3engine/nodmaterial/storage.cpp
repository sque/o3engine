#include "./storage.hpp"
#include "../pugixml/pugixml.hpp"
#include "../materialmanager.hpp"
#include "../nodmaterial.hpp"
#include <boost/regex.hpp>

namespace o3engine {
namespace nodmaterial {

	void unpack_param(const std::string & s, Color & dst) {
		static const boost::regex rx("^color\\(([\\d\\.]+),([\\d\\.]+),([\\d\\.]+),([\\d\\.]+)\\)$");
		boost::smatch results;
		if (!boost::regex_match(s, results, rx) ) {
			throw std::runtime_error("Error unpacking node parameter of type Color \"" + s + "\"");
		}
		dst.red = boost::lexical_cast<Color::channel_type>(results.str(1));
		dst.green = boost::lexical_cast<Color::channel_type>(results.str(2));
		dst.blue = boost::lexical_cast<Color::channel_type>(results.str(3));
		dst.alpha = boost::lexical_cast<Color::channel_type>(results.str(4));
	}

	void unpack_param(const std::string & s, Vector4 & dst) {
		static const boost::regex rx("^vec4\\(([\\d\\.]+),([\\d\\.]+),([\\d\\.]+),([\\d\\.]+)\\)$");
		boost::smatch results;
		if (!boost::regex_match(s, results, rx) ) {
			throw std::runtime_error("Error unpacking node parameter of type vec4 \"" + s + "\"");
		}
		dst.x = boost::lexical_cast<Color::channel_type>(results.str(1));
		dst.y = boost::lexical_cast<Color::channel_type>(results.str(2));
		dst.z = boost::lexical_cast<Color::channel_type>(results.str(3));
		dst.w = boost::lexical_cast<Color::channel_type>(results.str(4));
	}

	void unpack_param(const std::string & s, Vector3 & dst) {
		static const boost::regex rx("^vec3\\(([\\d\\.]+),([\\d\\.]+),([\\d\\.]+)\\)$");
		boost::smatch results;
		if (!boost::regex_match(s, results, rx) ) {
			throw std::runtime_error("Error unpacking node parameter of type vec3 \"" + s + "\"");
		}
		dst.x = boost::lexical_cast<Color::channel_type>(results.str(1));
		dst.y = boost::lexical_cast<Color::channel_type>(results.str(2));
		dst.z = boost::lexical_cast<Color::channel_type>(results.str(3));
	}

	void unpack_param(const std::string & s, Vector2 & dst) {
		static const boost::regex rx("^vec2\\(([\\d\\.]+),([\\d\\.]+)\\)$");
		boost::smatch results;
		if (!boost::regex_match(s, results, rx) ) {
			throw std::runtime_error("Error unpacking node parameter of type vec2 \"" + s + "\"");
		}
		dst.x = boost::lexical_cast<Color::channel_type>(results.str(1));
		dst.y = boost::lexical_cast<Color::channel_type>(results.str(2));
	}

	void import_xml(const std::string & fname) {

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(fname.c_str());

		if (result.status != pugi::status_ok) {
			throw std::runtime_error("Error loading materials from file \"" + fname + "\". " + result.description());
		}
		pugi::xml_node root = doc.root().first_child();
		if (std::string(root.name())  != "nodmaterials") {
			throw std::runtime_error("Error loading materials from file \"" + fname + "\". This is not a nodmaterials xml file.");
		}

		// Load all texture nodes
		pugi::xml_node texnodes = root.child("textures");
		for (pugi::xml_node_iterator texit = texnodes.begin(); texit != texnodes.end(); ++texit) {
			Texture * ptexture = new Texture(texit->attribute("name").value(), ogl::texture_type::TEX_2D);
			ptexture->uploadImage(Image(texit->attribute("filename").value()), true);
		}

		pugi::xml_node materials = root.child("materials");
		if (std::string(root.name())  != "nodmaterials") {
			return;	// No material to load
		}

		// Loop around all materials
		for (pugi::xml_node_iterator matit = materials.begin(); matit != materials.end(); ++matit) {

			// Verify unique material name
			std::string material_name = matit->attribute("name").value();
			if (MaterialManager::getSingleton().getObjectPtr(material_name) != nullptr) {
				throw  std::runtime_error("Error loading materials from file \"" + fname + "\". "
						"There is already material loaded with name \"" + material_name + "\".");
			}
			NodMaterial * pmat = new NodMaterial(material_name);

			// Load all material nodes
			pugi::xml_node matnodes = matit->child("nodes");
			for (pugi::xml_node_iterator nodeit = matnodes.begin(); nodeit != matnodes.end(); ++nodeit) {
				std::string node_type = std::string(nodeit->attribute("type").value());
				parameters_map_type params;
				for(pugi::xml_attribute_iterator ait = nodeit->attributes_begin();ait!= nodeit->attributes_end();ait++) {
					params[ait->name()] = ait->value();
				}

				if (node_type == "geometry") {
					pmat->createNode<GeometryNode>(nodeit->attribute("name").value());
				} else if (node_type == "color" ) {
					ColorNode * pnode = pmat->createNode<ColorNode>(nodeit->attribute("name").value());
					parameters_serialization<ColorNode>::unpack(params, *pnode);
				} else if (node_type == "shading") {
					ShadingNode * pnode = pmat->createNode<ShadingNode>(nodeit->attribute("name").value());
					parameters_serialization<ShadingNode>::unpack(params, *pnode);
				} else if (node_type == "texture") {
					TextureNode * pnode = pmat->createNode<TextureNode>(
						nodeit->attribute("name").value(),
						nodeit->attribute("texture").value());
					parameters_serialization<TextureNode>::unpack(params, *pnode);
				} else if (node_type == "time") {
					pmat->createNode<nodmaterial::TimeNode>(
						nodeit->attribute("name").value());
				} else {
					throw std::runtime_error("Error loading materials from file \"" + fname + "\". "
						"Unknown node type \"" + node_type + "\".");
				}
			}

			// Load all material node links
			pugi::xml_node matlinks = matit->child("links");
			for (pugi::xml_node_iterator linkit = matlinks.begin(); linkit != matlinks.end(); ++linkit) {
				std::string from_node_name = std::string(linkit->attribute("from_node").value());
				std::string to_node_name = std::string(linkit->attribute("to_node").value());
				std::string from_socket_name = std::string(linkit->attribute("from_socket").value());
				std::string to_socket_name = std::string(linkit->attribute("to_socket").value());
				nodmaterial::Node * from_node = pmat->getNodePtr(from_node_name);
				nodmaterial::Node * to_node = pmat->getNodePtr(to_node_name);
				if (!from_node) {
					throw std::runtime_error("Error loading materials from file \"" + fname + "\". "
						"Link references to unknown node \"" + from_node_name + "\".");
				}
				if (!to_node) {
					throw std::runtime_error("Error loading materials from file \"" + fname + "\". "
						"Link references to unknown node \"" + to_node_name + "\".");
				}

				if (!from_node->hasOutputSocket(from_socket_name)) {
					throw std::runtime_error("Error loading materials from file \"" + fname + "\". "
						"There is no output socket with name \"" + from_socket_name + "\".");
				}

				if (!to_node->hasInputSocket(to_socket_name)) {
					throw std::runtime_error("Error loading materials from file \"" + fname + "\". "
						"There is no input socket with name \"" + from_socket_name + "\".");
				}
				to_node->getInputSocket(to_socket_name)->connectTo(from_node->getOutputSocket(from_socket_name));

			}

			// Build material
			pmat->buildProgram();
		}
	}
}
}
