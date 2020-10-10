#pragma once

#include <iostream>
#include <array>

#include <utki/debug.hpp>
#include <utki/math.hpp>

#include "vector.hpp"

namespace r4{

template <class T> class vector3;

/**
 * @brief Two-dimensional vector class.
 */
template <class T> class vector<T, 2> : public vector_base<T, 2, vector>{
	typedef vector_base<T, 2, vector> base_type;
public:
	/**
	 * @brief 0th vector component.
	 */
	T& x()noexcept{
		return this->operator[](0);
	}

	/**
	 * @brief 0th vector component.
	 */
	const T& x()const noexcept{
		return this->operator[](0);
	}

	/**
	 * @brief 1th vector component.
	 */
	T& y()noexcept{
		return this->operator[](1);
	}

	/**
	 * @brief 1th vector component.
	 */
	const T& y()const noexcept{
		return this->operator[](1);
	}

	/**
	 * @brief default constructor.
	 * It does not initialize vector components.
	 * Their values are undefined right after construction.
	 */
	constexpr vector() = default;

	/**
	 * @brief Create vector with given values.
	 * @param x - x component of the vector.
	 * @param y - y component of the vector.
	 */
	constexpr vector(T x, T y)noexcept :
			base_type{x, y}
	{}

	/**
	 * @brief Create vector with given values.
	 * Creates a vector with all components initialized to a given value.
	 * @param xy - value to assign to all components of the vector.
	 */
	constexpr vector(T xy)noexcept :
			vector(xy, xy)
	{}

	/**
	 * @brief Create vector2 from vector3
	 * Creates a 2 dimensional vector and initializes its x and y components
	 * from x and y of given 3 dimensional vector.
	 * @param vec - 3 dimensional vector to copy x and y from.
	 */
	constexpr vector(const vector3<T>& vec)noexcept;

	/**
	 * @brief Assign value of given vector3 object.
	 * Note, the z component of given vector3 is ignored.
	 * @param vec - reference to the vector3 object to assign value from.
	 * @return reference to this vector2 object.
	 */
	vector& operator=(const vector3<T>& vec)noexcept;

	/**
	 * @brief Add vector2 and vector3.
	 * Note, the z component of given vector3 is ignored.
	 * @param vec - reference to the vector3 object to add.
	 * @return instance of the resulting vector2.
	 */
	vector operator+(const vector3<T>& vec)const noexcept;

	/**
	 * @brief Add and assign.
	 * Adds given vector2 and this vector2 and assigns the result to this vector2.
	 * @param vec - reference to the vector2 object to add.
	 * @return reference to this vector2 object.
	 */
	vector& operator+=(const vector& vec)noexcept{
		this->x() += vec.x();
		this->y() += vec.y();
		return *this;
	}

	/**
	 * @brief Add two vector2 vectors.
	 * @param vec - reference to the vector2 object to add.
	 * @return instance of the resulting vector2.
	 */
	vector operator+(const vector& vec)const noexcept{
		return (vector(*this) += vec);
	}

	/**
	 * @brief Add number to all vector components.
	 * @param num - number to add.
	 * @return resulting vector.
	 */
	vector operator+(T num)const noexcept{
		return vector{
			this->x() + num,
			this->y() + num
		};
	}

	/**
	 * @brief Subtract vector and assign.
	 * Subtracts given vector from this one and assigns result back to this vector.
     * @param vec - vector to subtract from this one.
     * @return Reference to this vector object.
     */
	vector& operator-=(const vector& vec)noexcept{
		this->x() -= vec.x();
		this->y() -= vec.y();
		return *this;
	}

	/**
	 * @brief Subtract vector.
     * @param vec - vector to subtract from this one.
     * @return Vector resulting from subtraction of given vector from this vector.
     */
	vector operator-(const vector& vec)const noexcept{
		return (vector(*this) -= vec);
	}

	/**
	 * @brief Subtract vector.
	 * Subtracts 3d vector from this 2d vector. 3rd component of subtracted vector is ignored, i.e.
	 * (this.x, this.y) - (x, y, z) = (this.x - x, this.y -y).
     * @param vec - vector to subtract from this one.
     * @return Resulting two-dimensional vector.
     */
	vector operator-(const vector3<T>& vec)const noexcept;

	/**
	 * @brief Unary minus.
	 * @return Vector resulting from negating this vector.
	 */
	vector operator-()const noexcept{
		return vector(-this->x(), -this->y());
	}

	/**
	 * @brief Multiply by scalar and assign.
	 * Multiplies this vector by scalar and assigns the result back to this vector.
     * @param num - scalar to multiply by.
     * @return Reference to this vector object.
     */
	vector& operator*=(T num)noexcept{
		this->x() *= num;
		this->y() *= num;
		return *this;
	}

	/**
	 * @brief Multiply by scalar.
	 * @param num - scalar to multiply by.
	 * @return Vector resulting from multiplication of this vector by given scalar.
	 */
	vector operator*(T num)const noexcept{
		return (vector(*this) *= num);
	}

	/**
	 * @brief Multiply scalar by vector.
     * @param num - scalar to multiply.
     * @param vec - vector to multiply by.
     * @return Vector resulting from multiplication of given scalar by given vector.
     */
	friend vector operator*(T num, const vector& vec)noexcept{
		return vec * num;
	}

	/**
	 * @brief Get component-wise minimum of two vectors.
	 * @param va - first vector.
	 * @param vb - second vector.
	 * @return vector2 whose components are component-wise minimum of initial vectors.
	 */
	friend vector min(const vector& va, const vector& vb)noexcept{
		using std::min;
		return vector{
				min(va[0], vb[0]),
				min(va[1], vb[1])
			};
	}

	/**
	 * @brief Get component-wise maximum of two vectors.
	 * @param va - first vector.
	 * @param vb - second vector.
	 * @return vector2 whose components are component-wise maximum of initial vectors.
	 */
	friend vector max(const vector& va, const vector& vb)noexcept{
		using std::max;
		return vector{
				max(va[0], vb[0]),
				max(va[1], vb[1])
			};
	}

	/**
	 * @brief Divide by scalar and assign.
	 * Divides this vector by scalar and assigns the result back to this vector.
     * @param num - scalar to divide by.
     * @return Reference to this vector object.
     */
	vector& operator/=(T num)noexcept{
		ASSERT(num != 0)
		this->x() /= num;
		this->y() /= num;
		return *this;
	}

	/**
	 * @brief Divide by scalar.
	 * @param num - scalar to divide this vector by.
	 * @return Vector resulting from dividing this vector by given scalar.
	 */
	vector operator/(T num)const noexcept{
		ASSERT(num != 0)
		return (vector(*this) /= num);
	}

	/**
	 * @brief Dot product.
	 * Dot product of this vector and a given vector.
	 * @return Dot product of two vectors (x1 * x2 + y1 * y2).
	 */
	T operator*(const vector& vec)const noexcept{
		return this->x() * vec.x() + this->y() * vec.y();
	}

	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of two vectors.
	 * Resulting vector is (x1 * x2, y1 * y2).
	 * The result of such operation is also vector.
     * @param vec - vector to multiply by.
     * @return Vector resulting from component-wise multiplication.
     */
	vector comp_mul(const vector& vec)const noexcept{
		return vector{
				this->x() * vec.x(),
				this->y() * vec.y()
			};
	}

	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of this vector by another given vector.
	 * See CompMul() for details.
     * @param vec - vector to multiply by.
     * @return reference to this vector2 instance.
     */
	vector& comp_multiply(const vector& vec)noexcept{
		this->x() *= vec.x();
		this->y() *= vec.y();
		return *this;
	}

	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of two vectors.
	 * Resulting vector is (x1 / x2, y1 / y2).
	 * The result of such operation is also vector.
     * @param v - vector to divide by.
     * @return Vector resulting from component-wise division.
     */
	vector comp_div(const vector& v)const noexcept{
		return vector{
				this->x() / v.x(),
				this->y() / v.y()
			};
	}

	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of this vector by another given vector.
	 * See CompDiv() for details.
     * @param v - vector to divide by.
     * @return reference to this vector2 instance.
     */
	vector& comp_divide(const vector& v)noexcept{
		this->x() /= v.x();
		this->y() /= v.y();
		return *this;
	}

	/**
	 * @brief Check if both vector components are zero.
	 * @return true if both vector components are zero.
	 * @return false otherwise.
	 */
	bool is_zero()const noexcept{
		return this->x() == 0 && this->y() == 0;
	}

	/**
	 * @brief Check if both vector components are positive or zero.
	 * @return true if both vector components are positive or zero.
	 * @return false otherwise.
	 */
	bool is_positive_or_zero()const noexcept{
		return this->x() >= 0 && this->y() >= 0;
	}

	/**
	 * @brief Check if both vector components are positive.
	 * @return true if both vector components are positive.
     * @return false otherwise.
     */
	bool is_positive()const noexcept{
		return this->x() > 0 && this->y() > 0;
	}

	/**
	 * @brief Check if both vector components are negative.
	 * @return true if both vector components are negative.
     * @return false otherwise.
     */
	bool is_negative()const noexcept{
		return this->x() < 0 && this->y() < 0;
	}

	/**
	 * @brief Negate this vector.
     * @return Reference to this vector object.
     */
	vector& negate()noexcept{
		// NOTE: this should be faster than (*this) = -(*this);
		this->x() = -this->x();
		this->y() = -this->y();
		return *this;
	}

	/**
	 * @brief Absolute vector value.
     * @return vector2 holding absolute values of this vector's components.
     */
	vector abs()const noexcept{
		using std::abs;
		return vector{
				abs(this->x()),
				abs(this->y())
			};
	}

	/**
	 * @brief Calculate power 2 of vector norm.
	 * @return Power 2 of this vector norm.
	 */
	T norm_pow2()noexcept{
		return utki::pow2(this->x()) + utki::pow2(this->y());
	}

	/**
	 * @brief Calculate norm of the vector.
	 * @return norm of this vector.
	 */
	T norm()noexcept{
		return T(std::sqrt(this->norm_pow2()));
	}

	/**
	 * @brief Normalize this vector.
	 * If the norm of vector is 0 then the result is vector (1, 0).
	 * @return Reference to this vector object.
	 */
	vector& normalize()noexcept{
		T mag = this->norm();
		if(mag == T(0)){
			this->x() = T(1);
			this->y() = T(0);
			return *this;
		}
		return (*this) /= this->norm();
	}

	/**
	 * @brief Calculate normalized vector.
	 * @return normalized vector.
	 */
	vector normed()const noexcept{
		return vector(*this).normalize();
	}

	/**
	 * @brief Set both vector components to given value.
	 * @param val - value to set vector components to.
	 * @return Reference to this vector object.
	 */
	vector& set(T val)noexcept{
		this->x() = val;
		this->y() = val;
		return *this;
	}

	/**
	 * @brief Rotate vector.
	 * Rotate this vector around (0, 0, 1) axis. Direction of the rotation is
	 * determined by right-hand rule. I.e. positive angle rotation is from X-axis to Y-axis.
     * @param angle - angle of rotation in radians.
     * @return Reference to this vector object.
     */
	vector& rotate(T angle)noexcept{
		using std::sin;
		using std::cos;
		T cosa = cos(angle);
		T sina = sin(angle);
		T tmp = this->x() * cosa - this->y() * sina;
		this->y() = this->y() * cosa + this->x() * sina;
		this->x() = tmp;
		return *this;
	}

	/**
	 * @brief Rotation of vector.
	 * Calculate vector resulting from rotation of this vector around (0, 0, 1) axis.
	 * Direction of the rotation is determined by right-hand rule.
	 * @param angle - angle of rotation in radians.
	 * @return Vector resulting from rotation of this vector.
	 */
	vector rot(T angle)const noexcept{
		return vector(*this).rotate(angle);
	}

	/**
	 * @brief Round vector components.
	 * @return rounded vector.
	 */
	friend vector round(const vector& v)noexcept{
		using std::round;
		return vector{
			round(v.x()),
			round(v.y())
		};
	}

	/**
	 * @brief Ceil vector components.
	 * @return ceiled vector.
	 */
	friend vector ceil(const vector& v)noexcept{
		using std::ceil;
		return vector{
			ceil(v.x()),
			ceil(v.y())
		};
	}

	/**
	 * @brief Floor vector components.
	 * @return floored vector.
	 */
	friend vector floor(const vector& v)noexcept{
		using std::floor;
		return vector{
			floor(v.x()),
			floor(v.y())
		};
	}

	friend std::ostream& operator<<(std::ostream& s, const vector<T, 2>& vec){
		s << "(" << vec.x() << ", " << vec.y() << ")";
		return s;
	}
};

}

