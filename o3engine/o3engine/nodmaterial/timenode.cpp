#include "timenode.hpp"
#include "builder_tools.hpp"
#include "../platform/platform.hpp"

namespace o3engine {
namespace nodmaterial {

TimeNode::TimeNode(NodeContainer * powner, const std::string & name) :
		UniqueNode(powner, name, typeid(this).name()){

		addOutputSocket<Socket::ValueType::Float>("time");
		addOutputSocket<Socket::ValueType::Vec2>("time_v2");
		addOutputSocket<Socket::ValueType::Vec3>("time_v3");
		addOutputSocket<Socket::ValueType::Vec4>("time_v4");
}

	std::string TimeNode::getStaticCode(ogl::shader_type type) {
		return "uniform float time_secs;\n";
	}

	std::string TimeNode::getExecutedCode(ogl::shader_type type) {
		return "";
	}

	std::string TimeNode::getOutputSocketReference(ogl::shader_type type, const std::string & socket_name) {
		if (socket_name == "time") {
			return "time_secs";
		} else if (socket_name == "time_v2") {
			return "vec2(time_secs, time_secs)";
		} else if (socket_name == "time_v3") {
			return "vec3(time_secs, time_secs, time_secs)";
		} else if (socket_name == "time_v4") {
			return "vec4(time_secs, time_secs, time_secs, time_secs)";
		}
		return "";
	}

	const Node::predraw_function_type TimeNode::getPreDrawFunction() {
		return [](const ogl::program & prog) {
			const_cast<ogl::program &>(prog).get_uniform("time_secs").set1f((double)Platform::getSingleton().getTimer().getMilliseconds() / 1000.0f);
		};
	}

}}
