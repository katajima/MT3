#include <Novice.h>
#include<Functions.h>
#include<imgui.h>

const char kWindowTitle[] = "LE2B_06_カタジマ_ロウノシン_タイトル";

Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); };
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); };
Vector3 operator*(const Vector3& v1, const Vector3& v2) { return Multiply(v1, v2); };
Vector3 operator*(float s, const Vector3& v) { return Multiply(s, v); };
Vector3 operator*(const Vector3& v, float s) { return s * v; };
Vector3 operator/(const Vector3& v, float s) { return Multiply(1.0f / s, v); }
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Add(m1, m2); };
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Subtract(m1, m2); };
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); };
Vector3 operator-(const Vector3& v) { return { -v.x,-v.y,-v.z }; };
Vector3 operator+(const Vector3& v) { return v; };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//移動
	Vector3 translate{};
	//回転
	Vector3 rotate{};
	//カメラポジション
	Vector3 cameraPosition{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };



	Sphere sphere{};
	sphere.center = { 0.0f,0.0f,0.0f };
	float deltaTime = 1.0f / 60.0f;
	bool flag = 0;

	Ball ball;
	ball.veloctiy = { 0.0f,0.0f,0.0f };
	ball.position = { 0.8f,1.2f,0.3f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.acceleration = { 0.0f,-9.8f,0.0f };
	ball.color = WHITE;

	Plane plane;
	plane.distance = 0.0f;
	plane.nomal = Nomalize({ -0.2f,0.9f,-0.3f });

	Capsule capsule;
	capsule.segment = Segment{ ball.position, ball.position + ball.veloctiy };
	capsule.radius = ball.radius;

	float e = 0.8f; // 反発係数
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


		Matrix4x4 worldMatrix = MakeAffineMatrixMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrixMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(1280) / float(720), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(1280), float(720), 0.0f, 1.0f);

		if (flag) {
			//ball.veloctiy = Add(ball.veloctiy, ball.acceleration * deltaTime);
			//ball.position = Add(ball.position, ball.veloctiy * deltaTime);
			ball.veloctiy.x += ball.acceleration.x * deltaTime;
			ball.veloctiy.y += ball.acceleration.y * deltaTime;
			ball.veloctiy.z += ball.acceleration.z * deltaTime;
		
			ball.position.x += ball.veloctiy.x * deltaTime;
			ball.position.y += ball.veloctiy.y * deltaTime;
			ball.position.z += ball.veloctiy.z * deltaTime;	

			capsule.segment = Segment{ ball.position, ball.position + ball.veloctiy * deltaTime };

		}
		
		
		
		if (IsCollision(Sphere{ ball.position,ball.radius }, plane)) {
			Vector3 reflected = Reflect(ball.veloctiy, plane.nomal);
			Vector3 projectToNomal = Project(reflected, plane.nomal);
			Vector3 movingDirection = reflected - projectToNomal;
			ball.veloctiy = projectToNomal * e + movingDirection;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///



		DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, WHITE);
		DrawSphere({ capsule.segment.origin,ball.radius}, worldViewProjectionMatrix, viewportMatrix, ball.color);
		

		ImGui::Begin("Win");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.1f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.1f);
		ImGui::Checkbox("flag", &flag);
		ImGui::DragFloat("e", &e, 0.01f);
		if (ImGui::Button("reset")) {
			plane.nomal = Nomalize({ -0.2f,0.9f,-0.3f });
			ball.position = { 0.8f,1.2f,0.3f };
			ball.veloctiy = { 0.0f,0.0f,0.0f };
		}
		ImGui::End();



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
