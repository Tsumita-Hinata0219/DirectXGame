#pragma once
#include "MyMath.h"


/// -------------------------------------------------------------------------
/// 2次元ベクトル
/// -------------------------------------------------------------------------
inline Vector2 operator+(const Vector2& v);
inline Vector2 operator-(const Vector2& v);
// 加算
inline Vector2 operator+(const Vector2& v, const float& n);
inline Vector2 operator+(const float& n, const Vector2& v);
inline Vector2 operator+(const Vector2& v1, const Vector2& v2);
inline Vector2& operator+=(Vector2& v1, const Vector2& v2);
// 減算
inline Vector2 operator-(const Vector2& v, const float& n);
inline Vector2 operator-(const float& n, const Vector2& v);
inline Vector2 operator-(const Vector2& v1, const Vector2& v2);
inline Vector2& operator-=(Vector2& v1, const Vector2& v2);
// 乗算
inline Vector2 operator*(const Vector2& v, const float& s);
inline Vector2 operator*(const float& s, const Vector2& v);
inline Vector2& operator*=(Vector2& v, const float& s);
inline Vector2 operator*(const Vector2& v1, const Vector2& v2);
inline Vector2& operator*=(Vector2& v1, const Vector2& v2);
// 除算
inline Vector2 operator/(const Vector2& v, const float& s);
inline Vector2 operator/(const float& s, const Vector2& v);
inline Vector2 operator/=(Vector2& v, const float& s);
inline Vector2 operator/(const Vector2& v1, const Vector2& v2);
inline Vector2& operator/=(Vector2& v1, const Vector2& v2);
// 内積
inline float Dot(const Vector2& v1, const Vector2& v2);
// 外積
inline float Cross(const Vector2& v1, const Vector2& v2);
// 長さ
inline float Lenght(const Vector2& v);
// 正規化
inline Vector2 Normalize(const Vector2& v);
// 正射影ベクトル
inline Vector2 Project(const Vector2& v1, const Vector2& v2);
// 線形補間
inline Vector2 Lerp(const Vector2& start, const Vector2& end, const float t);





/// -------------------------------------------------------------------------
/// 3次元ベクトル
/// -------------------------------------------------------------------------
inline Vector3 operator+(const Vector3& v);
inline Vector3 operator-(const Vector3& v);
// 加算
inline Vector3 operator+(const Vector3& v, const float& n);
inline Vector3 operator+(const float& n, const Vector3& v);
inline Vector3 operator+(const Vector3& v1, const Vector3& v2);
inline Vector3& operator+=(Vector3& v1, const Vector3& v2);
// 減算
inline Vector3 operator-(const Vector3& v, const float& n);
inline Vector3 operator-(const float& n, const Vector3& v);
inline Vector3 operator-(const Vector3& v1, const Vector3& v2);
inline Vector3& operator-=(Vector3& v1, const Vector3& v2);
// 乗算
inline Vector3 operator*(const Vector3& v, const float& s);
inline Vector3 operator*(const float& s, const Vector3& v);
inline Vector3& operator*=(Vector3& v, const float& s);
inline Vector3 operator*(const Vector3& v1, const Vector3& v2);
inline Vector3& operator*=(Vector3& v1, const Vector3& v2);
// 除算
inline Vector3 operator/(const Vector3& v, const float& s);
inline Vector3 operator/(const float& s, const Vector3& v);
inline Vector3 operator/=(Vector3& v, const float& s);
inline Vector3 operator/(const Vector3& v1, const Vector3& v2);
inline Vector3& operator/=(Vector3& v1, const Vector3& v2);
// 内積
inline float Dot(const Vector3& v1, const Vector3& v2);
// 外積
inline Vector3 Cross(const Vector3& v1, const Vector3& v2);
// 長さ
inline float Lenght(const Vector3& v);
// 正規化
inline Vector3 Normalize(const Vector3& v);
// 正射影ベクトル
inline Vector3 Project(const Vector3& v1, const Vector3& v2);
// 線形補間
inline Vector3 Lerp(const Vector3& start, const Vector3& end, const float t);
// 最近接線
inline Vector3 ClosestPoint(const Vector3& p, const Segment& s);
// 法線ベクトル
inline Vector3 Perpendicular(const Vector3& v);





/// -------------------------------------------------------------------------
/// 3x3行列
/// -------------------------------------------------------------------------
inline Matrix3x3 operator+(const Matrix3x3& m);
inline Matrix3x3 operator-(const Matrix3x3& m);
// 加算
inline Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2);
inline Matrix3x3& operator+=(Matrix3x3& m1, const Matrix3x3& m2);
// 減算
inline Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2);
inline Matrix3x3& operator-=(Matrix3x3& m1, const Matrix3x3& m2);
// 乗算
inline Matrix3x3 operator*(const Matrix3x3& m, const float& s);
inline Matrix3x3 operator*(const float& s, const Matrix3x3& m);
inline Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2);
inline Matrix3x3& operator*=(Matrix3x3& m1, const Matrix3x3& m2);





/// -------------------------------------------------------------------------
/// 4x4行列
/// -------------------------------------------------------------------------
inline Matrix4x4 operator+(const Matrix4x4& m);
inline Matrix4x4 operator-(const Matrix4x4& m);
// 加算
inline Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
inline Matrix4x4& operator+=(Matrix4x4& m1, const Matrix4x4& m2);
// 減算
inline Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
inline Matrix4x4& operator-=(Matrix4x4& m1, const Matrix4x4& m2);
// 乗算
inline Matrix4x4 operator*(const Matrix4x4& m, const float& s);
inline Matrix4x4 operator*(const float& s, const Matrix4x4& m);
inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
inline Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2);





/// -------------------------------------------------------------------------
/// クォータニオン
/// -------------------------------------------------------------------------
inline Quaternion operator+(const Quaternion& q);
inline Quaternion operator-(const Quaternion& q);
// 加算
inline Quaternion operator+(const Quaternion& q, const float& n);
inline Quaternion operator+(const float& n, const Quaternion& q);
inline Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
inline Quaternion& operator+=(Quaternion& q1, const Quaternion& q2);
// 減算
inline Quaternion operator-(const Quaternion& q, const float& n);
inline Quaternion operator-(const float& n, const Quaternion& q);
inline Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
inline Quaternion& operator-=(Quaternion& q1, const Quaternion& q2);
// 乗算
inline Quaternion operator*(const Quaternion& q, const float& s);
inline Quaternion operator*(const float& s, const Quaternion& q);
inline Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
inline Quaternion& operator*=(Quaternion& q1, const Quaternion& q2);





































