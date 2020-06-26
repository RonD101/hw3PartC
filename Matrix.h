//
// Created by Ron Dahan on 20/06/2020.
//

#ifndef HW3PARTB_MATRIX_H
#define HW3PARTB_MATRIX_H

#include "TemArray.h"
#include "Auxiliaries.h"
#include "Exception.h"

namespace mtm {
    template<class T>
    class Matrix {
        TemArray<TemArray<T>> row;
        Dimensions dim;
        Dimensions getDimensions() const;
    public:
        class AccessIllegalElement;
        class IllegalInitialization;
        class DimensionMismatch;
        class iterator;
        class const_iterator;
        iterator begin()
        {
            return iterator(this,1);
        }
        iterator end()
        {
            return iterator(this,this->size() + 1);
        }
        const_iterator begin() const
        {
            return const_iterator(this,1);
        }
        const_iterator end() const
        {
            return const_iterator(this,this->size() + 1);

        }
        explicit Matrix(const Dimensions& dimensions, T value = T());
        Matrix(const Matrix& matrix);
        ~Matrix() = default; //because of the RAII design there isn't a need for a special destructor
        Matrix transpose() const ;
        static Matrix<T> Diagonal(int dim, T value);
        int height() const;
        int width() const;
        int size() const;
        template <class Condition>
        Matrix apply(Condition condition) const;
        Matrix& operator=(const Matrix& matrix);
        Matrix& operator+=(const T value);
        Matrix operator-() const ;
        T& operator()(int row_num,int col_num);
        const T& operator()(int row_num,int col_num) const;
    };

    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T value);
    template <class T>
    Matrix<T> operator+(const T value, const Matrix<T>& matrix);
    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    template <class T>
    Matrix<bool> operator<(Matrix<T>& matrix, T value);
    template <class T>
    Matrix<bool> operator<=(Matrix<T>& matrix, T value);
    template <class T>
    Matrix<bool> operator>(Matrix<T>& matrix, T value);
    template <class T>
    Matrix<bool> operator>=(Matrix<T>& matrix, T value);
    template <class T>
    Matrix<bool> operator==(Matrix<T>& matrix, T value);
    template <class T>
    Matrix<bool> operator!=(Matrix<T>& matrix, T value);
    template <class T>
    bool any(const Matrix<T>& matrix);
    template <class T>
    bool all(const Matrix<T>& matrix);

    /////////////////////////////////////////////////////////////////////
    ///////////////////////-----Iterator-----////////////////////////////
    /////////////////////////////////////////////////////////////////////
    template <class T>
    class Matrix<T>::iterator{
        Matrix<T>* matrix;
        int index;
        friend class Matrix<T>;
        iterator(Matrix* matrix, int index):matrix(matrix),index(index) {}
    public:
        T& operator*();
        iterator& operator++() // prefix (++it)
        {
            index++;
            return *this;
        }
        iterator operator++(int)
        {
            iterator result = *this;
            ++(*this);
            return result;
        }
        bool operator==(const iterator& it) const
        {
            return this->index == it.index;
        }
        bool operator!=(const iterator& it) const
        {
            return this->index != it.index;
        }
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
    };

    template<class T>
    T& Matrix<T>::iterator::operator*() {
        if(index > matrix->size())
        {
            throw Matrix<T>::AccessIllegalElement();
        }
        int col_index = index % matrix->width();
        if(col_index == 0){
            col_index = matrix->width();
        }
        int row_index;
        if(index % matrix->width() == 0)
        {
            row_index = index/matrix->width();
        } else
        {
            row_index = (index/matrix->width() )+ 1;
        }
        return (*matrix)(row_index - 1, col_index - 1);
    }

    /////////////////////////////////////////////////////////////////////
    /////////////////////-----const Iterator-----////////////////////////
    /////////////////////////////////////////////////////////////////////
    template <class T>
    class Matrix<T>::const_iterator{
        const Matrix* matrix;
        int index;
        friend class Matrix;
        const_iterator(const Matrix* matrix, int index):matrix(matrix),index(index) {}
    public:
        const T& operator*() const;
        const_iterator& operator++() // prefix (++it)
        {
            index++;
            return *this;
        }
        const_iterator operator++(int)
        {
            iterator result = *this;
            ++(*this);
            return result;
        }
        bool operator==(const const_iterator& it) const
        {
            return this->index == it.index;
        }
        bool operator!=(const const_iterator& it) const
        {
            return this->index != it.index;
        }
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
    };

    template<class T>
    const T& Matrix<T>::const_iterator::operator*() const {
        int col_index = index % matrix->width();
        if(col_index == 0){
            col_index = matrix->width();
        }
        int row_index;
        if(index % matrix->width() == 0)
        {
            row_index = index/matrix->width();
        } else
        {
            row_index = (index/matrix->width() )+ 1;
        }
        return (*matrix)(row_index - 1, col_index - 1);
    }

    /////////////////////////////////////////////////////////////////////
    /////////////////////-----class function-----////////////////////////
    /////////////////////////////////////////////////////////////////////

    template<class T>
    Matrix<T>::Matrix(const Dimensions &dimensions, T value):dim(dimensions) {
        if(dimensions.getRow() < 1 || dimensions.getCol() <1)
        {
            throw Matrix<T>::IllegalInitialization();
        }
        int dim_row = dimensions.getRow();
        int dim_col = dimensions.getCol();
        //allocating rows
        row = TemArray<TemArray<T>>(dim_row);
        //allocating cols
        for (int i = 0; i < dim_row; ++i)
        {
            row[i] = TemArray<T>(dim_col);
        }
        //setting default value
        for (int i = 0; i < dim_row; ++i)
        {
            for (int j = 0; j < dim_col; ++j)
            {
                (*this)(i,j) = value;
            }
        }
    }

    template<class T>
    Matrix<T>::Matrix(const Matrix<T> &matrix) :dim(matrix.getDimensions()) {
        //allocating rows
        row = TemArray<TemArray<T>>(dim.getRow());
        //allocating cols
        for (int i = 0; i < dim.getRow(); ++i)
        {
            row[i] = TemArray<T>(dim.getCol());
        }
        //setting default value
        for (int i = 0; i < dim.getRow(); ++i)
        {
            for (int j = 0; j < dim.getCol(); ++j)
            {
                (*this)(i,j) = matrix(i,j);
            }
        }
    }

    template<class T>
    Dimensions Matrix<T>::getDimensions() const {
        return this->dim;
    }

    // Function returns a transposed matrix
    template <class T>
    Matrix<T> Matrix<T>::transpose() const {
        Dimensions d(this->width(), this->height());
        Matrix matrix(d);
        for (int j = 0; j < matrix.height(); ++j)
        {
            for (int i = 0; i < matrix.width(); ++i)
            {
                matrix(j,i) = (*this)(i,j);
            }
        }
        return matrix;
    }

    // Function that returns a diagonal matrix
    template<class T>
    Matrix<T> Matrix<T>::Diagonal(int dim, T value) {
        if(dim < 1)
        {
            //If one of the matrix's dimensions isn't positive, throw an exception
            throw Matrix<T>::IllegalInitialization();
        }
        Dimensions d(dim,dim);
        Matrix matrix = Matrix(d, 0);
        for (int i = 0; i < matrix.height(); ++i) {
            matrix(i,i) = value;
        }
        return matrix;
    }

    // Function to get number of rows of the matrix
    template<class T>
    int Matrix<T>::height() const {
        return dim.getRow();
    }

    // Function to get number of columns of the matrix
    template<class T>
    int Matrix<T>::width() const {
        return dim.getCol();
    }

    // Function to get the total number of values in the matrix
    template<class T>
    int Matrix<T>::size() const {
        return this->width()*this->height();
    }

    // Function checks if the matrix passed has at least one element whose value is true.
    // If so, returns true, if not returns false
    template <class T>
    bool any(const Matrix<T>& matrix)
    {
        for (int i = 0; i <matrix.height(); ++i)
        {
            for (int j = 0; j < matrix.width(); ++j)
            {
                if(matrix(i,j) != 0) //if a single elment is true, return true
                {
                    return true;
                }
            }
        }
        return false;
    }

    // Function checks if all elements if the matrix passed have the value of true.
    // If so, returns true, if not returns false
    template <class T>
    bool all(const Matrix<T>& matrix)
    {
        for (int i = 0; i < matrix.height(); ++i)
        {
            for (int j = 0; j < matrix.width(); ++j)
            {
                if(matrix(i,j) == 0) //if a single elment is false, return false
                {
                    return false;
                }
            }
        }
        return true;
    }

    template<class T>
    template<class Condition>
    Matrix<T> Matrix<T>::apply(Condition condition) const {
        Matrix<T> result(*this);
        for (int i = 0; i < height(); ++i) {
            for (int j = 0; j < width(); ++j) {
                result(i,j) = condition(result(i,j));
            }
        }
        return result;
    }

    /////////////////////////////////////////////////////////////////////
    ////////////////////-----class operators-----////////////////////////
    /////////////////////////////////////////////////////////////////////

    template<class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T> &matrix) {
        if(this == & matrix)
        {
            return *this;
        }
        //deallocate is working automatic because of the RAII design
        dim = matrix.dim;
        //allocating rows
        row = TemArray<TemArray<T>>(dim.getRow());
        //allocating cols
        for (int i = 0; i < this->height(); ++i)
        {
            row[i] = TemArray<T>(dim.getCol());
        }
        //setting new values
        for (int j = 0; j < this->height(); ++j)
        {
            for (int i = 0; i < this->width(); ++i)
            {
                (*this)(j,i) = matrix(j,i);
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator+=(const T value) {
        Matrix m(this->getDimensions(), value);
        *this = *this + m;
        return *this;
    }

    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T value)
    {
        Matrix<T> m = matrix;
        m += value;
        return m;
    }

    template <class T>
    Matrix<T> operator+(const T value, const Matrix<T>& matrix)
    {
        Matrix<T> m = matrix;
        m += value;
        return m;
    }

    template<class T>
    Matrix<T> operator+(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
        Dimensions d1(matrix1.height(),matrix1.width()), d2(matrix2.height(),matrix2.width());
        if(d1 != d2)
        {
            throw typename Matrix<T>::DimensionMismatch(d1,d2);
        }
        Matrix<T> matrix(d1);
        for (int i = 0; i < matrix.height(); ++i)
        {
            for (int j = 0; j < matrix.width(); ++j)
            {
                matrix(i,j) = matrix1(i,j) + matrix2(i,j);
            }
        }
        return matrix;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-() const {
        Matrix<T> matrix(*this);
        for (int i = 0; i < matrix.height(); ++i) {
            for (int j = 0; j < matrix.width(); ++j) {
                matrix(i,j) = -matrix(i,j);
            }
        }
        return matrix;
    }

    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
        return matrix1 + -matrix2;
    }

    template<class T>
    T& Matrix<T>::operator()(int row_num, int col_num)
    {
        try {
            return row[row_num][col_num];
        }
        //we catch if there is illegal access in TemArray and rethrow it as Martix::AccessIllegalElement
        catch (std::exception& e){
            throw Matrix<T>::AccessIllegalElement();
        }
    }

    template<class T>
    const T& Matrix<T>::operator()(int row_num, int col_num) const
    {
        try {
            return row[row_num][col_num];
        }
        //we catch if there is illegal access in TemArray and rethrow it as Martix::AccessIllegalElement
        catch (std::exception& e){
            throw Matrix<T>::AccessIllegalElement();
        }
    }

    template <class T>
    std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) {
          printMatrix(os,matrix.begin(),matrix.end(),matrix.width());
        return os;
    }

    // Function to check which elements in the matrix are smaller than the value passed
    // Returns new matrix with these rules:
    // Smaller values become true
    // Larger values become false
    template<class T>
    Matrix<bool> operator<(Matrix<T>& matrix, T value)
    {
        Dimensions dim(matrix.height(), matrix.width());
        Matrix<bool> matrix_new(dim);
        for (int i = 0; i < matrix_new.height(); ++i)
        {
            for (int j = 0; j < matrix_new.width(); ++j)
            {
                if(matrix(i,j) < value)
                {
                    matrix_new(i,j) = true;
                } else
                {
                    matrix_new(i,j) = false;
                }
            }
        }
        return matrix_new;
    }

    // Function to check which elements in the matrix are equal or smaller than the value passed
    // Returns new matrix with these rules:
    // Smaller or equal values become true
    // Larger values become false
    template <class T>
    Matrix<bool> operator<=(Matrix<T>& matrix, T value)
    {
        Dimensions dim(matrix.height(), matrix.width());
        Matrix<bool> matrix_new(dim);
        for (int i = 0; i < matrix_new.height(); ++i)
        {
            for (int j = 0; j < matrix_new.width(); ++j)
            {
                if(matrix(i,j) <= value)
                {
                    matrix_new(i,j) = true;
                } else
                {
                    matrix_new(i,j) = false;
                }
            }
        }
        return matrix_new;
    }

    // Function to check which elements in the matrix are larger than the value passed
    // Returns new matrix with these rules:
    // Larger values become true
    // Smaller values become false
    template <class T>
    Matrix<bool> operator>(Matrix<T>& matrix, T value)
    {
        Dimensions dim(matrix.height(), matrix.width());
        Matrix<bool> matrix_new(dim);
        for (int i = 0; i < matrix_new.height(); ++i)
        {
            for (int j = 0; j < matrix_new.width(); ++j)
            {
                if(matrix(i,j) > value)
                {
                    matrix_new(i,j) = true;
                } else
                {
                    matrix_new(i,j) = false;
                }
            }
        }
        return matrix_new;
    }

    // Function to check which elements in the matrix are equal or larger than the value passed
    // Returns new matrix with these rules:
    // Larger or equal values become true
    // Smaller values become false
    template <class T>
    Matrix<bool> operator>=(Matrix<T>& matrix, T value)
    {
        Dimensions dim(matrix.height(), matrix.width());
        Matrix<bool> matrix_new(dim);
        for (int i = 0; i < matrix_new.height(); ++i)
        {
            for (int j = 0; j < matrix_new.width(); ++j)
            {
                if(matrix(i,j) >= value)
                {
                    matrix_new(i,j) = true;
                } else
                {
                    matrix_new(i,j) = false;
                }
            }
        }
        return matrix_new;
    }

    // Function to check which elements in the matrix are equal to the value passed
    // Returns new matrix with these rules:
    // Equal values become true
    // Unequal values become false
    template <class T>
    Matrix<bool> operator==(Matrix<T>& matrix, T value)
    {
        Dimensions dim(matrix.height(), matrix.width());
        Matrix<bool> matrix_new(dim);
        for (int i = 0; i < matrix_new.height(); ++i)
        {
            for (int j = 0; j < matrix_new.width(); ++j)
            {
                if(matrix(i,j) == value)
                {
                    matrix_new(i,j) = true;
                } else
                {
                    matrix_new(i,j) = false;
                }
            }
        }
        return matrix_new;
    }

    // Function to check which elements in the matrix are unequal to the value passed
    // Returns new matrix with these rules:
    // Unequal values become true
    // Equal values become false
    template <class T>
    Matrix<bool> operator!=(Matrix<T>& matrix, T value)
    {
        Dimensions dim(matrix.height(), matrix.width());
        Matrix<bool> matrix_new(dim);
        for (int i = 0; i < matrix_new.height(); ++i)
        {
            for (int j = 0; j < matrix_new.width(); ++j)
            {
                if(matrix(i,j) != value)
                {
                    matrix_new(i,j) = true;
                } else
                {
                    matrix_new(i,j) = false;
                }
            }
        }
        return matrix_new;
    }

    ///////////////////////////////////////////////////////////////////
    ////////////////////////// Exception classes //////////////////////
    ///////////////////////////////////////////////////////////////////
    template <class T>
    class Matrix<T>::AccessIllegalElement  : public mtm::Exception {
    public:
        const char* what() const noexcept override
        {
            return "Mtm matrix error: An attempt to access an illegal element";
        }
    };

    template <class T>
class Matrix<T>::IllegalInitialization  : public mtm::Exception {
    public:
        const char* what() const noexcept override
        {
            return "Mtm matrix error: Illegal initialization values";
        }
    };

    template <class T>
class Matrix<T>::DimensionMismatch  : public std::exception {
        Dimensions m1;
        Dimensions m2;
        std::string out;
    public:
        DimensionMismatch(Dimensions m1, Dimensions m2):m1(m1),m2(m2),out("Mtm matrix error: Dimension mismatch: " + m1.toString() + " " + m2.toString()) {}
        const char* what() const noexcept override
        {
            return out.c_str();
        }
    };

    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
}

#endif //HW3PARTB_MATRIX_H
