#ifndef OGL_TYPES_HPP_INCLUDED
#define OGL_TYPES_HPP_INCLUDED

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <array>

namespace ogl{

	/*-----------------------------------------------*/
	// Data types
	typedef GLfloat float_type;
	typedef GLint int_type;
	typedef GLint64 int64_type;
	typedef GLuint uint_type;
	typedef GLuint64 uint64_type;
	typedef GLdouble double_type;
	typedef GLhalf half_type;
	typedef GLboolean boolean_type;


	/*-----------------------------------------------*/
	// Enumerations

	//! Variable type
	enum class variable_type: GLenum {
		FLOAT = GL_FLOAT,
		FLOAT_VEC2 = GL_FLOAT_VEC2,
		FLOAT_VEC3 = GL_FLOAT_VEC3,
		FLOAT_VEC4 = GL_FLOAT_VEC4,
		DOUBLE = GL_DOUBLE,
		DOUBLE_VEC2 = GL_DOUBLE_VEC2,
		DOUBLE_VEC3 = GL_DOUBLE_VEC3,
		DOUBLE_VEC4 = GL_DOUBLE_VEC4,
		INT = GL_INT,
		INT_VEC2 = GL_INT_VEC2,
		INT_VEC3 = GL_INT_VEC3,
		INT_VEC4 = GL_INT_VEC4,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		UNSIGNED_INT_VEC2 = GL_UNSIGNED_INT_VEC2,
		UNSIGNED_INT_VEC3 = GL_UNSIGNED_INT_VEC3,
		UNSIGNED_INT_VEC4 = GL_UNSIGNED_INT_VEC4,
		BOOL = GL_BOOL,
		BOOL_VEC2 = GL_BOOL_VEC2,
		BOOL_VEC3 = GL_BOOL_VEC3,
		BOOL_VEC4 = GL_BOOL_VEC4,
		FLOAT_MAT2 = GL_FLOAT_MAT2,
		FLOAT_MAT3 = GL_FLOAT_MAT3,
		FLOAT_MAT4 = GL_FLOAT_MAT4,
		FLOAT_MAT2x3 = GL_FLOAT_MAT2x3,
		FLOAT_MAT2x4 = GL_FLOAT_MAT2x4,
		FLOAT_MAT3x2 = GL_FLOAT_MAT3x2,
		FLOAT_MAT3x4 = GL_FLOAT_MAT3x4,
		FLOAT_MAT4x2 = GL_FLOAT_MAT4x2,
		FLOAT_MAT4x3 = GL_FLOAT_MAT4x3,
		DOUBLE_MAT2 = GL_DOUBLE_MAT2,
		DOUBLE_MAT3 = GL_DOUBLE_MAT3,
		DOUBLE_MAT4 = GL_DOUBLE_MAT4,
		DOUBLE_MAT2x3 = GL_DOUBLE_MAT2x3,
		DOUBLE_MAT2x4 = GL_DOUBLE_MAT2x4,
		DOUBLE_MAT3x2 = GL_DOUBLE_MAT3x2,
		DOUBLE_MAT3x4 = GL_DOUBLE_MAT3x4,
		DOUBLE_MAT4x2 = GL_DOUBLE_MAT4x2,
		DOUBLE_MAT4x3 = GL_DOUBLE_MAT4x3,
		SAMPLER_1D = GL_SAMPLER_1D,
		SAMPLER_2D = GL_SAMPLER_2D,
		SAMPLER_3D = GL_SAMPLER_3D,
		SAMPLER_CUBE = GL_SAMPLER_CUBE,
		SAMPLER_1D_SHADOW = GL_SAMPLER_1D_SHADOW,
		SAMPLER_2D_SHADOW = GL_SAMPLER_2D_SHADOW,
		SAMPLER_1D_ARRAY = GL_SAMPLER_1D_ARRAY,
		SAMPLER_2D_ARRAY = GL_SAMPLER_2D_ARRAY,
		SAMPLER_1D_ARRAY_SHADOW = GL_SAMPLER_1D_ARRAY_SHADOW,
		SAMPLER_2D_ARRAY_SHADOW = GL_SAMPLER_2D_ARRAY_SHADOW,
		SAMPLER_2D_MULTISAMPLE = GL_SAMPLER_2D_MULTISAMPLE,
		SAMPLER_2D_MULTISAMPLE_ARRAY = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
		SAMPLER_CUBE_SHADOW = GL_SAMPLER_CUBE_SHADOW,
		SAMPLER_BUFFER = GL_SAMPLER_BUFFER,
		SAMPLER_2D_RECT = GL_SAMPLER_2D_RECT,
		SAMPLER_2D_RECT_SHADOW = GL_SAMPLER_2D_RECT_SHADOW,
		INT_SAMPLER_1D = GL_INT_SAMPLER_1D,
		INT_SAMPLER_2D = GL_INT_SAMPLER_2D,
		INT_SAMPLER_3D = GL_INT_SAMPLER_3D,
		INT_SAMPLER_CUBE = GL_INT_SAMPLER_CUBE,
		INT_SAMPLER_1D_ARRAY = GL_INT_SAMPLER_1D_ARRAY,
		INT_SAMPLER_2D_ARRAY = GL_INT_SAMPLER_2D_ARRAY,
		INT_SAMPLER_2D_MULTISAMPLE = GL_INT_SAMPLER_2D_MULTISAMPLE,
		INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
		INT_SAMPLER_BUFFER = GL_INT_SAMPLER_BUFFER,
		INT_SAMPLER_2D_RECT = GL_INT_SAMPLER_2D_RECT,
		UNSIGNED_INT_SAMPLER_1D = GL_UNSIGNED_INT_SAMPLER_1D,
		UNSIGNED_INT_SAMPLER_2D = GL_UNSIGNED_INT_SAMPLER_2D,
		UNSIGNED_INT_SAMPLER_3D = GL_UNSIGNED_INT_SAMPLER_3D,
		UNSIGNED_INT_SAMPLER_CUBE = GL_UNSIGNED_INT_SAMPLER_CUBE,
		UNSIGNED_INT_SAMPLER_1D_ARRAY = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
		UNSIGNED_INT_SAMPLER_2D_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
		UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
		UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
		UNSIGNED_INT_SAMPLER_BUFFER = GL_UNSIGNED_INT_SAMPLER_BUFFER,
		UNSIGNED_INT_SAMPLER_2D_RECT = GL_UNSIGNED_INT_SAMPLER_2D_RECT,
		/* TODO: Glew 1.7
		IMAGE_1D = GL_IMAGE_1D,
		IMAGE_2D = GL_IMAGE_2D,
		IMAGE_3D = GL_IMAGE_3D,
		IMAGE_2D_RECT = GL_IMAGE_2D_RECT,
		IMAGE_CUBE = GL_IMAGE_CUBE,
		IMAGE_BUFFER = GL_IMAGE_BUFFER,
		IMAGE_1D_ARRAY = GL_IMAGE_1D_ARRAY,
		IMAGE_2D_ARRAY = GL_IMAGE_2D_ARRAY,
		IMAGE_2D_MULTISAMPLE = GL_IMAGE_2D_MULTISAMPLE,
		IMAGE_2D_MULTISAMPLE_ARRAY = GL_IMAGE_2D_MULTISAMPLE_ARRAY,
		INT_IMAGE_1D = GL_INT_IMAGE_1D,
		INT_IMAGE_2D = GL_INT_IMAGE_2D,
		INT_IMAGE_3D = GL_INT_IMAGE_3D,
		INT_IMAGE_2D_RECT = GL_INT_IMAGE_2D_RECT,
		INT_IMAGE_CUBE = GL_INT_IMAGE_CUBE,
		INT_IMAGE_BUFFER = GL_INT_IMAGE_BUFFER,
		INT_IMAGE_1D_ARRAY = GL_INT_IMAGE_1D_ARRAY,
		INT_IMAGE_2D_ARRAY = GL_INT_IMAGE_2D_ARRAY,
		INT_IMAGE_2D_MULTISAMPLE = GL_INT_IMAGE_2D_MULTISAMPLE,
		INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
		UNSIGNED_INT_IMAGE_1D = GL_UNSIGNED_INT_IMAGE_1D,
		UNSIGNED_INT_IMAGE_2D = GL_UNSIGNED_INT_IMAGE_2D,
		UNSIGNED_INT_IMAGE_3D = GL_UNSIGNED_INT_IMAGE_3D,
		UNSIGNED_INT_IMAGE_2D_RECT = GL_UNSIGNED_INT_IMAGE_2D_RECT,
		UNSIGNED_INT_IMAGE_CUBE = GL_UNSIGNED_INT_IMAGE_CUBE,
		UNSIGNED_INT_IMAGE_BUFFER = GL_UNSIGNED_INT_IMAGE_BUFFER,
		UNSIGNED_INT_IMAGE_1D_ARRAY = GL_UNSIGNED_INT_IMAGE_1D_ARRAY,
		UNSIGNED_INT_IMAGE_2D_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_ARRAY,
		UNSIGNED_INT_IMAGE_2D_MULTISAMPLE = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,
		UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
		UNSIGNED_INT_ATOMIC_COUNTER = GL_UNSIGNED_INT_ATOMIC_COUNTER
		*/
	};

