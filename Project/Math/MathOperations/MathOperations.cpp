#include "MathOperations.h"



/// -------------------------------------------------------------------------
/// 2次元ベクトル
/// -------------------------------------------------------------------------
inline Vector2 operator+(const Vector2& v) {
	return { +v.x, +v.y };
}
inline Vector2 operator-(const Vector2& v) {
	return { -v.x, -v.y };
}

// 加算
inline Vector2 operator+(const Vector2& v, const float& n) {
	return { v.x + n, v.y + n };
}
inline Vector2 operator+(const float& n, const Vector2& v) {
	return { v.x + n, v.y + n };
}
inline Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}
inline Vector2& operator+=(Vector2& v1, const Vector2& v2) {
	return v1 = v1 + v2;
}

// 減算
inline Vector2 operator-(const Vector2& v, const float& n) {
	return { v.x - n, v.y - n };
}
inline Vector2 operator-(const float& n, const Vector2& v) {
	return { v.x - n, v.y - n };
}
inline Vector2 operator-(const Vector2& v1, const Vector2& v2) {
	return { v1.x - v2.x, v1.y - v2.y };
}
inline Vector2& operator-=(Vector2& v1, const Vector2& v2) {
	return v1 = v1 - v2;
}

// 乗算
inline Vector2 operator*(const Vector2& v, const float& s) {
	return { v.x * s, v.y * s };
}
inline Vector2 operator*(const float& s, const Vector2& v) {
	return { v.x * s, v.y * s };
}
inline Vector2& operator*=(Vector2& v, const float& s) {
	return v = v * s;
}
inline Vector2 operator*(const Vector2& v1, const Vector2& v2) {
	return { v1.x * v2.x, v1.y * v2.y };
}
inline Vector2& operator*=(Vector2& v1, const Vector2& v2) {
	return v1 = v1 * v2;
}

// 除算
inline Vector2 operator/(const Vector2& v, const float& s) {
	return { v.x / s, v.y / s };
}
inline Vector2 operator/(const float& s, const Vector2& v) {
	return { v.x / s, v.y / s };
}
inline Vector2 operator/=(Vector2& v, const float& s) {
	return v = v / s;
}
inline Vector2 operator/(const Vector2& v1, const Vector2& v2) {
	return { v1.x / v2.x, v1.y / v2.y };
}
inline Vector2& operator/=(Vector2& v1, const Vector2& v2) {
	return v1 = v1 / v2;
}

// 内積
inline float Dot(const Vector2& v1, const Vector2& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

// 外積
inline float Cross(const Vector2& v1, const Vector2& v2) {
	return (v1.x * v2.y) - (v1.y * v2.x);
}

// 長さ
inline float Lenght(const Vector2& v) {
	return std::sqrt(Dot(v, v));
}

// 正規化
inline Vector2 Normalize(const Vector2& v) {
	return v * (1.0f / Lenght(v));
}

// 正射影ベクトル
inline Vector2 Project(const Vector2& v1, const Vector2& v2) {
	return Dot(v1, Normalize(v2)) * Normalize(v2);
}

// 線形補間
inline Vector2 Lerp(const Vector2& start, const Vector2& end, const float t) {
	return start + t * (end - start);
}




/// -------------------------------------------------------------------------
/// 3次元ベクトル
/// -------------------------------------------------------------------------
inline Vector3 operator+(const Vector3& v) {
	return { +v.x, +v.y, +v.z };
}
inline Vector3 operator-(const Vector3& v) {
	return { -v.x, -v.y, -v.z };
}

// 加算
inline Vector3 operator+(const Vector3& v, const float& n) {
	return { v.x + n, v.y + n, v.z + n };
}
inline Vector3 operator+(const float& n, const Vector3& v) {
	return { v.x + n, v.y + n, v.z + n };
}
inline Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}
inline Vector3& operator+=(Vector3& v1, const Vector3& v2) {
	return v1 = v1 + v2;
}

