#include <Novice.h>
#include<Functions.h>
#include<imgui.h>

const char kWindowTitle[] = "LE2B_06_カタジマ_ロウノシン_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//移動
	Vector3 translate{};
	//回転
	Vector3 rotate{};
	//カメラポジション
	Vector3 cameraPosition{ 0.0f,20.0f,-61.49f };
	Vector3 cameraRotate{ 0.25f,0.0f,0.0f };

	Vector3 controlPoint[3];
	controlPoint[0] = { 5,5,5 };
	controlPoint[1] = { 5,10,5 };
	controlPoint[2] = { 10,5,0 };
	Sphere sphere[3];
	for (int i = 0; i < 3; i++) {
		sphere[i].center = controlPoint[i];
		sphere[i].radius = 0.1f;
	}


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




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		
		DrawBezier(controlPoint[0], controlPoint[1], controlPoint[2], worldViewProjectionMatrix, viewportMatrix,BLUE);

		for (int i = 0; i < 3; i++) {
			sphere[i].center = controlPoint[i];
			DrawSphere(sphere[i], worldViewProjectionMatrix, viewportMatrix,BLACK);
		}

		ImGui::Begin("Win");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.1f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.1f);
		ImGui::DragFloat3("controlPoint0", &controlPoint[0].x, 0.1f);
		ImGui::DragFloat3("controlPoint1", &controlPoint[1].x, 0.1f);
		ImGui::DragFloat3("controlPoint2", &controlPoint[2].x, 0.1f);
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
