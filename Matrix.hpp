#pragma once

#include <string>
#include <vector>

namespace MathEngine{
    class Matrix
    {
    private:
        float* _data;
        int _w, _h;
        float _determinant = 0;
    public:
        //creates matrix from data (rows connected from top to down)
        Matrix(const int& width, const int& height, const std::vector<float>& data);
        //creates matrix filled by 'fill' value
        Matrix(const int& width, const int& height, const float& fill = 0);
        //creates copy of the matrix
        Matrix(const Matrix& m);
        ~Matrix();

        //returns width of matrix
        int Width()const;

        //returns height of matrix
        int Height()const;

        //returns matrix without the given row
        Matrix RemoveRow(const int& row)const;

        //returns matrix without the given column
        Matrix RemoveColumn(const int& column)const;

        //returns matrix without the given row and column, -1 argument means none
        Matrix RemoveRowAndColumn(const int& row,const int& column)const;

        //swap two rows in this matrix
        void SwapRows(const unsigned& a, const unsigned& b);

        //swap two columns of this matrix
        void SwapColumns(const unsigned& a, const unsigned& b);

        //returns item of matrix on (i, j) position from top-left corner
        const float& operator() (const unsigned& i, const unsigned& j)const;

        //multiply matrix by scalar
        Matrix operator* (const float& f)const;
        //multiply matrix by scalar
        void operator*= (const float& f);

        //divide matrix by scalar
        Matrix operator/ (const float& f)const;
        //divide matrix by scalar
        void operator/= (const float& f);

        //multiply matrix by matrics
        Matrix operator* (const Matrix& m)const;

        //add matrices
        Matrix operator+ (const Matrix& m)const;
        //add matrices
        void operator+= (const Matrix& m);

        //substract matrices
        Matrix operator- (const Matrix& m)const;
        //substract matrices
        void operator-= (const Matrix& m);

        //copy matrix
        Matrix& operator= (const Matrix& m);

        //returns determinant of matrix
        float Determinant();

        //returns transposed matrix
        Matrix GetTransposed()const;

        //returns inversed matrix
        Matrix GetInversed();

        //returns triangulated matrix
        Matrix GetTriangular()const;

        //returns rank of matrix
        int Rank()const;

        std::string ToString()const;
    };    
}