// 減算
inline Vector3 operator-(const Vector3& v, const float& n) {
	return { v.x - n, v.y - n, v.z - n };
}
inline Vector3 operator-(const float& n, const Vector3& v) {
	return { v.x - n, v.y - n, v.z - n };
}
inline Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
inline Vector3& operator-=(Vector3& v1, const Vector3& v2) {
	return v1 = v1 - v2;
}

// 乗算
inline Vector3 operator*(const Vector3& v, const float& s) {
	return { v.x * s, v.y * s, v.z * s };
}
inline Vector3 operator*(const float& s, const Vector3& v) {
	return { v.x * s, v.y * s, v.z * s };
}
inline Vector3& operator*=(Vector3& v, const float& s) {
	return v = v * s;
}
inline Vector3 operator*(const Vector3& v1, const Vector3& v2) {
	return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}
inline Vector3& operator*=(Vector3& v1, const Vector3& v2) {
	return v1 = v1 * v2;
}

// 除算
inline Vector3 operator/(const Vector3& v, const float& s) {
	return { v.x / s, v.y / s, v.z / s };
}
inline Vector3 operator/(const float& s, const Vector3& v) {
	return { v.x / s, v.y / s, v.z / s };
}
inline Vector3 operator/=(Vector3& v, const float& s) {
	return v = v / s;
}
inline Vector3 operator/(const Vector3& v1, const Vector3& v2) {
	return { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
}
inline Vector3& operator/=(Vector3& v1, const Vector3& v2) {
	return v1 = v1 / v2;
}

// 内積
inline float Dot(const Vector3& v1, const Vector3& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

// 外積
inline Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	return { (v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x) };
}

// 長さ
inline float Lenght(const Vector3& v) {
	return std::sqrt(Dot(v, v));
}

// 正規化
inline Vector3 Normalize(const Vector3& v) {
	return v * (1.0f / Lenght(v));
}

// 正射影ベクトル
inline Vector3 Project(const Vector3& v1, const Vector3& v2) {
	return Dot(v1, Normalize(v2)) * Normalize(v2);
}

// 線形補間
inline Vector3 Lerp(const Vector3& start, const Vector3& end, const float t) {
	return start + t * (end - start);
}

// 最近接線
inline Vector3 ClosestPoint(const Vector3& p, const Segment& s) {
	float length = Lenght(p);
	Vector3 normalize = Normalize(p);
	float dist = Dot((p - s.origin), normalize);
	dist = std::clamp(dist, 0.0f, length);
	Vector3 proj = dist * normalize;
	return s.origin + proj;
}

// 法線ベクトル
inline Vector3 Perpendicular(const Vector3& v) {
	if (v.x != 0.0f || v.y != 0.0f) {
		return { -v.y, v.x, 0.0f };
	}
	return { 0.0f, -v.z, v.y };
}





/// -------------------------------------------------------------------------
/// 3x3行列
/// -------------------------------------------------------------------------
inline Matrix3x3 operator+(const Matrix3x3& m) {
	return {
		+m.m[0][0], +m.m[0][1], +m.m[0][2],
		+m.m[1][0], +m.m[1][1], +m.m[1][2],
		+m.m[2][0], +m.m[2][1], +m.m[2][2] };
}
inline Matrix3x3 operator-(const Matrix3x3& m) {
	return {
		-m.m[0][0], -m.m[0][1], -m.m[0][2],
		-m.m[1][0], -m.m[1][1], -m.m[1][2],
		-m.m[2][0], -m.m[2][1], -m.m[2][2] };
}

// 加算
inline Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2) {
	return {
		m1.m[0][0] + m2.m[0][0], m1.m[0][1] + m2.m[0][1], m1.m[0][2] + m2.m[0][2],
		m1.m[1][0] + m2.m[1][0], m1.m[1][1] + m2.m[1][1], m1.m[1][2] + m2.m[1][2],
		m1.m[2][0] + m2.m[2][0], m1.m[2][1] + m2.m[2][1], m1.m[2][2] + m2.m[2][2] };
}
inline Matrix3x3& operator+=(Matrix3x3& m1, const Matrix3x3& m2) {
	return m1 = m1 + m2;
}

