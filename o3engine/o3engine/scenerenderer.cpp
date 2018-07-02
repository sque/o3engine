#include "scenerenderer.hpp"
#include "camera.hpp"
#include "genericnode.hpp"
#include "genericscene.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdint>
#include <memory>

namespace o3engine {

std::shared_ptr<float> to_floatv(const Matrix4 &m) {
	std::shared_ptr<float> fv(new float[16]);
	for(size_t i = 0; i < 16;i++) {
		(fv.get())[i] = (&m[0][0])[i];
	}
	return fv;
}

void set_dmat4_to_mat4(ogl::uniform & u, const Matrix4 &m) {
	float fv[16];
	for(size_t i = 0; i < 16;i++) {
		fv[i] = (&m[0][0])[i];
	}
	u.setmat4f(fv, false);
}

template<class To, class From, bool Transpose = false>
struct convert_impl_mat4{
	static void op(To & dst, const From & src) {
		dst[0][0] = src[0][0];
		dst[0][1] = src[0][1];
		dst[0][2] = src[0][2];
		dst[0][3] = src[0][3];
		dst[1][0] = src[1][0];
		dst[1][1] = src[1][1];
		dst[1][2] = src[1][2];
		dst[1][3] = src[1][3];
		dst[2][0] = src[2][0];
		dst[2][1] = src[2][1];
		dst[2][2] = src[2][2];
		dst[2][3] = src[2][3];
		dst[3][0] = src[3][0];
		dst[3][1] = src[3][1];
		dst[3][2] = src[3][2];
		dst[3][3] = src[3][3];
	}
};

template<class To, class From>
struct convert_impl_mat4<To, From, true>{
	static void op(To & dst, const From & src) {
		dst[0][0] = src[0][0];
		dst[1][0] = src[0][1];
		dst[2][0] = src[0][2];
		dst[3][0] = src[0][3];
		dst[0][1] = src[1][0];
		dst[1][1] = src[1][1];
		dst[2][1] = src[1][2];
		dst[3][1] = src[1][3];
		dst[0][2] = src[2][0];
		dst[1][2] = src[2][1];
		dst[2][2] = src[2][2];
		dst[3][2] = src[2][3];
		dst[0][3] = src[3][0];
		dst[1][3] = src[3][1];
		dst[2][3] = src[3][2];
		dst[3][3] = src[3][3];
	}
};

template<bool Transpose = false, class To, class From>
void convert_mat4(To & dst, From & src) {
	convert_impl_mat4<To, From, Transpose>::op(dst, src);
}

glm::vec4 toVec4(const Color & c) {
	return glm::vec4(c.red, c.green, c.blue, c.alpha);
}

glm::vec3 toVec3(const Vector3 & v) {
	return glm::vec3(v.x, v.y, v.z);
}

//! Double buffer for perfomance
struct DoubleUniformBufferObject {

	DoubleUniformBufferObject(size_t buff_size, ogl::buffer_usage_pattern pattern) {
		mp_buffer[0] = new ogl::buffer(ogl::buffer_type::UNIFORM);
		mp_buffer[0]->define_data(buff_size, NULL, pattern);
		mp_buffer[1] = new ogl::buffer(ogl::buffer_type::UNIFORM);
		mp_buffer[1]->define_data(buff_size, NULL, pattern);
		mp_active_index = 0;
	}

	~DoubleUniformBufferObject() {
		delete mp_buffer[0];
		delete mp_buffer[1];
	}

	//! Get current buffer
	ogl::buffer * getActive() {
		return mp_buffer[mp_active_index];
	}

	//! Swap buffers
	void swap() {
		mp_active_index = ! mp_active_index;
	}

private:
	//! Index to active uniform buffer object
	std::uint8_t mp_active_index;