	//! Buffer types
	enum class buffer_type : GLenum {
		ARRAY = GL_ARRAY_BUFFER,
		// TODO: GLEW 1.7 ATOMIC_COUNTER = GL_ATOMIC_COUNTER_BUFFER,
		COPY_READ = GL_COPY_READ_BUFFER,
		COPY_WRITE = GL_COPY_WRITE_BUFFER,
		DRAW_INDIRECT = GL_DRAW_INDIRECT_BUFFER,
		ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
		PIXEL_PACK = GL_PIXEL_PACK_BUFFER,
		PIXEL_UNPACK = GL_PIXEL_UNPACK_BUFFER,
		TEXTURE = GL_TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER,
		UNIFORM = GL_UNIFORM_BUFFER
	};

	//! Frame buffer types
	enum class frame_buffer_target : GLenum {
		DRAW = GL_DRAW_FRAMEBUFFER,
		READ = GL_READ_FRAMEBUFFER,
		ANY = GL_FRAMEBUFFER
	};

	//! Frame buffer status
	enum class frame_buffer_status : GLenum {
		COMPLETE = GL_FRAMEBUFFER_COMPLETE,
		UNDEFINED = GL_FRAMEBUFFER_UNDEFINED,
		INCOMPLETE_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
		INCOMPLETE_MISSING_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
		INCOMPLETE_DRAW_BUFFER = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
		INCOMPLETE_READ_BUFFER = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
		UNSUPPORTED = GL_FRAMEBUFFER_UNSUPPORTED,
		INCOMPLETE_MULTISAMPLE = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
		INCOMPLETE_LAYER_TARGETS = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
	};

	//! Buffer usage pattern
	enum class buffer_usage_pattern : GLenum {
		STREAM_DRAW = GL_STREAM_DRAW,
		STREAM_READ = GL_STREAM_READ,
		STREAM_COPY = GL_STREAM_COPY,
		STATIC_DRAW = GL_STATIC_DRAW,
		STATIC_READ = GL_STATIC_READ,
		STATIC_COPY = GL_STATIC_COPY,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		DYNAMIC_READ = GL_DYNAMIC_READ,
		DYNAMIC_COPY = GL_DYNAMIC_COPY
	};

	//! Buffer access type
	enum class buffer_access_type :GLenum {
		READ_ONLY = GL_READ_ONLY,
		WRITE_ONLY = GL_WRITE_ONLY,
		READ_WRITE = GL_READ_WRITE
	};


	//! Component integral data type
	enum class attribi_data_type : GLenum{
		BYTE = GL_BYTE,
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		SHORT = GL_SHORT,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		INT = GL_INT,
		UNSIGNED_INT = GL_UNSIGNED_INT
	};

	//! Component float data type
	enum class attribf_data_type : GLenum{
		BYTE = GL_BYTE,
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		SHORT = GL_SHORT,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		INT = GL_INT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		HALF_FLOAT = GL_HALF_FLOAT,
		FLOAT = GL_FLOAT,
		DOUBLE = GL_DOUBLE,
		FIXED = GL_FIXED,
		INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
		UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
	};

