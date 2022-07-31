#include "Matrix.hpp"

namespace MathEngine{
    Matrix::~Matrix(){
        delete [] _data;
    }
}