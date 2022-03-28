#include "lab_m1/tema2/tema2.h"
#include "lab_m1/tema2/object2D_temaa.h"
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <chrono>
#include <time.h> 
#include "stb/stb_image.h"
#include <lab_m1/tema2/transform2D.h>

using namespace std;
using namespace m1;



Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

void Tema2::Init()
{
	const string textureLoc = "src/lab_m1/tema2/textures/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "g.jpg").c_str(), GL_REPEAT);
		mapTextures["ground"] = texture;

	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "b.png").c_str(), GL_REPEAT);
		mapTextures["b"] = texture;

	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "w.jpg").c_str(), GL_REPEAT);
		mapTextures["sky"] = texture;
	}

	{
		Texture2D* texture2 = new Texture2D();
		texture2->Load2D((textureLoc + "Jinx.png").c_str(), GL_REPEAT);
		mapTextures["Jinx"] = texture2;
	}

	{
		Texture2D* texture3 = new Texture2D();
		texture3->Load2D((textureLoc + "J.png").c_str(), GL_REPEAT);
		mapTextures["J"] = texture3;
	}
	{
		Texture2D* texture3 = new Texture2D();
		texture3->Load2D((textureLoc + "u.png").c_str(), GL_REPEAT);
		mapTextures["u"] = texture3;
	}

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("plane");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh2 = new Mesh("Jinx");
		mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "Jinx.obj");
		meshes[mesh2->GetMeshID()] = mesh2;
	}

	{
		Mesh* mesh = new Mesh("A");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "J.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("u");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "u.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	LoadAnimationMesh();

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("LabShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("D");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShaderD.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShaderD.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("PapuciShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShaderPapuci.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("HaineShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShaderHaine.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("PieleShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShaderPiele.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("TextureShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShaderG.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShaderG.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader2 = new Shader("TextureShader2");
		shader2->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShaderT.glsl"), GL_VERTEX_SHADER);
		shader2->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShaderT.glsl"), GL_FRAGMENT_SHADER);
		shader2->CreateAndLink();
		shaders[shader2->GetName()] = shader2;
	}
	{
		floorPosition = glm::vec3(24.5f, 0, 24.50f);
		skyPosition = glm::vec3(24.5f, 15.0f, 24.5f);
		wallPosition2 = glm::vec3(54.5f, 0, 24.50f); // stanga
		wallPosition3 = glm::vec3(-5.5f, 0, 24.50f); //dreapta
		wallPosition4 = glm::vec3(24.5f, 0, 54.5f); //fata
		wallPosition1 = glm::vec3(24.5f, 0, -5.5f); //spate
	}


	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; j++)
		{
			out[i][j] = 0;
		}

	}

	copy = idk;
	idx = idxx;
	DrawMaze();

	cameraa = glm::vec3(p.x, p.y + 3.5, p.z);
	camera = new implemented::CameraT(cameraa);
	cameraaAux = glm::vec3(0, 1.8, 0.5);
	camera->Set(cameraa + cameraaAux, cameraa, glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.02f, 100.0f);
	camera->RotateThirdPerson_OY(RADIANS(270));
	camera->RotateThirdPerson_OX(RADIANS(30));
	renderCameraTarget = false;
	p.angle = 0;

	std::string texturePath = PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "cube");
	std::string shaderPath = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders");

	{
		Mesh* mesh = new Mesh("cube");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
		mesh->UseMaterials(false);
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader* shader = new Shader("CubeMap");
		shader->AddShader(PATH_JOIN(shaderPath, "VertexShaderPic.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(shaderPath, "FragmentShaderPic.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderNormal");
		shader->AddShader(PATH_JOIN(shaderPath, "Normal.VS.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(shaderPath, "Normal.FS.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	cubeMapTextureID = UploadCubeMapTexture(
		PATH_JOIN(texturePath, "posx.jpg"),
		PATH_JOIN(texturePath, "posy.jpg"),
		PATH_JOIN(texturePath, "posz.jpg"),
		PATH_JOIN(texturePath, "negx.jpg"),
		PATH_JOIN(texturePath, "negy.jpg"),
		PATH_JOIN(texturePath, "negz.jpg"));


	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	Mesh* healthb_score = object2D_temaa::CreateRectangle("health_s", glm::vec3(0, 0, 0), 60.0f, 60.2f, glm::vec3(0.36f, 0.65f, 0.49f), true);
	AddMeshToList(healthb_score);
	Mesh* healthb_min = object2D_temaa::CreateRectangle("health_m", glm::vec3(0, 0, 0), 60.0f, 60.2f, glm::vec3(0.36f, 0.65f, 0.49f), false);
	AddMeshToList(healthb_min);
	Mesh* time_score = object2D_temaa::CreateRectangle("time_s", glm::vec3(0, 0, 0), 60.0f, 60.2f, glm::vec3(0.96f, 1.0f, 0.65f), true);
	AddMeshToList(time_score);
	Mesh* time_min = object2D_temaa::CreateRectangle("time_m", glm::vec3(0, 0, 0), 60.0f, 60.2f, glm::vec3(0.96f, 1.0f, 0.65f), false);
	AddMeshToList(time_min);

	textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

	textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 28);

	textRenderer2 = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

	textRenderer2->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 60);

	textRenderer3 = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

	textRenderer3->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 28);

	textRenderer4 = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

	textRenderer4->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 28);


}