	//! Map access bit
	enum class map_access_bit : GLbitfield{
		MAP_READ_BIT = GL_MAP_READ_BIT,
		MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
		MAP_INVALIDATE_RANGE_BIT = GL_MAP_INVALIDATE_RANGE_BIT,
		MAP_INVALIDATE_BUFFER_BIT = GL_MAP_INVALIDATE_BUFFER_BIT,
		MAP_FLUSH_EXPLICIT_BIT = GL_MAP_FLUSH_EXPLICIT_BIT,
		MAP_UNSYNCHRONIZED_BIT = GL_MAP_UNSYNCHRONIZED_BIT
	};

	//! Shader types enumeration
	enum class shader_type : GLenum{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION = GL_TESS_EVALUATION_SHADER
	};

	enum class buffer_mode_type : GLenum {
		SEPARATE_ATTRIBS = GL_SEPARATE_ATTRIBS,
		INTERLEAVED_ATTRIBS = GL_INTERLEAVED_ATTRIBS
	};

	//! Texture types
	enum class texture_type : GLenum{
		TEX_1D = GL_TEXTURE_1D,
		TEX_2D = GL_TEXTURE_2D,
		TEX_3D = GL_TEXTURE_3D,
		TEX_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
		TEX_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
		TEX_CUBEMAP = GL_TEXTURE_CUBE_MAP
	};

	//! Minification filter types
	enum class min_filter_type : GLenum{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
	};

	//! Magnification filter types
	enum class mag_filter_type : GLenum{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR,
	};

	enum class compare_mode : GLenum{
		REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE,
		NONE = GL_NONE
	};

	//! Compare functions
	enum class compare_func : GLenum{
		LEQUAL = GL_LEQUAL,
		GEQUAL = GL_GEQUAL,
		LESS = GL_LESS,
		GREATER = GL_GREATER,
		EQUAL = GL_EQUAL,
		NOTEQUAL = GL_NOTEQUAL,
		ALWAYS = GL_ALWAYS,
		NEVER = GL_NEVER
	};

	//! Wrapping type
	enum class wrap_type : GLenum{
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		REPEAT = GL_REPEAT
	};

	//! All available swizzle types
	enum class swizzle_type : GLenum{
		RED = GL_RED,
		GREEN = GL_GREEN,
		BLUE = GL_BLUE,
		ONE = GL_ONE,
		ZERO = GL_ZERO
	};

	//! Draw primitives types
	enum class primitive_type : GLenum {
		POINTS = GL_POINTS,
		LINE_STRIP = GL_LINE_STRIP,
		LINE_LOOP = GL_LINE_LOOP,
		LINES = GL_LINES,
		LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
		LINES_ADJACENCY = GL_LINES_ADJACENCY,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
		PATCHES = GL_PATCHES
	};

