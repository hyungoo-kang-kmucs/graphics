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
            for(int i=0; i<4; i++)
            {
                translateMat(i,i) = 1;
            }

            translateMat(0,3) = dx;
            translateMat(1,3) = dy;
            translateMat(2,3) = dz;

            return translateMat;
        }

        template <typename T>
        mat<4, 4, T> rotate(T angle, T x, T y, T z)
        {
            mat<4, 4, T> rotateMat;


            // TODO: Fill up this function properly
            T ux, uy, uz, norm;
            norm = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
            ux = (x/norm);
            uy = (y/norm);
            uz = (z/norm);

            T theta = angle*M_PI/180;

            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; j++)
                {
                    rotateMat(i,j) += (1-cos(theta));
                }
            }

            for(int i=0; i<3; i++)
            {
                rotateMat(i,0) = rotateMat(i,0)*ux;
                rotateMat(i,1) = rotateMat(i,1)*uy;
                rotateMat(i,2) = rotateMat(i,2)*uz;
            }

            for(int j=0; j<3; j++)
            {
                rotateMat(0,j) = rotateMat(0,j)*ux;
                rotateMat(1,j) = rotateMat(1,j)*uy;
                rotateMat(2,j) = rotateMat(2,j)*uz;
            }

            rotateMat(0,0) += cos(theta);
            rotateMat(1,1) += cos(theta);
            rotateMat(2,2) += cos(theta);

            rotateMat(2,1) += ux*sin(theta);
            rotateMat(0,2) += uy*sin(theta);
            rotateMat(1,0) += uz*sin(theta);

            rotateMat(1,2) -= ux*sin(theta);
            rotateMat(2,0) -= uy*sin(theta);
            rotateMat(0,1) -= uz*sin(theta);            

            rotateMat(3,3) = 1;

            return rotateMat;
        }

        template<typename T>
        mat<4, 4, T> scale(T sx, T sy, T sz)
        {
            mat<4, 4, T> scaleMat;

            // TODO: Fill up this function properly 
            scaleMat(0,0) = sx;
            scaleMat(1,1) = sy;
            scaleMat(2,2) = sz;
            scaleMat(3,3) = 1;

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

            // camAxis 1 of 3) vec(cam_z_axis) = norm( vec(cX-eX, cY-eY, cZ-eZ) )
            vec<3, T> sub;
            sub(0) = -(centerX - eyeX);
            sub(1) = -(centerY - eyeY);
            sub(2) = -(centerZ - eyeZ);

            T norm;
            norm = sqrt(pow(sub(0), 2) + pow(sub(1),2) + pow(sub(2),2));
            
            for(int i=0; i<3; i++)
            {
                cam_z_axis(i) = (sub(i)/norm) ;
            }

            // camAxis 2 of 3) vec(cam_x_axis) = norm( vec(upX,upY,upZ) X vec(cam_z_axis) )
            vec<3, T> up;
            up(0) = upX;
            up(1) = upY;
            up(2) = upZ;

            sub = cross(up, cam_z_axis);
            norm = sqrt(pow(sub(0), 2) + pow(sub(1),2) + pow(sub(2),2));
            
            for(int i=0; i<3; i++)
            {
                cam_x_axis(i) = (sub(i)/norm) ;
            }

            // camAxis 3 of 3) vec(cam_y_axis) = norm( vec(cam_z_axis) X vec(cam_x_axis) )
            sub = cross(cam_z_axis, cam_x_axis);
            norm = sqrt(pow(sub(0), 2) + pow(sub(1),2) + pow(sub(2),2));
            
            for(int i=0; i<3; i++)
            {
                cam_y_axis(i) = (sub(i)/norm) ;
            }

            // camPos
            camPos(0) = -eyeX;
            camPos(1) = -eyeY;
            camPos(2) = -eyeZ;

            // result 1: camAxis(3x3)
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

            // result 3: etc
            viewMat(3,3) = 1;

            return viewMat;
        }

        template<typename T>
        mat<4, 4, T> ortho(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
            mat<4, 4, T> orthoMat;
            
            // TODO: Fill up this function properly 
            for(int i=0; i<4; i++)
            {
                orthoMat(i,i) += 1;
            }

            orthoMat(0,3) -= (right + left)/2;
            orthoMat(1,3) -= (top + bottom)/2;
            orthoMat(2,3) += (farVal + nearVal)/2;

            
            orthoMat(0,0) = orthoMat(0,0)*(2/(right - left));
            orthoMat(0,3) = orthoMat(0,3)*(2/(right - left));
            
            orthoMat(1,1) = orthoMat(1,1)*(2/(top - bottom));
            orthoMat(1,3) = orthoMat(1,3)*(2/(top - bottom));

            orthoMat(2,2) = orthoMat(2,2)*(2/(nearVal - farVal));
            orthoMat(2,3) = orthoMat(2,3)*(2/(nearVal - farVal));

            return orthoMat;
        }

        template<typename T>
        mat<4, 4, T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
           mat<4, 4, T> frustumMat;

           // TODO: Fill up this function properly 
           frustumMat(0,0) = (2*nearVal)/(right-left);
           frustumMat(0,2) = (right+left)/(right-left);

           frustumMat(1,1) = (2*nearVal)/(top-bottom);
           frustumMat(1,2) = (top+bottom)/(top-bottom);

           frustumMat(2,2) = -(farVal+nearVal)/(farVal-nearVal);
           frustumMat(2,3) = -(2*farVal*nearVal)/(farVal-nearVal);

           frustumMat(3,2) = -1;


           return frustumMat;
        }

        template<typename T>
        mat<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar)
        {
          T  right = 0;
          T  top = 0;

          // TODO: Fill up this function properly 
          T theta = (fovy*M_PI)/ 180;
          top = zNear * tan(theta/2);
          right = top * aspect;

          return frustum(-right, right, -top, top, zNear, zFar);
        }
    }
}
#endif
