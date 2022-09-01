#pragma once

#include <string>

namespace MathEngine{
    class Vector3
    {
    private:
        float _x, _y, _z;
        float _magnitude = -1;
    public:
        //create zero vector
        Vector3();
        //create (x, y, z) vector
        Vector3(const float& x, const float& y, const float& z);
        //copy vector
        Vector3(const Vector3& v);
        //create (f, f, f) vector
        Vector3(const float& f);

        ~Vector3();

        //x-component of vector
        float x()const;

        //y-component of vector
        float y()const;

        //z-component of vector
        float z()const;

        //returns magnitude of vector
        float magnitude();

        //returns square magnitude of vector
        float sqrMagnitude()const;

        //returns same vector with magnitude 1
        Vector3 normalized();

        //returns copy of vector
        Vector3& operator = (const Vector3& v);

        //returns addition of two vectors
        Vector3 operator + (const Vector3& v)const;
        //returns addition of two vectors
        void operator += (const Vector3& v);

        //returns subtruction of two vectors
        Vector3 operator - (const Vector3& v)const;
        //returns subtruction of two vectors
        void operator -= (const Vector3& v);

        //returns vector multiplied to float
        Vector3 operator * (const float& f)const;
        //returns vector multiplied to float
        void operator *= (const float& f);

        //returns vector divided to float
        Vector3 operator / (const float& f)const;
        //returns vector divided to float
        void operator /= (const float& f);

        //returns lerp product of two vectors (a if t = 0, b if t = 1)
        static Vector3 Lerp(const Vector3& a, const Vector3& b, const float& t);

        //returns dot product of two vectors
        static float Dot(const Vector3& a, const Vector3& b);

        //returns cross product of two vectors
        static Vector3 Cross(const Vector3& a, const Vector3& b);
        //returns cross product of two vectors
        Vector3 operator % (const Vector3& v)const;
        //returns cross product of two vectors
        void operator %= (const Vector3& v);

        //create string from vector (0, 0, 0)
        std::string ToString()const;

        //check if vector equals to other
        bool operator== (const Vector3& v);
        //check if vector equals to other
        bool Equals(const Vector3& v)const;
    };
}