	//! Context parameters
	enum class context_param_type : GLenum {
		ACTIVE_TEXTURE = GL_ACTIVE_TEXTURE,
		ALIASED_LINE_WIDTH_RANGE = GL_ALIASED_LINE_WIDTH_RANGE,
		ARRAY_BUFFER_BINDING = GL_ARRAY_BUFFER_BINDING,
		BLEND = GL_BLEND,
		BLEND_COLOR = GL_BLEND_COLOR,
		BLEND_DST = GL_BLEND_DST,
		BLEND_DST_ALPHA = GL_BLEND_DST_ALPHA,
		BLEND_DST_RGB = GL_BLEND_DST_RGB,
		BLEND_EQUATION_RGB = GL_BLEND_EQUATION_RGB,
		BLEND_EQUATION_ALPHA = GL_BLEND_EQUATION_ALPHA,
		BLEND_SRC = GL_BLEND_SRC,
		BLEND_SRC_ALPHA = GL_BLEND_SRC_ALPHA,
		BLEND_SRC_RGB = GL_BLEND_SRC_RGB,
		COLOR_CLEAR_VALUE = GL_COLOR_CLEAR_VALUE,
		COLOR_LOGIC_OP = GL_COLOR_LOGIC_OP,
		COLOR_WRITEMASK = GL_COLOR_WRITEMASK,
		COMPRESSED_TEXTURE_FORMATS = GL_COMPRESSED_TEXTURE_FORMATS,
		CONTEXT_FLAGS = GL_CONTEXT_FLAGS,
		CULL_FACE = GL_CULL_FACE,
		CULL_FACE_MODE = GL_CULL_FACE_MODE,
		CURRENT_PROGRAM = GL_CURRENT_PROGRAM,
		DEPTH_CLEAR_VALUE = GL_DEPTH_CLEAR_VALUE,
		DEPTH_FUNC = GL_DEPTH_FUNC,
		DEPTH_RANGE = GL_DEPTH_RANGE,
		DEPTH_TEST = GL_DEPTH_TEST,
		DEPTH_WRITEMASK = GL_DEPTH_WRITEMASK,
		DITHER = GL_DITHER,
		DOUBLEBUFFER = GL_DOUBLEBUFFER,
		DRAW_BUFFER = GL_DRAW_BUFFER,
		DRAW_BUFFER0 = GL_DRAW_BUFFER0,
		DRAW_BUFFER1 = GL_DRAW_BUFFER1,
		DRAW_BUFFER2 = GL_DRAW_BUFFER2,
		DRAW_BUFFER3 = GL_DRAW_BUFFER3,
		DRAW_BUFFER4 = GL_DRAW_BUFFER4,
		DRAW_BUFFER5 = GL_DRAW_BUFFER5,
		DRAW_BUFFER6 = GL_DRAW_BUFFER6,
		DRAW_BUFFER7 = GL_DRAW_BUFFER7,
		DRAW_BUFFER8 = GL_DRAW_BUFFER8,
		DRAW_BUFFER9 = GL_DRAW_BUFFER9,
		DRAW_BUFFER10 = GL_DRAW_BUFFER10,
		DRAW_BUFFER11 = GL_DRAW_BUFFER11,
		DRAW_BUFFER12 = GL_DRAW_BUFFER12,
		DRAW_BUFFER13 = GL_DRAW_BUFFER13,
		DRAW_BUFFER14 = GL_DRAW_BUFFER14,
		DRAW_BUFFER15 = GL_DRAW_BUFFER15,
		DRAW_FRAMEBUFFER_BINDING = GL_DRAW_FRAMEBUFFER_BINDING,
		READ_FRAMEBUFFER_BINDING = GL_READ_FRAMEBUFFER_BINDING,
		ELEMENT_ARRAY_BUFFER_BINDING = GL_ELEMENT_ARRAY_BUFFER_BINDING,
		FRAGMENT_SHADER_DERIVATIVE_HINT = GL_FRAGMENT_SHADER_DERIVATIVE_HINT,
		FRONT_FACE = GL_FRONT_FACE,
		IMPLEMENTATION_COLOR_READ_FORMAT = GL_IMPLEMENTATION_COLOR_READ_FORMAT,
		IMPLEMENTATION_COLOR_READ_TYPE = GL_IMPLEMENTATION_COLOR_READ_TYPE,
		LINE_SMOOTH = GL_LINE_SMOOTH,
		LINE_SMOOTH_HINT = GL_LINE_SMOOTH_HINT,
		LINE_WIDTH = GL_LINE_WIDTH,
		LAYER_PROVOKING_VERTEX = GL_LAYER_PROVOKING_VERTEX,
		LINE_WIDTH_GRANULARITY = GL_LINE_WIDTH_GRANULARITY,
		LINE_WIDTH_RANGE = GL_LINE_WIDTH_RANGE,
		LOGIC_OP_MODE = GL_LOGIC_OP_MODE,
		MAJOR_VERSION = GL_MAJOR_VERSION,
		MAX_3D_TEXTURE_SIZE = GL_MAX_3D_TEXTURE_SIZE,
		MAX_ARRAY_TEXTURE_LAYERS = GL_MAX_ARRAY_TEXTURE_LAYERS,
		MAX_CLIP_DISTANCES = GL_MAX_CLIP_DISTANCES,
		MAX_COLOR_TEXTURE_SAMPLES = GL_MAX_COLOR_TEXTURE_SAMPLES,
		//TODO: GLEW 1.7 MAX_COMBINED_ATOMIC_COUNTERS = GL_MAX_COMBINED_ATOMIC_COUNTERS,
		MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,
		MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS = GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,
		MAX_COMBINED_TEXTURE_IMAGE_UNITS = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		MAX_COMBINED_UNIFORM_BLOCKS = GL_MAX_COMBINED_UNIFORM_BLOCKS,
		MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,
		MAX_CUBE_MAP_TEXTURE_SIZE = GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		MAX_DEPTH_TEXTURE_SAMPLES = GL_MAX_DEPTH_TEXTURE_SAMPLES,
		MAX_DRAW_BUFFERS = GL_MAX_DRAW_BUFFERS,
		//TODO: GLEW 1.7 MAX_DUALSOURCE_DRAW_BUFFERS = GL_MAX_DUALSOURCE_DRAW_BUFFERS,
		MAX_ELEMENTS_INDICES = GL_MAX_ELEMENTS_INDICES,
		MAX_ELEMENTS_VERTICES = GL_MAX_ELEMENTS_VERTICES,
		//TODO: GLEW 1.7 MAX_FRAGMENT_ATOMIC_COUNTERS = GL_MAX_FRAGMENT_ATOMIC_COUNTERS,
		MAX_FRAGMENT_INPUT_COMPONENTS = GL_MAX_FRAGMENT_INPUT_COMPONENTS,
		MAX_FRAGMENT_UNIFORM_COMPONENTS = GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		MAX_FRAGMENT_UNIFORM_VECTORS = GL_MAX_FRAGMENT_UNIFORM_VECTORS,
		MAX_FRAGMENT_UNIFORM_BLOCKS = GL_MAX_FRAGMENT_UNIFORM_BLOCKS,
		//TODO: GLEW 1.7  MAX_GEOMETRY_ATOMIC_COUNTERS = GL_MAX_GEOMETRY_ATOMIC_COUNTERS,
		MAX_GEOMETRY_INPUT_COMPONENTS = GL_MAX_GEOMETRY_INPUT_COMPONENTS,
		MAX_GEOMETRY_OUTPUT_COMPONENTS = GL_MAX_GEOMETRY_OUTPUT_COMPONENTS,
		MAX_GEOMETRY_TEXTURE_IMAGE_UNITS = GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS,
		MAX_GEOMETRY_UNIFORM_BLOCKS = GL_MAX_GEOMETRY_UNIFORM_BLOCKS,
		MAX_GEOMETRY_UNIFORM_COMPONENTS = GL_MAX_GEOMETRY_UNIFORM_COMPONENTS,
		MAX_INTEGER_SAMPLES = GL_MAX_INTEGER_SAMPLES,
		//TODO: GLEW 1.7  MIN_MAP_BUFFER_ALIGNMENT = GL_MIN_MAP_BUFFER_ALIGNMENT,
		MAX_PROGRAM_TEXEL_OFFSET = GL_MAX_PROGRAM_TEXEL_OFFSET,
		MIN_PROGRAM_TEXEL_OFFSET = GL_MIN_PROGRAM_TEXEL_OFFSET,
		MAX_RECTANGLE_TEXTURE_SIZE = GL_MAX_RECTANGLE_TEXTURE_SIZE,
		MAX_RENDERBUFFER_SIZE = GL_MAX_RENDERBUFFER_SIZE,
		MAX_SAMPLE_MASK_WORDS = GL_MAX_SAMPLE_MASK_WORDS,
		MAX_SERVER_WAIT_TIMEOUT = GL_MAX_SERVER_WAIT_TIMEOUT,
		//TODO: GLEW 1.7 MAX_TESS_CONTROL_ATOMIC_COUNTERS = GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS,
		//TODO: GLEW 1.7 MAX_TESS_EVALUATION_ATOMIC_COUNTERS= GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS,
		MAX_TEXTURE_BUFFER_SIZE = GL_MAX_TEXTURE_BUFFER_SIZE,
		MAX_TEXTURE_IMAGE_UNITS = GL_MAX_TEXTURE_IMAGE_UNITS,
		MAX_TEXTURE_LOD_BIAS = GL_MAX_TEXTURE_LOD_BIAS,
		MAX_TEXTURE_SIZE = GL_MAX_TEXTURE_SIZE,
		MAX_UNIFORM_BUFFER_BINDINGS = GL_MAX_UNIFORM_BUFFER_BINDINGS,
		MAX_UNIFORM_BLOCK_SIZE = GL_MAX_UNIFORM_BLOCK_SIZE,
		MAX_VARYING_COMPONENTS = GL_MAX_VARYING_COMPONENTS,
		MAX_VARYING_VECTORS = GL_MAX_VARYING_VECTORS,
		MAX_VARYING_FLOATS = GL_MAX_VARYING_FLOATS,
		//TODO: GLEW 1.7 MAX_VERTEX_ATOMIC_COUNTERS = GL_MAX_VERTEX_ATOMIC_COUNTERS,
		MAX_VERTEX_ATTRIBS = GL_MAX_VERTEX_ATTRIBS,
		MAX_VERTEX_TEXTURE_IMAGE_UNITS = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		MAX_VERTEX_UNIFORM_COMPONENTS = GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		MAX_VERTEX_UNIFORM_VECTORS = GL_MAX_VERTEX_UNIFORM_VECTORS,
		MAX_VERTEX_OUTPUT_COMPONENTS = GL_MAX_VERTEX_OUTPUT_COMPONENTS,
		MAX_VERTEX_UNIFORM_BLOCKS = GL_MAX_VERTEX_UNIFORM_BLOCKS,
		MAX_VIEWPORT_DIMS = GL_MAX_VIEWPORT_DIMS,
		MAX_VIEWPORTS = GL_MAX_VIEWPORTS,
		MINOR_VERSION = GL_MINOR_VERSION,
		NUM_COMPRESSED_TEXTURE_FORMATS = GL_NUM_COMPRESSED_TEXTURE_FORMATS,
		NUM_EXTENSIONS = GL_NUM_EXTENSIONS,
		NUM_PROGRAM_BINARY_FORMATS = GL_NUM_PROGRAM_BINARY_FORMATS,
		NUM_SHADER_BINARY_FORMATS = GL_NUM_SHADER_BINARY_FORMATS,
		PACK_ALIGNMENT = GL_PACK_ALIGNMENT,
		PACK_IMAGE_HEIGHT = GL_PACK_IMAGE_HEIGHT,
		PACK_LSB_FIRST = GL_PACK_LSB_FIRST,
		PACK_ROW_LENGTH = GL_PACK_ROW_LENGTH,
		PACK_SKIP_IMAGES = GL_PACK_SKIP_IMAGES,
		PACK_SKIP_PIXELS = GL_PACK_SKIP_PIXELS,
		PACK_SKIP_ROWS = GL_PACK_SKIP_ROWS,
		PACK_SWAP_BYTES = GL_PACK_SWAP_BYTES,
		PIXEL_PACK_BUFFER_BINDING = GL_PIXEL_PACK_BUFFER_BINDING,
		PIXEL_UNPACK_BUFFER_BINDING = GL_PIXEL_UNPACK_BUFFER_BINDING,
		POINT_FADE_THRESHOLD_SIZE = GL_POINT_FADE_THRESHOLD_SIZE,
		PRIMITIVE_RESTART_INDEX = GL_PRIMITIVE_RESTART_INDEX,
		PROGRAM_BINARY_FORMATS = GL_PROGRAM_BINARY_FORMATS,
		PROGRAM_PIPELINE_BINDING = GL_PROGRAM_PIPELINE_BINDING,
		PROVOKING_VERTEX = GL_PROVOKING_VERTEX,
		POINT_SIZE = GL_POINT_SIZE,
		POINT_SIZE_GRANULARITY = GL_POINT_SIZE_GRANULARITY,
		POINT_SIZE_RANGE = GL_POINT_SIZE_RANGE,
		POLYGON_OFFSET_FACTOR = GL_POLYGON_OFFSET_FACTOR,
		POLYGON_OFFSET_UNITS = GL_POLYGON_OFFSET_UNITS,
		POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL,
		POLYGON_OFFSET_LINE = GL_POLYGON_OFFSET_LINE,
		POLYGON_OFFSET_POINT = GL_POLYGON_OFFSET_POINT,
		POLYGON_SMOOTH = GL_POLYGON_SMOOTH,
		POLYGON_SMOOTH_HINT = GL_POLYGON_SMOOTH_HINT,
		READ_BUFFER = GL_READ_BUFFER,
		RENDERBUFFER_BINDING = GL_RENDERBUFFER_BINDING,
		SAMPLE_BUFFERS = GL_SAMPLE_BUFFERS,
		SAMPLE_COVERAGE_VALUE = GL_SAMPLE_COVERAGE_VALUE,
		SAMPLE_COVERAGE_INVERT = GL_SAMPLE_COVERAGE_INVERT,
		SAMPLER_BINDING = GL_SAMPLER_BINDING,
		SAMPLES = GL_SAMPLES,
		SCISSOR_BOX = GL_SCISSOR_BOX,
		SCISSOR_TEST = GL_SCISSOR_TEST,
		SHADER_COMPILER = GL_SHADER_COMPILER,
		SMOOTH_LINE_WIDTH_RANGE = GL_SMOOTH_LINE_WIDTH_RANGE,
		SMOOTH_LINE_WIDTH_GRANULARITY = GL_SMOOTH_LINE_WIDTH_GRANULARITY,
		STENCIL_BACK_FAIL = GL_STENCIL_BACK_FAIL,
		STENCIL_BACK_FUNC = GL_STENCIL_BACK_FUNC,
		STENCIL_BACK_PASS_DEPTH_FAIL = GL_STENCIL_BACK_PASS_DEPTH_FAIL,
		STENCIL_BACK_PASS_DEPTH_PASS = GL_STENCIL_BACK_PASS_DEPTH_PASS,
		STENCIL_BACK_REF = GL_STENCIL_BACK_REF,
		STENCIL_BACK_VALUE_MASK = GL_STENCIL_BACK_VALUE_MASK,
		STENCIL_BACK_WRITEMASK = GL_STENCIL_BACK_WRITEMASK,
		STENCIL_CLEAR_VALUE = GL_STENCIL_CLEAR_VALUE,
		STENCIL_FAIL = GL_STENCIL_FAIL,
		STENCIL_FUNC = GL_STENCIL_FUNC,
		STENCIL_PASS_DEPTH_FAIL = GL_STENCIL_PASS_DEPTH_FAIL,
		STENCIL_PASS_DEPTH_PASS = GL_STENCIL_PASS_DEPTH_PASS,
		STENCIL_REF = GL_STENCIL_REF,
		STENCIL_TEST = GL_STENCIL_TEST,
		STENCIL_VALUE_MASK = GL_STENCIL_VALUE_MASK,
		STENCIL_WRITEMASK = GL_STENCIL_WRITEMASK,
		STEREO = GL_STEREO,
		SUBPIXEL_BITS = GL_SUBPIXEL_BITS,
		TEXTURE_BINDING_1D = GL_TEXTURE_BINDING_1D,
		TEXTURE_BINDING_1D_ARRAY = GL_TEXTURE_BINDING_1D_ARRAY,
		TEXTURE_BINDING_2D = GL_TEXTURE_BINDING_2D,
		TEXTURE_BINDING_2D_ARRAY = GL_TEXTURE_BINDING_2D_ARRAY,
		TEXTURE_BINDING_2D_MULTISAMPLE = GL_TEXTURE_BINDING_2D_MULTISAMPLE,
		TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY,
		TEXTURE_BINDING_3D = GL_TEXTURE_BINDING_3D,
		TEXTURE_BINDING_BUFFER = GL_TEXTURE_BINDING_BUFFER,
		TEXTURE_BINDING_CUBE_MAP = GL_TEXTURE_BINDING_CUBE_MAP,
		TEXTURE_BINDING_RECTANGLE = GL_TEXTURE_BINDING_RECTANGLE,
		TEXTURE_COMPRESSION_HINT = GL_TEXTURE_COMPRESSION_HINT,
		//TODO: GLEW 1.7 TEXTURE_BUFFER_BINDING = GL_TEXTURE_BUFFER_BINDING,
		TIMESTAMP = GL_TIMESTAMP,
		TRANSFORM_FEEDBACK_BUFFER_BINDING = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING,
		TRANSFORM_FEEDBACK_BUFFER_START = GL_TRANSFORM_FEEDBACK_BUFFER_START,
		TRANSFORM_FEEDBACK_BUFFER_SIZE = GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
		UNIFORM_BUFFER_BINDING = GL_UNIFORM_BUFFER_BINDING,
		UNIFORM_BUFFER_OFFSET_ALIGNMENT = GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
		UNIFORM_BUFFER_SIZE = GL_UNIFORM_BUFFER_SIZE,
		UNIFORM_BUFFER_START = GL_UNIFORM_BUFFER_START,
		UNPACK_ALIGNMENT = GL_UNPACK_ALIGNMENT,
		UNPACK_IMAGE_HEIGHT = GL_UNPACK_IMAGE_HEIGHT,
		UNPACK_LSB_FIRST = GL_UNPACK_LSB_FIRST,
		UNPACK_ROW_LENGTH = GL_UNPACK_ROW_LENGTH,
		UNPACK_SKIP_IMAGES = GL_UNPACK_SKIP_IMAGES,
		UNPACK_SKIP_PIXELS = GL_UNPACK_SKIP_PIXELS,
		UNPACK_SKIP_ROWS = GL_UNPACK_SKIP_ROWS,
		UNPACK_SWAP_BYTES = GL_UNPACK_SWAP_BYTES,
		VERTEX_PROGRAM_POINT_SIZE = GL_VERTEX_PROGRAM_POINT_SIZE,
		VIEWPORT = GL_VIEWPORT,
		VIEWPORT_BOUNDS_RANGE = GL_VIEWPORT_BOUNDS_RANGE,
		VIEWPORT_INDEX_PROVOKING_VERTEX = GL_VIEWPORT_INDEX_PROVOKING_VERTEX,
		VIEWPORT_SUBPIXEL_BITS = GL_VIEWPORT_SUBPIXEL_BITS
	};

