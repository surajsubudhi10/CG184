//#include <Maths/Matrix4D.h>
//
//#include <cassert>
//#include <iostream>
//#include <cstring>
//#include <cmath>
//
//
//#if OLD_IMP == 0
//
//namespace CG184
//{
//    Matrix4D::Matrix4D()
//    {
//        Set(1.0f);
//    }
//
//    Matrix4D::~Matrix4D()
//    {
//    }
//
//    Matrix4D::Matrix4D(float diagonal)
//    {
//        Set(diagonal);
//
//    }
//
//    Matrix4D::Matrix4D(Vector4F col1, Vector4F col2, Vector4F col3, Vector4F col4)
//    {
//        Set(col1, col2, col3, col4);
//    }
//
//    Matrix4D::Matrix4D(const Matrix4D& mat)
//    {
//        for (uint32_t i = 0; i < 16; i++)
//        {
//            elements[i] = mat.elements[i];
//        }
//    }
//
//    Matrix4D::Matrix4D(
//        float m00, float m01, float m02,
//        float m10, float m11, float m12,
//        float m20, float m21, float m22)
//    {
//        Set(Vector4F(m00, m10, m20, 0.0), Vector4F(m01, m11, m21, 0.0), Vector4F(m02, m12, m22, 0.0), Vector4F(0.0, 0.0, 0.0, 0.0));
//    }
//
//    Matrix4D::Matrix4D(
//        float m00, float m01, float m02, float m03,
//        float m10, float m11, float m12, float m13,
//        float m20, float m21, float m22, float m23,
//        float m30, float m31, float m32, float m33)
//    {
//        Set(Vector4F(m00, m10, m20, m30), Vector4F(m01, m11, m21, m31), Vector4F(m02, m12, m22, m32), Vector4F(m03, m13, m23, m33));
//    }
//
//    Vector4F Matrix4D::getColumn(int index)
//    {
//        return Vector4F(elements[0 + index * 4], elements[1 + index * 4], elements[2 + index * 4], elements[3 + index * 4]);
//    }
//
//
//    void Matrix4D::SetRow(int i, const Vector4F& vec)
//    {
//        elements[0 * 4 + i] = vec.x;
//        elements[1 * 4 + i] = vec.y;
//        elements[2 * 4 + i] = vec.z;
//        elements[3 * 4 + i] = vec.w;
//    }
//
//    void Matrix4D::SetColumn(int i, const Vector4F& vec)
//    {
//        elements[0 + i * 4] = vec.x;
//        elements[1 + i * 4] = vec.y;
//        elements[2 + i * 4] = vec.z;
//        elements[3 + i * 4] = vec.w;
//    }
//
//    Matrix4D Matrix4D::multiply(float scalar)
//    {
//        Matrix4D result;
//        for (int i = 0; i < 16; i++)
//        {
//            result.elements[i] = elements[i] * scalar;
//        }
//        return result;
//    }
//
//    Matrix4D Matrix4D::divide(float scalar)
//    {
//        assert(scalar != 0);
//
//        Matrix4D result;
//        for (int i = 0; i < 16; i++)
//        {
//            result.elements[i] = elements[i] / scalar;
//        }
//        return result;
//    }
//
//    Matrix4D Matrix4D::multiply(const Matrix4D& other)
//    {
//        Matrix4D result;
//        float data[16];
//        for (int y = 0; y < 4; y++)
//        {
//            for (int x = 0; x < 4; x++)
//            {
//                float sum = 0.0f;
//                for (int e = 0; e < 4; e++)
//                {
//                    sum += elements[x + e * 4] * other.elements[e + y * 4];
//                }
//                data[x + y * 4] = sum;
//            }
//        }
//        std::memcpy(result.elements, data, 4 * 4 * sizeof(float));
//        return result;
//    }
//
//    void Matrix4D::Set(float diagonal)
//    {
//        for (uint32_t i = 0; i < 16; i++)
//        {
//            elements[i] = 0.0f;
//        }
//        elements[0 + 0 * 4] = diagonal;
//        elements[1 + 1 * 4] = diagonal;
//        elements[2 + 2 * 4] = diagonal;
//        elements[3 + 3 * 4] = diagonal;
//    }
//
//    void Matrix4D::Set(Vector4F col1, Vector4F col2, Vector4F col3, Vector4F col4) 
//    {
//        elements[0 + 0 * 4] = col1.x; elements[1 + 0 * 4] = col1.y; elements[2 + 0 * 4] = col1.z; elements[3 + 0 * 4] = col1.w;
//        elements[0 + 1 * 4] = col2.x; elements[1 + 1 * 4] = col2.y; elements[2 + 1 * 4] = col2.z; elements[3 + 1 * 4] = col2.w;
//        elements[0 + 2 * 4] = col3.x; elements[1 + 2 * 4] = col3.y; elements[2 + 2 * 4] = col3.z; elements[3 + 2 * 4] = col3.w;
//        elements[0 + 3 * 4] = col4.x; elements[1 + 3 * 4] = col4.y; elements[2 + 3 * 4] = col4.z; elements[3 + 3 * 4] = col4.w;
//    }
//
//    Vector3F Matrix4D::multiply(const Vector3F& other)
//    {
//        return Vector3F( elements[0] * other.x + elements[4] * other.y + elements[8] * other.z + elements[12] * 1,
//                         elements[1] * other.x + elements[5] * other.y + elements[9] * other.z + elements[13] * 1,
//                         elements[2] * other.x + elements[6] * other.y + elements[10] * other.z + elements[14] * 1
//            );
//    }
//
//    Vector4F Matrix4D::multiply(const Vector4F& other)
//    {
//        return Vector4F(elements[0] * other.x + elements[4] * other.y + elements[ 8] * other.z + elements[12] * 1,
//                        elements[1] * other.x + elements[5] * other.y + elements[ 9] * other.z + elements[13] * 1,
//                        elements[2] * other.x + elements[6] * other.y + elements[10] * other.z + elements[14] * 1,
//                        elements[3] * other.x + elements[7] * other.y + elements[11] * other.z + elements[15] * 1
//        );
//    }
//
//    Matrix4D Matrix4D::transpose() const
//    {
//        Matrix4D result(
//            elements[0], elements[1], elements[2], elements[3],
//            elements[4], elements[5], elements[6], elements[7],
//            elements[8], elements[9], elements[10], elements[11],
//            elements[12], elements[13], elements[14], elements[15]
//        );
//
//        return result;
//    }
//
//    Matrix4D& Matrix4D::operator=(const Matrix4D& rhs) 
//    {
//        if (this == &rhs) {
//            return *this;
//        }
//
//        for (uint32_t i = 0; i < 16; i++) {
//            elements[i] = rhs.elements[i];
//        }
//
//        return *this;
//    }
//
//    float Matrix4D::at(int i)
//    {
//        return elements[i];
//    }
//
//    float Matrix4D::operator[](int i)
//    {
//        return at(i);
//    }
//
//    Matrix4D operator*(Matrix4D left, const Matrix4D &right) {
//
//        Matrix4D result;
//        float data[16];
//        for (int y = 0; y < 4; y++)
//        {
//            for (int x = 0; x < 4; x++)
//            {
//                float sum = 0.0f;
//                for (int e = 0; e < 4; e++)
//                {
//                    sum += left.elements[x + e * 4] * right.elements[e + y * 4];
//                }
//                data[x + y * 4] = sum;
//            }
//        }
//        std::memcpy(result.elements, data, 4 * 4 * sizeof(float));
//        return result;
//
//    }
//
//    std::ostream& operator<< (std::ostream& stream, const Matrix4D& mat){
//        stream << "(" << mat.elements[0] << ", " << mat.elements[4] << ", " << mat.elements[ 8] << ", " << mat.elements[12] << "," << '\n'
//               << "(" << mat.elements[1] << ", " << mat.elements[5] << ", " << mat.elements[ 9] << ", " << mat.elements[13] << "," << '\n'
//               << "(" << mat.elements[2] << ", " << mat.elements[6] << ", " << mat.elements[10] << ", " << mat.elements[14] << "," << '\n'
//               << "(" << mat.elements[3] << ", " << mat.elements[7] << ", " << mat.elements[11] << ", " << mat.elements[15] << ")" << '\n';
//        return stream;
//    }
//
//
//}   // End of CG184
//
//
//#endif