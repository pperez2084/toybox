#pragma once

namespace math3d {

template<size_t Rows, size_t Cols, class T>
struct Matrix {
	Matrix() = delete;
};

/*
* Column or Row Vector?
* There is NO DISTINCTION here between column vectors and row vectors. All vectors
* are implemented as 1-Column matrices, which suggests they're "column vectors", but that's
* not meaningful.
* In particular:
*	-Getting the ith column of a matrix returns the same vector orientation as getting a row.
*	-For matrix multiplication, a vector v on the right in (Mv) is interpreted
*	 a column vector, a vector on the left in (vM), the v on the left is a row vector
*   -if you write the dot product of v an w as a matrix multiplication, the vector on the left will
*	 be interpreted as a row and the vector on the right will be a column.
*	-In the case that you want the outer product/dyad product of v and w,
*	 there is a particular function for that. (TODO make that function)
*	-You cannot explicitly transpose a vector
*/
template<size_t Dim, class T>
using Vec = Matrix<Dim, 1, T>;

}

//forward declarations of crossProduct so that they can be defined in Vec2, Vec3 interface
//Visual Studio intellisense is sometimes not happy about these cross product
//functions, but they compile fine
template<class T, class U, class R = decltype(T{} *U{}) >
constexpr R crossProduct(const math3d::Vec<2, T>& a, const math3d::Vec<2, U>& b);

template<class T, class U, class R = decltype(T{} *U{}) >
constexpr math3d::Vec<3, R> crossProduct(const math3d::Vec<3, T>& a, const math3d::Vec<3, U>& b);

namespace math3d {

template<size_t Place, class T>
struct VecUnpack {
	
};

template<class T>
struct VecUnpack<0, T> {
	template<size_t Rows, size_t Cols>
	static constexpr Matrix<Rows, Cols, T>::RowType get(const Matrix<Rows, Cols, T>& v) {
		static_assert(Rows > 0);
		return v.x;
	}

	template<size_t Rows, size_t Cols>
	static Matrix<Rows, Cols, T>::RowType& get(Matrix<Rows, Cols, T>& v) {
		static_assert(Rows > 0);
		return v.x;
	}
};

template<class T>
struct VecUnpack<1, T> {
	template<size_t Rows, size_t Cols>
	static constexpr Matrix<Rows, Cols, T>::RowType get(const Matrix<Rows, Cols, T>& v) {
		static_assert(Rows > 1);
		return v.y;
	}

	template<size_t Rows, size_t Cols>
	static Matrix<Rows, Cols, T>::RowType& get(Matrix<Rows, Cols, T>& v) {
		static_assert(Rows > 1);
		return v.y;
	}
};

template<class T>
struct VecUnpack<2, T> {
	template<size_t Rows, size_t Cols>
	static constexpr Matrix<Rows, Cols, T>::RowType get(const Matrix<Rows, Cols, T>& v) {
		static_assert(Rows > 2);
		return v.z;
	}

	template<size_t Rows, size_t Cols>
	static Matrix<Rows, Cols, T>::RowType& get(Matrix<Rows, Cols, T>& v) {
		static_assert(Rows > 2);
		return v.z;
	}
};

template<class T>
struct VecUnpack<3, T> {
	template<size_t Rows, size_t Cols>
	static constexpr Matrix<Rows, Cols, T>::RowType get(const Matrix<Rows, Cols, T>& v) {
		static_assert(Rows > 3);
		return v.w;
	}

	template<size_t Rows, size_t Cols>
	static Matrix<Rows, Cols, T>::RowType& get(Matrix<Rows, Cols, T>& v) {
		static_assert(Rows > 3);
		return v.w;
	}
};

/*
* 2-Vector
*/
template<class T>
struct Matrix<2, 1, T>{
	using RowType = T;

	T x = 0;
	T y = 0;

	template<class U>
	constexpr explicit operator Vec<2, U>() {
		return { x, y };
	}

	T operator[](size_t i) const{
		return &x[i];
	}

	template<size_t I>
	constexpr T get() const{
		return VecUnpack<I, T>::get(*this);
	}

	template<class U>
	constexpr decltype(::crossProduct(Vec<2, T>{}, Vec<2, U>{})) cross(const Vec<2, U>& u) const {
		return ::crossProduct(*this, u);
	}

	constexpr Vec<2, T> normal() const{
		return { -y, x };
	}
};

/*
* 3-Vector
*/
template<class T>
struct Matrix<3, 1, T>{
	using RowType = T;