	enum class image_base_format: GLenum {
		DEPTH_COMPONENT= GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL,
		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,
	};

	enum class image_sized_format: GLenum {
		R8 = GL_R8,
		R8_SNORM = GL_R8_SNORM,
		R16 = GL_R16,
		R16_SNORM = GL_R16_SNORM,
		RG8 = GL_RG8,
		RG8_SNORM = GL_RG8_SNORM,
		RG16 = GL_RG16,
		RG16_SNORM = GL_RG16_SNORM,
		R3_G3_B2 = GL_R3_G3_B2,
		RGB4 = GL_RGB4,
		RGB5 = GL_RGB5,
		RGB8 = GL_RGB8,
		RGB8_SNORM = GL_RGB8_SNORM,
		RGB10 = GL_RGB10,
		RGB12 = GL_RGB12,
		RGB16_SNORM = GL_RGB16_SNORM,
		RGBA2 = GL_RGBA2,
		RGBA4 = GL_RGBA4,
		RGB5_A1 = GL_RGB5_A1,
		RGBA8 = GL_RGBA8,
		RGBA8_SNORM = GL_RGBA8_SNORM,
		RGB10_A2 = GL_RGB10_A2,
		RGB10_A2UI = GL_RGB10_A2UI,
		RGBA12 = GL_RGBA12,
		RGBA16 = GL_RGBA16,
		SRGB8 = GL_SRGB8,
		SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
		R16F = GL_R16F,
		RG16F = GL_RG16F,
		RGB16F = GL_RGB16F,
		RGBA16F = GL_RGBA16F,
		R32F = GL_R32F,
		RG32F = GL_RG32F,
		RGB32F = GL_RGB32F,
		RGBA32F = GL_RGBA32F,
		R11F_G11F_B10F = GL_R11F_G11F_B10F,
		RGB9_E5 = GL_RGB9_E5,
		R8I = GL_R8I,
		R8UI = GL_R8UI,
		R16I = GL_R16I,
		R16UI = GL_R16UI,
		R32I = GL_R32I,
		R32UI = GL_R32UI,
		RG8I = GL_RG8I,
		RG8UI = GL_RG8UI,
		RG16I = GL_RG16I,
		RG16UI = GL_RG16UI,
		RG32I = GL_RG32I,
		RG32UI = GL_RG32UI,
		RGB8I = GL_RGB8I,
		RGB8UI = GL_RGB8UI,
		RGB16I = GL_RGB16I,
		RGB16UI = GL_RGB16UI,
		RGB32I = GL_RGB32I,
		RGB32UI = GL_RGB32UI,
		RGBA8I = GL_RGBA8I,
		RGBA8UI = GL_RGBA8UI,
		RGBA16I = GL_RGBA16I,
		RGBA16UI = GL_RGBA16UI,
		RGBA32I = GL_RGBA32I,
		RGBA32UI = GL_RGBA32UI
	};

