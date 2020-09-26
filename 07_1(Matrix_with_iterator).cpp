#include <iostream>
#include <utility>
#include <vector>

template<typename It, typename Tag>
It advance_impl(It it, int n, Tag tag) {
    for (int i = 0; i < n; ++i)
        ++it;
    return it;
}

template<typename It>
It advance_impl(It it, int n, std::random_access_iterator_tag tag) {
    return it + n;
}

template<typename It>
It advance(It it, int n) {
    return advance_impl(it, n, typename It::iterator_category());
}

struct InconsistentSizes {
};

struct NonConformatArguments {
};

template<typename T>
class MatrixIterator;

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
public:
    Matrix(std::vector<std::vector<T>> _data): data(std::move(_data)){}

    Matrix(size_t rows, size_t columns) {
        data.resize(rows, std::vector<T>(columns));
    }

    Matrix operator+(const Matrix& matrix) const {
        auto matrixSize = matrix.size();
        if (size() != matrixSize)
            throw InconsistentSizes();
        Matrix res(matrixSize.first, matrixSize.second);
        for (size_t i = 0; i < matrixSize.first; ++i){
            for (size_t j = 0; j < matrixSize.second; ++j){
                res[i][j] = (*this)[i][j] + matrix[i][j];
            }
        }
        return res;
    };

    Matrix operator*(const Matrix& matrix) const {
        auto matrixSize = matrix.size();
        if (size().second != matrixSize.first)
            throw NonConformatArguments();
        Matrix res(size().first, matrixSize.second);
        for (size_t i = 0; i < size().first; ++i) {
            for (size_t j = 0; j < matrixSize.second; ++j) {
                for (size_t k = 0; k < matrixSize.first; ++k)
                res[i][j] += (*this)[i][k] + matrix[k][j];
            }
        }
        return res;
    };

    std::pair<size_t, size_t> size() const {
        if (!data.empty())
            return std::make_pair(data.size(), data[0].size());
        return {0, 0};
    }

    std::vector<T>& operator[](size_t i){
        return data[i];
    }

    const std::vector<T>& operator[](size_t i) const {
        return data[i];
    }

    MatrixIterator<T> begin() {
        return MatrixIterator<T>(*this, 0, 0);
    }

    MatrixIterator<T> end() {
        return MatrixIterator<T>(*this, size().second, 0);
    }
};

template<typename T>
class MatrixIterator {
private:
    Matrix<T>& matrix;
    size_t row, column;
public:
  MatrixIterator(Matrix<T>& _matrix, size_t _row = 0, size_t _column = 0)
      : matrix(_matrix)
      , row(_row)
      , column(_column)
  {}

  MatrixIterator<T>& operator++() {
      if (++column == matrix.size().second) {
          column = 0;
          ++row;
      }
      return *this;
  }

  MatrixIterator<T> operator++(int) {
      auto temp = *this;
      ++(*this);
      return temp;
  }

  T operator*() const {
      return matrix[row][column];
  }

  bool operator==(const MatrixIterator<T>& matrixIt) const {
      return row == matrixIt.row && column == matrixIt.column;
  }

  bool operator!=(const MatrixIterator<T>& matrixIt) const {
      return !((*this) == matrixIt);
  }
};

int main() {
    Matrix<int> A = std::vector<std::vector<int>>({{1, 2, 3}, {4, 5, 6}});
    for (int x: A) {
        std::cout<< x << '\n';
    }
    return 0;
}
