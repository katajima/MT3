#include<Functions.h>

#include<imgui.h>

float K;

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;


	return result;
};

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;


	return result;
};

float Dot(const Vector3& v1, const Vector3& v2) {
	float result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;


	return result;
};

float Length(const Vector3& v) {
	float result;

	result = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

	return result;
};
// 2つの点間の距離を計算する関数
float Distance(const Vector3& point1, const Vector3& point2) {
	float dx = point1.x - point2.x;
	float dy = point1.y - point2.y;
	float dz = point1.z - point2.z;
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

float Length(const float& v) {
	float result;

	result = sqrtf((v * v));

	return result;
};

float Clanp(float t) {

	if (1.0f <= t) {
		t = 1.0f;
	}
	if (0.0f >= t) {
		t = 0.0f;
	}

	return t;
}
// クランプ関数
float Clamp(float value, float min, float max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}
Vector3 Lerp(const Vector3& a, const Vector3& b, float t) {
	Vector3 temp{};

	temp.x = t * a.x + (1.0f - t) * b.x;
	temp.y = t * a.y + (1.0f - t) * b.y;
	temp.z = t * a.z + (1.0f - t) * b.z;

	return  temp;

}

Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t) {

	Vector3 p0p1 = Lerp(p0, p1, t);

	Vector3 p1p2 = Lerp(p1, p2, t);

	Vector3 p = Lerp(p0p1, p1p2, t);

	return Lerp(p0p1, p1p2, t);

}


Vector3 Nomalize(const Vector3& v) {
	Vector3 result{};
	float length;

	length = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	};

	return result;
};
//行列の積
Matrix4x4 Multiply(const Matrix4x4& v1, const Matrix4x4& v2) {
	Matrix4x4 result{};

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			for (int z = 0; z < 4; z++) {
				result.m[y][x] += v1.m[y][z] * v2.m[z][x];
			}
		}
	}

	return result;
};
// Vector3同士
Vector3 Multiply(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;

	return result;
}
// floatとVector3
Vector3 Multiply(const float& v, const Vector3& v1) {
	Vector3 result{};

	result.x = v1.x * v;
	result.y = v1.y * v;
	result.z = v1.z * v;

	return result;
}

//移動行列
Matrix4x4 MakeTranslateMatrix(const  Vector3& translate) {
	Matrix4x4 result{};

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;

	return result;
}
//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const  Vector3& scale) {
	Matrix4x4 result{};

	result.m[0][0] = scale.x;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}
