#pragma once
#include "MyMath.h"


/// -------------------------------------------------------------------------
/// 2次元ベクトル
/// -------------------------------------------------------------------------
inline Vector2 operator+(const Vector2& v);
inline Vector2 operator-(const Vector2& v);
// 加算
inline Vector2 operator+(const Vector2& v1, const Vector2& v2);
inline Vector2& operator+=(Vector2& v1, const Vector2& v2);
// 減算
inline Vector2 operator-(const Vector2& v1, const Vector2& v2);
inline Vector2& operator-=(Vector2& v1, const Vector2& v2);
// 乗算
inline Vector2 operator*(const Vector2& v, const float& s);
inline Vector2 operator*(const float& s, const Vector2& v);
inline Vector2& operator*=(Vector2& v, const float& s);
// 除算
inline Vector2 operator/(const Vector2& v, const float& s);
inline Vector2 operator/(const float& s, const Vector2& v);
inline Vector2 operator/=(Vector2& v, const float& s);
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
inline Vector3 operator+(const Vector3& v1, const Vector3& v2);
inline Vector3& operator+=(Vector3& v1, const Vector3& v2);
// 減算
inline Vector3 operator-(const Vector3& v1, const Vector3& v2);
inline Vector3& operator-=(Vector3& v1, const Vector3& v2);
// 乗算
inline Vector3 operator*(const Vector3& v, const float& s);
inline Vector3 operator*(const float& s, const Vector3& v);
inline Vector3& operator*=(Vector3& v, const float& s);
// 除算
inline Vector3 operator/(const Vector3& v, const float& s);
inline Vector3 operator/(const float& s, const Vector3& v);
inline Vector3 operator/=(Vector3& v, const float& s);
// 内積
inline float Dot(const Vector3& v1, const Vector3& v2);
// 外積
inline float Cross(const Vector3& v1, const Vector3& v2);
// 長さ
inline float Lenght(const Vector3& v);
// 正規化
inline Vector3 Normalize(const Vector3& v);
// 正射影ベクトル
inline Vector3 Project(const Vector3& v1, const Vector3& v2);
// 線形補間
inline Vector3 Lerp(const Vector3& start, const Vector3& end, const float t);












































