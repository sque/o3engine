#include "./materialmanager.hpp"
#include "./string_functions.hpp"
#include "./texturemanager.hpp"
#include "./programmanager.hpp"

using namespace std;

namespace o3engine {
	Real _parse_value(const string & var) {
		float tm;
		sscanf(var.c_str(), " %f ", &tm);
		return tm;
	}

	Color _parse_color3(const string & r, const string & g,
			const string & b) {
		Real cr, cg, cb;
		cr = _parse_value(r);
		cg = _parse_value(g);
		cb = _parse_value(b);
		//printf("Parsing color \"%s %s %s\" to %f, %f, %f\n", r.c_str(), g.c_str(), b.c_str(), cr, cg, cb);
		return Color(cr, cg, cb);
	}

	Color _parse_color4(const string & r, const string & g,
			const string & b, const string & a) {
		Real cr, cg, cb, ca;
		cr = _parse_value(r);
		cg = _parse_value(g);
		cb = _parse_value(b);
		ca = _parse_value(a);
		//printf("Parsing color \"%s %s %s %s\" to %f, %f, %f, %f\n", r.c_str(), g.c_str(), b.c_str(), a.c_str(), cr, cg, cb, ca);
		return Color(cr, cg, cb, ca);
	}

	//- SingletonManager Initialization
	template<> MaterialManager* SingletonManager<MaterialManager, string, Material>::ms_singleton = nullptr;

	// Constructor
	MaterialManager::MaterialManager() :
		mp_default_material(nullptr){
	}

	// Destructor
	MaterialManager::~MaterialManager() {
	}

	void MaterialManager::initialize() {
		ProgramManager::getSingleton().loadProgram("default", "default.vert", "default.frag");
		mp_default_material = new Material("default");
	}

	// Parse a materials file and load everything
	bool MaterialManager::loadMaterials(const string & fname) {
		/*FILE * fin;
		std::string line_str;
		Material * pMat = NULL;
		Color tmpColor;
		TextureManager * p_tex_manager = TextureManager::getSingletonPtr();
		Texture * p_text; // Texture

		vector<string> tmp_tokens;
		vector<string>::iterator it_tok;

		printf(">> LOAD Materials: from file \"%s\"\n", fname.c_str());
		if (NULL == (fin = fopen(fname.c_str(), "rt"))) {
			printf("  >> ERROR: cannot open materials file \"%s\"\n",
					fname.c_str());
			return false;
		}

		// Read a line
		line_str = fgetline(fin);
		while (!line_str.empty()) {
			// Tokenize
			tmp_tokens = tokenize_string(trim_white_space(line_str), " ");
			if (tmp_tokens.size() == 0) {
				line_str = fgetline(fin);
				continue;
			}

			else if (tmp_tokens[0] == "material") {
				// Create a new material to work on it
				pMat = new Material(tmp_tokens[1]);
				printf("  >> LOAD material: \"%s\"\n", tmp_tokens[1].c_str());
			}
			// Abort 2nd pass on textures
			else if (pMat->hasTexture()) {
				line_str = fgetline(fin);
				continue;
			} else if (tmp_tokens[0] == "ambient") {
				tmpColor = _parse_color4(tmp_tokens[1], tmp_tokens[2],
						tmp_tokens[3], tmp_tokens[4]);
				pMat->setAmbient(tmpColor);
			} else if (tmp_tokens[0] == "diffuse") {
				tmpColor = _parse_color4(tmp_tokens[1], tmp_tokens[2],
						tmp_tokens[3], tmp_tokens[4]);
				pMat->setDiffuse(tmpColor);
				pMat->setBasicColor(tmpColor);
			} else if (tmp_tokens[0] == "emissive") {
				tmpColor = _parse_color4(tmp_tokens[1], tmp_tokens[2],
						tmp_tokens[3], tmp_tokens[4]);
				pMat->setEmissive(tmpColor);
			} else if (tmp_tokens[0] == "specular") {
				tmpColor = _parse_color4(tmp_tokens[1], tmp_tokens[2],
						tmp_tokens[3], tmp_tokens[4]);
				pMat->setSpecular(tmpColor);
				pMat->setShininess(_parse_value(tmp_tokens[5]));
			} else if (tmp_tokens[0] == "depth_write") {
				if (tmp_tokens[1] == "off")
					pMat->disableDepthWrite();
			} else if (tmp_tokens[0] == "lighting") {
				if (tmp_tokens[1] == "off")
					pMat->disableLightingEffects();
			} else if (tmp_tokens[0] == "texture") {
				// Attach texture
				if (NULL == (p_text = p_tex_manager->getObjectPtr(tmp_tokens[1]))) {
					printf("  >> LOAD texture: \"%s\"\n", tmp_tokens[1].c_str());
					p_text = new Texture(tmp_tokens[1], tmp_tokens[1]);
				}

				pMat->attachTexture(p_text);
			}
			// Read new line
			line_str = fgetline(fin);
		}

		// Close file and exit
		fclose(fin);
		return true;*/
		return false;
	}
}
