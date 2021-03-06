﻿#pragma once

enum Side
{
    SIDE_LEFT,
    SIDE_RIGHT
};

struct AxisAlignedBoundingBox
{
    Eigen::Vector3f begin { INFINITY, INFINITY, INFINITY };
    Eigen::Vector3f end { -INFINITY, -INFINITY, -INFINITY };

    Eigen::Vector3f getCenter() const
    {
        return (begin + end) / 2;
    }

    float getCenter(const int32_t i) const
    {
        return (begin[i] + end[i]) / 2;
    }

    Eigen::Vector3f getCorner(const int32_t i) const
    {
        switch (i)
        {
        case 0:
            return { begin[0], begin[1], begin[2] };
        case 1:
            return { begin[0], begin[1], end[2] };
        case 2:
            return { begin[0], end[1], begin[2] };
        case 3:
            return { begin[0], end[1], end[2] };
        case 4:
            return { end[0], begin[1], begin[2] };
        case 5:
            return { end[0], begin[1], end[2] };
        case 6:
            return { end[0], end[1], begin[2] };
        case 7:
            return { end[0], end[1], end[2] };
        default:
            return { 0, 0, 0 };
        }
    }

    AxisAlignedBoundingBox getHalf(const int32_t i, const Side side) const
    {
        AxisAlignedBoundingBox half = *this;

        const float center = (begin[i] + end[i]) / 2;

        if (side == SIDE_LEFT)
            half.end[i] = center;
        else
            half.begin[i] = center;

        return half;
    }

    AxisAlignedBoundingBox merge(const AxisAlignedBoundingBox& right) const
    {
        return { begin.cwiseMin(right.begin), end.cwiseMax(right.end) };
    }

    float getSize(const int32_t i) const
    {
        return end[i] - begin[i];
    }

    float getSizeMax() const
    {
        return (end - begin).maxCoeff();
    }

    float getRadius() const
    {
        return getSizeMax() / 2;
    }

    void addPoint(const Eigen::Vector3f& point)
    {
        begin = begin.cwiseMin(point);
        end = end.cwiseMax(point);
    }
};
