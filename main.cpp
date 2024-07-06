#include <Novice.h>
#include<Functions.h>
#include<imgui.h>

const char kWindowTitle[] = "LE2B_06_カタジマ_ロウノシン_タイトル";

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

	Vector3 translates[3];
	translates[0] = { 0.2f,1.0f,0 };
	translates[1] = { 0.4f,0.0f,0 };
	translates[2] = { 0.3f,0.0f,0 };
	Vector3 rotates[3];
	rotates[0] = { 0,0,-6.8f };
	rotates[1] = { 0,0,-1.4f };
	rotates[2] = { 0,0,0 };

	Vector3 scales[3];
	scales[0] = { 1,1,1 };
	scales[1] = { 1,1,1 };
	scales[2] = { 1,1,1 };

	Sphere sphere[3];
	for (int i = 0; i < 3; i++) {
		sphere[i].center = translates[i];
		sphere[i].radius = 0.05f;
	}

	Matrix4x4 worldMatrixs[3];
	//Matrix4x4 worldViewProjectionMatrixs[3];
	//Vector3 scr[3];
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


		if (keys[DIK_A]) {
			cameraPosition.x -= 2;

		}
		if (keys[DIK_D]) {
			cameraPosition.x += 2;

		}
		if (keys[DIK_W]) {
			cameraPosition.y += 2;

		}
		if (keys[DIK_S]) {
			cameraPosition.y -= 2;

		}
		if (keys[DIK_UP]) {
			cameraPosition.z += 2;

		}
		if (keys[DIK_DOWN]) {
			cameraPosition.z -= 2;

		}
		if (keys[DIK_RIGHT]) {
			cameraRotate.y += 0.01f;

		}
		if (keys[DIK_LEFT]) {
			cameraRotate.y -= 0.01f;

		}


		Matrix4x4 worldMatrix = MakeAffineMatrixMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrixMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(1280) / float(720), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(1280), float(720), 0.0f, 1.0f);

		for (int i = 0; i < 3; i++) {
			worldMatrixs[i] = MakeAffineMatrixMatrix(scales[i], rotates[i], translates[i]);
		}
		worldMatrixs[0] = worldMatrixs[0];
		worldMatrixs[1] = Multiply(worldMatrixs[1], worldMatrixs[0]);
		worldMatrixs[2] = Multiply(worldMatrixs[2], worldMatrixs[1]);




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		DrawGrid(worldViewProjectionMatrix, viewportMatrix);



		for (int i = 0; i < 3; i++) {

			sphere[i].center.x = worldMatrixs[i].m[3][0];
			sphere[i].center.y = worldMatrixs[i].m[3][1];
			sphere[i].center.z = worldMatrixs[i].m[3][2];
		}

		DrawLine({ sphere[0].center,sphere[1].center }, worldViewProjectionMatrix, viewportMatrix, WHITE);
		DrawLine({ sphere[1].center,sphere[2].center }, worldViewProjectionMatrix, viewportMatrix, WHITE);


		DrawSphere(sphere[0], worldViewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(sphere[1], worldViewProjectionMatrix, viewportMatrix, GREEN);
		DrawSphere(sphere[2], worldViewProjectionMatrix, viewportMatrix, BLUE);


		ImGui::Begin("Win");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.1f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.1f);
		ImGui::End();
		ImGui::Begin("obj");
		ImGui::DragFloat3("translates[0]", &translates[0].x, 0.1f);
		ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.1f);
		//ImGui::DragFloat3("scales[0]", &scales[0].x, 0.1f);
		ImGui::DragFloat3("translates[1]", &translates[1].x, 0.1f);
		ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.1f);
		//ImGui::DragFloat3("scales[1]", &scales[1].x, 0.1f);
		ImGui::DragFloat3("translates[2]", &translates[2].x, 0.1f);
		ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.1f);
		//ImGui::DragFloat3("scales[2]", &scales[2].x, 0.1f);
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
