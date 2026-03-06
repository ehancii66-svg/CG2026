#pragma once

#include "shape.h"

#include <vector>
#include <imgui.h>

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

    void set_closed();        //设置闭合

    void drop_last_point();         //删掉预览点（最后一个点）

   // Whether polygon has enough committed vertices to close.
   bool can_close() const;

   // Number of committed vertices (excluding preview point while drawing).
   int committed_vertex_count() const;
   

    // Overrides Shape's update function to adjust the end point during
    // interaction
    void update(float x, float y) override;

    void add_point(float x, float y);   //添加新的多边形端点

   private:
   std::vector<ImVec2> points_;

   bool is_closed_ = false;   //用来标记多边形是已闭合
};
}  // namespace USTC_CG
