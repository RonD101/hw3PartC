//
// Created by Ron Dahan on 20/06/2020.
//

#ifndef HW3PARTB_MATRIX_H
#define HW3PARTB_MATRIX_H

#include "TemArray.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
/**
* Class T typed Matrix
*
* Implements a class T typed Matrix using a template.
* The type of the matrix's value is T.
* The matrix has an internal iterator for external use. For all functions
* where the state of the iterator after calling that function is not stated,
* it is undefined. That is you cannot assume anything about it.
*
* The following functions are available:
*   the big three - constructor , destructor and copy constructor.
*   begin		- Return an iterator for the start of the matrix.
*   end		- Return an iterator for the end of the matrix.
*   transpose		- Returns a copy of the matrix transposed.
*   Diagonal	- Returns a diagonal matrix with value passed. Elements out of the diagonal are initialized to be
*                              the value returned by class T's constructor
*   height		    - Return the height of the matrix (amount of rows).
*   width  	    - Returns the width of the matrix (amount of columns).
*   size		- Return the amount of variables in matrix
*   any	    - Return true if any of the matrix's variable is different than true, and false otherwise.
*   all		-  Return true if all of the matrix's variable is different than true, and false otherwise.
*
* The following operators are available:
*   operator=      - Assignment of one matrix to the other
*   operator+=      - Add matrices and then assign
*   operator-(binary)   - Subtract one matrix from the other
*   operator-(unary)    - Return copy of the matrix with -value
*   operator()      - Return reference to value
*   operator<<      - Return a ostream value to print
*   operator+(Value)     - Add value to each element in matrix
*   operator+(Matrix)   - Return copy of added matrices
*   operator<,<=,>,>=,== ,!=     - Return a matrix of true's and false's depending on the result between
*                                          the two elements
*/

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
        /**	begin:  Return a iterator for the top left element of the matrix.
        *	Use this to start iterating over the matrix.
        *
        * @return
        * 	The first element of the matrix
        */
        iterator begin()
        {
            return iterator(this,1);
        }
        /**	end:  Return a iterator for element after the last element in matrix.
        *	Use this to stop iterating over the matrix.
        *
        * @return
        * 	The one after the last element of the matrix
        */									   
        iterator end()
        {
            return iterator(this,this->size() + 1);
        }
/**
        *	begin:  Return a iterator for the top left element of the matrix.
        *   the element cannot be change
        *	Use this to start iterating over const matrix.
        *
        * @return
        * 	The first element of the matrix
        */ 
        const_iterator begin() const
        {
            return const_iterator(this,1);
        }
        /**	end:  Return a iterator for element after the last element in matrix.
        *	Use this to stop iterating over const matrix.
        *
        * @return
        * 	The one after the last element of the matrix
        */
        const_iterator end() const
        {
            return const_iterator(this,this->size() + 1);

        }
        /**	Constructor: create a new matrix
        *
        * @param
        * dimensions - The dimension for the new matrix
        * value - Initial value (optional)
        * @return
        * 	The new matrix
        * 	@assumptions
        * 	    there is = operator for class T
        */
        explicit Matrix(const Dimensions& dimensions, T value = T());
        /**
        *	Copy Constructor: create a copy matrix
        *
        * @param
        * matrix - The matrix which we copy the values from.
        * @return
        * 	The copied matrix
        * @assumptions
        *   there is = operator for class T
        */
        Matrix(const Matrix& matrix);
        /**    Destructor: Destroy the matrix when her 'life' end.
        *
        * @return
        * 	No Return Value.
        */
        ~Matrix() = default; //because of the RAII design there isn't a need for a special destructor

        /**
        *	transpose: Returns a copy of the matrix transposed.
        *
        * @return
        * 	The transposed matrix
        * @assumption
        *   There is = operator for class T
        */
        Matrix transpose() const ;
        /**	Diagonal: Returns a copy of Diagonal matrix.
        *
        * @param
                * dim - the dimension of the Diagonal matrix
        * @return
        * 	The Diagonal matrix
        * @assumption
        *   There is = operator for class T
        */
        static Matrix<T> Diagonal(int dim, T value);
		/**
        *	height: Returns the height of the matrix (amount of row).
        *
        * @return
        * 	Amount of row
        */
        int height() const;
        /**	width: Returns the width of the matrix (amount of columns).
        *
        * @return
        * 	Amount of columns
        */ 
        int width() const;
        /**	size: Returns the amount of element in matrix.
        *
        * @return
        * 	Amount of elements
        */
        int size() const;
        // class for function objects
        template <class Condition>
        /**	apply: Returns a copy of Diagonal matrix.
        *
        * @param
                * condition - the condition to apply on the matrix elements
                    * condition is of class Condition
        * @return
        * 	The applied matrix
        * @assumptions
        *  there is = operator for class T
        */
        Matrix apply(Condition condition) const;
        /**	operator=: assign matrix
        *
        * @param
        * matrix - The matrix which we copy the values from.
        * @return
        * 	The assigned matrix
         * 	@assumptions
         *      there is = operator for class T
        */
        Matrix& operator=(const Matrix& matrix);
        /**	operator+=: add value to each element in matrix, and then assign the matrix
        *
        * @param
        * value - The value to add for each element.
        * @return
        * 	The assigned matrix
        */
        Matrix& operator+=(const T value);
        /**	operator-: return copied matrix with -values
        *
        * @return
        * 	The copied matrix
        * @assumption
        *   There is =,- operator for class T
        */
        Matrix operator-() const ;
