template <typename T>
class MatrixIterator;

template <typename T>
class ConstMatrixIterator;

struct InconsistentSizes {
    
}

struct NonconformantArguments {
    
}

template <typename It, typename Tag>
It advance_impl(It it, int n, Tag tag) {
    for (int i = 0; i < n; ++i)
        ++it;
    return it;    
}

template <typename It>
It advance_impl(It it, int n, std::random_access_iterator_category tag) {
    return it + n;
}

template <typename It>
It advance(It it, int n) {
    return advance_impl(it, n, typename It::iterator_category());
    /*if (......) { // It - итератор произвольного доступа
        return it + n;
    } else {
        for (int i = 0; i < n; ++i)
            ++it;
        return it;
    }*/
}

template <typename T>
class Matrix {
    std::vector<std::vector<T>> data;
    
    // std::vector<T> data;
    // T ** data;
    
public:
    void f() {
        
        Matrix<T>* const this;
    }
    
    void g() const {
        
        const Matrix<T>* const this;
        
    }


    Matrix(std::vector<std::vector<T>> _data): data(std::move(_data)) {
        // data = _data;
    }
    
    Matrix(size_t rows, size_t columns) {
        data.resize(rows, std::vector<T>(columns));
    }
    
    friend Matrix operator + (const Matrix& matrix1, const Matrix& matrix2) {
        auto sizes = matrix1.size();
        if (matrix2.size() != sizes) {
            throw InconsistentSizes();
        }
        Matrix res(sizes.first, sizes.second);
        for (size_t i = 0; i != sizes.first; ++i) {
            for (size_t j = 0; j != sizes.second; ++j) {
                res[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        return res;
    }
    
    Matrix operator*(const Matrix& b) const {
        if (cols() != b.rows())
            throw NonconformantArguments();
        Matrix c(rows(), b.cols());
        for (size_t i = 0; i < rows(); ++i)
            for (size_t j = 0; j < b.cols(); ++j) 
                for (size_t k = 0; k < cols(); ++k)
                    c[i][j] += (*this)[i][k] * b[k][j];
        return c;
    }
    
    std::pair<size_t, size_t> size() const {
        return (!data.empty() ? {data.size(), data[0].size()} : {0, 0});
    }
    
    size_t rows() const {
        return size().first;
    }
    
    size_t cols() const {
        return size().second;
    }
    
    std::vector<T>& operator[](size_t i) {
        return data[i];
    }
    
    const std::vector<T>& operator[](size_t i) const {
        return data[i];
    }
    
    MatrixIterator<T> begin() {
        return MatrixIterator<T>(*this, 0, 0);
    }
    
    MatrixIterator<T> end() {
        return MatrixIterator<T>(*this, rows(), 0);
    }
    
    ConstMatrixIterator<T> begin() const {
        return ConstMatrixIterator<T>(*this, 0, 0);
    }
    
    ConstMatrixIterator<T> end() const {
        return {*this, rows(), 0};
        //return ConstMatrixIterator<T>(*this, rows(), 0);
    }
    
    ConstMatrixIterator<T> cbegin() const {
        return ConstMatrixIterator<T>(*this, 0, 0);
    }
    
    ConstMatrixIterator<T> cend() const {
        return {*this, rows(), 0};
        //return ConstMatrixIterator<T>(*this, rows(), 0);
    }
};


template<typename T>
class ConstMatrixIterator {
    const Matrix<T>& matrix;
    size_t row, col;
    
public:
    ConstMatrixIterator(const Matrix<T>& _matrix, // <T>?
        size_t _row = 0,
        size_t _col = 0)
        : matrix(_matrix)
        , row(_row)
        , col(_col)
        {}
            
    ConstMatrixIterator<T>& operator++() {
        if (++col == matrix.cols()) {
            col = 0;
            ++row;
        }
        return *this;
    }
    
    ConstMatrixIterator<T> operator++(int) {
        auto temp = *this;
        ++(*this);
        return temp;
    }
    
    const T& operator *() const {
        return matrix[row][col];
    }
    
    friend bool operator == (const ConstMatrixIterator<T>& it1, const ConstMatrixIterator<T>& it2) {
        return it1.row == it2.row && it1.col == it2.col;
    }
    
    bool operator!=(const ConstMatrixIterator<T>& it1) const {
        return !((*this) == it1);
    }
};

template<typename T>
class MatrixIterator {
    Matrix<T>& matrix;
    size_t row, col;
    
public:
    MatrixIterator(Matrix<T>& _matrix, // <T>?
        size_t _row = 0,
        size_t _col = 0)
        : matrix(_matrix)
        , row(_row)
        , col(_col)
        {}
            
    MatrixIterator<T>& operator++() {
        if (++col == matrix.cols()) {
            col = 0;
            ++row;
        }
        return *this;
    }
    
    MatrixIterator<T> operator++(int) {
        auto temp = *this;
        ++(*this);
        return temp;
    }
    
    T& operator *() const {
        return matrix[row][col];
    }
    
    friend bool operator == (const MatrixIterator<T>& it1, const MatrixIterator<T>& it2) {
        return it1.row == it2.row && it1.col == it2.col;
    }
    
    bool operator!=(const MatrixIterator<T>& it1) const {
        return !((*this) == it1);
    }
};


int main() {
    Matrix<int> A = {{1, 2, 3}, {4, 5, 6}};   
    // for (auto it = A.begin(); it != A.end(); ++it) {
        // int x = *it;
        // ...
    // }
    for (int x : A) {
        std::cout << x << "\n";
    }
}ru
