#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/tema2/camera.h"
#include "lab_m1/tema2/transform3D.h"
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <components/text_renderer.h>
namespace m1
{
	class Tema2 : public gfxc::SimpleScene
	{
	public:
		Tema2();
		~Tema2();

		struct Cell
		{
			float x[10];
			float z[10];

		};

		struct Player
		{
			float x;
			float y;
			float z;
			float angle;

		};
		struct CellOut
		{
			float x[12];
			float z[12];

		};
		struct Enemy
		{
			float x;
			float z;
			float cellx;
			float cellz;
			float angle;
			bool dist;
			int clk;
			int coli;

		};

		struct Proo
		{
			float x;
			float z;
			float y;
			glm::vec3 p;

		};
		struct Prooz
		{
			float x;
			float z;
			float y;
			glm::vec3 p;

		};
		struct Boxx
		{
			float x;
			float z;
			float cellx;
			float cellz;

		};
		void Init() override;

	private:
		void FrameStart() override;
		void DrawPlayer();
		void LoadAnimationMesh();
		void DrawMap();
		bool StillConnected();
		void DFS(int i, int j);
		void FillMap(int seed);
		void DrawMaze();
		void DrawEnemy(float d);
		void MoveEnemy();
		void PlayerCollisionEnemy();
		void ProCollisionMaze();
		void Maze();
		void Pro(float d);
		void ProCollisionEnemy();
		void PlayerCollisionMaze();
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL);
		void Render(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void DrawHealthBar();
		void DrawTime();
		void GameOver();
		unsigned int UploadCubeMapTexture(const std::string& pos_x, const std::string& pos_y, const std::string& pos_z, const std::string& neg_x, const std::string& neg_y, const std::string& neg_z);
		void CubeMap();

		Player p;
		std::unordered_map<std::string, Texture2D*> mapTextures;
		GLuint randomTextureID;

		glm::vec3 floorPosition;
		glm::vec3 wallPosition1;
		glm::vec3 wallPosition2;
		glm::vec3 wallPosition3;
		glm::vec3 wallPosition4;
		glm::vec3 skyPosition;
		glm::vec3 labPosition;
		glm::vec3 startPosition;
		glm::vec3 endPosition;
		glm::vec3 cameraPlayerPos;
		glm::vec3 cameraAux;
		glm::vec3 cameraaAux;
		glm::vec3 cameraa;
		glm::vec3 paux;
		glm::mat3 modelMatrixx;
		implemented::CameraT* camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		//int lab[10][10];
		std::vector<std::vector<int> > lab;
		int out[12][12];
		std::vector<std::vector<int> > visited;
		int maze = 10;
		Cell cells;
		Proo pro;
		CellOut cellsout;
		int flag = 0;

		int count_path = 0;
		int ra[100];
		int idk = rand() % (maze - 2) + 1;
		int idxx = rand() % (maze - 1) + 1;
		int n[10][10];
		int copy = 0;
		int idx = 0;
		std::vector<Enemy> enemyy;
		std::vector<Prooz> prz;
		float move = 0;
		int f_move1 = 0;
		int f_move2 = 0;
		int f_move3 = 0;
		int f_move4 = 0;
		int fp = 0;
		int ctrl = 0;
		bool f = false;
		int caseAD = 0;
		bool shootA = false;
		int box_ = 0;
		std::vector<Boxx> box;
		bool coliW = false;
		bool coliA = false;
		bool coliS = false;
		bool coliD = false;
		bool coli = false;
		bool space = false;
		glm::mat4 modelMatrix;
		int time = 0;
		int time2 = 0;
		int copyt = 0;
		int clk = 0;
		std::chrono::steady_clock::time_point distance;
		Texture2D* originalImage;
		int outputMode;
		int cubeMapTextureID;
		int health = 5;
		bool game_end = false;
		gfxc::TextRenderer* textRenderer;
		gfxc::TextRenderer* textRenderer2;
		gfxc::TextRenderer* textRenderer3;
		gfxc::TextRenderer* textRenderer4;
		// Draw primitives mode
		GLenum polygonMode;
		// Colors
		const glm::vec3 kTextColor = NormalizedRGB(162, 137, 176);
		int time_game = 0;


	};
}   // namespace m1
