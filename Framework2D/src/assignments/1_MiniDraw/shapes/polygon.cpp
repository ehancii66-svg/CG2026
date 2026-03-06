#include "polygon.h"

#include <imgui.h>

namespace USTC_CG
{
Polygon::Polygon(float start_point_x, float start_point_y) {
    points_.push_back(ImVec2(start_point_x, start_point_y));
    points_.push_back(ImVec2(start_point_x, start_point_y));
}

void Polygon::draw(const Config& config) const {
    if(points_.empty()){
        return;
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    std::vector<ImVec2> draw_points;
    draw_points.reserve(points_.size());

    for(auto pt : points_){
        draw_points.push_back(ImVec2(config.bias[0] + pt.x, config.bias[1] + pt.y));
    }

    if(config.show_fill && draw_points.size() > 2) {
        draw_list->AddConvexPolyFilled(
            draw_points.data(),
            draw_points.size(),
            IM_COL32(
                config.fill_color[0],
                config.fill_color[1],
                config.fill_color[2],
                config.fill_color[3]));
    }

    ImDrawFlags flags = is_closed_ ? ImDrawFlags_Closed : ImDrawFlags_None;

    draw_list->AddPolyline(
        draw_points.data(),
        draw_points.size(),
        IM_COL32(
            config.line_color[0],
            config.line_color[1],
            config.line_color[2],
            config.line_color[3]),
        flags,              //根据右键自动判断是否闭合
        config.line_thickness);
}

void Polygon::update(float x, float y){
    if(!points_.empty()){
        points_.back() = ImVec2(x, y);
    }   
}

void Polygon::add_point(float x, float y){
    points_.push_back(ImVec2(x, y));
}

void Polygon::set_closed(){
    is_closed_ = true;
}

void Polygon::drop_last_point(){
    if(points_.size() > 1){
        points_.pop_back();
    }
}

}
