#pragma once
#include <Novice.h>
#include<cmath>
#include<assert.h>
#include<struct.h>

static const int kColumnWidth = 60;

static const int kRowHeight = 20;

//行列
struct Matrix4x4
{
	float m[4][4];
};

struct Vector3 {
	float x, y, z;


};

// 円
struct Sphere{
	Vector3 center; //!<中心点
	float radius;   //!<半径 
};

//平面
struct Plane {
	Vector3 nomal;  //!< 法線
	float distance; //!< 距離 
};


//直線
struct Line
{
	Vector3 origin; //!<始点
	Vector3 diff;   //!<終点への差分ベクトル
};
//半直線
struct Ray
{
	Vector3 origin; //!<始点
	Vector3 diff;   //!<終点への差分ベクトル
};
//線分
struct Segment
{
	Vector3 origin; //!<始点
	Vector3 diff;   //!<終点への差分ベクトル
};
//三角形
struct Triangle
{
	Vector3 vertices[3]; // !頂点
};
//AABB
struct AABB {
	Vector3 min; //!< 最小点
	Vector3 max; //!< 最大点
};
//ばね
struct Spring
{
	Vector3 anchor;      // アンカーの固定された端の位置
	float naturalLength; // 自然長
	float stiffness;     // 剛性。バネ定数k
	float dampingCoefficient; // 減衰係数
};
struct Ball {
	Vector3 position;		//位置
	Vector3 veloctiy;		//速度
	Vector3 acceleration;	//加速度
	float mass;				//質量
	float radius;			//半径
	unsigned int color;		//色
};
struct Pendulum {
	Vector3 anchor;				// アンカーポイント
	float length;				// 紐の長さ
	float angle;				// 現在の角度
	float angularVelocity;		// 角度ω
	float angularAcceleration;	// 角加速度
};




//
Vector3 Add(const Vector3& v1, const Vector3& v2);
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
//
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
//
float Dot(const Vector3& v1, const Vector3& v2);
//
float Length(const Vector3& v);
//
float Distance(const Vector3& point1, const Vector3& point2);
//
float Clanp(float t);
//
float Clamp(float value, float min, float max);
//
Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
//
Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t);

Vector3 Nomalize(const Vector3& v);
//行列の積
Matrix4x4 Multiply(const Matrix4x4& v1, const Matrix4x4& v2);

Vector3 Multiply(const Vector3& v1, const Vector3& v2);

Vector3 Multiply(const float& v2 , const Vector3& v1);
//移動行列
Matrix4x4 MakeTranslateMatrix(const  Vector3& translate);
//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const  Vector3& scale);
//回転行列X
Matrix4x4 MakeRotateXMatrix(float rotate);
//回転行列Y
Matrix4x4 MakeRotateYMatrix(float rotate);
//回転行列Z
Matrix4x4 MakeRotateZMatrix(float rotate);
//逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
//転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
//単位行列
Matrix4x4 Identity();
//アフィン変換
Matrix4x4 MakeAffineMatrixMatrix(const  Vector3& scale, const  Vector3& rotate, const  Vector3& translate);
//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//透視射影行列
Matrix4x4 MakePerspectiveFovMatrix(float forY, float aspectRatio, float nearClip, float farClip);
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float leht, float top, float width, float height, float minDepth, float maxDepth);
//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

Vector3 Cross(const Vector3& v1, const Vector3& v2);

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);
//線
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
//円
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
//
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
//ライン
void DrawLine(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
//
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
//
void DrawBox(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
//
void DrawBezier(const Vector3 controlPoint0, const Vector3 controlPoint1, const Vector3 controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
//
Vector3 Project(const Vector3& v1, const Vector3& v2);
//最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
//球と四角形に対する最近接点
Vector3 ClosestPointAABBSphere(const Sphere& sphere, const AABB& aabb);
//衝突判定(球と球)
bool IsCollision(const Sphere& s1, const Sphere& s2);
//衝突判定(球と平面)
bool IsCollision(const Sphere& sphere, const Plane& plane);
//衝突判定(線と平面)
bool IsCollision(const Segment& segment, const Plane& plane);
//三角形と線の衝突判定
bool IsCollision(const Triangle& triangle, const Segment& segment);
//四角形と四角形の衝突判定
bool IsCollision(const AABB& aabb1, const AABB& aabb2);
//四角形と球の衝突判定
bool IsCollision(const AABB& aabb, const Sphere& sphere);
//四角形と線の衝突判定
bool IsCollision(const AABB& aabb, const Segment& segment);
//
bool IsPointInsideAABB(const Vector3& point, const AABB& aabb);
//
Vector3 Perpendicular(const Vector3& vector);

Plane PlaneFromPoints(const Vector3& p1, const Vector3& p2, const Vector3& p3);
//マウス
void Mouse(Vector3& cameraPosition);



//// コンストラクタ
//Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
//
//// スカラー乗算
//Vector3& operator*=(float s) {
//    x *= s;
//    y *= s;
//    z *= s;
//    return *this;
//}

//// ベクトル引き算
//Vector3& operator-=(const Vector3& v) {
//    x -= v.x;
//    y -= v.y;
//    z -= v.z;
//    return *this;
//}
//
//// ベクトル加算
//Vector3& operator+=(const Vector3& v) {
//    x += v.x;
//    y += v.y;
//    z += v.z;
//    return *this;
//}
//
//// スカラー除算
//Vector3& operator/=(float s) {
//    x /= s;
//    y /= s;
//    z /= s;
//    return *this;
//}


















