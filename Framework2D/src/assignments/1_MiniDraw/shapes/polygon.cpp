#include "polygon.h"

#include <imgui.h>

namespace USTC_CG
{
Polygon::Polygon(float start_point_x, float start_point_y){
    points_.push_back(ImVec2(start_point_x, start_point_y));
    points_.push_back(ImVec2(start_point_x, start_point_y));
}


}
