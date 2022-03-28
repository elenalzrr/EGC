#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D_tema.h"
#include <random>

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}
Tema1::~Tema1()
{
}
void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 cornerr = glm::vec3(0, 0, 0);
	logicSpace.x = 0;
	logicSpace.y = 0;
	logicSpace.width = 20;
	logicSpace.height = 20;
	player.x = logicSpace.width / 2;
	player.y = logicSpace.height / 2;

	center_x = corner.x + enemy_b / 2;
	center_y = corner.y + enemy_b / 2;

	map_X = 50;
	map_Y = 30;
	angularStep = 0;
	obstacle.w = 5;
	obstacle.h = 1;
	Mesh* map = object2D_tema::CreateRectangle("map", corner, map_X, map_Y, glm::vec3(0.44f, 0.86f, 0.87f), true);
	AddMeshToList(map);

	Mesh* obstacles_o = object2D_tema::CreateRectangle("obstacles_o", corner, obstacle.w, obstacle.h, glm::vec3(0.62f, 0.27f, 0.03f), true);
	AddMeshToList(obstacles_o);
	Mesh* obstacles_v = object2D_tema::CreateRectangle("obstacles_v", corner, obstacle.h, obstacle.w, glm::vec3(0.07f, 0.39f, 0.20f), true);
	AddMeshToList(obstacles_v);

	Mesh* pro = object2D_tema::CreatePro("pro");
	AddMeshToList(pro);

	Mesh* enemyb = object2D_tema::CreateSquare("enemy_b", corner, enemy_b, glm::vec3(0.92f, 0.30f, 0.27f), true);
	AddMeshToList(enemyb);

	glm::vec3 corner2 = glm::vec3(-0.3f, -1.1f, 0);
	Mesh* enemy_l1 = object2D_tema::CreateSquare("enemy_l1", corner2, enemy_l, glm::vec3(0.92f, 0.70f, 0.68f), true);
	AddMeshToList(enemy_l1);

	glm::vec3 corner3 = glm::vec3(-1.1f, -1.1f, 0);
	Mesh* enemy_l2 = object2D_tema::CreateSquare("enemy_l2", corner3, enemy_l, glm::vec3(0.92f, 0.70f, 0.68f), true);
	AddMeshToList(enemy_l2);

	glm::vec3 corner4 = glm::vec3(-0.3f, 0.7f, 0);
	Mesh* playerb = object2D_tema::CreateCircle("player_b", cornerr, 0.65f, glm::vec3(0.66f, 0.32f, 0.68f), true);
	AddMeshToList(playerb);

	glm::vec3 corner5 = glm::vec3(0.3f, 0.7f, 0);
	Mesh* playerl1 = object2D_tema::CreateCircle("player_l1", corner4, 0.25f, glm::vec3(1, 0.74f, 0.96f), true);
	AddMeshToList(playerl1);

	Mesh* playerl2 = object2D_tema::CreateCircle("player_l2", corner5, 0.25f, glm::vec3(1, 0.74f, 0.96f), true);
	AddMeshToList(playerl2);
	for (int i = 0; i < 18; i++) {
		obstacle.x[i] = 0;
		obstacle.y[i] = 0;
	}
	enemy_spawn = std::chrono::steady_clock::now();

	Mesh* healthb_score = object2D_tema::CreateRectangle("health_s", corner, 1.0f, 1.2f, glm::vec3(0.36f, 0.65f, 0.49f), true);
	AddMeshToList(healthb_score);
	Mesh* healthb_min = object2D_tema::CreateRectangle("health_m", corner, 1.0f, 1.2f, glm::vec3(0.36f, 0.65f, 0.49f), false);
	AddMeshToList(healthb_min);
}
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	tx = viewSpace.x - sx * logicSpace.x;
	ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(
		sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f));
}
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}
glm::mat3 Tema1::VisualizationTransf2DMax(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty, smax;
	sx = logicSpace.width / viewSpace.width;
	sy = logicSpace.height / viewSpace.height;
	if (sx > sy)
		smax = sx;
	else
		smax = sy;
	tx = logicSpace.x - smax * viewSpace.x + (logicSpace.width - smax * viewSpace.width) / 2;
	ty = logicSpace.y - smax * viewSpace.y + (logicSpace.height - smax * viewSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smax, 0.0f, tx,
		0.0f, smax, ty,
		0.0f, 0.0f, 1.0f));
}
void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}
void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}
void Tema1::PlayerCollisionMap() {
	if (player.y + player.h > map_Y) {
		collW = true;
	}
	else {
		collW = false;
	}
	if (player.y - player.h < 0) {
		collS = true;
	}
	else {
		collS = false;
	}
	if (player.x + player.w > map_X) {
		collD = true;
	}
	else {
		collD = false;
	}

	if (player.x - player.w < 0) {
		collA = true;
	}
	else {
		collA = false;
	}
}
void Tema1::EnemyCollisionPro() {
	for (int i = 0; i < enemy.size(); i++) {
		for (int k = 0; k < pro.size(); k++) {
			if (pro[k].x + pro_w > enemy[i].x &&
				pro[k].x  < enemy[i].x + enemy[i].b &&
				pro[k].y + pro_h > enemy[i].y &&
				pro[k].y < enemy[i].y + enemy[i].b) {
				pro.erase(pro.begin() + k);
				enemy.erase(enemy.begin() + i);
				score++;
			}
		}
	}
}
void Tema1::EnemyCollisionPlayer() {
	for (int i = 0; i < enemy.size(); i++) {
		if (player.x + player.w > enemy[i].x &&
			player.x - player.w  < enemy[i].x + enemy[i].b &&
			player.y + player.h > enemy[i].y &&
			player.y - player.h < enemy[i].y + enemy[i].b) {
			seconds_coli = clock() / CLOCKS_PER_SEC;
			if (seconds_coli > time_coli + 1) {
				time_coli = 1;

				if (time_coli == 1) {
					enemy.erase(enemy.begin() + i);
					health--;
					if (health == 0) {
						game_end = true;
					}
				}
			}
		}
	}
}
void Tema1::PlayerCollisionObstacle() {
	for (int i = 0; i < 8; i++) {
		if (player.x + (player.w / 2) > obstacle.x[i] &&
			player.x + (player.w / 2) < obstacle.x[i] + obstacle.w + player.w &&
			player.y + player.h > obstacle.y[i] &&
			player.y + player.h < obstacle.y[i] + obstacle.h) {
			player.y = obstacle.y[i] - player.h;
			logicSpace.y = obstacle.y[i] - 10.5;
			coliW = true;

		}

		if (player.x + (player.w / 2) > obstacle.x[i] &&
			player.x + (player.w / 2) < obstacle.x[i] + obstacle.w + player.w &&
			player.y - player.h < obstacle.y[i] + obstacle.h &&
			player.y - player.h + 1> obstacle.y[i] + obstacle.h) {
			player.y = obstacle.y[i] + obstacle.h + player.h;
			logicSpace.y = obstacle.y[i] + obstacle.h - 9.5;
			coliS = true;

		}


		if (player.x + player.w > obstacle.x[i] &&
			player.x + player.w < obstacle.x[i] + 1 &&
			player.y + player.h > obstacle.y[i] &&
			player.y - player.h < obstacle.y[i] + obstacle.h) {
			player.x = obstacle.x[i] - player.w;
			logicSpace.x = obstacle.x[i] - 10.5;
			coliD = true;


		}
		if (player.x < obstacle.x[i] + obstacle.w + player.w &&
			player.x + 1 > obstacle.x[i] + obstacle.w + player.w &&
			player.y + player.h > obstacle.y[i] &&
			player.y - player.h < obstacle.y[i] + obstacle.h) {
			coliA = true;

			player.x = obstacle.x[i] + obstacle.w + player.w;
			logicSpace.x = obstacle.x[i] + obstacle.w - 9.5;
		}
	}

}
void Tema1::PlayerCollisionObstacle_VERT() {
	for (int i = 8; i < 18; i++) {
		if (player.x + (player.w / 2) > obstacle.x[i] &&
			player.x + (player.w / 2) < obstacle.x[i] + obstacle.h + player.w &&
			player.y + player.h > obstacle.y[i] &&
			player.y + player.h < obstacle.y[i] + obstacle.w) {
			player.y = obstacle.y[i] - player.h;
			logicSpace.y = obstacle.y[i] - 10.5;
			coliW = true;

		}

		if (player.x + (player.w / 2) > obstacle.x[i] &&
			player.x + (player.w / 2) < obstacle.x[i] + obstacle.h + player.w &&
			player.y - player.h < obstacle.y[i] + obstacle.w &&
			player.y - player.h + 1> obstacle.y[i] + obstacle.w) {
			player.y = obstacle.y[i] + obstacle.w + player.h;
			logicSpace.y = obstacle.y[i] + obstacle.w - 9.5;
			coliS = true;

		}


		if (player.x + player.w > obstacle.x[i] &&
			player.x + player.w < obstacle.x[i] + 1 &&
			player.y + player.h > obstacle.y[i] &&
			player.y - player.h < obstacle.y[i] + obstacle.w) {
			player.x = obstacle.x[i] - player.w;
			logicSpace.x = obstacle.x[i] - 10.5;
			coliD = true;


		}
		if (player.x < obstacle.x[i] + obstacle.h + player.w &&
			player.x + 1 > obstacle.x[i] + obstacle.h + player.w &&
			player.y + player.h > obstacle.y[i] &&
			player.y - player.h < obstacle.y[i] + obstacle.w) {
			coliA = true;

			player.x = obstacle.x[i] + obstacle.h + player.w;
			logicSpace.x = obstacle.x[i] + obstacle.h - 9.5;


		}
	}

}
void Tema1::Map(glm::mat3 visMatrix)
{
	modelMatrix = visMatrix * transform2D::Translate(0, 0);
	RenderMesh2D(meshes["map"], shaders["VertexColor"], modelMatrix);

}
void Tema1::Obstacle(glm::mat3 visMatrix)
{

	obstacle.x[0] = 5;
	obstacle.y[0] = 5;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[0], obstacle.y[0]);
	RenderMesh2D(meshes["obstacles_o"], shaders["VertexColor"], modelMatrix);

	obstacle.x[1] = 15;
	obstacle.y[1] = 15;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[1], obstacle.y[1]);
	RenderMesh2D(meshes["obstacles_o"], shaders["VertexColor"], modelMatrix);

	obstacle.x[2] = 10;
	obstacle.y[2] = 4;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[2], obstacle.y[2]);
	RenderMesh2D(meshes["obstacles_o"], shaders["VertexColor"], modelMatrix);

	obstacle.x[3] = 15;
	obstacle.y[3] = 27;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[3], obstacle.y[3]);
	RenderMesh2D(meshes["obstacles_o"], shaders["VertexColor"], modelMatrix);

	obstacle.x[4] = 25;
	obstacle.y[4] = 10;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[4], obstacle.y[4]);
	RenderMesh2D(meshes["obstacles_o"], shaders["VertexColor"], modelMatrix);

	obstacle.x[5] = 35;
	obstacle.y[5] = 10;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[5], obstacle.y[5]);
	RenderMesh2D(meshes["obstacles_o"], shaders["VertexColor"], modelMatrix);

	obstacle.x[6] = 30;
	obstacle.y[6] = 15;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[6], obstacle.y[6]);
	RenderMesh2D(meshes["obstacles_o"], shaders["VertexColor"], modelMatrix);

	obstacle.x[7] = 2;
	obstacle.y[7] = 20;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[7], obstacle.y[7]);
	RenderMesh2D(meshes["obstacles_o"], shaders["VertexColor"], modelMatrix);

	obstacle.x[8] = 5;
	obstacle.y[8] = 5;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[8], obstacle.y[8]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);

	obstacle.x[9] = 10;
	obstacle.y[9] = 4;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[9], obstacle.y[9]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);

	obstacle.x[10] = 20;
	obstacle.y[10] = 2;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[10], obstacle.y[10]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);

	obstacle.x[11] = 20;
	obstacle.y[11] = 20;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[11], obstacle.y[11]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);

	obstacle.x[12] = 30;
	obstacle.y[12] = 4;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[12], obstacle.y[12]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);

	obstacle.x[13] = 25;
	obstacle.y[13] = 20;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[13], obstacle.y[13]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);

	obstacle.x[14] = 35;
	obstacle.y[14] = 17;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[14], obstacle.y[14]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);

	obstacle.x[15] = 10;
	obstacle.y[15] = 17;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[15], obstacle.y[15]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);

	obstacle.x[16] = 15;
	obstacle.y[16] = 17;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[16], obstacle.y[16]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);

	obstacle.x[17] = 3;
	obstacle.y[17] = 20;
	modelMatrix = visMatrix * transform2D::Translate(obstacle.x[17], obstacle.y[17]);
	RenderMesh2D(meshes["obstacles_v"], shaders["VertexColor"], modelMatrix);


}
void Tema1::DrawPlayer(glm::mat3 visMatrix) {

	modelMatrix = visMatrix * transform2D::Translate(player.x, player.y);
	modelMatrix *= transform2D::Rotate((float)angularStep);
	RenderMesh2D(meshes["player_l1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = visMatrix * transform2D::Translate(player.x, player.y);
	modelMatrix *= transform2D::Rotate((float)angularStep);
	RenderMesh2D(meshes["player_l2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = visMatrix * transform2D::Translate(player.x, player.y);
	modelMatrix *= transform2D::Rotate((float)angularStep);
	RenderMesh2D(meshes["player_b"], shaders["VertexColor"], modelMatrix);

}
void Tema1::DrawPro(glm::mat3 visMatrix) {
	for (int i = 0; i < pro.size(); i++) {
		pro[i].y += 0.2f * sin((float)(pro[i].angle)) * pro[i].speed;
		pro[i].x += 0.2f * cos((float)(pro[i].angle)) * pro[i].speed;

		modelMatrix = visMatrix * transform2D::Translate(pro[i].x - player.w / 2, pro[i].y - player.h / 2);
		modelMatrix *= transform2D::Rotate((float)(pro[i].angle - M_PI / 2));
		RenderMesh2D(meshes["pro"], shaders["VertexColor"], modelMatrix);
	}

	for (int i = 0; i < pro.size(); i++) {
		if (pro[i].x > map_X || pro[i].y > map_Y || pro[i].x < 0.75 || pro[i].y < 0.8) {
			pro.erase(pro.begin() + i);
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < pro.size(); j++) {
			if (pro[j].x + (pro_w / 2) > obstacle.x[i] &&
				pro[j].x  < obstacle.x[i] + obstacle.w + player.w + (pro_w / 2) &&
				pro[j].y + pro_h > obstacle.y[i] &&
				pro[j].y < obstacle.y[i] + obstacle.h + player.h + (pro_w / 2)) {
				pro.erase(pro.begin() + j);
			}
		}
	}
	for (int i = 8; i < 18; i++) {
		for (int j = 0; j < pro.size(); j++) {
			if (pro[j].y + (pro_w / 2) > obstacle.y[i] &&
				pro[j].y  < obstacle.y[i] + obstacle.w + player.h + (pro_w / 2) &&
				pro[j].x + pro_w > obstacle.x[i] &&
				pro[j].x < obstacle.x[i] + obstacle.h + player.h + (pro_w / 2)) {
				pro.erase(pro.begin() + j);
			}
		}
	}

	for (int i = 0; i < pro.size(); i++) {
		auto end = std::chrono::steady_clock::now();
		seconds_distance = std::chrono::duration_cast<std::chrono::milliseconds>(end - distance).count() / 100;
		if (seconds_distance > 6) {
			seconds_distance = 0;
			pro.erase(pro.begin() + i);
		}
	}

}
void Tema1::DrawEnemy(glm::mat3 visMatrix) {
	for (int i = 0; i < enemy.size(); i++) {
		float distX = player.x - enemy[i].x;
		float distY = player.y - enemy[i].y;
		float distEnemy = sqrt(distX * distX + distY * distY);
		float X = (float)(distX / distEnemy);
		float Y = (float)(distY / distEnemy);
		float random = std::rand() % (10 - 1);
		enemy[i].speed = random / 100;
		enemy[i].angle = (float)(atan2(distY, distX) + M_PI / 2);

		//coliziunea cu mapa
		if (enemy[i].y + enemy[i].b > map_Y || enemy[i].y < 0) {
			enemy[i].x += X * enemy[i].speed;
			enemy[i].y -= Y * enemy[i].speed;
		}
		else if (enemy[i].x < 0 || enemy[i].x + enemy[i].b > map_X) {
			enemy[i].y += Y * enemy[i].speed;
			enemy[i].x -= X * enemy[i].speed;
		}
		else {
			enemy[i].x += X * enemy[i].speed;
			enemy[i].y += Y * enemy[i].speed;

		}

		modelMatrix = visMatrix * transform2D::Translate(enemy[i].x, enemy[i].y);
		modelMatrix *= transform2D::Translate(center_x, center_y);
		modelMatrix *= transform2D::Rotate(enemy[i].angle);
		modelMatrix *= transform2D::Translate(center_x, center_y);
		RenderMesh2D(meshes["enemy_l1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = visMatrix * transform2D::Translate(enemy[i].x, enemy[i].y);
		modelMatrix *= transform2D::Translate(center_x, center_y);
		modelMatrix *= transform2D::Rotate(enemy[i].angle);
		modelMatrix *= transform2D::Translate(center_x, center_y);
		RenderMesh2D(meshes["enemy_l2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = visMatrix * transform2D::Translate(enemy[i].x, enemy[i].y);
		modelMatrix *= transform2D::Translate(center_x, center_y);
		modelMatrix *= transform2D::Rotate(enemy[i].angle);
		modelMatrix *= transform2D::Translate(-center_x, -center_y);
		RenderMesh2D(meshes["enemy_b"], shaders["VertexColor"], modelMatrix);
	}

}
void Tema1::DrawHealthBar(glm::mat3 visMatrix) {
	health_x = logicSpace.x + 22;
	health_y = logicSpace.y + 18;

	if (health == 5) {
		modelMatrix = visMatrix * transform2D::Translate(health_x, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 1.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 2.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 3.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 4.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
	}
	else if (health == 4) {
		modelMatrix = visMatrix * transform2D::Translate(health_x, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 1.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 2.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 3.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 4.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);

	}
	else if (health == 3) {
		modelMatrix = visMatrix * transform2D::Translate(health_x, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 1.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 2.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 3.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 4.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
	}
	else if (health == 2) {
		modelMatrix = visMatrix * transform2D::Translate(health_x, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 1.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 2.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 3.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 4.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
	}
	else if (health == 1) {
		modelMatrix = visMatrix * transform2D::Translate(health_x, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 1.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 2.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 3.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 4.0f, health_y);
		RenderMesh2D(meshes["health_s"], shaders["VertexColor"], modelMatrix);
	}
	else if (health == 0 || game_end == true) {
		modelMatrix = visMatrix * transform2D::Translate(health_x, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 1.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 2.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 3.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
		modelMatrix = visMatrix * transform2D::Translate(health_x + 4.0f, health_y);
		RenderMesh2D(meshes["health_m"], shaders["VertexColor"], modelMatrix);
	}
}
void Tema1::DrawScene(glm::mat3 visMatrix)
{
	if (game_end == false) {
		DrawHealthBar(visMatrix);
		DrawPlayer(visMatrix);
		DrawEnemy(visMatrix);
		DrawPro(visMatrix);
		Obstacle(visMatrix);
		Map(visMatrix);

	}
	else {
		DrawHealthBar(visMatrix);
		Obstacle(visMatrix);
		Map(visMatrix);
		DrawHealthBar(visMatrix);
	}

}
void Tema1::Update(float deltaTimeSeconds)
{

	glm::ivec2 resolution = window->GetResolution();
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0, 0, 0), true);

	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

	DrawScene(visMatrix);
	PlayerCollisionMap();
	PlayerCollisionObstacle();
	PlayerCollisionObstacle_VERT();
	EnemyCollisionPro();
	EnemyCollisionPlayer();
	//spawn
	Enemyy e;
	seconds_spawn = clock() / CLOCKS_PER_SEC;
	if (seconds_spawn > time_aux + 1) {

		time_aux++;
		if (time_aux % 3 == 0) {
			e.x = e.x + std::rand() % (map_X - 1);
			e.y = e.y + std::rand() % (map_Y - 1);
			enemy.push_back(e);
			enemy_nr++;
		}

	}
	//afisare scor din 10 in 10 secunde
	show_score = clock() / CLOCKS_PER_SEC;

	if (show_score > score_aux + 1) {
		score_aux++;
		if (score_aux % 10 == 0) {
			cout << "SCORUL JUCATORULUI ESTE : " << score << endl;
		}
	}
}

void Tema1::FrameEnd()
{
}
void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (collW == false && coliW == false) {

		if (window->KeyHold(GLFW_KEY_W))
		{
			logicSpace.y += deltaTime * player_speed;
			player.y += deltaTime * player_speed;
			big_health_y += deltaTime * player_speed;

		}

	}

	if (collS == false && coliS == false) {
		if (window->KeyHold(GLFW_KEY_S))
		{
			player.y -= deltaTime * player_speed;
			logicSpace.y -= deltaTime * player_speed;
			big_health_y -= deltaTime * player_speed;
		}
	}
	if (collA == false && coliA == false) {
		if (window->KeyHold(GLFW_KEY_A))
		{
			player.x -= deltaTime * player_speed;
			logicSpace.x -= deltaTime * player_speed;
			big_health_x -= deltaTime * player_speed;
		}
	}
	if (collD == false && coliD == false) {
		if (window->KeyHold(GLFW_KEY_D))
		{
			player.x += deltaTime * player_speed;
			logicSpace.x += deltaTime * player_speed;
			big_health_x += deltaTime * player_speed;

		}
	}

}
void Tema1::OnKeyPress(int key, int mods)
{
	// Add key press event
	if (window->KeyHold(GLFW_KEY_W)) {
		coliW = false;
	}
	if (window->KeyHold(GLFW_KEY_A)) {
		coliA = false;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		coliS = false;
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		coliD = false;
	}


}
void Tema1::OnKeyRelease(int key, int mods)
{
}
void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2DMax(logicSpace, viewSpace);
	glm::vec3 mouse = visMatrix * glm::vec3(mouseX, viewSpace.height - mouseY, 1);
	angularStep = (atan2(mouse.y - player.y, mouse.x - player.x) - (M_PI / 2)) * rotation_speed;
}
void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		Proiectil p;
		p.angle = angularStep + M_PI / 2;
		p.x = player.x + player.h / 2;
		p.y = player.y + player.w / 2;

		distance = std::chrono::steady_clock::now();

		auto end = std::chrono::steady_clock::now();
		seconds_fire_rate = std::chrono::duration_cast<std::chrono::milliseconds>(end - fire_rate).count() / 100;
		if (seconds_fire_rate > 1) {
			pro.push_back(p);
		}
		else {
			seconds_fire_rate += seconds_fire_rate;
		}
	}
}
void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	fire_rate = std::chrono::steady_clock::now();
}
void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
void Tema1::OnWindowResize(int width, int height)
{
}
