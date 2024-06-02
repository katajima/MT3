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

	AABB aabb1;
	aabb1.max = { 5.0f,5.0f,5.0f };
	aabb1.min = { 0.0f,0.0f,0.0f };
	AABB aabb2;
	aabb2.max = { 15.0f,5.0f,15.0f };
	aabb2.min = { 0.0f,0.0f,5.0f };
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
		if (IsCollision(aabb1,aabb2)) {
			DrawBox(aabb1, worldViewProjectionMatrix, viewportMatrix, RED);
		}
		else {
			DrawBox(aabb1, worldViewProjectionMatrix, viewportMatrix, WHITE);
		}
		DrawBox(aabb2, worldViewProjectionMatrix, viewportMatrix, WHITE);

		ImGui::Begin("Win");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.1f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.1f);
		ImGui::DragFloat3("aabb1.max", &aabb1.max.x, 0.1f);
		ImGui::DragFloat3("aabb1.min", &aabb1.min.x, 0.1f);
		ImGui::InputFloat3("aabb2.max", &aabb2.max.x);
		ImGui::InputFloat3("aabb2.min", &aabb2.min.x);
		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);
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
