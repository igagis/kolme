#pragma once

#include <array>

namespace r4{

template <class T, unsigned D, template <class, unsigned> class V> class vector_base :
		public std::array<T, D>
{
	template <class, unsigned> friend class vector;

	typedef std::array<T, D> base_type;

	vector_base(){}

	template <typename ...A, typename std::enable_if<sizeof...(A) == D, int>::type = 0> vector_base(A ...args) :
			base_type{{args...}}
	{}

public:

	/**
	 * @brief Convert to vector with different type of component.
	 * Convert this vector to a vector whose component type is different from T.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
     * @return converted vector.
     */
	template <class TT> V<TT, D> to()const noexcept{
		V<TT, D> ret;

		auto di = ret.begin();
		auto si = this->begin();
		for(; si != this->end(); ++si, ++di){
			*di = TT(*si);
		}

		return ret;
	}

};

template <class T, unsigned D> class vector : public vector_base<T, D, vector>{
	typedef vector_base<T, D, vector> base_type;
public:
	template <typename ...A, typename std::enable_if<sizeof...(A) == D, int>::type = 0> vector(A ...args) :
			base_type{args...}
	{}
};

}
