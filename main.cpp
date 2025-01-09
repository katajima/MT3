#include <Novice.h>
#include<Functions.h>
#include<imgui.h>


const char kWindowTitle[] = "LE2B_06_カタジマ_ロウノシン_タイトル";

// ベクトルの正規化関数
Vector3 Normalize(const Vector3& v) {
	float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return { v.x / length, v.y / length, v.z / length };
}


// クォータニオンの正規化関数
Quaternion Normalize(const Quaternion& q) {
	float length = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	return { q.w / length, q.x / length, q.y / length, q.z / length };
}

// 軸と角度からクォータニオンを生成する関数
Quaternion MakeQuaternion(const Vector3& axis, float angle) {
	Quaternion rotated;
	rotated.x = axis.x * sinf(angle / 2);
	rotated.y = axis.y * sinf(angle / 2);
	rotated.z = axis.z * sinf(angle / 2);
	rotated.w = cosf(angle / 2);
	return rotated;
}

// クォータニオンから回転行列を生成する関数
Matrix4x4 MakeRotateMatrix(const Quaternion& q) {
	Matrix4x4 m{};
	float xx = q.x * q.x;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float xw = q.x * q.w;
	float yy = q.y * q.y;
	float yz = q.y * q.z;
	float yw = q.y * q.w;

	float zz = q.z * q.z;
	float zw = q.z * q.w;

	m.m[0][0] = (1 - 2) * (yy + zz); m.m[0][1] = 2 * (xy - zw);       m.m[0][2] = 2 * (xz + yw);     m.m[0][3] = 0;
	m.m[1][0] = 2 * (xy + zw);     m.m[1][1] = (1 - 2) * (xx + zz);  m.m[1][2] = 2 * (yz - xw);      m.m[1][3] = 0;
	m.m[2][0] = 2 * (xz - yw);	   m.m[2][1] = 2 * (yz + xw);        m.m[2][2] = (1 - 2) * (xx + yy); m.m[2][3] = 0;
	m.m[3][0] = 0;                 m.m[3][1] = 0;                   m.m[3][2] = 0;                 m.m[3][3] = 1;

	return m;
}

// クォータニオンを使用してベクトルを回転させる関数
Vector3 RotateVector(const Vector3& v, const Quaternion& q) {
	Quaternion qv = { 0, v.x, v.y, v.z };
	Quaternion qConjugate = { q.w, -q.x, -q.y, -q.z };

	Quaternion temp;
	temp.w = q.w * qv.w - q.x * qv.x - q.y * qv.y - q.z * qv.z;
	temp.x = q.w * qv.x + q.x * qv.w + q.y * qv.z - q.z * qv.y;
	temp.y = q.w * qv.y - q.x * qv.z + q.y * qv.w + q.z * qv.x;
	temp.z = q.w * qv.z + q.x * qv.y - q.y * qv.x + q.z * qv.w;

	Quaternion result;
	result.w = temp.w * qConjugate.w - temp.x * qConjugate.x - temp.y * qConjugate.y - temp.z * qConjugate.z;
	result.x = temp.w * qConjugate.x + temp.x * qConjugate.w + temp.y * qConjugate.z - temp.z * qConjugate.y;
	result.y = temp.w * qConjugate.y - temp.x * qConjugate.z + temp.y * qConjugate.w + temp.z * qConjugate.x;
	result.z = temp.w * qConjugate.z + temp.x * qConjugate.y - temp.y * qConjugate.x + temp.z * qConjugate.w;

	return { result.x, result.y, result.z };
}






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


	Quaternion rotation = MakeQuaternion(Nomalize(Vector3{ 1.0f, 0.4f, -0.2f }), 0.45f);
	Vector3 pointY = { 2.1f, -0.9f, 1.3f };
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation); 
	Vector3 rotateByQuaternion = RotateVector(pointY, rotation); 
	Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);

	
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

		
		QuaternionScreenPrintf(0, 0, rotation, ": rotation");
		MatrixScreenPrintf(0, 20, rotateMatrix, "rotateMatrix");
		VectorScreenPrintf(0, 20 * 6, rotateByQuaternion, ": rotateByQuaternion");
		VectorScreenPrintf(0, 20 * 7, rotateByMatrix, ": rotateByMatrix");
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///



		DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		


		
		ImGui::Begin("Win");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.1f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.1f);
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