unsigned int Tema2::UploadCubeMapTexture(const std::string& pos_x, const std::string& pos_y, const std::string& pos_z, const std::string& neg_x, const std::string& neg_y, const std::string& neg_z)
{
	int width, height, chn;

	unsigned char* data_pos_x = stbi_load(pos_x.c_str(), &width, &height, &chn, 0);
	unsigned char* data_pos_y = stbi_load(pos_y.c_str(), &width, &height, &chn, 0);
	unsigned char* data_pos_z = stbi_load(pos_z.c_str(), &width, &height, &chn, 0);
	unsigned char* data_neg_x = stbi_load(neg_x.c_str(), &width, &height, &chn, 0);
	unsigned char* data_neg_y = stbi_load(neg_y.c_str(), &width, &height, &chn, 0);
	unsigned char* data_neg_z = stbi_load(neg_z.c_str(), &width, &height, &chn, 0);

	unsigned int textureID = 0;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (GLEW_EXT_texture_filter_anisotropic) {
		float maxAnisotropy;

		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_pos_x);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_pos_y);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_pos_z);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_neg_x);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_neg_y);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_neg_z);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	if (GetOpenGLError() == GL_INVALID_OPERATION)
	{
		cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
	}

	SAFE_FREE(data_pos_x);
	SAFE_FREE(data_pos_y);
	SAFE_FREE(data_pos_z);
	SAFE_FREE(data_neg_x);
	SAFE_FREE(data_neg_y);
	SAFE_FREE(data_neg_z);

	return textureID;
}

void Tema2::CubeMap() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		Shader* shader = shaders["ShaderNormal"];
		shader->Use();
		glm::mat4 modelMatrix2 = glm::mat4(1);
		modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(24.5f, 0, 24.5f));
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1), glm::vec3(30, 50, 50));
		modelMatrix2 = glm::scale(modelMatrix2, glm::vec3(60));
		GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
		glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix2));

		glm::mat4 viewMatrix = camera->GetViewMatrix();
		int loc_view_matrix = glGetUniformLocation(shader->program, "View");
		glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
		glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
		int loc_texture = shader->GetUniformLocation("texture_cubemap");
		glUniform1i(loc_texture, 0);

		meshes["cube"]->Render();
	}
}

void Tema2::LoadAnimationMesh() {
	{
		Mesh* mesh = new Mesh("j1");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j1.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j2");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j2.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j3");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j3.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j4");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j4.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j5");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j5.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j6");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j6.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j7");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j7.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j8");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j8.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j9");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j9.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j10");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j10.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j11");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j11.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j12");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j12.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j13");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j13.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j14");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j14.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j15");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j15.obj");
		meshes[mesh->GetMeshID()] = mesh;

	}
	{
		Mesh* mesh = new Mesh("j16");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j16.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j17");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j17.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j18");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j18.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j19");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j19.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j20");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j20.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j21");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j21.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j22");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j22.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j23");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j23.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j24");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j24.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("j25");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "j25.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

}

void Tema2::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::DrawPlayer() {
	modelMatrix = glm::mat4(1);
	modelMatrix *= transform3D::Translate(p.x, p.y, p.z);
	modelMatrix *= transform3D::Scale(0.3, 0.5, 0.3);
	modelMatrix *= transform3D::Translate(0, 0, -0.9f);
	modelMatrix *= transform3D::RotateOY(RADIANS(p.angle));
	RenderSimpleMesh(meshes["box"], shaders["PieleShader"], modelMatrix);

	modelMatrix *= transform3D::Translate(0, 0, 1.1f);
	RenderSimpleMesh(meshes["box"], shaders["PieleShader"], modelMatrix);

	modelMatrix *= transform3D::Translate(0, 1.20f, -0.55f);
	modelMatrix *= transform3D::Scale(1, 1 / 0.7, 1 / 0.48);
	RenderSimpleMesh(meshes["box"], shaders["HaineShader"], modelMatrix);

	modelMatrix *= transform3D::Translate(0, 0.25, -0.78);
	modelMatrix *= transform3D::Scale(1, 0.5, 0.5);
	RenderSimpleMesh(meshes["box"], shaders["HaineShader"], modelMatrix);

	modelMatrix *= transform3D::Translate(0, 0, 3.1);
	RenderSimpleMesh(meshes["box"], shaders["HaineShader"], modelMatrix);


	modelMatrix *= transform3D::Translate(0, -1.05f, 0);
	RenderSimpleMesh(meshes["box"], shaders["PieleShader"], modelMatrix);

	modelMatrix *= transform3D::Translate(0, 0, -3.1);
	RenderSimpleMesh(meshes["box"], shaders["PieleShader"], modelMatrix);

	//capu

	modelMatrix *= transform3D::Translate(0, 2.1, 1.5);
	modelMatrix *= transform3D::Scale(1, 1 / 0.9, 1 / 0.75);
	if (ctrl != 1) {
		RenderSimpleMesh(meshes["box"], shaders["PieleShader"], modelMatrix);
	}


}