/**
        *	operator(): Return element from matrix
        *
        * @param
        * rom_num - The row number of the element
        * col_num - The column number of the element
        * @return
        * 	Reference to the element
        */
        T& operator()(int row_num,int col_num);
        /**	operator(): Return a const element from matrix
        *
        * @param
        * rom_num - The row number of the element
        * col_num - The column number of the element
        * @return
        * 	Reference to the const element
        */
        const T& operator()(int row_num,int col_num) const;
    };

    /**	operator<<: Returns a osstream to print.
    *
    * @param
    * os - ostream for the message to print
    * matrix - the matrix to print
    * @return
    * 	The ostream
    */
    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);
    /**	operator+: Returns a copy of the added matrix.
    *
    * @param
    * matrix1 - First matrix to add
    * matrix2 - Second matrix to add
    * @return
    * 	The added matrix
     * 	@assumptions
     * 	Assuming there is =,+ operators for class T
    */
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    /**	operator+: Returns a copy of the added matrix with value.
    *
    * @param
    * matrix - The matrix to copy.
    * value - The value to add for each element.
    * @return
    * 	The added matrix
    */
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T value);
    /**
    *	operator+: Returns a copy of the added matrix with value.
    *
    * @param
    * value - The value to add for each element.
    * matrix - The matrix to copy.
    * @return
    * 	The added matrix
    */
	template <class T>
    Matrix<T> operator+(const T value, const Matrix<T>& matrix);
    /**
    *	operator-: Returns a copy of the subtract matrix.
    *
    * @param
    * matrix1 - The matrix to subtract from
    * matrix2 - The matrix to subtract
    * @return
    * 	The subtracted matrix
    */
    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    /**
    *	comparison operators: Returns matrix of trues and false's depending on the return value
    *           of the comparison.
    *
    * @param
    * matrix - The matrix to compare.
    * value - Value to compare to.
    * @return
    * 	The trues and false's matrix
    * @assumptions
    *   There are the <,<=,>,>=,==,!= operators for class T
    */ 
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
	/**
    *	any: check if any of the element is different from zero
    *
    * @param
    * matrix - The matrix to check.
    * @return
    * 	True if any of the element is different from zero, and false otherwise.
    * @assumption
    * 	Assuming there is != operator for class T
    */
	template <class T>
    bool any(const Matrix<T>& matrix);
   /**
    *	all: check if all of the element is different from zero
    *
    * @param
    * matrix - The matrix to check.
    * @return
    * 	True if all the element are different from zero, and false otherwise.
    * @assumption
    * 	Assuming there is == operator for class T    */
    template <class T>
    bool all(const Matrix<T>& matrix);

    /////////////////////////////////////////////////////////////////////
    ///////////////////////-----Iterator-----////////////////////////////
    /////////////////////////////////////////////////////////////////////
    /** Matrix's Iterator
    *
    * Implements of the matrix Iterator.
    * The Iterator methods support the basic uses of a normal Iterator
    */
    template <class T>
    class Matrix<T>::iterator{
        Matrix<T>* matrix;
        int index;
        friend class Matrix<T>;
        iterator(Matrix* matrix, int index):matrix(matrix),index(index) {}
    public:
        T& operator*();
        // operator++ prefix (++it)
        iterator& operator++()		  
        {
            index++;
            return *this;
        }
        // operator++ suffix (it++)
        iterator operator++(int)
        {
            iterator result = *this;
            ++(*this);
            return result;
        }
        // operator== for iterator
        bool operator==(const iterator& it) const
        {
            return this->index == it.index;
        }
        // operator!= for iterator
        bool operator!=(const iterator& it) const
        {
            return this->index != it.index;
        }
        iterator(const iterator&) = default;  // copy constructor for iterator
        iterator& operator=(const iterator&) = default;// operator= for iterator
    };

	// operator* returns the element pointed to by the iterator.
    // throws exception AccessIllegalElement if iterator doesn't point to a legal element																					 
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
    /**
    * const Matrix's Iterator
    *
    * Implements of the const matrix Iterator.
    * The Iterator methods support the basic uses of a normal Iterator
    */
    template <class T>
    class Matrix<T>::const_iterator{
        const Matrix* matrix;
        int index;
        friend class Matrix;
        const_iterator(const Matrix* matrix, int index):matrix(matrix),index(index) {}
    public:
        const T& operator*() const;
        // operator++ prefix (++it)
        const_iterator& operator++()
        {
            index++;
            return *this;
        }
        // operator++ suffix (it++)
        const_iterator operator++(int)
        {
            iterator result = *this;
            ++(*this);
            return result;
        }
        // operator== for iterator
        bool operator==(const const_iterator& it) const
        {
            return this->index == it.index;
        }
		// operator!= for iterator						  
        bool operator!=(const const_iterator& it) const
        {
            return this->index != it.index;
        }
        const_iterator(const const_iterator&) = default; // copy constructor for iterator
        const_iterator& operator=(const const_iterator&) = default; // operator= for iterator
    };

    // operator* returns the element pointed to by the iterator.
    // throws exception AccessIllegalElement if iterator doesn't point to a legal element																 
    template<class T>
    const T& Matrix<T>::const_iterator::operator*() const {
        if(index > matrix->size())
        {
            throw Matrix<T>::AccessIllegalElement();
        }        int col_index = index % matrix->width();
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

    // constructor of matrix. if one of the dimensions is <= 1 throws exception IllegalInitialization
    // Assuming there is = operator for class T
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

    // copy constructor for matrix
    // Assuming there is = operator for class T
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

    // function returns the dimensions of this matrix
    template<class T>
    Dimensions Matrix<T>::getDimensions() const {
        return this->dim;
    }

    // Function returns a transposed matrix
    // Assuming there is = operator for class T
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

    // Function that returns a diagonal matrix. If one of the matrix's dimensions isn't positive, throw an exception
    // Assuming there is = operator for class T
    template<class T>
    Matrix<T> Matrix<T>::Diagonal(int dim, T value) {
        if(dim < 1)
        {
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
    // Assuming there is != operator for class T
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
    // Assuming there is == operator for class T
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

    // copies the matrix, receives function object as param and applies it on every element in the copy
    // Assuming there is = operator for class T										   
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

    // operator= for Matrix
    // Assuming there is = operator for class T
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

    // Function returns the sum of this matrix and the T value param
    template<class T>
    Matrix<T>& Matrix<T>::operator+=(const T value) {
        Matrix m(this->getDimensions(), value);
        *this = *this + m;
        return *this;
    }

    // Function returns new matrix which is the sum of the matrix and T value params (matrix + val)
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T value)
    {
        Matrix<T> m = matrix;
        m += value;
        return m;
    }

    // Function returns new matrix which is the sum of the matrix and T value params (val + matrix)
    template <class T>
    Matrix<T> operator+(const T value, const Matrix<T>& matrix)
    {
        Matrix<T> m = matrix;
        m += value;
        return m;
    }

    // function returns new matrix which is the sum of the 2 matrices params.
    // if the dimensions of matrix1 is unequal to that of matrix2, throws exception DimensionMismatch
    // Assuming there is =,+ operators for class T
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

	// operator- for matrix
    // Assuming there is =,- operators for class T										  
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

	// returns the substraction of the 2 matrices parans.
    // if the dimensions of matrix1 is unequal to that of matrix2, operator+ throws exception DimensionMismatch													 																									   
    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
        return matrix1 + -matrix2;
    }

	// function returns the contents of the Matrix in the coordinates row_num, col_num
    // e.g T value = matrix(i, j)							 
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
	// function returns the contents of the Matrix in the coordinates row_num, col_num
    // e.g T value = matrix(i, j)							 
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

	// output function for matrix using function printMatrix														
    template <class T>
    std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) {
          printMatrix(os,matrix.begin(),matrix.end(),matrix.width());
        return os;
    }

    /** Function to check which elements in the matrix are smaller than the value passed
        Returns new matrix with these rules:
        Smaller values become true
        Larger or equal values become false
        Assuming there is < operator for class T
    */
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

    /** Function to check which elements in the matrix are equal or smaller than the value passed
    Returns new matrix with these rules:
    Smaller or equal values become true
    Larger values become false
    Assuming there is <= operator for class T
    */
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

    /** Function to check which elements in the matrix are larger than the value passed
        Returns new matrix with these rules:
        Larger values become true
        Smaller or equal values become false
        Assuming there is > operator for class T
    */
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

    /** Function to check which elements in the matrix are equal or larger than the value passed
        Returns new matrix with these rules:
        Larger or equal values become true
        Smaller values become false
        Assuming there is >= operator for class T
    */
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

    /** Function to check which elements in the matrix are equal to the value passed
        Returns new matrix with these rules:
        Equal values become true
        Unequal values become false
        Assuming there is == operator for class T
    */
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

    /** Function to check which elements in the matrix are unequal to the value passed
        Returns new matrix with these rules:
        Unequal values become true
        Equal values become false
        Assuming there is != operator for class T
    */
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
	// This section is for all the exceptions needed for Matrix.h															 
    template <class T>
    class Matrix<T>::AccessIllegalElement  : public mtm::Exceptions {
    public:
        const char* what() const noexcept override
        {
            return "Mtm matrix error: An attempt to access an illegal element";
        }
    };

    template <class T>
class Matrix<T>::IllegalInitialization  : public mtm::Exceptions {
    public:
        const char* what() const noexcept override
        {
            return "Mtm matrix error: Illegal initialization values";
        }
    };

    template <class T>
class Matrix<T>::DimensionMismatch  : public mtm::Exceptions {
        Dimensions m1;
        Dimensions m2;
        std::string out;
    public:
        DimensionMismatch(Dimensions m1, Dimensions m2):m1(m1),m2(m2),out("Mtm matrix error: Dimension mismatch: " 
		+ m1.toString() + " " + m2.toString()) {}
        const char* what() const noexcept override
        {
            return out.c_str();
        }
    };

    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
}

#endif //HW3PARTB_MATRIX_H
