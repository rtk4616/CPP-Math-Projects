/*
 * =====================================================================================
 *
 *       Filename:  multiplication.cpp
 *
 *    Description:  Matrix multiplication per Eigen example
 *
 *        Version:  1.0
 *        Created:  06/04/17 19:10:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Brenton Horne <brentonhorne77@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <eigen3/Eigen/Dense>
using namespace Eigen;
int main()
{
  Matrix2d mat;
  mat << 1, 2,
         3, 4;
  Vector2d u(-1,1), v(2,0);
  std::cout << "Here is mat*mat:\n" << mat*mat << std::endl;
  std::cout << "Here is mat*u:\n" << mat*u << std::endl;
  std::cout << "Here is u^T*mat:\n" << u.transpose()*mat << std::endl;
  std::cout << "Here is u^T*v:\n" << u.transpose()*v << std::endl;
  std::cout << "Here is u*v^T:\n" << u*v.transpose() << std::endl;
  std::cout << "Let's multiply mat by itself" << std::endl;
  mat = mat*mat;
  std::cout << "Now mat is mat:\n" << mat << std::endl;
}