void Tema2::DrawMap() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			cells.x[i] = 2.0f * (2 + 1.5 * i + (i - 1));
			cells.z[j] = 2.0f * (2 + 1.5 * j + (j - 1));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(cells.x[i], 0, cells.z[j]));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.10f));
			RenderSimpleMesh(meshes["plane"], shaders["TextureShader"], modelMatrix, mapTextures["ground"]);
		}
	}
	for (int i = 0; i < 12; i++) {
		cellsout.x[i] = 2.0f * (2 + 1.5 * i + (i - 1)) - 5;
		cellsout.z[0] = -(2.0f * (2 + 1.5 * 0 + (0 - 1))) - 1;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(cellsout.x[i], 0, cellsout.z[0]));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.10f));
		RenderSimpleMesh(meshes["plane"], shaders["TextureShader"], modelMatrix, mapTextures["ground"]);
	}

	for (int i = 0; i < 12; i++) {
		cellsout.x[i] = 2.0f * (2 + 1.5 * i + (i - 1)) - 5;
		cellsout.z[11] = -(2.0f * (2 + 1.5 * -11 + (-11 - 1))) - 1;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(cellsout.x[i], 0, cellsout.z[11]));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.10f));
		RenderSimpleMesh(meshes["plane"], shaders["TextureShader"], modelMatrix, mapTextures["ground"]);
	}
	for (int j = 0; j < 12; j++) {
		cellsout.x[0] = -(2.0f * (2 + 1.5 * 0 + (0 - 1))) - 1;
		cellsout.z[j] = (2.0f * (2 + 1.5 * j + (j - 1))) - 5;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(cellsout.x[0], 0, cellsout.z[j]));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.10f));
		RenderSimpleMesh(meshes["plane"], shaders["TextureShader"], modelMatrix, mapTextures["ground"]);
	}

	for (int j = 0; j < 12; j++) {
		cellsout.x[11] = -(2.0f * (2 + 1.5 * -11 + (-11 - 1))) - 1;
		cellsout.z[j] = (2.0f * (2 + 1.5 * j + (j - 1))) - 5;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(cellsout.x[11], 0, cellsout.z[j]));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.10f));
		RenderSimpleMesh(meshes["plane"], shaders["TextureShader"], modelMatrix, mapTextures["ground"]);
	}

}

bool Tema2::StillConnected()
{
	visited = std::vector<std::vector<int>>(maze, std::vector<int>(maze, 0));
	int cnt = 0;
	for (int i = 0; i < maze; i++)
	{
		for (int j = 0; j < maze; j++)
		{
			if (lab[i][j] == 0 && visited[i][j] == 0)
			{
				cnt++;
				DFS(i, j);
			}
		}
	}
	return (cnt == 1);
}

void Tema2::DFS(int i, int j)
{
	if (i < 0 || j < 0 || i == maze || j == maze)
		return;
	if (visited[i][j] == 1 || lab[i][j] == 1)
		return;
	visited[i][j] = 1;

	DFS(i + 1, j);
	DFS(i - 1, j);
	DFS(i, j + 1);
	DFS(i, j - 1);
}

void Tema2::FillMap(int seed)
{

	srand(seed);
	srand(std::time(0));


	for (int i = 0; i < 12; ++i)
	{
		out[i][0] = out[i][11] = 1;

	}

	for (int j = 0; j < 12; j++)
	{
		out[0][j] = out[11][j] = 1;
	}
	for (int i = 0; i < maze; ++i)
	{
		lab[i][0] = lab[i][maze - 1] = 1;

	}
	for (int j = 0; j < maze; j++)
	{
		lab[0][j] = lab[maze - 1][j] = 1;
	}
	lab[0][copy] = 0;
	//cout << "0" << " " << copy << endl;
	lab[maze - 1][idx] = 0;
	//cout << maze - 1 << " " << idx << endl;
	out[11][idx + 1] = 0;
	out[0][copy + 1] = 2;
	for (int i = 0; i < maze; ++i)
	{
		for (int j = 0; j < maze; j++)
		{
			if (i == 0 && j == copy)continue;
			if (i == maze - 1 && j == idx)continue;

			if ((rand() % 100) < 50)
			{
				lab[i][j] = 1;
				if (!StillConnected()) {
					lab[i][j] = 0;
				}

			}

		}
	}

	{
		int i = 0;

		int j = copy;

		p.x = 5.0f * i - 2.5;
		p.z = 5.0f * j + 2.5;
		p.y = 0.25;

	}

}