//回転行列X
Matrix4x4 MakeRotateXMatrix(float rotate) {
	Matrix4x4 result{};

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = std::cos(rotate);
	result.m[1][2] = std::sin(rotate);
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = -std::sin(rotate);
	result.m[2][2] = std::cos(rotate);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;


	return result;
}
//回転行列Y
Matrix4x4 MakeRotateYMatrix(float rotate) {
	Matrix4x4 result{};

	result.m[0][0] = std::cos(rotate);
	result.m[0][1] = 0;
	result.m[0][2] = -std::sin(rotate);;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = std::sin(rotate);
	result.m[2][1] = 0;
	result.m[2][2] = std::cos(rotate);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;


	return result;
}
//回転行列Z
Matrix4x4 MakeRotateZMatrix(float rotate) {
	Matrix4x4 result{};

	result.m[0][0] = std::cos(rotate);
	result.m[0][1] = std::sin(rotate);
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = -std::sin(rotate);
	result.m[1][1] = std::cos(rotate);
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;


	return result;
}
//逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result{};
	float result2;

	result2 =
		1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3])
			+ (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1])
			+ (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])

			- (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1])
			- (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3])
			- (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])

			- (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3])
			- (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1])
			- (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])

			+ (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1])
			+ (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3])
			+ (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])

			+ (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3])
			+ (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1])
			+ (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])

			- (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1])
			- (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3])
			- (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])

			- (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0])
			- (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0])
			- (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])


			+ (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0])
			+ (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0])
			+ (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]));


	//一行目一列目
	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2]);
	//一行目二列目
	result.m[0][1] = -(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2]);
	//一行目三列目
	result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2]);
	//一行目四列目
	result.m[0][3] = -(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2]);


	//二行目一列目
	result.m[1][0] = -(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[1][3] * m.m[2][0] * m.m[3][2])
		+ (m.m[1][3] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[1][0] * m.m[2][3] * m.m[3][2]);
	//二行目二列目
	result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) + (m.m[0][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][3]) - (m.m[0][0] * m.m[2][3] * m.m[3][2]);
	//二行目三列目
	result.m[1][2] = -(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][3]) + (m.m[0][0] * m.m[1][3] * m.m[3][2]);

	//二行目四列目
	result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) + (m.m[0][3] * m.m[1][0] * m.m[2][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][3]) - (m.m[0][0] * m.m[1][3] * m.m[2][2]);


	//三行目一列目
	result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1])
		- (m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1]);
	//三行目二列目
	result.m[2][1] = -(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1]);
	//三行目三列目
	result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1])
		- (m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1]);
	//三行目四列目
	result.m[2][3] = -(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1]);


	//四行目一列目
	result.m[3][0] = -(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][1])
		+ (m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[1][1] * m.m[2][0] * m.m[3][2]) + (m.m[1][0] * m.m[2][2] * m.m[3][1]);
	//四行目二列目
	result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[2][1] * m.m[3][0]) - (m.m[0][1] * m.m[2][0] * m.m[3][2]) - (m.m[0][0] * m.m[2][2] * m.m[3][1]);
	//四行目三列目
	result.m[3][2] = -(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][1] * m.m[3][0]) + (m.m[0][1] * m.m[1][0] * m.m[3][2]) + (m.m[0][0] * m.m[1][2] * m.m[3][1]);
	//四行目四列目
	result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0]) - (m.m[0][1] * m.m[1][0] * m.m[2][2]) - (m.m[0][0] * m.m[1][2] * m.m[2][1]);

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {

			result.m[y][x] = result.m[y][x] * result2;

		}
	}


	return result;
}
//転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result{};


	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			result.m[y][x] = m.m[x][y];
		}
	}
	return result;
}
//単位行列
Matrix4x4 Identity() {
	Matrix4x4 result{};


	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (x == y) {
				result.m[y][x] = 1.0f;
			}
			else {
				result.m[y][x] = 0.0f;
			}
		}
	}
	return result;
}
//アフィン変換
Matrix4x4 MakeAffineMatrixMatrix(const  Vector3& scale, const  Vector3& rotate, const  Vector3& translate) {
	Matrix4x4 result{};

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));


	result.m[0][0] = scale.x * rotateXYZMatrix.m[0][0];
	result.m[0][1] = scale.x * rotateXYZMatrix.m[0][1];
	result.m[0][2] = scale.x * rotateXYZMatrix.m[0][2];
	result.m[0][3] = 0;
	result.m[1][0] = scale.y * rotateXYZMatrix.m[1][0];
	result.m[1][1] = scale.y * rotateXYZMatrix.m[1][1];
	result.m[1][2] = scale.y * rotateXYZMatrix.m[1][2];
	result.m[1][3] = 0;
	result.m[2][0] = scale.z * rotateXYZMatrix.m[2][0];
	result.m[2][1] = scale.z * rotateXYZMatrix.m[2][1];
	result.m[2][2] = scale.z * rotateXYZMatrix.m[2][2];
	result.m[2][3] = 0;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;



	return result;
};
//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result{};

	result.m[0][0] = 2 / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2 / (top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[2][3] = 0;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1;





	return result;
}
//透視射影行列
Matrix4x4 MakePerspectiveFovMatrix(float forY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{};

	result.m[0][0] = (1 / aspectRatio) * 1 / std::tan(forY / 2);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1 / std::tan(forY / 2);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	result.m[3][3] = 0;

	return result;
}
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float leht, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{};

	result.m[0][0] = width / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = (-height) / 2;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = leht + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;
};
//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
};

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth * 1, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {

			Novice::ScreenPrintf(x + column * kColumnWidth, 20 + y + row * kRowHeight, "%6.02f", matrix.m[row][column]);

		}
	}

}

