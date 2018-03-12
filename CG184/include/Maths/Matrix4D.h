#pragma once
#include "Vector4D.h"

#define OLD_IMP 1

#if OLD_IMP == 0

namespace CG184 
{
    // TODO Create Template classes for Matrices
    class Matrix4D
    {
    public:

        //! Basic Matrix Structure.
        //! Matrix4D arr = {
        //!     {0, 4,  8, 12},
        //!     {1, 5,  9, 13},
        //!     {2, 6, 10, 14},
        //!     {3, 7, 11, 15}
        //! };
        float elements[4 * 4];
        

        Matrix4D();
        Matrix4D(float diagonal);
        Matrix4D(Vector4F col1, Vector4F col2, Vector4F col3, Vector4F col4);
        Matrix4D(const Matrix4D& mat);

        Matrix4D(
            float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22);


        Matrix4D(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);

        Vector4F getColumn(int index);
        

        void SetRow(int i, const Vector4F& vec);
        void SetColumn(int i, const Vector4F& vec);

        Matrix4D multiply(float scalar);
        Matrix4D divide(float scalar);
        Matrix4D multiply(const Matrix4D& other);
        Vector3F multiply(const Vector3F& other);
        Vector4F multiply(const Vector4F& other);

        // TODO add more Set functions
        void Set(float diagonal);
        void Set(Vector4F col1, Vector4F col2, Vector4F col3, Vector4F col4);

        Matrix4D& operator=(const Matrix4D& rhs);

        // TODO Implement the inverse and matrix multiplication
        friend Matrix4D operator*(Matrix4D left, const Matrix4D& right);
        Matrix4D& operator*=(const Matrix4D& other);

        float at(int i);
        float operator[](int i);

        Matrix4D transpose() const;
        void inverse();

        ~Matrix4D();

    private:
        
    };

    std::ostream& operator<< (std::ostream& stream, const Matrix4D& mat);
    
}   // End of CG184


#else


namespace CG184
{
    template <typename T>
    class Matrix4
    {
    public:
        static_assert(std::is_floating_point<T>::value,
            "Matrix only can be instantiated with floating point types");

        //! Basic Matrix Structure.
        //! Matrix4D arr = {
        //!     {0, 4,  8, 12},
        //!     {1, 5,  9, 13},
        //!     {2, 6, 10, 14},
        //!     {3, 7, 11, 15}
        //! };
         T elements[4 * 4];

    public:
        //! Constructs default vector (0, 0).
        Matrix4();

        //! Set all diagonal components to \p _val.
        explicit Matrix4(T _val);

        //! Constructs Matrix with given column vectors \p col1, \p col2, \p col3, \p col4.
        template <typename U>
        Matrix4(Vector4<U> col1, Vector4<U> col2, Vector4<U> col3, Vector4<U> col4);

        //! Copy constructor.
        template <typename U>
        Matrix4(const Matrix4<U>& mat);

        //! Constructs Matrix with given parameters
        Matrix4(
            T m00, T m01, T m02,
            T m10, T m11, T m12,
            T m20, T m21, T m22);


        Matrix4(
            T m00, T m01, T m02, T m03,
            T m10, T m11, T m12, T m13,
            T m20, T m21, T m22, T m23,
            T m30, T m31, T m32, T m33);

        //! Get the column vector at index val
        Vector4<T> get_column(int index);

        //! Set the row vector at index val
        template <typename U>
        void set_row(int i, const Vector4<U>& vec);

        //! Set the column vector at index val
        template <typename U>
        void set_column(int i, const Vector4<U>& vec);

        //! Multiply with a scalar val
        template <typename U>
        Matrix4<T> multiply(U scalar);

        //! Divide with a scalar val
        template <typename U>
        Matrix4<T> divide(U scalar);

        //! Computes MatA * MatOther
        template <typename U>
        Matrix4<T> multiply(const Matrix4<U>& other);

        Vector3<T> multiply(const Vector3<T>& other);
        Vector4<T> multiply(const Vector4<T>& other);

