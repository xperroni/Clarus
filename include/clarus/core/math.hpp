/*
Copyright (c) Helio Perroni Filho <xperroni@gmail.com>

This file is part of Clarus.

Clarus is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Clarus is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Clarus. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CLARUS_CORE_MATH_HPP
#define CLARUS_CORE_MATH_HPP

#include <clarus/core/list.hpp>

#include <boost/function.hpp>

#include <opencv2/opencv.hpp>

namespace clarus {
    typedef boost::function<double(double, double)> BinaryOp;

    typedef boost::function<double(double)> UnaryOp;

    List<double> vectorize(BinaryOp op, const List<double> &a, const List<double> &b);

    List<double> vectorize(UnaryOp op, const List<double> &a);

    double add(double a, double b);

    double sub(double a, double b);

    double mul(double a, double b);

    double div(double a, double b);

    double log(double x, double base);

    double log2(double x);

    /**
    \brief Returns the 2D coordinates of the highest value in the given matrix.
    */
    cv::Point argmax(const cv::Mat &data);

    /**
    \brief Returns the 2D coordinates of the lowest value in the given matrix.
    */
    cv::Point argmin(const cv::Mat &data);

    double min(const cv::Mat &data);

    double max(const cv::Mat &data);

    /**
    \brief Returns the average of all values in the given matrix.

    If the matrix is multi-channel, the average across all channels is returned.
    */
    double mean(const cv::Mat &data);

    /**
    \brief Returns a double type (CV_64F) row vector of averages across the given dimension.

    If the matrix is multi-channel, the average across all channels is returned.
    */
    cv::Mat mean(const cv::Mat &data, int dim);

    void shift(cv::Mat &data, int rows, int cols);

    cv::Mat pow(const cv::Mat &data, double power);
}

#endif
