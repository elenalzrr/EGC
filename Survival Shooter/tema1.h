#pragma once

#include "components/simple_scene.h"
#include <chrono>

namespace m1
{
	class Tema1 : public gfxc::SimpleScene
	{
	public:
		struct ViewportSpace
		{
			ViewportSpace() : x(0), y(0), width(1), height(1) {}
			ViewportSpace(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {}
			int x;
			int y;
			int width;
			int height;
		};

		struct LogicSpace
		{
			LogicSpace() : x(0), y(0), width(1), height(1) {}
			LogicSpace(float x, float y, float width, float height)
				: x(x), y(y), width(width), height(height) {}
			float x;
			float y;
			float width;
			float height;
		};

		struct Obstacles
		{
			float x[18];
			float y[18];
			float w;
			float h;
		};


		struct Playerr
		{
			Playerr() : x(0), y(0), w(0.65f), h(0.65f) {}
			Playerr(float x, float y, float w, float h)
				: x(x), y(y), w(w), h(h) {}
			float x;
			float y;
			float w;
			float h;
		};

		struct Enemyy
		{
			Enemyy() : x(0), y(0), b(1.0f), l(0.40f), speed(0.05f), angle(0) {}
			Enemyy(float x, float y, float b, float l, float speed, float angle)
				: x(x), y(y), b(b), l(l), speed(speed), angle(angle) {}
			float x;
			float y;
			float b;
			float l;
			float speed;
			float angle;
		};
		struct Proiectil {
			Proiectil() : x(0), y(0), speed(1.0f), angle(0) {}
			Proiectil(float x, float y, float speed, float angle)
				: x(x), y(y), speed(speed), angle(angle) {}
			float x;
			float y;
			float speed;
			float angle;
		};

	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void PlayerCollisionMap();
		void EnemyCollisionPro();
		void EnemyCollisionPlayer();
		void PlayerCollisionObstacle();
		void PlayerCollisionObstacle_VERT();
		void DrawPlayer(glm::mat3 modelMatrix);
		void DrawPro(glm::mat3 visMatrix);
		void DrawEnemy(glm::mat3 visMatrix);
		void DrawHealthBar(glm::mat3 visMatrix);
		void DrawScene(glm::mat3 visMatrix);
		void Map(glm::mat3 visMatrix);
		void Obstacle(glm::mat3 visMatrix);
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
		glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
		glm::mat3 VisualizationTransf2DMax(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
		void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

	protected:
		ViewportSpace viewSpace;
		LogicSpace logicSpace;
		glm::mat3 modelMatrix, visMatrix;
		float angularStep;
		float player_speed = 8.0f;
		int map_X, map_Y;
		//pentru mapa
		bool collW = false;
		bool collA = false;
		bool collS = false;
		bool collD = false;
		Obstacles obstacle;
		Playerr player;
		//pentru obstacole
		bool coliW = false;
		bool coliA = false;
		bool coliS = false;
		bool coliD = false;
		std::vector<Proiectil> pro;
		std::vector<Enemyy> enemy;
		float pro_w = 0.4f;
		float pro_h = 0.3f;
		float rotation_speed = 1.0f;
		std::chrono::steady_clock::time_point distance;
		std::chrono::steady_clock::time_point fire_rate;
		std::chrono::steady_clock::time_point enemy_spawn;
		int seconds_distance;
		int seconds_spawn = 0;
		int seconds_coli = 0;
		int time_coli = 0;
		float seconds_fire_rate = 0;
		float center_x, center_y;
		float enemy_l = 0.40f;
		float enemy_b = 1.0f;
		int time_aux = 0;
		int enemy_nr = 0;
		float coliEnemy = false;
		int score = 0;
		int health = 5;
		bool game_end = false;
		float big_health_x = 0;
		float big_health_y = 0;
		float health_x = 0;
		float health_y = 0;
		int show_score = 0;
		int score_aux = 0;

	};
}
