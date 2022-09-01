#include "Vector3.hpp"

#include <cmath>
#include <stdexcept>
#include <sstream>

namespace MathEngine{
    Vector3::Vector3():_x(0.0),_y(0.0),_z(0.0){}
    Vector3::Vector3(const float& x, const float& y, const float& z):_x(x),_y(y),_z(z){}
    Vector3::Vector3(const Vector3& v):_x(v._x),_y(v._y),_z(v._z){}
    Vector3::Vector3(const float& f):_x(f),_y(f),_z(f){}

    Vector3::~Vector3(){}

    float Vector3::x()const{return _x;}
    float Vector3::y()const{return _y;}
    float Vector3::z()const{return _z;}

    float Vector3::magnitude(){
        if (_magnitude == -1){
            _magnitude = std::sqrt(_x*_x + _y*_y + _z*_z);
        }
        return _magnitude;
    }

    float Vector3::sqrMagnitude()const{
        return _x*_x + _y*_y + _z*_z;
    }

    Vector3 Vector3::normalized(){
        if (magnitude() == 0)
            throw std::runtime_error("Can't calculate normalized vector from zero vector!");
        return *this / _magnitude;
    }

    Vector3& Vector3::operator= (const Vector3& v){
        _x = v._x;
        _y = v._y;
        _z = v._z;
        return *this;
    }

    Vector3 Vector3::operator+ (const Vector3& v)const{
        return Vector3(_x + v._x, _y + v._y, _z + v._z);
    }

    void Vector3::operator+= (const Vector3& v){
        _x += v._x;
        _y += v._y;
        _z += v._z;
    }

    Vector3 Vector3::operator- (const Vector3& v)const{
        return Vector3(_x - v._x, _y - v._y, _z - v._z);
    }

    void Vector3::operator-= (const Vector3& v){
        _x -= v._x;
        _y -= v._y;
        _z -= v._z;
    }

    Vector3 Vector3::operator* (const float& f)const{
        return Vector3(_x * f, _y * f, _z * f);
    }

    void Vector3::operator*= (const float& f){
        _x *= f;
        _y *= f;
        _z *= f;
    }

    Vector3 Vector3::operator/ (const float& f)const{
        if (f == 0)
            throw std::runtime_error("Can't divide vector on zero!");
        return Vector3(_x / f, _y / f, _z / f);
    }

    void Vector3::operator/= (const float& f){
        if (f == 0)
            throw std::runtime_error("Can't divide vector on zero!");
        _x /= f;
        _y /= f;
        _z /= f;
    }

    Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, const float& t){
        return a * (1 - t) + b * t;
    }

    float Vector3::Dot(const Vector3& a, const Vector3& b){
        return a._x * b._x + a._y * b._y + a._z * b._z;
    }

    Vector3 Vector3::Cross(const Vector3& a, const Vector3& b){
        return Vector3(
            a._y * b._z - a._z * b._y,
            a._z * b._x - a._x * b._z,
            a._x * b._y - a._y * b._x
        );
    }

    Vector3 Vector3::operator% (const Vector3& v)const{
        return Cross(*this, v);
    }

    void Vector3::operator%= (const Vector3& v){
        _x = _y * v._z - _z * v._y;
        _y = _z * v._x - _x * v._z;
        _z = _x * v._y - _y * v._x;
    }

    std::string Vector3::ToString()const{
        std::ostringstream result;
        result << "(" << _x << ", " << _y << ", " << _z << ")";
        return result.str();
    }

    bool Vector3::operator== (const Vector3& v){
        return v._x == _x && v._y == _y && v._z == _z;
    }

    bool Vector3::Equals(const Vector3& v)const{
        return v._x == _x && v._y == _y && v._z == _z;
    }
}