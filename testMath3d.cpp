#include "math3d.h"
#include <cassert>
#include <cmath>

using Vec2f = math3d::Vec<2, float>;
using Vec2i = math3d::Vec<2, int>;
using Vec3f = math3d::Vec<3, float>;
using Vec3i = math3d::Vec<3, int>;
using Vec4f = math3d::Vec<4, float>;

template<class VecType, class ScalarType>
void scalarProductCompileTest() {
	VecType vec{};
	ScalarType scalar{};
	VecType prod = scalar * vec;
	prod = vec * scalar;
	prod = vec / scalar;
}

template<class VType, class UType, class SumType>
void sumCompilesTest() {
	VType v{};
	UType u{};
	SumType sum = v + u;
	sum = u + v;
	sum = v - u;
	sum = u - v;
}

template<class VType, class UType, class ResultType>
void dotProductCompilesTest() {
	VType v{};
	UType u{};

	ResultType product = dotProduct(v, u);
	product = dotProduct(u, v);
}

template<size_t Dim, class T>
void dotProductInterfaceCompilesTest() {
	math3d::Vec<Dim, T> v{};
	math3d::Vec<Dim, T> u{};
	T product = v.dot(u);
	product = v.lengthSquared();
	product = v.length();
}

void pythagoreanTests() {
	constexpr Vec2f a = { 3, 0 };
	constexpr Vec2f b = { 0, 4 };
	constexpr Vec2f c = a + b;
	static_assert(lengthSquared(c) == 25.0);

	//check other right triangles of pythagorean triples
}

template<class T>
void constexprTests() {
	using Vec2 = math3d::Vec<2, T>;
	using Vec3 = math3d::Vec<3, T>;
	using Vec4 = math3d::Vec<4, T>;
	{
		constexpr Vec2 zero{};
		static_assert(sizeof(Vec2) == 2 * sizeof(T));
		static_assert(zero.x == 0);
		static_assert(zero.y == 0);
		static_assert(zero.get<0>() == 0);
		static_assert(zero.get<1>() == 0);
	}
	{
		constexpr Vec3 zero{};
		static_assert(sizeof(Vec3) == 3 * sizeof(T));
		static_assert(zero.x == 0);
		static_assert(zero.y == 0);
		static_assert(zero.z == 0);
		static_assert(zero.get<0>() == 0);
		static_assert(zero.get<1>() == 0);
		static_assert(zero.get<2>() == 0);
	}

	{
		constexpr Vec4 zero{};
		static_assert(sizeof(Vec4) == 4 * sizeof(T));
		static_assert(zero.x == 0);
		static_assert(zero.y == 0);
		static_assert(zero.z == 0);
		static_assert(zero.w == 0);
		static_assert(zero.get<0>() == 0);
		static_assert(zero.get<1>() == 0);
		static_assert(zero.get<2>() == 0);
		static_assert(zero.get<3>() == 0);
	}
}

template<size_t Dim, class T>
struct TestVec {
	//This struct is used to provide a vector of dimension Dim
	//with each component a different value
};

template<class T>
struct TestVec<2, T> {
	static constexpr math3d::Vec<2, T> value{ (T)1.1, (T)2.1 };
};

template<class T>
struct TestVec<3, T> {
	static constexpr math3d::Vec<3, T> value{ (T)1.1, (T)2.1, (T)3.1 };
};

template<class T>
struct TestVec<4, T> {
	static constexpr math3d::Vec<4, T> value{ (T)1.1, (T)2.1, (T)3.1, (T)4.1 };
};

template<size_t Dim, class T>
void equalsTest() {

	using Vec = math3d::Vec<Dim, T>;
	constexpr Vec a = TestVec<Dim, T>::value;
	constexpr Vec b = TestVec<Dim, T>::value;
	constexpr Vec zero{};
	static_assert(a == b);
	static_assert(b == a);
	static_assert((a == b) != (a != b));
	static_assert(zero == zero);
	static_assert((zero == zero) != (zero != zero));
	static_assert(a != zero);
	static_assert(b != zero);
	static_assert(zero != a);
	static_assert((a != zero) != (a == zero));
}

template<size_t Dim, class T>
void additiveIdentityTest() {
	using Vec = math3d::Vec<Dim, T>;
	constexpr Vec zero{};
	constexpr Vec a = TestVec<Dim, T>::value;
	static_assert(a + zero == a);
	static_assert(zero + a == a);
	static_assert(a - zero == a);
}

template<size_t Dim, class T>
void scalarMultIdentityTest() {
	using Vec = math3d::Vec<Dim, T>;
	constexpr Vec a = TestVec<Dim, T>::value;
	static_assert(1.0f * a == a);
	static_assert(a * 1.0f == a);
	static_assert(a / 1.0f == a);
	static_assert(1.0 * a == a);
	static_assert(a * 1.0 == a);
	static_assert(a / 1.0 == a);
	static_assert(1 * a == a);
	static_assert(a * 1 == a);
	static_assert(a / 1 == a);
}