	enum class image_compressed_format: GLenum {
		COMPRESSED_RED = GL_COMPRESSED_RED,
		COMPRESSED_RG = GL_COMPRESSED_RG,
		COMPRESSED_RGB = GL_COMPRESSED_RGB,
		COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
		COMPRESSED_SRGB = GL_COMPRESSED_SRGB,
		COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA,
		COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1,
		COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
		COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2,
		COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
/*TODO: GLEW 1.7		COMPRESSED_RGBA_BPTC_UNORM = GL_COMPRESSED_RGBA_BPTC_UNORM,
		COMPRESSED_SRGB_ALPHA_BPTC_UNORM = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
		COMPRESSED_RGB_BPTC_SIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
		COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,*/
	};

	enum class image_format: GLenum {
		DEPTH_COMPONENT= GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL,
		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		R8 = GL_R8,
		R8_SNORM = GL_R8_SNORM,
		R16 = GL_R16,
		R16_SNORM = GL_R16_SNORM,
		RG8 = GL_RG8,
		RG8_SNORM = GL_RG8_SNORM,
		RG16 = GL_RG16,
		RG16_SNORM = GL_RG16_SNORM,
		R3_G3_B2 = GL_R3_G3_B2,
		RGB4 = GL_RGB4,
		RGB5 = GL_RGB5,
		RGB8 = GL_RGB8,
		RGB8_SNORM = GL_RGB8_SNORM,
		RGB10 = GL_RGB10,
		RGB12 = GL_RGB12,
		RGB16_SNORM = GL_RGB16_SNORM,
		RGBA2 = GL_RGBA2,
		RGBA4 = GL_RGBA4,
		RGB5_A1 = GL_RGB5_A1,
		RGBA8 = GL_RGBA8,
		RGBA8_SNORM = GL_RGBA8_SNORM,
		RGB10_A2 = GL_RGB10_A2,
		RGB10_A2UI = GL_RGB10_A2UI,
		RGBA12 = GL_RGBA12,
		RGBA16 = GL_RGBA16,
		SRGB8 = GL_SRGB8,
		SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
		R16F = GL_R16F,
		RG16F = GL_RG16F,
		RGB16F = GL_RGB16F,
		RGBA16F = GL_RGBA16F,
		R32F = GL_R32F,
		RG32F = GL_RG32F,
		RGB32F = GL_RGB32F,
		RGBA32F = GL_RGBA32F,
		R11F_G11F_B10F = GL_R11F_G11F_B10F,
		RGB9_E5 = GL_RGB9_E5,
		R8I = GL_R8I,
		R8UI = GL_R8UI,
		R16I = GL_R16I,
		R16UI = GL_R16UI,
		R32I = GL_R32I,
		R32UI = GL_R32UI,
		RG8I = GL_RG8I,
		RG8UI = GL_RG8UI,
		RG16I = GL_RG16I,
		RG16UI = GL_RG16UI,
		RG32I = GL_RG32I,
		RG32UI = GL_RG32UI,
		RGB8I = GL_RGB8I,
		RGB8UI = GL_RGB8UI,
		RGB16I = GL_RGB16I,
		RGB16UI = GL_RGB16UI,
		RGB32I = GL_RGB32I,
		RGB32UI = GL_RGB32UI,
		RGBA8I = GL_RGBA8I,
		RGBA8UI = GL_RGBA8UI,
		RGBA16I = GL_RGBA16I,
		RGBA16UI = GL_RGBA16UI,
		RGBA32I = GL_RGBA32I,
		RGBA32UI = GL_RGBA32UI,
		COMPRESSED_RED = GL_COMPRESSED_RED,
		COMPRESSED_RG = GL_COMPRESSED_RG,
		COMPRESSED_RGB = GL_COMPRESSED_RGB,
		COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
		COMPRESSED_SRGB = GL_COMPRESSED_SRGB,
		COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA,
		COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1,
		COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
		COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2,
		COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
/*TODO GLEW 1.7		COMPRESSED_RGBA_BPTC_UNORM = GL_COMPRESSED_RGBA_BPTC_UNORM,
		COMPRESSED_SRGB_ALPHA_BPTC_UNORM = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
		COMPRESSED_RGB_BPTC_SIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
		COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,*/
	};

