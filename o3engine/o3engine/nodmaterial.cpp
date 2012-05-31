#include "nodmaterial.hpp"
#include "nodmaterial/builder_tools.hpp"
#include "programmanager.hpp"
#include "pugixml/pugixml.hpp"

namespace o3engine {

	NodMaterial::NodMaterial(const std::string & name) :
		Material(name),
		Node(this, "material", typeid(this).name()){
		addInputSocket<nodmaterial::Socket::ValueType::Vec4>("color", Vector4(0, 0, 0, 1));

		m_nodes["material"] = this;	// Hack to self register our selfs to our-selfs container
	}

	std::string NodMaterial::getStaticCode(ogl::shader_type type) {
		return "";
	}

	std::string NodMaterial::getExecutedCode(ogl::shader_type type) {
		return "";
	}

	std::string NodMaterial::getOutputSocketReference(ogl::shader_type type, const std::string & connector_name) {
		switch(type) {
		case ogl::shader_type::FRAGMENT:
			return "outColor = " + nodmaterial::builder::input_value(type, this, "color") + ";";
		default:
			return "";
		}
	}

	void NodMaterial::preUse() const {
		for(auto & func : m_predraw_functions) {
			func();
		}
	}

	void NodMaterial::buildProgram() {

		// Build GLSL Program, and gather prepare functions
		nodmaterial::ProgramBuilder mat_builder(this);
		mat_builder.build();

		setProgram(ProgramManager::getSingleton()
			.loadProgram("material_" + Material::getName(), mat_builder.getVertexSource(), mat_builder.getFragmentSource()));
		m_predraw_functions = mat_builder.getPreDrawFunctions();
	}

	void import_nodmaterials(const std::string & fname) {

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
				nodmaterial::Node * pnode;
				if (node_type == "geometry") {
					pnode = pmat->createNode<nodmaterial::GeometryNode>(nodeit->attribute("name").value());
				} else if (node_type == "color" ) {
					pnode = pmat->createNode<nodmaterial::ColorNode>(nodeit->attribute("name").value());
				} else if (node_type == "shading") {
					pnode = pmat->createNode<nodmaterial::ShadingNode>(nodeit->attribute("name").value());
				} else if (node_type == "texture") {
					pnode = pmat->createNode<nodmaterial::TextureNode>(
						nodeit->attribute("name").value(),
						nodeit->attribute("texture").value());
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