// 減算
inline Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2) {
	return {
		m1.m[0][0] - m2.m[0][0], m1.m[0][1] - m2.m[0][1], m1.m[0][2] - m2.m[0][2],
		m1.m[1][0] - m2.m[1][0], m1.m[1][1] - m2.m[1][1], m1.m[1][2] - m2.m[1][2],
		m1.m[2][0] - m2.m[2][0], m1.m[2][1] - m2.m[2][1], m1.m[2][2] - m2.m[2][2] };
}
inline Matrix3x3& operator-=(Matrix3x3& m1, const Matrix3x3& m2) {
	return m1 = m1 - m2;
}

// 乗算
inline Matrix3x3 operator*(const Matrix3x3& m, const float& s) {
	return {
		m.m[0][0] * s, m.m[0][1] * s, m.m[0][2] * s,
		m.m[1][0] * s, m.m[1][1] * s, m.m[1][2] * s,
		m.m[2][0] * s, m.m[2][1] * s, m.m[2][2] * s };
}
inline Matrix3x3 operator*(const float& s, const Matrix3x3& m) {
	return {
		m.m[0][0] * s, m.m[0][1] * s, m.m[0][2] * s,
		m.m[1][0] * s, m.m[1][1] * s, m.m[1][2] * s,
		m.m[2][0] * s, m.m[2][1] * s, m.m[2][2] * s };
}
inline Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2) {
	return {
		m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0],
		m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1],
		m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2],

		m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0],
		m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1],
		m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2],

		m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0],
		m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1],
		m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] };
}
inline Matrix3x3& operator*=(Matrix3x3& m1, const Matrix3x3& m2) {
	return m1 = m1 * m2;
}





/// -------------------------------------------------------------------------
/// 4x4行列
/// -------------------------------------------------------------------------
inline Matrix4x4 operator+(const Matrix4x4& m) {
	return {
		+m.m[0][0], +m.m[0][1], +m.m[0][2], +m.m[0][3],
		+m.m[1][0], +m.m[1][1], +m.m[1][2], +m.m[1][3],
		+m.m[2][0], +m.m[2][1], +m.m[2][2], +m.m[2][3],
		+m.m[3][0], +m.m[3][1], +m.m[3][2], +m.m[3][3] };
}
inline Matrix4x4 operator-(const Matrix4x4& m) {
	return {
		-m.m[0][0], -m.m[0][1], -m.m[0][2], -m.m[0][3],
		-m.m[1][0], -m.m[1][1], -m.m[1][2], -m.m[1][3],
		-m.m[2][0], -m.m[2][1], -m.m[2][2], -m.m[2][3],
		-m.m[3][0], -m.m[3][1], -m.m[3][2], -m.m[3][3] };
}

// 加算
inline Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) {
	return {
		m1.m[0][0] + m2.m[0][0], m1.m[0][1] + m2.m[0][1], m1.m[0][2] + m2.m[0][2], m1.m[0][3] + m2.m[0][3],
		m1.m[1][0] + m2.m[1][0], m1.m[1][1] + m2.m[1][1], m1.m[1][2] + m2.m[1][2], m1.m[1][3] + m2.m[1][3],
		m1.m[2][0] + m2.m[2][0], m1.m[2][1] + m2.m[2][1], m1.m[2][2] + m2.m[2][2], m1.m[2][3] + m2.m[2][3],
		m1.m[3][0] + m2.m[3][0], m1.m[3][1] + m2.m[3][1], m1.m[3][2] + m2.m[3][2], m1.m[3][3] + m2.m[3][3] };
}
inline Matrix4x4& operator+=(Matrix4x4& m1, const Matrix4x4& m2) {
	return m1 = m1 + m2;
}