void Tema2::DrawMaze() {
	lab = std::vector<std::vector<int>>(maze, std::vector<int>(maze, 0));
	int seed = rand();
	FillMap(seed);
	Enemy e;
	Boxx b;
	for (int i = 1; i < maze - 1; i++)
	{
		for (int j = 1; j < maze - 1; j++)
		{

			if (visited[i][j] == 1) {

				e.x = i;
				e.z = j;
				n[i][j] = count_path;
				count_path++;
				for (int r = 0; r < count_path / 2; r++) {
					ra[r] = rand() % (count_path - 1) + 1;
					if (n[i][j] == ra[r]) {

						lab[i][j] = 2;
						e.cellx = i * 2.5;
						e.cellz = j * 2.5;
						e.dist = false;
						e.clk = 0;
						e.coli = 0;
						enemyy.push_back(e);
					}

				}
			}
		}
	}

	for (int i = 0; i < maze; i++)
	{
		for (int j = 0; j < maze; j++)
		{
			if (visited[i][j] == 0) {
				box_++;

				b.x = i;
				b.z = j;
				box.push_back(b);

			}
		}
	}
}

void Tema2::MoveEnemy() {
	float speed = 0.035f;
	for (int x = 0; x < enemyy.size(); x++) {
		if (f_move4 == 0) {
			if (enemyy[x].cellx < (enemyy[x].x + 1) * 2.5 - 0.5) {
				enemyy[x].cellx += speed;
			}
			else {
				f_move1 = 1;
				f_move2 = 0;
				f_move3 = 0;
				f_move4 = 1;
			}
		}



		if (f_move1 == 1) {
			if (enemyy[x].cellz < (enemyy[x].z + 1) * 2.5 - 0.5) {
				enemyy[x].cellz += speed;

			}

			else {
				f_move2 = 1;
				f_move1 = 0;
				f_move3 = 0;
				f_move4 = 1;
			}
		}
		if (f_move2 == 1) {
			if (enemyy[x].cellx > (enemyy[x].x) * 2.5) {
				enemyy[x].cellx -= speed;
			}
			else {
				f_move3 = 1;
				f_move2 = 0;
				f_move1 = 0;
				f_move4 = 1;
			}
		}

		if (f_move3 == 1) {
			if (enemyy[x].cellz > (enemyy[x].z) * 2.5) {
				enemyy[x].cellz -= speed;

			}

			else {
				f_move4 = 0;
				f_move2 = 0;
				f_move3 = 0;
				f_move1 = 0;
			}
		}


	}

}