//線
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	// Z軸方向のグリッド線を描画
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float x = -kGridHalfWidth + xIndex * kGridEvery;
		Vector3 start = { x, 0, -kGridHalfWidth };
		Vector3 end = { x, 0, kGridHalfWidth };

		Vector3 transformedStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 transformedEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);
		if (xIndex == kSubdivision / 2) {
			Novice::DrawLine(int(transformedStart.x), int(transformedStart.y), int(transformedEnd.x), int(transformedEnd.y), BLACK);
		}
		else {
			Novice::DrawLine(int(transformedStart.x), int(transformedStart.y), int(transformedEnd.x), int(transformedEnd.y), 0xAAAAAAFF);
		}
	}

	// X軸方向のグリッド線を描画
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float z = -kGridHalfWidth + zIndex * kGridEvery;
		Vector3 start = { -kGridHalfWidth, 0, z };
		Vector3 end = { kGridHalfWidth, 0, z };

		Vector3 transformedStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 transformedEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		if (zIndex == kSubdivision / 2) {
			Novice::DrawLine(int(transformedStart.x), int(transformedStart.y), int(transformedEnd.x), int(transformedEnd.y), BLACK);
		}
		else {
			Novice::DrawLine(int(transformedStart.x), int(transformedStart.y), int(transformedEnd.x), int(transformedEnd.y), 0xAAAAAAFF);
		}
	}
}

