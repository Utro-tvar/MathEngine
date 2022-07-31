namespace MathEngine{
    class Matrix
    {
    private:
        float* _data;
        int _w, _h;
        float _determinant;
    public:
        Matrix(const int& width, const int& height, const float* data);
        ~Matrix();

        //returns width of matrix
        int Width()const;

        //returns height of matrix
        int Height()const;

        //return n row of matrix
        float* GetRow(const int& n)const;

        //return n column of matrix
        float* GetColumn(const int& n)const;

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
        //multiply matrix by matrics
        void operator*= (const Matrix& m);

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
        float Determinant()const;

        //returns rank of matrix
        int Rank()const;

        //returns inversed matrix
        Matrix Inverse()const;
    };    
}