#include "freehand.h"

#include <imgui.h>

namespace USTC_CG
{
Freehand::Freehand(float start_point_x, float start_point_y) {
    points_.push_back(ImVec2(start_point_x, start_point_y));
}

void Freehand::draw(const Config& config) const {
    if(points_.size() < 2){
        return;
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    std::vector<ImVec2> draw_points;
    draw_points.reserve(points_.size());

    for(auto pt : points_){
        draw_points.push_back(ImVec2(config.bias[0] + pt.x, config.bias[1] + pt.y));
    }

    draw_list->AddPolyline(
        draw_points.data(),
        draw_points.size(),
        IM_COL32(
            config.line_color[0],
            config.line_color[1],
            config.line_color[2],
            config.line_color[3]),
        ImDrawFlags_None,             //不自动闭合
        config.line_thickness);
}

void Freehand::update(float x, float y){
    if(!points_.empty()){
        points_.push_back(ImVec2(x, y));
    }   
}

}
