#pragma once

#include <cmath>

template <unsigned N>
class Vector {
public:
	static Vector<N> zero();

	Vector();
	Vector(const float data[]);
	Vector(const Vector<N>& v);
	Vector<N>& operator = (const Vector<N>& v);

	float operator() (int i);
	float operator() (int i) const;

	//operators
	Vector<N> operator - ();
	Vector<N> operator + (const Vector<N>& v);
	Vector<N> operator - (const Vector<N>& v);

	Vector<N>& operator += (const Vector<N>& v);
	Vector<N>& operator -= (const Vector<N>& v);

	Vector<N> operator * (float c);
	Vector<N> operator / (float c);

	Vector<N>& operator *= (float c);
	Vector<N>& operator /= (float c);

	//inner product
	float operator* (const Vector<N>& v);

	//distance & length
	float norm();
	float distance(const Vector<N>& v);

	Vector<N> normalize();

private:
	float m_data[N];
};

template <unsigned N>
Vector<N> Vector<N>::zero() {
	Vector ret;

	for (int i = 0; i < N; i++)
		ret.m_data[i] = 0.0;

	return ret;
}

template <unsigned N>
Vector<N>::Vector() {
}

template <unsigned N>
Vector<N>::Vector(const float data[]) {
	for (int i = 0; i < N; i++)
		m_data[i] = data[i];
}

template <unsigned N>
Vector<N>::Vector(const Vector<N>& v) {
	*this = v;
}

template <unsigned N>
Vector<N>& Vector<N>::operator = (const Vector<N>& v) {
	for (int i = 0; i < N; i++)
		m_data[i] = v.m_data[i];

	return *this;
}

template <unsigned N>
float Vector<N>::operator () (int i) {
	return m_data[i];
}

template <unsigned N>
float Vector<N>::operator () (int i) const {
	return m_data[i];
}

template <unsigned N>
Vector<N> Vector<N>::operator - () {
	Vector ret;

	for (int i = 0; i < N; i++)
		ret.m_data[i] = -m_data[i];

	return ret;
}

template <unsigned N>
Vector<N> Vector<N>::operator + (const Vector<N>& v) {
	Vector ret;

	for (int i = 0; i < N; i++)
		ret.m_data[i] = m_data[i] + v.m_data[i];

	return ret;
}

template <unsigned N>
Vector<N> Vector<N>::operator - (const Vector<N>& v) {
	Vector ret;

	for (int i = 0; i < N; i++)
		ret.m_data[i] = m_data[i] - v.m_data[i];

	return ret;
}

template <unsigned N>
Vector<N>& Vector<N>::operator += (const Vector<N>& v) {
	for (int i = 0; i < N; i++)
		m_data[i] += v.m_data[i];

	return *this;
}

template <unsigned N>
Vector<N>& Vector<N>::operator -= (const Vector<N>& v) {
	for (int i = 0; i < N; i++)
		m_data[i] -= v.m_data[i];

	return *this;
}

template <unsigned N>
Vector<N> Vector<N>::operator * (float c) {
	Vector ret;

	for (int i = 0; i < N; i++)
		ret.m_data[i] = m_data[i] * c;

	return ret;
}

template <unsigned N>
Vector<N> Vector<N>::operator / (float c) {
	Vector ret;

	for (int i = 0; i < N; i++)
		ret.m_data[i] = m_data[i] / c;

	return ret;
}

template <unsigned N>
Vector<N>& Vector<N>::operator *= (float c) {
	for (int i = 0; i < N; i++)
		m_data[i] *= c;

	return *this;
}

template <unsigned N>
Vector<N>& Vector<N>::operator /= (float c) {
	for (int i = 0; i < N; i++)
		m_data[i] /= c;

	return *this;
}

template <unsigned N>
float Vector<N>::operator* (const Vector<N>& v) {
	float sum = 0;

	for (int i = 0; i < N; i++)
		sum += m_data[i] * v.m_data[i];

	return sum;
}

template <unsigned N>
float Vector<N>::norm() {
	return std::sqrt(*this * *this);
}

template <unsigned N>
float Vector<N>::distance(const Vector<N>& v) {
	return (*this - v).norm();
}

template <unsigned N>
Vector<N> Vector<N>::normalize() {
	return *this / this->norm();
}

template <unsigned N>
Vector<N> crossProduct(const Vector<N>& v1, const Vector<N>& v2) {
	float c0 = v1(1) * v2(2) - v1(2) * v2(1);
	float c1 = v1(2) * v2(0) - v1(0) * v2(2);
	float c2 = v1(0) * v2(1) - v1(1) * v2(0);

	float data[] = { c0, c1, c2 };
	return Vector(data);
}


typedef Vector<3> Point3f;
typedef Vector<2> Point2f;
