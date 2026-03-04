#pragma once

#include "shape.h"

#include <vector>

namespace USTC_CG
{
class Polygon : public Shape
{
   public:
    Polygon() = default;

    // Constructor to initialize a Polygon with start and end coordinates
    Polygon(float start_point_x, float start_point_y);

    virtual ~Polygon() = default;

    // Overrides draw function to implement Polygon-specific drawing logic
    void draw(const Config& config) const override;

    // Overrides Shape's update function to adjust the end point during
    // interaction
    void update(float x, float y) override;

    void add_point(float x, float y);   //添加新的点

   private:
   std::vector<ImVec2> points_;
};
}  // namespace USTC_CG