#include "vector3.hpp"

namespace r4{

template <class T> constexpr vector<T, 2>::vector(const vector3<T>& vec)noexcept :
		vector{vec[0], vec[1]}
{}

template <class T> vector<T, 2>& vector<T, 2>::operator=(const vector3<T>& vec)noexcept{
	this->x() = vec.x();
	this->y() = vec.y();
	return *this;
}

template <class T> vector<T, 2> vector<T, 2>::operator+(const vector3<T>& vec)const noexcept{
	return vector{
			this->x() + vec.x(),
			this->y() + vec.y()
		};
}

template <class T> vector<T, 2> vector<T, 2>::operator-(const vector3<T>& vec)const noexcept{
	return vector{
			this->x() - vec.x(),
			this->y() - vec.y()
		};
}

template <class T> using vector2 = vector<T, 2>;

static_assert(sizeof(vector2<bool>) == sizeof(bool) * 2, "size mismatch");
static_assert(sizeof(vector2<int>) == sizeof(int) * 2, "size mismatch");
static_assert(sizeof(vector2<unsigned>) == sizeof(unsigned) * 2, "size mismatch");
static_assert(sizeof(vector2<float>) == sizeof(float) * 2, "size mismatch");
static_assert(sizeof(vector2<double>) == sizeof(double) * 2, "size mismatch");

}