	enum class image_rendable_format: GLenum {
		DEPTH_COMPONENT= GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL,
		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		R8 = GL_R8,
		R8_SNORM = GL_R8_SNORM,
		R16 = GL_R16,
		R16_SNORM = GL_R16_SNORM,
		RG8 = GL_RG8,
		RG8_SNORM = GL_RG8_SNORM,
		RG16 = GL_RG16,
		RG16_SNORM = GL_RG16_SNORM,
		R3_G3_B2 = GL_R3_G3_B2,
		RGB4 = GL_RGB4,
		RGB5 = GL_RGB5,
		RGB8 = GL_RGB8,
		RGB8_SNORM = GL_RGB8_SNORM,
		RGB10 = GL_RGB10,
		RGB12 = GL_RGB12,
		RGB16_SNORM = GL_RGB16_SNORM,
		RGBA2 = GL_RGBA2,
		RGBA4 = GL_RGBA4,
		RGB5_A1 = GL_RGB5_A1,
		RGBA8 = GL_RGBA8,
		RGBA8_SNORM = GL_RGBA8_SNORM,
		RGB10_A2 = GL_RGB10_A2,
		RGB10_A2UI = GL_RGB10_A2UI,
		RGBA12 = GL_RGBA12,
		RGBA16 = GL_RGBA16,
		SRGB8 = GL_SRGB8,
		SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
		R16F = GL_R16F,
		RG16F = GL_RG16F,
		RGB16F = GL_RGB16F,
		RGBA16F = GL_RGBA16F,
		R32F = GL_R32F,
		RG32F = GL_RG32F,
		RGB32F = GL_RGB32F,
		RGBA32F = GL_RGBA32F,
		R11F_G11F_B10F = GL_R11F_G11F_B10F,
		RGB9_E5 = GL_RGB9_E5,
		R8I = GL_R8I,
		R8UI = GL_R8UI,
		R16I = GL_R16I,
		R16UI = GL_R16UI,
		R32I = GL_R32I,
		R32UI = GL_R32UI,
		RG8I = GL_RG8I,
		RG8UI = GL_RG8UI,
		RG16I = GL_RG16I,
		RG16UI = GL_RG16UI,
		RG32I = GL_RG32I,
		RG32UI = GL_RG32UI,
		RGB8I = GL_RGB8I,
		RGB8UI = GL_RGB8UI,
		RGB16I = GL_RGB16I,
		RGB16UI = GL_RGB16UI,
		RGB32I = GL_RGB32I,
		RGB32UI = GL_RGB32UI,
		RGBA8I = GL_RGBA8I,
		RGBA8UI = GL_RGBA8UI,
		RGBA16I = GL_RGBA16I,
		RGBA16UI = GL_RGBA16UI,
		RGBA32I = GL_RGBA32I,
		RGBA32UI = GL_RGBA32UI
	};