//円
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	float pi = 3.14f;
	const uint32_t kSubdivision = 16; //分割数
	const float kLonEvery = pi * 2 / float(kSubdivision);      //経度分割1つ分の角度
	const float kLatEvery = pi * 2 / float(kSubdivision);      //緯度分割1つ分の角度



	Vector3 screenGridA;
	Vector3 screenGridB;
	Vector3 screenGridC;

	//　緯度の方向に分割　-π/2 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;// 現在の緯度
		//　経度の方向に分割　0 ～ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;// 現在の経度
			//world座標系でのa,b,cを求める
			//Matrix4x4 worldMatrix = 
			Vector3 a, b, c;
			a = { sphere.radius * std::cos(lat) * std::cos(lon)                                 ,sphere.radius * std::sin(lat)                             ,sphere.radius * std::cos(lat) * std::sin(lon) };
			b = { sphere.radius * std::cos(lat + (pi / float(kSubdivision))) * std::cos(lon)    ,sphere.radius * std::sin(lat + (pi / float(kSubdivision))),sphere.radius * std::cos(lat + (pi / float(kSubdivision))) * std::sin(lon) };
			c = { sphere.radius * std::cos(lat) * std::cos(lon + (2 * pi / float(kSubdivision))),sphere.radius * std::sin(lat)                             ,sphere.radius * std::cos(lat) * std::sin(lon + (2 * pi / float(kSubdivision))) };
			a = { a.x + sphere.center.x,a.y + sphere.center.y,a.z + sphere.center.z };
			b = { b.x + sphere.center.x,b.y + sphere.center.y,b.z + sphere.center.z };
			c = { c.x + sphere.center.x,c.y + sphere.center.y,c.z + sphere.center.z };


			//a,b,cをScureen座標まで変換
			Vector3 ndcGridA = Transform(a, viewProjectionMatrix);
			Vector3 ndcGridB = Transform(b, viewProjectionMatrix);
			Vector3 ndcGridC = Transform(c, viewProjectionMatrix);

			screenGridA = Transform(ndcGridA, viewportMatrix);
			screenGridB = Transform(ndcGridB, viewportMatrix);
			screenGridC = Transform(ndcGridC, viewportMatrix);
			//ac,bcで線を引く

			Novice::DrawLine(int(screenGridA.x), int(screenGridA.y), int(screenGridB.x), int(screenGridB.y), color);
			Novice::DrawLine(int(screenGridA.x), int(screenGridA.y), int(screenGridC.x), int(screenGridC.y), color);

		}
	}
}
//平面
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	//中心点
	Vector3 center = Multiply(plane.distance, plane.nomal);
	Vector3 perpendiculars[4];

	perpendiculars[0] = Nomalize(Perpendicular(plane.nomal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.nomal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };


	//中心点にそれぞれ定数倍してたす
	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(6.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), RED);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[1].x), int(points[1].y), GREEN);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[0].x), int(points[0].y), BLACK);

}
//ライン
void DrawLine(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	Vector3 origin = segment.origin;
	Vector3 diff = segment.diff;

	Vector3 ndcOri = Transform(origin, viewProjectionMatrix);
	Vector3 ndcDiff = Transform(diff, viewProjectionMatrix);

	Vector3 originScr = Transform(ndcOri, viewportMatrix);
	Vector3 diffScr = Transform(ndcDiff, viewportMatrix);


	Novice::DrawLine(int(originScr.x), int(originScr.y), int(diffScr.x), int(diffScr.y), color);
	//DrawSphere({ origin ,0.1f }, viewProjectionMatrix, viewportMatrix, RED);
	//DrawSphere({ diff ,0.1f }, viewProjectionMatrix, viewportMatrix, BLUE);
}
//三角形
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	Vector3 tri[3];
	tri[0] = triangle.vertices[0];
	tri[1] = triangle.vertices[1];
	tri[2] = triangle.vertices[2];
	Vector3 ndcTri[3];
	Vector3 scrTri[3];
	for (int i = 0; i < 3; i++) {
		ndcTri[i] = Transform(tri[i], viewProjectionMatrix);
		scrTri[i] = Transform(ndcTri[i], viewportMatrix);
	}

	Novice::DrawTriangle(
		int(scrTri[0].x), int(scrTri[0].y),
		int(scrTri[1].x), int(scrTri[1].y),
		int(scrTri[2].x), int(scrTri[2].y),
		color, kFillModeWireFrame);
}
void DrawBox(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	aabb.max;
	aabb.min;


	Vector3 aabb1[8];
	Vector3 aabbNdc[8];
	Vector3 aabbScr1[8];

	aabb1[0] = { aabb.min.x,aabb.min.y,aabb.min.z };
	aabb1[1] = { aabb.min.x,aabb.min.y,aabb.max.z };
	aabb1[2] = { aabb.min.x,aabb.max.y,aabb.min.z };
	aabb1[3] = { aabb.min.x,aabb.max.y,aabb.max.z };
	aabb1[4] = { aabb.max.x,aabb.min.y,aabb.min.z };
	aabb1[5] = { aabb.max.x,aabb.min.y,aabb.max.z };
	aabb1[6] = { aabb.max.x,aabb.max.y,aabb.min.z };
	aabb1[7] = { aabb.max.x,aabb.max.y,aabb.max.z };

	for (int i = 0; i < 8; i++) {
		aabbNdc[i] = Transform(aabb1[i], viewProjectionMatrix);
		aabbScr1[i] = Transform(aabbNdc[i], viewportMatrix);
	}


	Novice::DrawLine(int(aabbScr1[0].x), int(aabbScr1[0].y), int(aabbScr1[1].x), int(aabbScr1[1].y), color);
	Novice::DrawLine(int(aabbScr1[1].x), int(aabbScr1[1].y), int(aabbScr1[3].x), int(aabbScr1[3].y), color);
	Novice::DrawLine(int(aabbScr1[2].x), int(aabbScr1[2].y), int(aabbScr1[3].x), int(aabbScr1[3].y), color);
	Novice::DrawLine(int(aabbScr1[2].x), int(aabbScr1[2].y), int(aabbScr1[0].x), int(aabbScr1[0].y), color);

	Novice::DrawLine(int(aabbScr1[4].x), int(aabbScr1[4].y), int(aabbScr1[5].x), int(aabbScr1[5].y), color);
	Novice::DrawLine(int(aabbScr1[5].x), int(aabbScr1[5].y), int(aabbScr1[7].x), int(aabbScr1[7].y), color);
	Novice::DrawLine(int(aabbScr1[7].x), int(aabbScr1[7].y), int(aabbScr1[6].x), int(aabbScr1[6].y), color);
	Novice::DrawLine(int(aabbScr1[6].x), int(aabbScr1[6].y), int(aabbScr1[4].x), int(aabbScr1[4].y), color);

	Novice::DrawLine(int(aabbScr1[0].x), int(aabbScr1[0].y), int(aabbScr1[4].x), int(aabbScr1[4].y), color);
	Novice::DrawLine(int(aabbScr1[1].x), int(aabbScr1[1].y), int(aabbScr1[5].x), int(aabbScr1[5].y), color);
	Novice::DrawLine(int(aabbScr1[2].x), int(aabbScr1[2].y), int(aabbScr1[6].x), int(aabbScr1[6].y), color);
	Novice::DrawLine(int(aabbScr1[3].x), int(aabbScr1[3].y), int(aabbScr1[7].x), int(aabbScr1[7].y), color);

}

