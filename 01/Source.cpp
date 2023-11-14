#include <iostream>
#include <exception>
#include <algorithm>


template <typename T>
class Vector {
	size_t _capacity;
	size_t _size;
	T* data;
public:
	Vector() :_capacity(13), _size(0), data(new T[_capacity]{}) {}
	Vector(size_t arr_size) :_capacity(arr_size), _size(0), data(new T[_capacity]{}) {}
	Vector(size_t arr_size, T elem) :_capacity(arr_size), _size(0), data(new T[_capacity]{ elem }) {}
	Vector(const Vector<T>& other) :_capacity(other._capacity), _size(other._size), data(new T[_capacity]) {
		for (int i = 0; i < _capacity; ++i) {
			data[i] = other.data[i];
		}

	}
	Vector(Vector<T>&& other) :Vector(other) {
		other.data = NULL;
	}

	~Vector() {
		delete[] data;
	}

	Vector<T>& operator=(const Vector<T>& other) {
		if (this == other) {
			return *this;
		}
		this->_size = other._size;
		this->_capacity = other._capacity;
		data = new T[_capacity];

		for (int i = 0; i < _capacity; ++i) {
			data[i] = other.data[i];
		}

		return *this;
	}
	Vector<T>& operator=(Vector<T>&& other) {
		if (this == other) {
			return *this;
		}
		this->_size = other._size;
		this->_capacity = other._capacity;
		data = new T[_capacity];

		for (int i = 0; i < _capacity; ++i) {
			data[i] = other.data[i];
		}
		other.data = NULL;
		return *this;
	}

	size_t size() const {
		return _size;
	}
	size_t capacity() const {
		return _capacity;
	}

	bool empty() const {
		if (_size == 0)
			return true;
		return false;
	}

	T& operator[](size_t index) {
		return data[index];
	}
	const T& operator[](size_t index) const {
		//const_cast<Vector* tmp>(this)->[index];
		return data[index];
	}

	const T& at(size_t index) const {
		if (index > _size)
			throw std::out_of_range("Index is greater that size!");
		return data[index];
	}
	T& at(size_t index) {
		return data[index];
	}

	void push_back(const T& x) {
		if (_size == _capacity) {
			_capacity *= 2;
			auto tmp = new T[_capacity];
			for (int i = 0; i < _size; ++i) {
				tmp[i] = data[i];
			}
			delete[] data;
			data = tmp;
		}
		data[_size++] = x;
	}
	void push_back(T&& x) {
		if (_size == _capacity) {
			_capacity *= 2;
			auto tmp = new T[_capacity];
			for (int i = 0; i < _size; ++i) {
				tmp[i] = data[i];
			}
			delete[] data;
			data = tmp;
		}
		data[_size++] = std::move(x);
	}

	void pop_back() {
		if (_size == 0)
			return;
		else
			--_size;
	}

	void clear() {
		_size = 0;
		delete[] data;
	}
};

auto Exercise1(const Vector<int>& vec) {
	int N = vec.capacity();
	Vector <int> result(N);

	Vector<int> left_product(N,1);
	Vector<int> right_product(N, 1);

	for (int i = 1; i < n; ++i) {
		left_product[i] = left_product[i - 1] * nums[i - 1];
	}

	for (int i = n - 2; i >= 0; --i) {
		right_product[i] = right_product[i + 1] * nums[i + 1];
	}

	for (int i = 0; i < n; ++i) {
		result[i] = left_product[i] * right_product[i];
	}

	return result;
}

auto Exercise2(const Vector<Vector<int>>& matrix) {
	int N = matrix.size();
	int M = matrix[0].size();

	Vector<int>row_min(N, INT_MAX);
	Vector<int>col_max(M, INT_MIN);
	Vector<int> lucky_numbers;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			row_min[i] = std::min(row_min[i], matrix[i][j]);
			col_max[j] = std::max(col_max[j], matrix[i][j]);
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (matrix[i][j] == row_min[i] && matrix[i][j] == col_max[j]) {
				lucky_numbers.push_back(matrix[i][j]);
			}
		}
	}

	return lucky_numbers;
}

int main() {

}