        template <typename U>
        void set_diagonal(U diagonal);

        void set_columns(Vector4<T> col1, Vector4<T> col2, Vector4<T> col3, Vector4<T> col4);

        //Matrix4D& operator=(const Matrix4<T>& rhs);

        // TODO Implement the inverse and matrix multiplication
        //friend Matrix4<T> operator*(Matrix4<T> left, const Matrix4<T>& right);
        //Matrix4<T>& operator*=(const Matrix4<T>& other);

        T at(int i);
        T operator[](int i);

        Matrix4<T> transpose() const;
        
        //! Compute the inverse of the matrix
        void inverse();

        //! Compute the determinant of the matrix
        T determinant() const;

    };

    typedef Matrix4<float> Matrix4D;


    //! Positive sign operator.
    template <typename T>
    Matrix4<T> operator+(const Matrix4<T>& a)
    {
        return a;
    }

    //! Negative sign operator.
    template <typename T>
    Matrix4<T> operator-(const Matrix4<T>& a)
    {
        return Matrix4<T>(  -a.elements[0], -a.elements[4], -a.elements[ 8], -a.elements[12],
                            -a.elements[1], -a.elements[5], -a.elements[ 9], -a.elements[13], 
                            -a.elements[2], -a.elements[6], -a.elements[10], -a.elements[14], 
                            -a.elements[3], -a.elements[7], -a.elements[11], -a.elements[15]);
    }

    //! Computes (Mat a) * (Mat b).
    template <typename T>
    Matrix4<T> operator*(const Matrix4<T>& a, const Matrix4<T>& b) 
    {
        return a.multiply(b);
    }

    template <typename T>
    Matrix4<T>::Matrix4()
    {
        elements[0] = (T)1.0; elements[4] = (T)0.0; elements[ 8] = (T)0.0; elements[12] = (T)0.0;
        elements[1] = (T)0.0; elements[5] = (T)1.0; elements[ 9] = (T)0.0; elements[13] = (T)0.0;
        elements[2] = (T)0.0; elements[6] = (T)0.0; elements[10] = (T)1.0; elements[14] = (T)0.0;
        elements[3] = (T)0.0; elements[7] = (T)0.0; elements[11] = (T)0.0; elements[15] = (T)1.0;
    }

    template <typename T>
    Matrix4<T>::Matrix4(T _val)
    {
        elements[0] =   _val; elements[4] = (T)0.0; elements[ 8] = (T)0.0; elements[12] = (T)0.0;
        elements[1] = (T)0.0; elements[5] =   _val; elements[ 9] = (T)0.0; elements[13] = (T)0.0;
        elements[2] = (T)0.0; elements[6] = (T)0.0; elements[10] =   _val; elements[14] = (T)0.0;
        elements[3] = (T)0.0; elements[7] = (T)0.0; elements[11] = (T)0.0; elements[15] =   _val;
    }

    template <typename T>
    template <typename U>
    Matrix4<T>::Matrix4(Vector4<U> col1, Vector4<U> col2, Vector4<U> col3, Vector4<U> col4)
    {
        set_columns(col1, col2, col3, col4);
    }

    template <typename T>
    template <typename U>
    Matrix4<T>::Matrix4(const Matrix4<U>& mat)
    {
        for (uint32_t i = 0; i < 16; i++)
        {
            elements[i] = (T)mat.elements[i];
        }
    }

    template <typename T>
    Matrix4<T>::Matrix4(
        T m00, T m01, T m02,
        T m10, T m11, T m12,
        T m20, T m21, T m22)
    {
        set_columns(Vector4<T>(m00, m10, m20, 0.0), Vector4<T>(m01, m11, m21, 0.0), Vector4<T>(m02, m12, m22, 0.0), Vector4<T>(0.0, 0.0, 0.0, 1.0));
    }

