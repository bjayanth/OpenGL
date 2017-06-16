#pragma once

// Windows
#include <windows.h>
#include <Shlwapi.h>

// Standard
#include <exception>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>

// OpenGL
#include "GL/gl3w.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "glm/glm.hpp"
#include "glm/gtx/simd_mat4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SOIL.h"

// Assimp
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

// Local
#include "RTTI.h"
#include "ServiceContainer.h"
#include "GameException.h"
#include "ColorHelper.h"
#include "VectorHelper.h"
#include "MatrixHelper.h"
#include "Utility.h"
#include "Game.h"
#include "GameClock.h"
#include "GameTime.h"
#include "Camera.h"
#include "FirstPersonCamera.h"
#include "Model.h"
#include "Mesh.h"
#include "ModelMaterial.h"
#include "Variable.h"
#include "ShaderProgram.h"
#include "BasicEffect.h"
#include "SkyboxEffect.h"
#include "GameComponent.h"
#include "DrawableGameComponent.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "VertexDeclarations.h"
#include "Grid.h"
#include "ProxyModel.h"
#include "Skybox.h"

namespace Library
{
	extern ServiceContainer GlobalServices;
}