	enum class frame_buffer_attachment :GLenum{
		DEPTH = GL_DEPTH_ATTACHMENT,
		STENCIL = GL_STENCIL_ATTACHMENT,
// TODO GLEW 1.7		DEPTH_STENCIL= GL_DEPTH_STENCIL_ATTACHMMENT,
		COLOR0 = GL_COLOR_ATTACHMENT0,
		COLOR1 = GL_COLOR_ATTACHMENT1,
		COLOR2 = GL_COLOR_ATTACHMENT2,
		COLOR3 = GL_COLOR_ATTACHMENT3,
		COLOR4 = GL_COLOR_ATTACHMENT4,
		COLOR5 = GL_COLOR_ATTACHMENT5,
		COLOR6 = GL_COLOR_ATTACHMENT6,
		COLOR7 = GL_COLOR_ATTACHMENT7,
		COLOR8 = GL_COLOR_ATTACHMENT8,
		COLOR9 = GL_COLOR_ATTACHMENT9,
		COLOR10 = GL_COLOR_ATTACHMENT10,
		COLOR11 = GL_COLOR_ATTACHMENT11,
		COLOR12 = GL_COLOR_ATTACHMENT12,
		COLOR13 = GL_COLOR_ATTACHMENT13,
		COLOR14 = GL_COLOR_ATTACHMENT14,
		COLOR15 = GL_COLOR_ATTACHMENT15,
	};

	enum class elements_type : GLenum {
		UNSIGNED_INT = GL_UNSIGNED_INT,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE
	};

	enum class tex2d_update_target : GLenum {
		TEX_2D = GL_TEXTURE_2D,
		PROXY_TEX_2D = GL_PROXY_TEXTURE_2D,
		TEX_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
		PROXY_TEX_1D_ARRAY = GL_PROXY_TEXTURE_1D_ARRAY,
		TEX_RECTANGLE = GL_TEXTURE_RECTANGLE,
		PROXY_TEX_RECTANGLE = GL_PROXY_TEXTURE_RECTANGLE,
		TEX_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		TEX_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		TEX_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		TEX_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		TEX_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		TEX_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		PROXY_TEX_CUBE_MAP = GL_PROXY_TEXTURE_CUBE_MAP
	};

	enum class pixel_format : GLenum {
		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		BGR = GL_BGR,
		RGBA = GL_RGBA,
		BGRA = GL_BGRA
	};

	enum class tex_pixel_type : GLenum {
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		BYTE = GL_BYTE,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		SHORT = GL_SHORT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		INT = GL_INT,
		FLOAT = GL_FLOAT,
		UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
		UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
		UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
		UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
		UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
		UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
		UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
		UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
		UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
		UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
		UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
		UNSIGNED_INT_2_10_10_10_REV
	};

	enum class pixel_data_format: GLenum {
		STENCIL_INDEX = GL_STENCIL_INDEX,
		DEPTH_COMPONENT= GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL,
		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,
	};

	enum class fbo_pixel_type : GLenum {
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		BYTE = GL_BYTE,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		SHORT = GL_SHORT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		INT = GL_INT,
		HALF_FLOAT = GL_HALF_FLOAT,
		FLOAT = GL_FLOAT,
		UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
		UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
		UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
		UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
		UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
		UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
		UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
		UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
		UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
		UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
		UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
		UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
		UNSIGNED_INT_24_8 = GL_UNSIGNED_INT_24_8,
		UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV,
		UNSIGNED_INT_5_9_9_9_REV = GL_UNSIGNED_INT_5_9_9_9_REV,
		FLOAT_32_UNSIGNED_INT_24_8_REV = GL_FLOAT_32_UNSIGNED_INT_24_8_REV
		};

	enum class logic_op : GLenum {
		CLEAR  = GL_CLEAR,
		SET = GL_SET,
		COPY = GL_COPY,
		COPY_INVERTED = GL_COPY_INVERTED,
		NOOP = GL_NOOP,
		INVERT = GL_INVERT,
		AND = GL_AND,
		NAND = GL_NAND,
		OR = GL_OR,
		NOR = GL_NOR,
		XOR = GL_XOR,
		EQUIV = GL_EQUIV,
		AND_REVERSE = GL_AND_REVERSE,
		AND_INVERTED = GL_AND_INVERTED,
		OR_REVERSE = GL_OR_REVERSE,
		OR_INVERTED = GL_OR_INVERTED
	};

	enum class blend_factor : GLenum {
		ZERO = GL_ZERO,
		ONE = GL_ONE,
		SRC_COLOR = GL_SRC_COLOR,
		ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
		DST_COLOR = GL_DST_COLOR,
		ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
		SRC_ALPHA = GL_SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
		DST_ALPHA = GL_DST_ALPHA,
		ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
		CONSTANT_COLOR = GL_CONSTANT_COLOR,
		ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
		CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
		ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA
	};

	enum class blend_equation : GLenum {
		FUNC_ADD = GL_FUNC_ADD,
		FUNC_SUBTRACT = GL_FUNC_SUBTRACT,
		FUNC_REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT,
		MIN = GL_MIN,
		MAX = GL_MAX
	};

	enum class stencil_op : GLenum {
		KEEP = GL_KEEP,
		ZERO = GL_ZERO,
		REPLACE = GL_REPLACE,
		INCR = GL_INCR,
		INCR_WRAP = GL_INCR_WRAP,
		DECR = GL_DECR,
		DECR_WRAP = GL_DECR_WRAP,
		INVERT = GL_INVERT
	};

	enum class face_type : GLenum {
		FRONT = GL_FRONT,
		BACK = GL_BACK,
		FRONT_AND_BACK = GL_FRONT_AND_BACK
	};

	enum class face_orientation : GLenum {
		CLOCKWISE = GL_CW,
		COUNTER_CLOCKWISE = GL_CCW
	};
}

#endif