    template <typename T>
    Matrix4<T>::Matrix4(
        T m00, T m01, T m02, T m03,
        T m10, T m11, T m12, T m13,
        T m20, T m21, T m22, T m23,
        T m30, T m31, T m32, T m33)
    {
        set_columns(Vector4<T>(m00, m10, m20, m03), Vector4<T>(m01, m11, m21, m13), Vector4<T>(m02, m12, m22, m23), Vector4<T>(m03, m13, m23, m33));
    }

    template <typename T>
    Vector4<T> Matrix4<T>::get_column(int index)
    {
        return Vector4<T>(elements[0 + index * 4], elements[1 + index * 4], elements[2 + index * 4], elements[3 + index * 4]);
    }


    template <typename T>
    template <typename U>
    void Matrix4<T>::set_row(int i, const Vector4<U>& vec)
    {
        elements[0 * 4 + i] = (T)vec.x;
        elements[1 * 4 + i] = (T)vec.y;
        elements[2 * 4 + i] = (T)vec.z;
        elements[3 * 4 + i] = (T)vec.w;
    }

    template <typename T>
    template <typename U>
    void Matrix4<T>::set_column(int i, const Vector4<U>& vec)
    {
        elements[0 + i * 4] = (T)vec.x;
        elements[1 + i * 4] = (T)vec.y;
        elements[2 + i * 4] = (T)vec.z;
        elements[3 + i * 4] = (T)vec.w;
    }

    template <typename T>
    template <typename U>
    Matrix4<T> Matrix4<T>::multiply(U scalar)
    {
        Matrix4<T> result;
        for (int i = 0; i < 16; i++)
        {
            result.elements[i] = elements[i] * (T)scalar;
        }
        return result;
    }

    template <typename T>
    template <typename U>
    Matrix4<T> Matrix4<T>::divide(U scalar)
    {
        assert(scalar != 0)

        Matrix4<T> result;
        for (int i = 0; i < 16; i++)
        {
            result.elements[i] = elements[i] / (T)scalar;
        }
        return result;
    }