template<class T, class U, class R>
void matrix2x2AdditionTest() {
	using MatT = math3d::Matrix<2, 2, T>;
	using MatU = math3d::Matrix<2, 2, U>;
	using MatR = math3d::Matrix<2, 2, R>;
	constexpr MatT a{ {1, 2}, {3, 4} };
	constexpr MatU b{ {10, 20}, {30, 40} };
	constexpr MatT zero{};
	constexpr MatR sum_ab = a + b;
	constexpr MatR sum_ba = b + a;
	static_assert(sum_ab.x.x == 11);
	static_assert(sum_ab.x.y == 22);
	static_assert(sum_ab.y.x == 33);
	static_assert(sum_ab.y.y == 44);
	static_assert(sum_ab.x.x == sum_ba.x.x);
	static_assert(sum_ab.x.y == sum_ba.x.y);
	static_assert(sum_ab.y.x == sum_ba.y.x);
	static_assert(sum_ab.y.y == sum_ba.y.y);

	constexpr MatR diff_ba = b - a;
	static_assert(diff_ba.x.x == 9);
	static_assert(diff_ba.x.y == 18);
	static_assert(diff_ba.y.x == 27);
	static_assert(diff_ba.y.y == 36);
}



int main() {
	//These expressions must compile
	constexprTests<float>();
	constexprTests<int>();
	constexprTests<double>();
	constexprTests<short>();

	//scalar product defined with same numeric type
	scalarProductCompileTest<Vec2f, float>();
	scalarProductCompileTest<Vec2i, int>();

	//scalar product defined with differing numeric types
	//scalar product conserves Vec type
	scalarProductCompileTest<Vec2f, int>();
	scalarProductCompileTest<Vec2i, float>();

	//sum commutes with same result type
	sumCompilesTest<Vec2i, Vec2i, Vec2i>();
	sumCompilesTest<Vec2f, Vec2f, Vec2f>();
	sumCompilesTest<Vec2f, Vec2i, Vec2f>();
	sumCompilesTest<Vec3f, Vec3f, Vec3f>();
	sumCompilesTest<Vec3i, Vec3i, Vec3i>();
	sumCompilesTest<Vec3f, Vec3i, Vec3f>();

	//dot product is defined
	dotProductCompilesTest<Vec2i, Vec2i, int>();
	dotProductCompilesTest<Vec3i, Vec3i, int>();
	dotProductCompilesTest<Vec2f, Vec2f, float>();
	dotProductCompilesTest<Vec3f, Vec3f, float>();
	dotProductCompilesTest<Vec3i, Vec3f, float>();

	pythagoreanTests();

	{
		//cross product defined for 2-Vec
		Vec2f v{}, u{};
		auto x = crossProduct(v, u);
		float f = v.cross(u);

		Vec2i iv{}, iu{};
		int i = iv.cross(iu);
	}
	{
		constexpr Vec2f v{};
		constexpr Vec2f normal = v.normal();
		static_assert(dotProduct(v, normal) == 0);
	}

	{
		constexpr Vec3f v{1, 0, 0}, u{0, 1, 0};
		constexpr Vec3f product = v.cross(u);
		static_assert(dotProduct(v, product) == 0);
		static_assert(dotProduct(u, product) == 0);
		static_assert(lengthSquared(v) * lengthSquared(u) == lengthSquared(product));
	}

	{
		constexpr Vec3f v{ 0, 1, 2 };
		constexpr Vec3f u{ 3, 4, 5 };
		constexpr Vec3f sum = v + u;
		static_assert(sum.x == 3);
		static_assert(sum.y == 5);
		static_assert(sum.z == 7);

	}

	//operator== and operator!= defined, need tests
	equalsTest<2, float>();
	equalsTest<3, float>();
	equalsTest<4, float>();
	equalsTest<2, int>();
	equalsTest<3, int>();
	equalsTest<4, int>();
	equalsTest<2, short>();
	equalsTest<3, short>();
	equalsTest<4, short>();
	equalsTest<2, double>();
	equalsTest<3, double>();
	equalsTest<4, double>();
	
	//arithmetic identity tests: a + {0}, a - {0}, 1 * a, a * 1, a / 1, {0} + a
	additiveIdentityTest<2, float>();
	additiveIdentityTest<3, float>();
	additiveIdentityTest<4, float>();
	additiveIdentityTest<2, int>();
	additiveIdentityTest<3, int>();
	additiveIdentityTest<4, int>();
	additiveIdentityTest<2, double>();
	additiveIdentityTest<3, double>();
	additiveIdentityTest<4, double>();
	additiveIdentityTest<2, short>();
	additiveIdentityTest<3, short>();
	additiveIdentityTest<4, short>();

	scalarMultIdentityTest<2, float>();
	scalarMultIdentityTest<3, float>();
	scalarMultIdentityTest<4, float>();
	scalarMultIdentityTest<2, int>();
	scalarMultIdentityTest<3, int>();
	scalarMultIdentityTest<4, int>();
	scalarMultIdentityTest<2, double>();
	scalarMultIdentityTest<3, double>();
	scalarMultIdentityTest<4, double>();
	scalarMultIdentityTest<2, short>();
	scalarMultIdentityTest<3, short>();
	scalarMultIdentityTest<4, short>();

	//arithmetic correctness tests: a + b, a - b, scalar * v, v * scalar, v / scalar
	//dot product, cross product
	//lengthSquared
	//length
	//unit(v)

	return 0;
}
