#ifndef KMUCS_GRAPHICS_TRANSFORM_HPP
#define KMUCS_GRAPHICS_TRANSFORM_HPP

#include <cmath>
#include "vec.hpp"
#include "mat.hpp"
#include "operator.hpp"

namespace kmuvcl
{
    namespace math
    {
#ifndef M_PI
        const float M_PI = 3.14159265358979323846f;
#endif

        template <typename T>
        mat<4, 4, T> translate(T dx, T dy, T dz)
        {
            mat<4, 4, T> translateMat;

            // TODO: Fill up this function properly 

            return translateMat;
        }

        template <typename T>
        mat<4, 4, T> rotate(T angle, T x, T y, T z)
        {
            mat<4, 4, T> rotateMat;

            // TODO: Fill up this function properly 

            return rotateMat;
        }

        template<typename T>
        mat<4, 4, T> scale(T sx, T sy, T sz)
        {
            mat<4, 4, T> scaleMat;

            // TODO: Fill up this function properly 

            return scaleMat;
        }

        template<typename T>
        mat<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ)
        {
            mat<4, 4, T> viewMat;

            // TODO: Fill up this function properly 
            mat<3, 3, T> camAxis;
            
            // camAxis의 행벡터 선언
            vec<3, T> cam_x_axis, cam_y_axis, cam_z_axis;
            // camPos 열벡터 선언
            vec<3, T> camPos;

            // camAxis 연산 
            // vec(cam_z_axis) = norm vec(cX-eX, cY-eY, cZ-eZ)
            vec<3, T> sub;
            // sub(0) = centerX - eyeX;
            // sub(1) = centerY - eyeY;
            // sub(2) = centerZ - eyeZ;
            sub(0) = -(centerX - eyeX);
            sub(1) = -(centerY - eyeY);
            sub(2) = -(centerZ - eyeZ);
            // sub(0) = abs(centerX - eyeX);
            // sub(1) = abs(centerY - eyeY);
            // sub(2) = abs(centerZ - eyeZ);

            //단위벡터화

            T norm;
            norm = sqrt(pow(sub(0), 2) + pow(sub(1),2) + pow(sub(2),2));
            
            for(int i=0; i<3; i++)
            {
                cam_z_axis(i) = (sub(i)/norm) ;
            }

            // vec(cam_x_axis) = vec(upX upY upZ) X vec(cam_z_axis)
            vec<3, T> up;
            up(0) = upX;
            up(1) = upY;
            up(2) = upZ;

            //단위벡터화

            sub = cross(up, cam_z_axis);
            norm = sqrt(pow(sub(0), 2) + pow(sub(1),2) + pow(sub(2),2));
            
            for(int i=0; i<3; i++)
            {
                cam_x_axis(i) = (sub(i)/norm) ;
            }

            // vec(cam_y_axis) = vec(cam_z_axis) X vec(cam_x_axis)
            //단위벡터화

            sub = cross(cam_z_axis, cam_x_axis);
            norm = sqrt(pow(sub(0), 2) + pow(sub(1),2) + pow(sub(2),2));
            
            for(int i=0; i<3; i++)
            {
                cam_y_axis(i) = (sub(i)/norm) ;
            }

            // camPos 연산
            camPos(0) = -eyeX;
            camPos(1) = -eyeY;
            camPos(2) = -eyeZ;

            // result 1
            camAxis.set_ith_row(0,cam_x_axis);
            camAxis.set_ith_row(1,cam_y_axis);
            camAxis.set_ith_row(2,cam_z_axis);

            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; j++)
                {
                    viewMat(i,j) = camAxis(i,j);
                }
            }

            // result 2: camAxis(3x3) * camPos(3x1)
            for(int i=0; i<3; i++)
            {
                viewMat(i,3)= (camAxis*camPos)(i);
            }
            viewMat(3,3) = 1;

            return viewMat;
        }

        template<typename T>
        mat<4, 4, T> ortho(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
            mat<4, 4, T> orthoMat;
            
            // TODO: Fill up this function properly 

            return orthoMat;
        }

        template<typename T>
        mat<4, 4, T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
           mat<4, 4, T> frustumMat;

           // TODO: Fill up this function properly 

           return frustumMat;
        }

        template<typename T>
        mat<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar)
        {
          T  right = 0;
          T  top = 0;

          // TODO: Fill up this function properly 

          return frustum(-right, right, -top, top, zNear, zFar);
        }
    }
}
#endif
