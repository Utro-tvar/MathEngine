#include "Matrix.hpp"
#include <stdexcept>
#include <sstream>
#include <math.h>
#include <iostream>

namespace MathEngine{
    Matrix::Matrix(const int& width, const int& height, const std::vector<float>& data):
    _w(width), _h(height){
        if(data.size() != _w * _h){
            throw std::invalid_argument("Matrix and array sizes must be same to construct matrix, but they're not!");
        }
        _data = new float[_w * _h];
        for (int i = 0; i < _w * _h; ++i){
            _data[i] = data.at(i);
        }
    }

    Matrix::Matrix(const int& width, const int& height, const float& fill):
    _w(width), _h(height){
        _data = new float[_w * _h];
        for (int i = 0; i < _w * _h; ++i)
            _data[i] = fill;
    }

    Matrix::Matrix(const Matrix& m):
    _w(m._w), _h(m._h), _determinant(m._determinant){
        _data = new float[_w * _h];
        for (int i = 0; i < _w * _h; ++i){
            _data[i] = m._data[i];
        }
    }

    Matrix::~Matrix(){
        delete [] _data;
    }

    int Matrix::Width()const{
        return _w;
    }

    int Matrix::Height()const{
        return _h;
    }

    Matrix Matrix::RemoveRow(const int& row)const{
        return RemoveRowAndColumn(row, -1);
    }

    Matrix Matrix::RemoveColumn(const int& column)const{
        return RemoveRowAndColumn(-1, column);
    }

    Matrix Matrix::RemoveRowAndColumn(const int& row, const int& column)const{
        if (row >= _h){
            std::stringstream message;
            message << "This matrix hasn't row " << row << "!";
            throw std::invalid_argument(message.str());
        }
        if (column >= _w){
            std::stringstream message;
            message << "This matrix hasn't column " << column << "!";
            throw std::invalid_argument(message.str());
        }
        Matrix result(column == -1 ? _w : _w - 1, row == -1 ? _h : _h - 1);
        int i = 0;
        for (int y = 0; y < _h; ++y){
            if (y == row)
                continue;
            for (int x = 0; x < _w; ++x){
                if (x == column)
                    continue;
                result._data[i] = (*this)(x, y);
                ++i;
            }
        }
        return result;
    }

    void Matrix::SwapRows(const unsigned& a, const unsigned& b){
        if (a >= _h || b >= _h)
            throw std::out_of_range("Row index out of range!");
        for (int n1 = _w * a, n2 = _w * b; n1 < _w * (a + 1); ++n1, ++n2){
            int t = _data[n1];
            _data[n1] = _data[n2];
            _data[n2] = t;
        }
    }

    void Matrix::SwapColumns(const unsigned& a, const unsigned& b){
        if (a >= _w || b >= _w)
            throw std::out_of_range("Column index out of range!");
        for (int n1 = a, n2 = b; n1 < _h * _w; n1 += _w, n2 += _w){
            int t = _data[n1];
            _data[n1] = _data[n2];
            _data[n2] = t;
        }
    }

    const float& Matrix::operator()(const unsigned& i, const unsigned& j)const{
        if (i >= _w || j >= _h)
            throw std::out_of_range("Index out of matrix");
        return _data[j * _w + i];
    }

    Matrix Matrix::operator* (const float& f)const{
        Matrix result = *this;
        result *= f;
        return result;
    }

    void Matrix::operator*= (const float& f){
        for (int i = 0; i < _w * _h; ++i)
            _data[i] *= f;
        _determinant = 0;
    }

    Matrix Matrix::operator/ (const float& f)const{
        Matrix result = *this;
        result /= f;
        return result;
    }

    void Matrix::operator/= (const float& f){
        for (int i = 0; i < _w * _h; ++i)
            _data[i] /= f;
        _determinant = 0;
    }

    Matrix Matrix::operator* (const Matrix& m)const{
        if (_w != m._h)
            throw std::invalid_argument("The width of the first matrix should match the height of the other, but it doesn't!");
        Matrix result(m._w, _h);
        for (int x = 0; x < m._w; ++x){
            for (int y = 0; y < _h; ++y){
                float dot = 0;
                for (int i = 0; i < _w; ++i)
                    dot += (*this)(i, y) * m(x, i);
                result._data[y * m._w + x] = dot;
            }
        }
        return result;
    }