	T x = 0;
	T y = 0;
	T z = 0;

	template<class U>
	constexpr explicit operator Vec<3, U>() {
		return { x, y, z };
	}

	T operator[](size_t i) const{
		return &x[i];
	}

	template<size_t I>
	constexpr T get() const {
		return VecUnpack<I, T>::get(*this);
	}

	template<class U>
	constexpr decltype(::crossProduct(Vec<3, T>{}, Vec<3, U>{})) cross(const Vec<3, U>& u) const {
		return ::crossProduct(*this, u);
	}
};

/*
* 4-Vector
*/
template<class T>
struct Matrix<4, 1, T>{
	using RowType = T;

	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;

	template<class U>
	constexpr explicit operator Vec<4, U>() {
		return { x, y, z, w };
	}

	T operator[](size_t i) const{
		return &x[i];
	}

	template<size_t I>
	constexpr T get() const {
		return VecUnpack<I, T>::get(*this);
	}
};

template<size_t Cols, class T>
struct Matrix<2, Cols, T> {
	using RowType = Vec<Cols, T>;

	RowType x = {};
	RowType y = {};

	template<size_t I>
	constexpr RowType get() const {
		return VecUnpack<I, T>::get(*this);
	}
};

template<size_t Cols, class T>
struct Matrix<3, Cols, T> {
	using RowType = Vec<Cols, T>;

	RowType x = {};
	RowType y = {};
	RowType z = {};

	template<size_t I>
	constexpr RowType get() const {
		return VecUnpack<I, T>::get(*this);
	}
};

template<size_t Cols, class T>
struct Matrix<4, Cols, T> {
	using RowType = Vec<Cols, T>;

	RowType x = {};
	RowType y = {};
	RowType z = {};
	RowType w = {};

	template<size_t I>
	constexpr RowType get() const {
		return VecUnpack<I, T>::get(*this);
	}
};

namespace componentwise {
	template<size_t Rows, size_t Cols, class T, class U, class R = decltype(T{} *U{}) >
	constexpr Matrix < Rows, Cols, R> operator*(const Matrix<Rows, Cols, T>& a, const Matrix<Rows, Cols, U>& b) {
		using Mult = MatrixArithmetic<Rows, Cols, T, U>::Multiply;
		return ComponentwiseOp<Rows - 1, Mult>::mmop(a, b);
	}
}

using componentwise::operator*;

//For scalar-matrix operations, parameter T is used for the matrix element type
//and parameter U is used for the scalar type
template<size_t Rows, size_t Cols, class T, class U>
struct MatrixArithmetic {
	using Mat_t = Matrix<Rows, Cols, T>;
	using Mat_u = Matrix<Rows, Cols, U>;
	using R_t = Mat_t::RowType;
	using R_u = Mat_u::RowType;


	struct Add {
		static constexpr decltype(R_t{} + R_u{}) value(const R_t &tRow, const R_u &uRow) {
			return tRow + uRow;
		}
	};

	struct Subtract {
		static constexpr decltype(R_t{} - R_u{}) value(const R_t &tRow, const R_u &uRow) {
			return tRow - uRow;
		}
	};

	struct Multiply {
		static constexpr decltype(R_t{} *R_u{}) value(const R_t &a, const R_u &b) {
			return a * b;
		}
	};

	struct ScalarMultiply {
		static constexpr R_t value(R_t vec, U scalar) {
			return static_cast<R_t>(vec * scalar);
		}
	};

	struct ScalarDivide {
		//here, parameter a will the vector component, b will be the scalar
		static constexpr R_t value(R_t vec, U scalar) {
			return static_cast<R_t>(vec / scalar);
		}
	};
};

/*
* When applied to a Matrix<Rows, Cols, T>, the starting case should be called with Place = Rows - 1
* When applied to a Vec<Dim, T>, the starting case should be called with Place = Dim - 1
*/
template<size_t Place, class Op>
struct ComponentwiseOp {
	using Succ = ComponentwiseOp<Place - 1, Op>;
	
	template<class T, class U>
	using RType = decltype(Op::value(T{}, U{}));

	//Matrix-Matrix operations
	//Recursive Case
	template<size_t Rows, size_t Cols, class T, class U, class... Tail>
	static constexpr Matrix<Rows, Cols, RType<T, U>> mmop(const Matrix<Rows, Cols, T>& a, const Matrix<Rows, Cols, U>& b, Tail... tail) {
		return Succ::mmop(a, b, Op::value(a.template get<Place>(), b.template get<Place>()), tail...);
	}

