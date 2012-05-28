#ifndef O3ENGINE_MATERILIZER_COLORNODE_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_COLORNODE_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace materilizer {

	class ColorNode : public Node{
	public:


		ColorNode(const std::string & name, const Color & color) :
			Node(name){
			addOutputConnector("value", Connector::ValueType::Vec4);
		}

		ColorNode(const std::string & name):
			ColorNode(name, Color::BLACK){
		}

		void setColor(const Color & c) {
			m_color = c;
		}

		const Color & getColor() const {
			return m_color;
		}

		virtual std::string getStaticCode(ogl::shader_type type);

		virtual std::string getGeneratedCode(ogl::shader_type type);

		virtual std::string getGeneratedOutputValue(ogl::shader_type type, const std::string & connector_name);

	private:
		Color m_color;
	};
}
}


#endif