void DrawBezier(const Vector3 controlPoint0, const Vector3 controlPoint1, const Vector3 controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const int SPLIT = 8;
	Vector3 bezier0[SPLIT];
	Vector3 bezier1[SPLIT];
	Vector3 scrbezier0[SPLIT];
	Vector3 scrbezier1[SPLIT];
	//ライン
	for (int index = 0; index < SPLIT; index++) {
		float t0 = index / float(SPLIT);
		float t1 = (index + 1) / float(SPLIT);

		bezier0[index] = Bezier(controlPoint0, controlPoint1, controlPoint2, t0);
		bezier1[index] = Bezier(controlPoint0, controlPoint1, controlPoint2, t1);
	
		scrbezier0[index] = Transform(Transform(bezier0[index], viewProjectionMatrix), viewportMatrix);
		scrbezier1[index] = Transform(Transform(bezier1[index], viewProjectionMatrix), viewportMatrix);
	
		Novice::DrawLine(int(scrbezier0[index].x), int(scrbezier0[index].y), int(scrbezier1[index].x), int(scrbezier1[index].y), color);

	}
	ImGui::Begin("Bezier");
	ImGui::InputFloat3("0", &bezier0[0].x);
	ImGui::InputFloat3("1", &bezier0[0].x);
	ImGui::InputFloat3("2", &bezier0[0].x);
	ImGui::InputFloat3("3", &bezier0[0].x);
	ImGui::InputFloat3("4", &bezier0[0].x);
	ImGui::InputFloat3("5", &bezier0[0].x);
	ImGui::InputFloat3("6", &bezier0[0].x);
	ImGui::InputFloat3("7", &bezier0[0].x);
	ImGui::End();

};


Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	float v2length = Dot(v2, v2);

	float dot = Dot(v1, v2);


	result.x = dot / v2length * v2.x;
	result.y = dot / v2length * v2.y;
	result.z = dot / v2length * v2.z;


	return result;
}


Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	Vector3 result{};
	Vector3 d = {
		segment.diff.x - segment.origin.x,
		segment.diff.y - segment.origin.y,
		segment.diff.z - segment.origin.z };
	Vector3 v = {
		point.x - segment.origin.x,
		point.y - segment.origin.y,
		point.z - segment.origin.z };


	float dot = Dot(d, d);
	if (dot == 0.0f) {
		return segment.origin;
	}

	float t = Dot(v, d) / dot;

	t = Clanp(t);

	result.x = segment.origin.x + d.x * t;
	result.y = segment.origin.y + d.y * t;
	result.z = segment.origin.z + d.z * t;

	return result;
}
//
Vector3 ClosestPointAABBSphere(const Sphere& sphere, const AABB& aabb)
{
	Vector3 closestPoint;
	closestPoint.x = Clamp(sphere.center.x, aabb.min.x, aabb.max.x);
	closestPoint.y = Clamp(sphere.center.y, aabb.min.y, aabb.max.y);
	closestPoint.z = Clamp(sphere.center.z, aabb.min.z, aabb.max.z);

	return closestPoint;
}
//衝突判定(球と球)
bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	Vector3 result{};
	float isDistance = false;

	result.x = s2.center.x - s1.center.x;
	result.y = s2.center.y - s1.center.y;
	result.z = s2.center.z - s1.center.z;

	float distance = Length(result);

	if (distance <= s2.radius + s1.radius) {

		isDistance = true;

	}
	else {

		isDistance = false;

	}

	return isDistance;
}
//衝突判定(球と平面)
bool IsCollision(const Sphere& sphere, const Plane& plane)
{
	//フラグ
	//float isDistance = false;

	Vector3 dis = Nomalize(plane.nomal);

	float distance = Dot(sphere.center, dis) - plane.distance;
	//float d = plane.distance;

	//法線と平面上の任意の1点から求める
	//float d = Dot(sphere.center,plane.nomal) - plane.distance;

	//float k = Dot(plane.nomal, sphere.center) - d;

	//float kLength = Length(k);

	//K = kLength;

	//if (kLength <= sphere.radius) {
	//	isDistance = true;
	//}
	//else {
	//	isDistance = false;
	//}
	//return isDistance;


	return std::abs(distance) < sphere.radius;
}
//衝突判定(線と平面)
bool IsCollision(const Segment& segment, const Plane& plane)
{
	Vector3 diff = Subtract(segment.diff, segment.origin);


	//まず垂直判定を行うために、法線と線の内積を求める
	float dot = Dot(plane.nomal, diff);

	// 垂直=平行であるので、衝突しているはずがない
	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.nomal)) / dot;


	//Vector3 v;
	// tの値と線の種類によって衝突しているかを判断する
	//v = Multiply(Add(segment.origin, { t,t,t }), segment.diff);

	ImGui::Begin("t");
	ImGui::DragFloat("t", &t);
	ImGui::End();


	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}
	return false;
}