    template <typename T>
    template <typename U>
    Matrix4<T> Matrix4<T>::multiply(const Matrix4<U>& other)
    {
        Matrix4<T> result;
        T data[16];
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                T sum = 0.0f;
                for (int e = 0; e < 4; e++)
                {
                    sum += elements[x + e * 4] * (T)other.elements[e + y * 4];
                }
                data[x + y * 4] = sum;
            }
        }
        std::memcpy(result.elements, data, 4 * 4 * sizeof(T));
        return result;
    }

    template <typename T>
    template <typename U>
    void Matrix4<T>::set_diagonal(U diagonal)
    {
        for (uint32_t i = 0; i < 16; i++)
        {
            elements[i] = 0.0f;
        }

        elements[0 + 0 * 4] = (T)diagonal;
        elements[1 + 1 * 4] = (T)diagonal;
        elements[2 + 2 * 4] = (T)diagonal;
        elements[3 + 3 * 4] = (T)diagonal;
    }

    template <typename T>
    void Matrix4<T>::set_columns(Vector4<T> col1, Vector4<T> col2, Vector4<T> col3, Vector4<T> col4)
    {
        elements[0 + 0 * 4] = col1.x; elements[1 + 0 * 4] = col1.y; elements[2 + 0 * 4] = col1.z; elements[3 + 0 * 4] = col1.w;
        elements[0 + 1 * 4] = col2.x; elements[1 + 1 * 4] = col2.y; elements[2 + 1 * 4] = col2.z; elements[3 + 1 * 4] = col2.w;
        elements[0 + 2 * 4] = col3.x; elements[1 + 2 * 4] = col3.y; elements[2 + 2 * 4] = col3.z; elements[3 + 2 * 4] = col3.w;
        elements[0 + 3 * 4] = col4.x; elements[1 + 3 * 4] = col4.y; elements[2 + 3 * 4] = col4.z; elements[3 + 3 * 4] = col4.w;
    }

    template <typename T>
    T Matrix4<T>::at(int i)
    {
        return elements[i];
    }

    template <typename T>
    T Matrix4<T>::operator[](int i)
    {
        return at(i);
    }

    template <typename T>
    Matrix4<T> Matrix4<T>::transpose() const
    {
        Matrix4<T> result(
            elements[ 0], elements[ 1], elements[ 2], elements[ 3],
            elements[ 4], elements[ 5], elements[ 6], elements[ 7],
            elements[ 8], elements[ 9], elements[10], elements[11],
            elements[12], elements[13], elements[14], elements[15]
        );

        return result;
    }

    template <typename T>
    void Matrix4<T>::inverse()
    {
        T d = determinant();
        Matrix4<T> m;
        m.elements[ 0] = elements[5] * elements[10] * elements[15] + elements[6] * elements[11] * elements[13] + elements[7] * elements[ 9] * elements[14] - elements[5] * elements[11] * elements[14] - elements[6] * elements[9] * elements[15] - elements[7] * elements[10] * elements[13];
        m.elements[ 1] = elements[1] * elements[11] * elements[14] + elements[2] * elements[ 9] * elements[15] + elements[3] * elements[10] * elements[13] - elements[1] * elements[10] * elements[15] - elements[2] * elements[11] * elements[13] - elements[3] * elements[9] * elements[14];
        m.elements[ 2] = elements[1] * elements[ 6] * elements[15] + elements[2] * elements[ 7] * elements[13] + elements[3] * elements[ 5] * elements[14] - elements[1] * elements[ 7] * elements[14] - elements[2] * elements[5] * elements[15] - elements[3] * elements[6] * elements[13];
        m.elements[ 3] = elements[1] * elements[ 7] * elements[10] + elements[2] * elements[ 5] * elements[11] + elements[3] * elements[ 6] * elements[ 9] - elements[1] * elements[ 6] * elements[11] - elements[2] * elements[7] * elements[9] - elements[3] * elements[5] * elements[10];
        m.elements[ 4] = elements[4] * elements[11] * elements[14] + elements[6] * elements[ 8] * elements[15] + elements[7] * elements[10] * elements[12] - elements[4] * elements[10] * elements[15] - elements[6] * elements[11] * elements[12] - elements[7] * elements[8] * elements[14];
        m.elements[ 5] = elements[0] * elements[10] * elements[15] + elements[2] * elements[11] * elements[12] + elements[3] * elements[ 8] * elements[14] - elements[0] * elements[11] * elements[14] - elements[2] * elements[8] * elements[15] - elements[3] * elements[10] * elements[12];
        m.elements[ 6] = elements[0] * elements[ 7] * elements[14] + elements[2] * elements[ 4] * elements[15] + elements[3] * elements[ 6] * elements[12] - elements[0] * elements[ 6] * elements[15] - elements[2] * elements[7] * elements[12] - elements[3] * elements[4] * elements[14];
        m.elements[ 7] = elements[0] * elements[ 6] * elements[11] + elements[2] * elements[ 7] * elements[ 8] + elements[3] * elements[ 4] * elements[10] - elements[0] * elements[ 7] * elements[10] - elements[2] * elements[4] * elements[11] - elements[3] * elements[6] * elements[8];
        m.elements[ 8] = elements[4] * elements[ 9] * elements[15] + elements[5] * elements[11] * elements[12] + elements[7] * elements[ 8] * elements[13] - elements[4] * elements[11] * elements[13] - elements[5] * elements[8] * elements[15] - elements[7] * elements[9] * elements[12];
        m.elements[ 9] = elements[0] * elements[11] * elements[13] + elements[1] * elements[ 8] * elements[15] + elements[3] * elements[ 9] * elements[12] - elements[0] * elements[ 9] * elements[15] - elements[1] * elements[11] * elements[12] - elements[3] * elements[8] * elements[13];
        m.elements[10] = elements[0] * elements[ 5] * elements[15] + elements[1] * elements[ 7] * elements[12] + elements[3] * elements[ 4] * elements[13] - elements[0] * elements[ 7] * elements[13] - elements[1] * elements[4] * elements[15] - elements[3] * elements[5] * elements[12];
        m.elements[11] = elements[0] * elements[ 7] * elements[ 9] + elements[1] * elements[ 4] * elements[11] + elements[3] * elements[ 5] * elements[ 8] - elements[0] * elements[ 5] * elements[11] - elements[1] * elements[7] * elements[8] - elements[3] * elements[4] * elements[9];
        m.elements[12] = elements[4] * elements[10] * elements[13] + elements[5] * elements[ 8] * elements[14] + elements[6] * elements[ 9] * elements[12] - elements[4] * elements[ 9] * elements[14] - elements[5] * elements[10] * elements[12] - elements[6] * elements[8] * elements[13];
        m.elements[13] = elements[0] * elements[ 9] * elements[14] + elements[1] * elements[10] * elements[12] + elements[2] * elements[ 8] * elements[13] - elements[0] * elements[10] * elements[13] - elements[1] * elements[8] * elements[14] - elements[2] * elements[9] * elements[12];
        m.elements[14] = elements[0] * elements[ 6] * elements[13] + elements[1] * elements[ 4] * elements[14] + elements[2] * elements[ 5] * elements[12] - elements[0] * elements[ 5] * elements[14] - elements[1] * elements[6] * elements[12] - elements[2] * elements[4] * elements[13];
        m.elements[15] = elements[0] * elements[ 5] * elements[10] + elements[1] * elements[ 6] * elements[ 8] + elements[2] * elements[ 4] * elements[ 9] - elements[0] * elements[ 6] * elements[9] - elements[1] * elements[4] * elements[10] - elements[2] * elements[5] * elements[8];
        
        m = m.divide(d);
    }

    template<typename T>
    T Matrix4<T>::determinant() const
    {
        return
              elements[0] * elements[5] * elements[10] * elements[15] + elements[0] * elements[6] * elements[11] * elements[13] + elements[0] * elements[7] * elements[ 9] * elements[14]
            + elements[1] * elements[4] * elements[11] * elements[14] + elements[1] * elements[6] * elements[ 8] * elements[15] + elements[1] * elements[7] * elements[10] * elements[12]
            + elements[2] * elements[4] * elements[ 9] * elements[15] + elements[2] * elements[5] * elements[11] * elements[12] + elements[2] * elements[7] * elements[ 8] * elements[13]
            + elements[3] * elements[4] * elements[10] * elements[13] + elements[3] * elements[5] * elements[ 8] * elements[14] + elements[3] * elements[6] * elements[ 9] * elements[12]
            - elements[0] * elements[5] * elements[11] * elements[14] - elements[0] * elements[6] * elements[ 9] * elements[15] - elements[0] * elements[7] * elements[10] * elements[13]
            - elements[1] * elements[4] * elements[10] * elements[15] - elements[1] * elements[6] * elements[11] * elements[12] - elements[1] * elements[7] * elements[ 8] * elements[14]
            - elements[2] * elements[4] * elements[11] * elements[13] - elements[2] * elements[5] * elements[ 8] * elements[15] - elements[2] * elements[7] * elements[ 9] * elements[12]
            - elements[3] * elements[4] * elements[ 9] * elements[14] - elements[3] * elements[5] * elements[10] * elements[12] - elements[3] * elements[6] * elements[ 8] * elements[13];
    }
    

    template <typename T>
    std::ostream& operator<< (std::ostream& stream, const Matrix4<T>& mat) {
        stream  << "(" << mat.elements[0] << ", " << mat.elements[4] << ", " << mat.elements[8] << ", " << mat.elements[12] << "," << '\n'
                << "(" << mat.elements[1] << ", " << mat.elements[5] << ", " << mat.elements[9] << ", " << mat.elements[13] << "," << '\n'
                << "(" << mat.elements[2] << ", " << mat.elements[6] << ", " << mat.elements[10] << ", " << mat.elements[14] << "," << '\n'
                << "(" << mat.elements[3] << ", " << mat.elements[7] << ", " << mat.elements[11] << ", " << mat.elements[15] << ")" << '\n';
        return stream;
    }
}


#endif