	//Matrix-Scalar operations
	//Recursive Case
	template<size_t Dim, class VType, class ScalarType, class... Ts>
	static constexpr Vec<Dim, VType> smop(const Vec<Dim, VType>& v, ScalarType s, Ts... ts) {
		return Succ::smop(v, s, Op::value(v.template get<Place>(), s), ts...);
	}
};

template<class Op>
struct ComponentwiseOp<0, Op> {
	template<class T, class U>
	using RType = decltype(Op::value(T{}, U{}));

	//Matrix-Matrix operations
	//Base case
	template<size_t Rows, size_t Cols, class T, class U, class... Tail>
	static constexpr Matrix<Rows, Cols, RType<T, U>> mmop(const Matrix<Rows, Cols, T>& a, const Matrix<Rows, Cols, U>& b, Tail... tail) {
		return { Op::value(a.template get<0>(), b.template get<0>()), tail... };
	}

	//Scalar-Vector Operations
	//Base case
	template<size_t Dim, class VType, class ScalarType, class... Ts>
	static constexpr Vec<Dim, VType> smop(const Vec<Dim, VType>& v, ScalarType s, Ts... ts) {
		return { Op::value(v.template get<0>(), s), ts... };
	}
};

template<size_t Place>
struct DotProdIteration {
	using Succ = DotProdIteration<Place - 1>;
	
	template<class T, class U>
	using RType = decltype(T{} *U{});

	//Recursive Case
	template<size_t Dim, class T, class U>
	static constexpr RType<T, U> dot(const Vec<Dim, T>& t, const Vec<Dim, U>& u) {
		return (t.template get<Place>() * u.template get<Place>()) + Succ::dot(t, u);
	}
	
	//defining both equals and notequals explicitly here until I get around to
	//verifying the compiler can apply demorgans to optimize whenever appropriate
	template<size_t Dim, class T, class U>
	static constexpr bool equals(const Vec<Dim, T>& t, const Vec<Dim, U>& u) {
		return (t.template get<Place>() == u.template get<Place>()) && Succ::equals(t, u);
	}

	template<size_t Dim, class T, class U>
	static constexpr bool notequals(const Vec<Dim, T>& t, const Vec<Dim, U>& u) {
		return (t.template get<Place>() != u.template get<Place>()) || Succ::notequals(t, u);
	}
};

template<>
struct DotProdIteration<0> {
	template<class T, class U>
	using RType = decltype(T{} *U{});

	//base case
	template<size_t Dim, class T, class U>
	static constexpr RType<T, U> dot(const Vec<Dim, T>& t, const Vec<Dim, U>& u) {
		return t.template get<0>() * u.template get<0>();
	}

	template<size_t Dim, class T, class U>
	static constexpr bool equals(const Vec<Dim, T>& t, const Vec<Dim, U>& u) {
		return t.template get<0>() == u.template get<0>();
	}

	template<size_t Dim, class T, class U>
	static constexpr bool notequals(const Vec<Dim, T>& t, const Vec<Dim, U>& u) {
		return t.template get<0>() != u.template get<0>();
	}
};

}

/*
* Matrix Addition and Subtraction
*/
template<size_t Rows, size_t Cols, class T, class U, class R = decltype(T{} + U{}) >
constexpr math3d::Matrix<Rows, Cols, R> operator+(const math3d::Matrix<Rows, Cols, T>& a, const math3d::Matrix<Rows, Cols, U>& b) {
	using Add = math3d::MatrixArithmetic<Rows, Cols, T, U>::Add;
	return math3d::ComponentwiseOp<Rows - 1, Add>::mmop(a, b);
}

template<size_t Rows, size_t Cols, class T, class U, class R = decltype(T{} - U{}) >
constexpr math3d::Matrix<Rows, Cols, R> operator-(const math3d::Matrix<Rows, Cols, T>& a, const math3d::Matrix<Rows, Cols, U>& b) {
	using Subtract = math3d::MatrixArithmetic<Rows, Cols, T, U>::Subtract;
	return math3d::ComponentwiseOp<Rows - 1, Subtract>::mmop(a, b);
}

/*
* Componentwise Multiplication (Hadamard Product)
* You can optionally use operator* as componentwiseProduct by
*	using math3d::componentwise::operator*;
*/
template<size_t Rows, size_t Cols, class T, class U, class R = decltype(T{} *U{}) >
constexpr math3d::Matrix < Rows, Cols, R> componentwiseProduct(const math3d::Matrix<Rows, Cols, T>& a, const math3d::Matrix<Rows, Cols, U>& b) {
	using Mult = math3d::MatrixArithmetic<Rows, Cols, T, U>::Multiply;
	return ComponentwiseOp<Rows - 1, Mult>::mmop(a, b);
}

