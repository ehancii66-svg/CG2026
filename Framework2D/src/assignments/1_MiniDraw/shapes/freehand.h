#pragma once

#include "shape.h"

#include <vector>
#include <imgui.h>

namespace USTC_CG
{
class Freehand : public Shape
{
   public:
    Freehand() = default;

    // Constructor to initialize a Freehand with start and end coordinates
    Freehand(float start_point_x, float start_point_y);

    virtual ~Freehand() = default;

    // Overrides draw function to implement Freehand-specific drawing logic
    void draw(const Config& config) const override;

    // Overrides Shape's update function to adjust the end point during
    // interaction
    void update(float x, float y) override; //稍作修改，用来添加实时点

   private:
   std::vector<ImVec2> points_;
};
}  // namespace USTC_CG