//三角形と線の衝突判定
bool IsCollision(const Triangle& triangle, const Segment& segment) {
	Vector3 diff = Subtract(segment.diff, segment.origin);


	//三点の位置から平面を求める
	Plane plane = PlaneFromPoints(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);


	float dot = Dot(plane.nomal, diff);

	// 垂直=平行であるので、衝突しているはずがない
	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.nomal)) / dot;


	Vector3 p = { segment.origin.x + t * diff.x, segment.origin.y + t * diff.y, segment.origin.z + t * diff.z };

	Vector3 v01 = Subtract(triangle.vertices[0], triangle.vertices[1]);
	Vector3 v12 = Subtract(triangle.vertices[1], triangle.vertices[2]);
	Vector3 v20 = Subtract(triangle.vertices[2], triangle.vertices[0]);

	Vector3 v0p = Subtract(triangle.vertices[0], p);
	Vector3 v1p = Subtract(triangle.vertices[1], p);
	Vector3 v2p = Subtract(triangle.vertices[2], p);

	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);


	float dot01 = Dot(cross01, plane.nomal);
	float dot12 = Dot(cross12, plane.nomal);
	float dot20 = Dot(cross20, plane.nomal);

	ImGui::Begin("t");
	ImGui::DragFloat("t", &t);
	ImGui::DragFloat("dot01", &dot01);
	ImGui::DragFloat("dot12", &dot12);
	ImGui::DragFloat("dot20", &dot20);
	ImGui::End();



	if (Dot(cross01, plane.nomal) >= 0.0f &&
		Dot(cross12, plane.nomal) >= 0.0f &&
		Dot(cross20, plane.nomal) >= 0.0f) {
		// 線分の始点と終点が三角形の面のどちら側にあるかを判定
		if (t >= 0.0f && t <= 1.0f) {
			return true;
		}
	}

	return false;
}
//
bool IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {

		return true;
	}

	return false;
}
//
bool IsCollision(const AABB& aabb, const Sphere& sphere)
{
	Vector3 closestPoint = ClosestPointAABBSphere(sphere, aabb);

	float dist = Distance(sphere.center, closestPoint);

	if (dist <= sphere.radius) {
		return true;
	}
	else {
		return false;
	}
}
//四角形と線の衝突判定
bool IsCollision(const AABB& aabb, const Segment& segment)
{
	//点がAABB内にあるなら
	if (IsPointInsideAABB(segment.origin, aabb) || IsPointInsideAABB(segment.diff, aabb)) {

		return true;
	}

	Plane planeX1, planeY1, planeZ1;
	planeX1.nomal = { 1,0,0 };
	planeY1.nomal = { 0,1,0 };
	planeZ1.nomal = { 0,0,1 };

	Vector3 diff = Subtract(segment.diff, segment.origin);

	float dotX = Dot(planeX1.nomal, diff);
	float dotY = Dot(planeY1.nomal, diff);
	float dotZ = Dot(planeZ1.nomal, diff);


	// 特異点チェック: 線分が軸に平行である場合
	if (std::abs(dotX) < 1e-6) {
		if (segment.origin.x < aabb.min.x || segment.origin.x > aabb.max.x) return false;
	}
	if (std::abs(dotY) < 1e-6) {
		if (segment.origin.y < aabb.min.y || segment.origin.y > aabb.max.y) return false;
	}
	if (std::abs(dotZ) < 1e-6) {
		if (segment.origin.z < aabb.min.z || segment.origin.z > aabb.max.z) return false;
	}


	Vector3 tMin, tMax;

	tMin.x = (aabb.min.x - Dot(segment.origin, planeX1.nomal)) / dotX;
	tMin.y = (aabb.min.y - Dot(segment.origin, planeY1.nomal)) / dotY;
	tMin.z = (aabb.min.z - Dot(segment.origin, planeZ1.nomal)) / dotZ;

	tMax.x = (aabb.max.x - Dot(segment.origin, planeX1.nomal)) / dotX;
	tMax.y = (aabb.max.y - Dot(segment.origin, planeY1.nomal)) / dotY;
	tMax.z = (aabb.max.z - Dot(segment.origin, planeZ1.nomal)) / dotZ;


	Vector3 tNear, tFar;

	tNear.x = min(tMin.x, tMax.x);
	tNear.y = min(tMin.y, tMax.y);
	tNear.z = min(tMin.z, tMax.z);
	tFar.x = max(tMin.x, tMax.x);
	tFar.y = max(tMin.y, tMax.y);
	tFar.z = max(tMin.z, tMax.z);


	// AABBとの衝突点(貫通点)のtが小さい方
	float tmin = max(max(tNear.x, tNear.y), tNear.z);

	// AABBとの衝突点(貫通点)のtが大きい方
	float tmax = min(min(tFar.x, tFar.y), tFar.z);

	if (tmin <= tmax) {
		return true;
	}


	return false;
}