/*
 * Scalar Multiplication:
 * Returns Vec of the same type as the Vec argument, regardless of scalar type
 */

template<size_t Rows, size_t Cols, class MType, class ScalarType>
constexpr math3d::Matrix<Rows, Cols, MType> operator*(ScalarType c, const math3d::Matrix<Rows, Cols, MType>& m) {
	using Multiply = math3d::MatrixArithmetic<Rows, Cols, MType, ScalarType>::ScalarMultiply;
	return math3d::ComponentwiseOp<Rows - 1, Multiply>::smop(m, c);
}

template<size_t Rows, size_t Cols, class MType, class ScalarType>
constexpr math3d::Matrix<Rows, Cols, MType> operator*(const math3d::Matrix<Rows, Cols, MType>& m, ScalarType c) {
	return operator*(c, m);
}

template<size_t Rows, size_t Cols, class MType, class ScalarType>
constexpr math3d::Matrix<Rows, Cols, MType> operator/(const math3d::Matrix<Rows, Cols, MType>& m, ScalarType c) {
	using Divide = math3d::MatrixArithmetic<Rows, Cols, MType, ScalarType>::ScalarDivide;
	return math3d::ComponentwiseOp<Rows - 1, Divide>::smop(m, c);
}

//////////////////////////////////////////////

/*
* Dot Product
* Actually, I don't know what the dot product of a Vec4 in homogeneous coordinates should be...
*	Well, it's still important for matrix operations, but maybe 3d vector products should also be here
*	for Vec4 in homogeneous coordinates?
*/
template<size_t Dim, class T, class U, class R = decltype(T{} *U{}) >
constexpr R dotProduct(const math3d::Vec<Dim, T>& a, const math3d::Vec<Dim, U>& b) {
	return math3d::DotProdIteration<Dim - 1>::dot(a, b);
}

template<size_t Dim, class T>
constexpr T lengthSquared(const math3d::Vec<Dim, T>& v) {
	return dotProduct(v, v);
}

template<size_t Dim, class T, class U>
constexpr bool operator!=(const math3d::Vec<Dim, T>& a, const math3d::Vec<Dim, U>& b) {
	return math3d::DotProdIteration<Dim - 1>::notequals(a, b);
}

template<size_t Dim, class T, class U>
constexpr bool operator==(const math3d::Vec<Dim, T>& a, const math3d::Vec<Dim, U>& b) {
	return math3d::DotProdIteration<Dim - 1>::equals(a, b);
}

/*
* Cross Product (2D)
*/
template<class T, class U, class R >
constexpr R crossProduct(const math3d::Vec<2, T>& a, const math3d::Vec<2, U>& b) {
	return a.x * b.y - a.y * b.x;
}

/*
* Cross Product (3D)
*/
template<class T, class U, class R >
constexpr math3d::Vec < 3, R > crossProduct(const math3d::Vec<3, T>& a, const math3d::Vec<3, U>& b) {
	return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}

/*
* Geometry metrics
*/
namespace std {
	//forward declarations to avoid inclusion of cmath here
	float sqrt(float);
	double sqrt(double);
	long double sqrt(long double);

	float atan2(float, float);
	double atan2(double, double);
	long double atan2(long double, long double);
}

template<class T>
using RootType = decltype(std::sqrt(T{}));
template<size_t Dim, class T>
RootType<T> length(const math3d::Vec<Dim, T>& v) {
	return std::sqrt(lengthSquared(v));
}

template<class T, class U>
using AngleType = decltype(std::atan2(T{} *U{}, T{} *U{}));
template<class T, class U>
AngleType<T, U> angle(const math3d::Vec<2, T>& t, const math3d::Vec<2, U>& u) {
	return std::atan2(crossProduct(t, u), dotProduct(t, u));
}

//You really want the angle and also the axis that angle is about,
//should be able to get the pair from another function
template<class T, class U>
AngleType<T, U> angle(const math3d::Vec<3, T>& t, const math3d::Vec<3, U>& u) {
	return atan2(length(crossProduct(t, u)), dotProduct(t, u));
}

template<size_t Dim, class T>
math3d::Vec<Dim, RootType<T>> unit(const math3d::Vec<Dim, T>& v) {
	return v / length(v);
}