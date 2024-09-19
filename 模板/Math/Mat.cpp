using ll = long long;
template <typename T>
class Matrix {
public:
    std::vector<std::vector<T>> mat;
    int rows, cols;
    int mod;
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        mat.resize(rows, std::vector<T>(cols, 0));
    }
    Matrix(int rows, int cols, const T& initial) : rows(rows), cols(cols) {
        mat.resize(rows, std::vector<T>(cols, initial));
    }
    Matrix(const std::vector<std::vector<T>>& data) {
        rows = static_cast<int>(data.size());
        if (rows > 0) {
            cols = static_cast<int>(data[0].size());
            mat = data;
        } else {
            rows = 0;
            cols = 0;
        }
    }
    Matrix(const Matrix& other) {
        rows = other.rows;
        cols = other.cols;
        mat = other.mat;
    }
    //运算
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            mat = other.mat;
        }
        return *this;
    }

    Matrix operator+(const T& scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.mat[i][j] = mat[i][j] + scalar;
            }
        }
        return result;
    }
    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.mat[i][j] = mat[i][j] + other.mat[i][j];
            }
        }
        return result;
    }
    Matrix& operator+=(const Matrix& other) {
        *this = *this + other;
        return *this;
    }
    Matrix& operator+=(const T& scalar) {
        *this = *this + scalar;
        return *this;
    }

    Matrix operator-(const T& scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.mat[i][j] = mat[i][j] - scalar;
            }
        }
        return result;
    }
    Matrix operator-(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.mat[i][j] = mat[i][j] - other.mat[i][j];
            }
        }
        return result;
    }
    Matrix& operator-=(const Matrix& other) {
        *this = *this - other;
        return *this;
    }
    Matrix& operator-=(const T& scalar) {
        *this = *this - scalar;
        return *this;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }
        return result;
    }
    Matrix& operator*=(const Matrix& other) {
        *this = *this * other;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.cols; j++) {
                os << matrix.mat[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
    std::vector<T>& operator[](int index) {
        if (index < 0 || index >= rows) {
            throw std::out_of_range("Matrix index out of range.");
        }
        return mat[index];
    }

    static Matrix<T> power(const Matrix<T>& base, int exponent) {
        if (exponent == 0) {
            Matrix<T> result(base.rows, base.cols);
            for (int i = 0; i < base.rows; i++) {
                result.mat[i][i] = 1;
            }
            return result;
        }
        if (exponent % 2 == 0) {
            Matrix<T> half_pow = power(base, exponent / 2);
            return half_pow * half_pow;
        } else {
            return base * power(base, exponent - 1);
        }
    }
    //求行列式
    T determinant(int mod){
        this->mod=mod;
        int res=1,w=1;
        for(int i=0;i<rows;i++){ 
            for(int j=i+1;j<cols;++j){
                while(mat[i][i]){
                    int div=mat[j][i]/mat[i][i];
                    for(int k=i;k<rows;++k){
                        mat[j][k]=(mat[j][k]-1ll*div*mat[i][k]%mod+mod)%mod;
                    }
                    swap(mat[i],mat[j]);w=-w;
                }	
                swap(mat[i],mat[j]);w=-w;
            }
        }
        for(int i=0;i<rows;i++)res=1ll*mat[i][i]*res%mod;
        res=1ll*w*res;
        return (res+mod)%mod;
    }
    //转置
    Matrix<T> transpose() const {
        Matrix<T> result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.mat[j][i] = mat[i][j];
            }
        }
        return result;
    }
    //点乘
    Matrix<T> EWMultiply(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions do not match for element-wise multiplication.");
        }

        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.mat[i][j] = mat[i][j] * other.mat[i][j];
            }
        }
        return result;
    }
    Matrix<T> EWMultiply_Vec(const vector<T>& other) const {
        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.mat[i][j] = mat[i][j] * other[i];
            }
        }
        return result;
    }
};
using Matri = Matrix<ll>;