void Tema2::DrawEnemy(float d) {
	copyt++;
	for (int i = 0; i < maze; i++)
	{
		for (int j = 0; j < maze; j++)
		{

			if (visited[i][j] == 1) {
				if (lab[i][j] == 2) {
					for (int x = 0; x < enemyy.size(); x++) {
						float distX = p.x - enemyy[x].x;
						float distZ = p.z - enemyy[x].z;
						enemyy[x].angle = (float)(atan2(distZ, distX));


						if (enemyy[x].dist == false) {
							glm::mat4 modelMatrix = glm::mat4(1);
							modelMatrix *= glm::translate(modelMatrix, glm::vec3(enemyy[x].cellx, 0.01f, enemyy[x].cellz));
							modelMatrix *= glm::scale(modelMatrix, glm::vec3(0.01f));
							if (copyt == 1) {
								RenderSimpleMesh(meshes["j1"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 2) {
								RenderSimpleMesh(meshes["j2"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 3) {
								RenderSimpleMesh(meshes["j3"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 4) {
								RenderSimpleMesh(meshes["j4"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 5) {
								RenderSimpleMesh(meshes["j5"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 6) {
								RenderSimpleMesh(meshes["j6"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 7) {
								RenderSimpleMesh(meshes["j7"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 8) {
								RenderSimpleMesh(meshes["j8"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 9) {
								RenderSimpleMesh(meshes["j9"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 10) {
								RenderSimpleMesh(meshes["j10"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 11) {
								RenderSimpleMesh(meshes["j11"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 12) {
								RenderSimpleMesh(meshes["j12"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 13) {
								RenderSimpleMesh(meshes["j13"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 14) {
								RenderSimpleMesh(meshes["j14"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 15) {
								RenderSimpleMesh(meshes["j15"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 16) {
								RenderSimpleMesh(meshes["j16"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 17) {
								RenderSimpleMesh(meshes["j17"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 18) {
								RenderSimpleMesh(meshes["j18"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 19) {
								RenderSimpleMesh(meshes["j19"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 20) {
								RenderSimpleMesh(meshes["j20"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 21) {
								RenderSimpleMesh(meshes["j21"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 22) {
								RenderSimpleMesh(meshes["j22"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 23) {
								RenderSimpleMesh(meshes["j23"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 24) {
								RenderSimpleMesh(meshes["j24"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else if (copyt == 25) {
								RenderSimpleMesh(meshes["j25"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
							}
							else {
								RenderSimpleMesh(meshes["j1"], shaders["TextureShader2"], modelMatrix, mapTextures["J"]);
								copyt = 0;
							}
						}
						if (enemyy[x].dist == true) {

							clk++;
							glm::mat4 modelMatrix = glm::mat4(1);
							modelMatrix *= glm::translate(modelMatrix, glm::vec3(enemyy[x].cellx, 0.01f, enemyy[x].cellz));
							modelMatrix *= glm::scale(modelMatrix, glm::vec3(0.01f));
							RenderSimpleMesh(meshes["j1"], shaders["D"], modelMatrix, mapTextures["J"]);

							if (clk == 2000) {
								enemyy.erase(enemyy.begin() + x);
							}
							else if (clk > 2000) {
								clk = 0;
							}


						}



					}

				}
			}
		}
	}

}

void Tema2::Pro(float d) {

	auto end = std::chrono::steady_clock::now();
	time = std::chrono::duration_cast<std::chrono::milliseconds>(end - distance).count() / 100;

	if (f == true)
	{
		if (space == true) {
			if (time < 15) {
				for (int x = 0; x < prz.size(); x++) {

					modelMatrix = glm::mat4(1);
					modelMatrix *= transform3D::Translate(prz[x].p.x, prz[x].p.y, prz[x].p.z);
					modelMatrix *= transform3D::Scale(0.01, 0.01, 0.01);
					RenderSimpleMesh(meshes["u"], shaders["TextureShader2"], modelMatrix, mapTextures["u"]);
					prz[x].p = prz[x].p + glm::normalize(camera->forward) * d * 3.0f;

				}
				pro.p = pro.p + glm::normalize(camera->forward) * d * 3.0f;
			}
			else if (time > 15) {
				pro.p = camera->GetTargetPosition();
				pro.x = camera->GetTargetPosition().x;
				pro.y = camera->GetTargetPosition().y - 0.1f;
				pro.z = camera->GetTargetPosition().z;

				for (int z = 0; z < prz.size(); z++) {
					prz.erase(prz.begin() + z);
				}

				Prooz pp;
				pp.p = camera->GetTargetPosition();
				prz.push_back(pp);
			}

		}
	}

	for (int x = 0; x < prz.size(); x++) {

		modelMatrix = glm::mat4(1);
		modelMatrix *= transform3D::Translate(prz[x].p.x, prz[x].p.y, prz[x].p.z);
		modelMatrix *= transform3D::Scale(0.01, 0.01, 0.01);
		RenderSimpleMesh(meshes["u"], shaders["TextureShader2"], modelMatrix, mapTextures["u"]);
		time = 0;
	}

}

void Tema2::PlayerCollisionEnemy() {

	for (int x = 0; x < enemyy.size(); x++) {
		if (enemyy[x].cellx * 2.0f < p.x + 1.0f &&
			enemyy[x].cellx * 2.0f > p.x - 0.9f &&
			enemyy[x].cellz * 2.0f < p.z + 0.5f &&
			enemyy[x].cellz * 2.0f > p.z - 0.5f * 2) {
			enemyy[x].coli++;
		}
		else {
			enemyy[x].coli = 0;
		}
	}

	for (int x = 0; x < enemyy.size(); x++) {
		if (enemyy[x].coli == 1) {
			health--;
		}
	}
}

void Tema2::ProCollisionEnemy() {
	if (ctrl == 1) {

		for (int x = 0; x < enemyy.size(); x++) {
			if (
				enemyy[x].cellx * 2.0f < pro.p.x
				&&
				enemyy[x].cellz * 2.0f < pro.p.z + 0.6f
				&&
				enemyy[x].cellz * 2.0f > pro.p.z - 0.5f
				) {
				prz.erase(prz.begin() + 0);
				Prooz pp;
				prz.push_back(pp);
				pp.p = camera->GetTargetPosition();
				coli = true;
				enemyy[x].dist = true;

			}
		}



	}
}

void Tema2::Maze() {
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (out[i][j] == 1)
			{

				labPosition = glm::vec3(cellsout.x[i], 0, cellsout.z[j]);
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, labPosition);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(4.9f));

				RenderSimpleMesh(meshes["box"], shaders["TextureShader2"], modelMatrix, mapTextures["b"]);
			}
		}
	}
	for (int i = 0; i < maze; i++)
	{
		for (int j = 0; j < maze; j++)
		{

			if (lab[i][j] == 1)
			{

				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(cells.x[i], 0, cells.z[j]));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(4.9f));
				RenderSimpleMesh(meshes["box"], shaders["TextureShader2"], modelMatrix, mapTextures["b"]);

			}
		}
	}
}

void Tema2::PlayerCollisionMaze() {
	float player_size = 0.5f;
	for (int x = 0; x < box_; x++) {

		if (p.x > box[x].x * 5 - player_size &&
			p.x < box[x].x * 5 + 5 - player_size
			&&
			p.z > box[x].z * 5 + 5 - player_size &&
			p.z < box[x].z * 5 + 5) {
			coliA = true;


		}

		if (p.x > box[x].x * 5 - player_size &&
			p.x < box[x].x * 5 + 5 - player_size
			&&
			p.z > box[x].z * 5 - player_size * 2 &&
			p.z < box[x].z * 5) {
			coliD = true;
		}

		if (p.z > box[x].z * 5 - player_size &&
			p.z < box[x].z * 5 + 5 - player_size
			&&
			p.x > box[x].x * 5 - player_size * 2 &&
			p.x < box[x].x * 5) {

			p.x = box[x].x * 5 - player_size * 2;

			cameraa = glm::vec3(box[x].x * 5 - player_size * 2, p.y, p.z);
			coliW = true;

		}

		if (p.z > box[x].z * 5 - player_size &&
			p.z < box[x].z * 5 + 5 - player_size
			&&
			p.x > box[x].x * 5 + 5 - player_size &&
			p.x < box[x].x * 5 + 5) {

			p.x = box[x].x * 5 + 5;

			cameraa = glm::vec3(box[x].x * 5 + 5, p.y, p.z);
			coliS = true;

		}

	}

	if (p.x < -5.3f) {
		coliS = true;
	}

	if (p.z > 48.5f) {

		coliD = true;
	}
	if (p.z < 0) {
		coliA = true;
	}
	if (p.z > (copy + 1) * 5 - player_size * 2 &&
		p.x > -5.3f &&
		p.x < -0.5f) {
		coliD = true;
	}

	if (p.z < (copy) * 5 &&
		p.x > -5.3f &&
		p.x < -0.5f) {
		coliA = true;
	}

	if ((p.z > (copy + 1) * 5 - player_size * 2 ||
		p.z < (copy) * 5) &&
		p.x < -0.5f) {

		p.x = -0.5f * 5;

		cameraa = glm::vec3(-0.5f * 5, p.y, p.z);
		coliS = true;
	}

	if (p.z > (idx + 1) * 5 - player_size * 2 &&
		p.x < 55 - 0.5 &&
		p.x > 50 - 0.5) {
		coliD = true;
	}

	if (p.z < (idx) * 5 &&
		p.x < 55 - 0.5 &&
		p.x > 50 - 0.5) {
		coliA = true;
	}
	if (p.x > 54.5f) {
		cout << "Ai castigat!";
		coliW = true;
	}
	if ((p.z > (idx) * 5 + 5 - player_size * 2 ||
		p.z < (idx) * 5) &&
		p.x > 50 - player_size) {
		coliW = true;
	}


}

void Tema2::ProCollisionMaze() {
	float player_size = 0.5f;
	if (ctrl == 1) {
		for (int x = 0; x < box_; x++) {

			if (pro.p.x > box[x].x * 5 - player_size &&
				pro.p.x < box[x].x * 5 + 5 - player_size
				&&
				pro.p.z > box[x].z * 5 + 5 - player_size &&
				pro.p.z < box[x].z * 5 + 5) {
				prz.erase(prz.begin() + 0);
				Prooz pp;
				prz.push_back(pp);
				pp.p = camera->GetTargetPosition();


			}

			if (pro.p.x > box[x].x * 5 - player_size &&
				pro.p.x < box[x].x * 5 + 5 - player_size
				&&
				pro.p.z > box[x].z * 5 - player_size * 2 &&
				pro.p.z < box[x].z * 5) {
				prz.erase(prz.begin() + 0);
				Prooz pp;
				prz.push_back(pp);
				pp.p = camera->GetTargetPosition();
			}

			if (pro.p.z > box[x].z * 5 - player_size &&
				pro.p.z < box[x].z * 5 + 5 - player_size
				&&
				pro.p.x > box[x].x * 5 - player_size * 2 &&
				pro.p.x < box[x].x * 5) {

				prz.erase(prz.begin() + 0);
				Prooz pp;
				prz.push_back(pp);
				pp.p = camera->GetTargetPosition();

			}

			if (pro.p.z > box[x].z * 5 - player_size &&
				pro.p.z < box[x].z * 5 + 5 - player_size
				&&
				pro.p.x > box[x].x * 5 + 5 - player_size &&
				pro.p.x < box[x].x * 5 + 5) {
				prz.erase(prz.begin() + 0);
				Prooz pp;
				prz.push_back(pp);
				pp.p = camera->GetTargetPosition();
			}

		}

		if (pro.p.x < -5.3f) {
			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();
		}

		if (pro.p.z > 48.5f) {

			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();
		}
		if (pro.p.z < 0) {
			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();
		}
		if (pro.p.z > (copy + 1) * 5 - player_size * 2 &&
			pro.p.x > -5.3f &&
			pro.p.x < -0.5f) {
			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();
		}

		if (pro.p.z < (copy) * 5 &&
			pro.p.x > -5.3f &&
			pro.p.x < -0.5f) {
			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();
		}

		if ((pro.p.z > (copy + 1) * 5 - player_size * 2 ||
			pro.p.z < (copy) * 5) &&
			pro.p.x < -0.5f) {
			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();
		}

		if (pro.p.z > (idx + 1) * 5 - player_size * 2 &&
			pro.p.x < 55 - 0.5 &&
			pro.p.x > 50 - 0.5) {
			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();
		}

		if (pro.p.z < (idx) * 5 &&
			pro.p.x < 55 - 0.5 &&
			pro.p.x > 50 - 0.5) {
			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();

		}
		if (pro.p.x > 54.5f) {
			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();
		}
		if ((pro.p.z > (idx) * 5 + 5 - player_size * 2 ||
			pro.p.z < (idx) * 5) &&
			pro.p.x > 50 - player_size) {
			prz.erase(prz.begin() + 0);
			Prooz pp;
			prz.push_back(pp);
			pp.p = camera->GetTargetPosition();
		}
	}

}

void Tema2::DrawHealthBar() {

	const float kTopY = 10.f;
	const float kRowHeight = 25.f;

	int rowIndex = 0;

	textRenderer->RenderText("Health Bar", 1050.0f, kTopY + kRowHeight * rowIndex++, 1.0f, kTextColor);
	if (health == 5) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(970, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1030, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1090, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1150, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1210, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else if (health == 4) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(970, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1030, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1090, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1150, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1210, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else if (health == 3) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(970, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1030, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1090, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1150, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1210, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else if (health == 2) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(970, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1030, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1090, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1150, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1210, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else if (health == 1) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(970, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1030, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1090, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1150, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1210, 620);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(970, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1030, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1090, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1150, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(1210, 620);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrixxx);
	}
}

void Tema2::DrawTime() {
	const float kTopY = 10.f;
	const float kRowHeight = 25.f;
	int rowIndex = 0;
	if ((150 - time_game) > 0 && health > 0) {

		textRenderer3->RenderText("Time: " + std::to_string(150 - time_game), 100.0f, kTopY + kRowHeight * rowIndex++, 1.0f, kTextColor);
	}
	else if (health <= 0) {
		textRenderer3->RenderText("Time: 0", 100.0f, kTopY + kRowHeight * rowIndex++, 1.0f, kTextColor);
	}
	else
	{
		textRenderer3->RenderText("Time: 0", 100.0f, kTopY + kRowHeight * rowIndex++, 1.0f, kTextColor);
	}

	if (time_game <= 30) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(10, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(70, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(130, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(190, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(250, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else if (time_game > 30 && time_game < 60) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(10, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(70, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(130, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(190, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(250, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else if (time_game >= 60 && time_game < 90) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(10, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(70, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(130, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(190, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(250, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else if (time_game >= 90 && time_game < 120) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(10, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(70, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(130, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(190, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(250, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else if (time_game >= 120 && time_game < 150) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(10, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(70, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(130, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(190, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(250, 620);
		RenderMesh2D(meshes["time_s"], shaders["VertexColor"], modelMatrixxx);
	}
	else if (time_game <= 150) {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(10, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(70, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(130, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(190, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(250, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
	}
	else {
		glm::mat3 modelMatrixxx = glm::mat3(1);
		modelMatrixxx = transform2D::Translate(10, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(70, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(130, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(190, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
		modelMatrixxx = transform2D::Translate(250, 620);
		RenderMesh2D(meshes["time_m"], shaders["VertexColor"], modelMatrixxx);
	}
	if ((150 - time_game) < 0) {
		game_end = true;
	}

}

void Tema2::GameOver() {

	textRenderer2->RenderText("Game Over!", 500.0f, 500.0f, 1.0f, kTextColor);
}

void Tema2::Update(float deltaTimeSeconds)
{
	time_game = (clock() / CLOCKS_PER_SEC) - 4;
	CubeMap();
	if (health > 0) {
		DrawPlayer();
	}
	DrawMap();
	Maze();
	DrawEnemy(deltaTimeSeconds);
	MoveEnemy();
	PlayerCollisionMaze();
	Pro(deltaTimeSeconds);
	ProCollisionEnemy();
	PlayerCollisionEnemy();
	ProCollisionMaze();
	DrawHealthBar();
	DrawTime();
	if (health <= 0 || game_end == true) {
		GameOver();
	}
}

void Tema2::FrameEnd()
{

}

void Tema2::Render(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	int timeLoc = glGetUniformLocation(shader->program, "time");
	glUniform1f(timeLoc, clk / 100);

	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));


	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}


	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 3.2f;
	float camspeed = 1.2f;
	float s = 3.2f;
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (coliA == false) {
			if (window->KeyHold(GLFW_KEY_A)) {
				p.angle += 0.5;
				coliW = false;
				coliS = false;
				coliD = false;
				f = false;
				pro.z -= 0.1f;
				if (ctrl != 1) {
					cameraa = glm::vec3(p.x, p.y + 3.5, p.z);
					cameraaAux = glm::vec3(0, 1.8, 0.5);
					camera->Set(cameraa + cameraaAux, cameraa, glm::vec3(0, 1, 0));
					projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.02f, 100.0f);
					camera->RotateThirdPerson_OY(RADIANS(270));
					camera->RotateThirdPerson_OX(RADIANS(30));


					camera->TranslateRight(-camspeed * deltaTime);
					cameraa -= glm::vec3(0, 0, deltaTime * speed);

					p.z -= deltaTime * speed;
				}
				if (ctrl == 1) {
					cameraa = glm::vec3(p.x, p.y + 1.4, p.z);
					cameraAux = glm::vec3(0.2, 0, 0);
					camera->Set(cameraa + cameraAux, cameraa, glm::vec3(0, 1, 0));

					camera->RotateFirstPerson_OY(RADIANS(180));

					camera->RotateFirstPerson_OY(RADIANS(p.angle));
					for (int x = 0; x < prz.size(); x++) {
						prz[x].p = camera->GetTargetPosition();
					}
					pro.p = camera->GetTargetPosition();
					pro.x = camera->GetTargetPosition().x;
					pro.y = camera->GetTargetPosition().y - 0.1f;
					pro.z = camera->GetTargetPosition().z;

				}

			}
		}

		if (coliS == false) {
			if (window->KeyHold(GLFW_KEY_S)) {

				coliW = false;
				coliD = false;
				coliA = false;
				if (ctrl != 1) {
					cameraa = glm::vec3(p.x, p.y + 3.5, p.z);
					cameraaAux = glm::vec3(0, 1.8, 0.5);
					camera->Set(cameraa + cameraaAux, cameraa, glm::vec3(0, 1, 0));
					projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.02f, 100.0f);
					camera->RotateThirdPerson_OY(RADIANS(270));
					camera->RotateThirdPerson_OX(RADIANS(30));
					f = false;


					camera->MoveForward(-camspeed * deltaTime);
					cameraa -= glm::vec3(deltaTime * speed, 0, 0);

					p.x -= deltaTime * speed;
				}
			}

		}


		if (coliD == false) {
			if (window->KeyHold(GLFW_KEY_D)) {
				coliS = false;
				coliW = false;
				coliA = false;
				p.angle -= 0.5;
				f = false;
				if (ctrl != 1) {
					cameraa = glm::vec3(p.x, p.y + 3.5, p.z);
					cameraaAux = glm::vec3(0, 1.8, 0.5);
					camera->Set(cameraa + cameraaAux, cameraa, glm::vec3(0, 1, 0));
					projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.02f, 100.0f);
					camera->RotateThirdPerson_OY(RADIANS(270));
					camera->RotateThirdPerson_OX(RADIANS(30));
					camera->TranslateRight(camspeed * deltaTime);
					cameraa += glm::vec3(0, 0, deltaTime * speed);

					p.z += deltaTime * speed;
				}
				if (ctrl == 1) {
					cameraa = glm::vec3(p.x, p.y + 1.4, p.z);
					cameraAux = glm::vec3(0.2, 0, 0);
					camera->Set(cameraa + cameraAux, cameraa, glm::vec3(0, 1, 0));

					camera->RotateFirstPerson_OY(RADIANS(180));

					camera->RotateFirstPerson_OY(RADIANS(p.angle));
					pro.p = camera->GetTargetPosition();
					pro.x = camera->GetTargetPosition().x;
					pro.y = camera->GetTargetPosition().y - 0.1f;
					pro.z = camera->GetTargetPosition().z;
					for (int x = 0; x < prz.size(); x++) {
						prz[x].p = camera->GetTargetPosition();
					}
					f = true;

				}


			}
		}

		if ((coliW == false)) {

			if (window->KeyHold(GLFW_KEY_W)) {
				coliS = false;
				coliA = false;
				coliD = false;
				f = false;
				if (ctrl != 1) {
					cameraa = glm::vec3(p.x, p.y + 3.5, p.z);
					cameraaAux = glm::vec3(0, 1.8, 0.5);
					camera->Set(cameraa + cameraaAux, cameraa, glm::vec3(0, 1, 0));
					projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.02f, 100.0f);
					camera->RotateThirdPerson_OY(RADIANS(270));
					camera->RotateThirdPerson_OX(RADIANS(30));


					camera->MoveForward(speed * deltaTime);

					p.x += deltaTime * speed;

					cameraa += glm::vec3(deltaTime * speed, 0, 0);
				}
			}
		}
	}

	if (window->KeyHold(GLFW_KEY_SPACE)) {
		space = true;
		distance = std::chrono::steady_clock::now();

	}


	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			camera->TranslateForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			camera->TranslateRight(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->TranslateForward(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			camera->TranslateRight(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			camera->TranslateUpward(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			camera->TranslateUpward(cameraSpeed * deltaTime);
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
		ctrl++;

		if (ctrl == 1) {
			cameraa = glm::vec3(p.x, p.y + 1.4, p.z);
			cameraAux = glm::vec3(0.2, 0, 0);
			camera->Set(cameraa + cameraAux, cameraa, glm::vec3(0, 1, 0));
			Prooz pp;
			camera->RotateFirstPerson_OY(RADIANS(180));
			pp.p = camera->GetTargetPosition();
			prz.push_back(pp);
			pro.p = camera->GetTargetPosition();
			pro.x = camera->GetTargetPosition().x;
			pro.y = camera->GetTargetPosition().y - 0.1f;
			pro.z = camera->GetTargetPosition().z;
			f = true;

		}
		else {
			for (int z = 0; z < prz.size(); z++) {
				prz.erase(prz.begin() + z);
			}
			pro.p = camera->GetTargetPosition();
			pro.x = camera->GetTargetPosition().x;
			pro.y = camera->GetTargetPosition().y - 0.1f;
			pro.z = camera->GetTargetPosition().z;
			cameraa = glm::vec3(p.x, p.y + 3.5, p.z);
			cameraaAux = glm::vec3(0, 1.8, 0.5);
			camera->Set(cameraa + cameraaAux, cameraa, glm::vec3(0, 1, 0));
			projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.02f, 100.0f);
			camera->RotateThirdPerson_OY(RADIANS(270));
			camera->RotateThirdPerson_OX(RADIANS(30));
			f = false;
			fp = 1;
			ctrl = 0;

		}
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
		}

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