	//! Repository of active buffers
	ogl::buffer * mp_buffer[2];
};

//! Implementation of SceneRenderVisitor
struct SceneRendererDrawVisitor:
	public SceneRendererVisitor {

	struct UniformSceneParameters {
		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionViewMatrix;
		glm::vec4 CameraPositionWs;
	} m_ubd_sceneparams;

	struct UniformLight{
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::vec3 position;
		float __pad1;
		glm::vec3 direction;
		float __pad2;
		float spot_cutoff;
		std::uint32_t type;
		glm::vec2 __pad3;

		void setByNode(GenericNode & node) {
			const Light & light = node.getLight();
			ambient = toVec4(light.getAmbient());
			diffuse = toVec4(light.getDiffuse());
			specular = toVec4(light.getSpecular());
			position = toVec3(node.getGlobalPosition());
			direction = toVec3(Vector3::NEGATIVE_UNIT_Z * node.getGlobalOrientation().conjugate());
			spot_cutoff = light.getSpotCutOffAngle();
			type = static_cast<std::uint32_t>(light.getType());
		}
	};
	struct UniformSceneLights {
		uint32_t TotalLights;
		glm::vec3 __pad1;
		UniformLight Lights[10];
	} m_ubd_lights;

	//! Pointer to owner scene renderer
	SceneRenderer * mp_renderer;

	//! Pointer to the object's node
	GenericNode * mp_object_node;

	//! Uniform buffer object for scene parameters
	DoubleUniformBufferObject m_ubo_scene;

	//! Uniform buffer object for lights
	DoubleUniformBufferObject m_ubo_light;

	//! Index of active UBO
	std::uint8_t m_active_ubo;

	SceneRendererDrawVisitor(SceneRenderer * prenderer):
		mp_renderer(prenderer),
		m_ubo_scene(sizeof(UniformSceneParameters), ogl::buffer_usage_pattern::STREAM_READ),
		m_ubo_light(sizeof(UniformSceneLights), ogl::buffer_usage_pattern::STREAM_READ),
		m_active_ubo(0){
	}

	~SceneRendererDrawVisitor() {
	}

	void setSceneUniforms() {
		convert_mat4<true>(m_ubd_sceneparams.ProjectionMatrix, mp_renderer->getCameraPtr()->getProjectionMatrix());
		Matrix4 view_matrix = mp_renderer->getCameraPtr()->getSceneNode()->getGlobalTransformation();
				view_matrix = view_matrix.inverse();
		convert_mat4(m_ubd_sceneparams.ViewMatrix, view_matrix);
		Matrix4 proj_view_matrix = view_matrix * mp_renderer->getCameraPtr()->getSceneNode()->getGlobalTransformation();
		convert_mat4<true>(m_ubd_sceneparams.ProjectionViewMatrix, proj_view_matrix);
		Vector3 cam_pos_ws = mp_renderer->getCameraPtr()->getSceneNode()->getGlobalPosition();
		m_ubd_sceneparams.CameraPositionWs = glm::vec4(cam_pos_ws.x,cam_pos_ws.y, cam_pos_ws.z, 1);
		m_ubo_scene.getActive()->update_subdata(0, sizeof(UniformSceneParameters), &m_ubd_sceneparams);
		m_ubo_scene.getActive()->bind_at_point(0);
		m_ubo_scene.swap();

		m_ubd_lights.TotalLights = mp_renderer->getScenePtr()->getLightNodes().size();
		for(std::uint8_t i = 0;i < m_ubd_lights.TotalLights;i++) {
			m_ubd_lights.Lights[i].setByNode(*mp_renderer->getScenePtr()->getLightNodes()[i]);
		}
		m_ubo_light.getActive()->update_subdata(0, sizeof(UniformSceneLights), &m_ubd_lights);
		m_ubo_light.getActive()->bind_at_point(1);
		m_ubo_light.swap();
	}

	//! Populate programs parameters with uniform values
	virtual void preDraw(ogl::program * pprog){
		set_dmat4_to_mat4(pprog->get_uniform("ModelMatrix"), mp_object_node->getGlobalTransformation());
	}
};

//! Implementation of SceneRenderer Node Visitor
struct SceneRendererNodeVisitor {
	SceneRenderer * mp_renderer;
	SceneRendererDrawVisitor  m_render_visitor;


	SceneRendererNodeVisitor(SceneRenderer * prenderer):
		m_render_visitor(prenderer){
		mp_renderer = prenderer;
	}

	void visitNode(GenericNode * pnode) {
	}

	void visitObject(GenericNode * pnode, DrawableObject * pobject) {
		m_render_visitor.mp_object_node = pnode;
		pobject->draw(&m_render_visitor);
	}

};

SceneRenderer::SceneRenderer(Camera * pcamera):
	mp_scene_node_visitor(new SceneRendererNodeVisitor(this)){
	setCamera(pcamera);
}

SceneRenderer::~SceneRenderer() {
	if (mp_scene_node_visitor)
		delete mp_scene_node_visitor;
}

void SceneRenderer::setCamera(Camera * pcamera) {
	mp_camera = pcamera;
	if (!mp_camera->getSceneNode())
		throw std::runtime_error("Cannot render from a detached camera.");
	mp_scene = dynamic_cast<GenericScene *>(mp_camera->getSceneNode()->getMySceneManager());
	mp_scene_node_visitor->m_render_visitor.setSceneUniforms();
}

void SceneRenderer::render() {
	mp_scene->nextLoopCounterToBeChangedUglyFunction();
	mp_scene_node_visitor->m_render_visitor.setSceneUniforms();
	mp_scene->navigateActiveObjects(*mp_scene_node_visitor);
	renderNext();	//! Continue render line
}
}