    Matrix Matrix::operator+ (const Matrix& m)const{
        if (_w != m._w || _h != m._h)
            throw std::invalid_argument("The matrices should have the same dimensions for addition!");
        Matrix result = *this;
        result += m;
        return result;
    }

    void Matrix::operator+= (const Matrix& m){
        if (_w != m._w || _h != m._h)
            throw std::invalid_argument("The matrices should have the same dimensions for addition!");
        for (int i = 0; i < _w * _h; ++i)
            _data[i] += m._data[i];
        _determinant = 0;
    }

    Matrix Matrix::operator- (const Matrix& m)const{
        if (_w != m._w || _h != m._h)
            throw std::invalid_argument("The matrices should have the same dimensions for subtraction!");
        Matrix result = *this;
        result -= m;
        return result;
    }

    void Matrix::operator-= (const Matrix& m){
        if (_w != m._w || _h != m._h)
            throw std::invalid_argument("The matrices should have the same dimensions for addition!");
        for (int i = 0; i < _w * _h; ++i)
            _data[i] -= m._data[i];
        _determinant = 0;
    }

    Matrix& Matrix::operator= (const Matrix& m){
        _w = m._w;
        _h = m._h;
        _data = new float[_h * _w];
        for (int i = 0; i < _w * _h; ++i)
            _data[i] = m._data[i];
        _determinant = m._determinant;
        return *this;
    }

    float Matrix::Determinant(){
        if (_w != _h)
            throw std::runtime_error("Only square matrix has determinant!");
        if (_determinant != 0) return _determinant;
        if (_w == 2){
            _determinant = _data[0] * _data[3] - _data[1] * _data[2];
            return _determinant;
        }
        for (int n = 0, sign = 1; n < _w; ++n, sign = -sign){
            _determinant += sign * _data[n] * RemoveRowAndColumn(0, n).Determinant();
        }
        return _determinant;
    }

    Matrix Matrix::GetTransposed()const{
        Matrix result(_h, _w);
        for (int y = 0; y < _h; ++y){
            for (int x = 0; x < _w; ++x)
                result._data[x * _h + y] = (*this)(x, y);
        }
        return result;
    }

    Matrix Matrix::GetInversed(){
        if (_w != _h)
            throw std::runtime_error("Only square matrix can be inversed!");
        Matrix result(_w, _h);
        for (int y = 0; y < _h; ++y){
            for (int x = 0; x < _w; ++x){
                float d = RemoveRowAndColumn(x, y).Determinant();
                d *= pow(-1, x + y);
                result._data[y * _w + x] = d;
            }
        }
        return result / Determinant();
    }

    std::string Matrix::ToString()const{
        std::stringstream ss;
        for (int y = 0; y < _h; ++y){
            for (int x = 0; x < _w; ++x)
                ss << (*this)(x, y) << '\t';
            ss << std::endl;
        }
        return ss.str();
    }

    Matrix Matrix::GetTriangular()const{
        Matrix result = *this;
        int x = 0;
        for (int y = 0; y < _h; ++y){
            while (result(x, y) == 0){
                for (int y1 = y; y1 < _h; ++y1){
                    if (result(x, y1) != 0){
                        result.SwapRows(y, y1);
                        break;
                    }
                }
                if (result(x, y) == 0)
                    ++x;
                    if (x >= _w) return result;
            }
            for (int y1 = y + 1; y1 < _h; ++y1){
                float factor = result(x, y1) / result(x, y);
                for (int x1 = x; x1 < _w; ++x1){
                    result._data[y1 * _w + x1] -= result(x1, y) * factor;
                }
            }
        }
        return result;
    }

    int Matrix::Rank()const{
        Matrix tiangular = GetTriangular();
        int rank = 0;
        for (int y = 0; y < _h; ++y){
            bool zero = true;
            for (int x = 0; x < _w; ++x){
                zero &= tiangular(x, y) == 0;
            }
            if (!zero) ++rank;
        }
        return rank;
    }
}