// 減算
inline Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) {
	return {
		m1.m[0][0] - m2.m[0][0], m1.m[0][1] - m2.m[0][1], m1.m[0][2] - m2.m[0][2], m1.m[0][3] - m2.m[0][3],
		m1.m[1][0] - m2.m[1][0], m1.m[1][1] - m2.m[1][1], m1.m[1][2] - m2.m[1][2], m1.m[1][3] - m2.m[1][3],
		m1.m[2][0] - m2.m[2][0], m1.m[2][1] - m2.m[2][1], m1.m[2][2] - m2.m[2][2], m1.m[2][3] - m2.m[2][3],
		m1.m[3][0] - m2.m[3][0], m1.m[3][1] - m2.m[3][1], m1.m[3][2] - m2.m[3][2], m1.m[3][3] - m2.m[3][3] };
}
inline Matrix4x4& operator-=(Matrix4x4& m1, const Matrix4x4& m2) {
	return m1 = m1 - m2;
}

// 乗算
inline Matrix4x4 operator*(const Matrix4x4& m, const float& s) {
	return {
		m.m[0][0] * s, m.m[0][1] * s, m.m[0][2] * s, m.m[0][3],
		m.m[1][0] * s, m.m[1][1] * s, m.m[1][2] * s, m.m[1][3],
		m.m[2][0] * s, m.m[2][1] * s, m.m[2][2] * s, m.m[2][3],
		m.m[3][0] * s, m.m[3][1] * s, m.m[3][2] * s, m.m[3][3] };
}
inline Matrix4x4 operator*(const float& s, const Matrix4x4& m) {
	return {
		m.m[0][0] * s, m.m[0][1] * s, m.m[0][2] * s, m.m[0][3],
		m.m[1][0] * s, m.m[1][1] * s, m.m[1][2] * s, m.m[1][3],
		m.m[2][0] * s, m.m[2][1] * s, m.m[2][2] * s, m.m[2][3],
		m.m[3][0] * s, m.m[3][1] * s, m.m[3][2] * s, m.m[3][3] };
}
inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
	return {
		m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0],
		m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1],
		m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2],
		m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],

		m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0],
		m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1],
		m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2],
		m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],

		m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0],
		m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1],
		m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2],
		m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],

		m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0],
		m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1],
		m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2],
		m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3] };
}
inline Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2) {
	return m1 = m1 * m2;
}





/// -------------------------------------------------------------------------
/// クォータニオン
/// -------------------------------------------------------------------------
inline Quaternion operator+(const Quaternion& q) {
	return { +q.w, +q.x, +q.y, +q.z };
}
inline Quaternion operator-(const Quaternion& q) {
	return { -q.w, -q.x, -q.y, -q.z };
}

// 加算
inline Quaternion operator+(const Quaternion& q, const float& n) {
	return { q.w + n, q.x + n, q.y + n, q.z + n };
}
inline Quaternion operator+(const float& n, const Quaternion& q) {
	return { q.w + n, q.x + n, q.y + n, q.z + n };
}
inline Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
	return { q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z };
}
inline Quaternion& operator+=(Quaternion& q1, const Quaternion& q2) {
	return q1 = q1 + q2;
}

// 減算
inline Quaternion operator-(const Quaternion& q, const float& n) {
	return { q.w - n, q.x - n, q.y - n, q.z - n };
}
inline Quaternion operator-(const float& n, const Quaternion& q) {
	return { q.w - n, q.x - n, q.y - n, q.z - n };
}
inline Quaternion operator-(const Quaternion& q1, const Quaternion& q2) {
	return { q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z };
}
inline Quaternion& operator-=(Quaternion& q1, const Quaternion& q2) {
	return q1 = q1 - q2;
}

// 乗算
inline Quaternion operator*(const Quaternion& q, const float& s) {
	return { q.w * s, q.x * s, q.y * s, q.z * s };
}
inline Quaternion operator*(const float& s, const Quaternion& q) {
	return { q.w * s, q.x * s, q.y * s, q.z * s };
}
inline Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
	return {
		(q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z),
		(q1.y * q2.z) - (q1.z * q2.y) + (q1.w * q2.x) + (q1.x * q2.w),
		(q1.z * q2.x) - (q1.x * q2.z) + (q1.w * q2.y) + (q1.y * q2.w),
		(q1.x * q2.y) - (q1.y * q2.x) + (q1.w * q2.z) + (q1.z * q2.w) };
}
inline Quaternion& operator*=(Quaternion& q1, const Quaternion& q2) {
	return q1 = q1 * q2;
}