//
Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}
//
Plane PlaneFromPoints(const Vector3& p1, const Vector3& p2, const Vector3& p3) {
	Plane result;

	// ベクトルを計算
	Vector3 v1 = Subtract(p2, p1);
	Vector3 v2 = Subtract(p3, p1);

	// 法線を計算
	result.nomal = Cross(v1, v2);

	// 距離を計算
	result.distance = Dot(result.nomal, p1);

	return result;
};
//マウス
void Mouse(Vector3& cameraPosition)
{
	Vector3 came = cameraPosition;





	if (0 != Novice::IsTriggerMouse(0)) {
		//int sx, sy ;
		//Novice::GetMousePosition(&sx, &sy);
	}
	if (Novice::IsTriggerMouse(0)) {
		//int x, y;
		//Novice::GetMousePosition(&x, &y);

		/*int px = sx - x;
		int py = sx - x;

		cameraPosition.x  = came.x + px;
		cameraPosition.x = came.y + py;*/
	}
	else if (Novice::IsTriggerMouse(1)) {
	}

}

bool IsPointInsideAABB(const Vector3& point, const AABB& aabb) {
	return (point.x >= aabb.min.x && point.x <= aabb.max.x) &&
		(point.y >= aabb.min.y && point.y <= aabb.max.y) &&
		(point.z >= aabb.min.z && point.z <= aabb.max.z);
}
