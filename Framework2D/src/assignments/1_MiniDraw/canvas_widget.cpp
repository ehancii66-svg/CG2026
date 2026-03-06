#include "canvas_widget.h"

#include <cmath>
#include <iostream>

#include "imgui.h"
#include "shapes/line.h"
#include "shapes/rect.h"
#include "shapes/ellipse.h"
#include "shapes/polygon.h"
#include "shapes/freehand.h"

namespace USTC_CG
{
void Canvas::draw()
{
    draw_background();
    // HW1_TODO: more interaction events :增加了右键封闭多边形的绘制

    if (is_hovered_ && ImGui::IsMouseClicked(ImGuiMouseButton_Right)){
        mouse_right_click_event();
    }

    if (is_hovered_ && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        mouse_click_event();
    mouse_move_event();
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
        mouse_release_event();

    draw_shapes();
}

void Canvas::set_attributes(const ImVec2& min, const ImVec2& size)
{
    canvas_min_ = min;
    canvas_size_ = size;
    canvas_minimal_size_ = size;
    canvas_max_ =
        ImVec2(canvas_min_.x + canvas_size_.x, canvas_min_.y + canvas_size_.y);
}

void Canvas::show_background(bool flag)
{
    show_background_ = flag;
}

void Canvas::set_default()
{
    draw_status_ = false;
    shape_type_ = kDefault;
}

void Canvas::set_line()
{
    draw_status_ = false;
    shape_type_ = kLine;
}

void Canvas::set_rect()
{
    draw_status_ = false;
    shape_type_ = kRect;
}

void Canvas::set_ellipse(){
    draw_status_ = false;
    shape_type_ = kEllipse;
}

void Canvas::set_polygon(){
    draw_status_ = false;
    shape_type_ = kPolygon;
}

void Canvas::set_freehand(){
    draw_status_ = false;
    shape_type_ = kFreehand;
}

// HW1_TODO: more shape types, implements

void Canvas::clear_shape_list()
{
    shape_list_.clear();
    undo_list_.clear();
}

void Canvas::draw_background()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    if (show_background_)
    {
        // Draw background recrangle
        draw_list->AddRectFilled(canvas_min_, canvas_max_, background_color_);
        // Draw background border
        draw_list->AddRect(canvas_min_, canvas_max_, border_color_);
    }
    /// Invisible button over the canvas to capture mouse interactions.
    ImGui::SetCursorScreenPos(canvas_min_);
    ImGui::InvisibleButton(
        label_.c_str(), canvas_size_, ImGuiButtonFlags_MouseButtonLeft);
    // Record the current status of the invisible button
    is_hovered_ = ImGui::IsItemHovered();
    is_active_ = ImGui::IsItemActive();
}

void Canvas::draw_shapes()
{
    //Shape::Config s = { .bias = { canvas_min_.x, canvas_min_.y } }; 改成每个图形的config
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // ClipRect can hide the drawing content outside of the rectangular area
    draw_list->PushClipRect(canvas_min_, canvas_max_, true);
    for (const auto& shape : shape_list_)
    {
        shape->config.bias[0] = canvas_min_.x;
        shape->config.bias[1] = canvas_min_.y;
        shape->draw(shape->config);
    }
    if (draw_status_ && current_shape_)
    {
        current_shape_->config.bias[0] = canvas_min_.x;
        current_shape_->config.bias[1] = canvas_min_.y;
        current_shape_->draw(current_shape_->config);
    }

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && current_shape_)
    {
        ImVec2 mouse_pos = mouse_pos_in_canvas();
        ImVec2 global_pos(current_shape_->config.bias[0] + mouse_pos.x, current_shape_->config.bias[1] + mouse_pos.y);
        
        draw_list->AddCircleFilled(global_pos, 8.0f, IM_COL32(255, 200, 100, 150));

        draw_list->AddCircle(global_pos, 10.0f, IM_COL32(255, 200, 100, 255), 0, 2.0f);   //在鼠标周围添加光圈以获得更好体验
    }

    draw_list->PopClipRect();
}

void Canvas::mouse_click_event()
{
    // HW1_TODO: Drawing rule for more primitives

    if (!draw_status_)
    {
        draw_status_ = true;
        start_point_ = end_point_ = mouse_pos_in_canvas();
        switch (shape_type_)
        {
            case USTC_CG::Canvas::kDefault:
            {
                break;
            }
            case USTC_CG::Canvas::kLine:
            {
                current_shape_ = std::make_shared<Line>(
                    start_point_.x, start_point_.y, end_point_.x, end_point_.y);
                break;
            }
            case USTC_CG::Canvas::kRect:
            {
                current_shape_ = std::make_shared<Rect>(
                    start_point_.x, start_point_.y, end_point_.x, end_point_.y);
                break;
            }
            case USTC_CG::Canvas::kEllipse:
            {
                current_shape_ = std::make_shared<Ellipse>(
                    start_point_.x, start_point_.y, end_point_.x, end_point_.y);
                break;
            }
            case USTC_CG::Canvas::kPolygon:
            {
                    current_shape_ = std::make_shared<Polygon>(start_point_.x, start_point_.y); 
                break;
            }
            case USTC_CG::Canvas::kFreehand:
            {
                current_shape_ = std::make_shared<Freehand>(start_point_.x, start_point_.y);
                break;
            }
            // HW1_TODO: case USTC_CG::Canvas::kEllipse:
            default: break;
        }

        if(current_shape_){
                current_shape_->config.line_color[0] = static_cast<unsigned char>(current_color_[0] * 255);
                current_shape_->config.line_color[1] = static_cast<unsigned char>(current_color_[1] * 255);
                current_shape_->config.line_color[2] = static_cast<unsigned char>(current_color_[2] * 255);
                current_shape_->config.line_color[3] = static_cast<unsigned char>(current_color_[3] * 255);
                current_shape_->config.line_thickness = current_thickness_;
                current_shape_->config.show_fill = show_fill_;
                current_shape_->config.fill_color[0] = static_cast<unsigned char>(current_fill_color_[0] * 255);
                current_shape_->config.fill_color[1] = static_cast<unsigned char>(current_fill_color_[1] * 255);
                current_shape_->config.fill_color[2] = static_cast<unsigned char>(current_fill_color_[2] * 255);
                current_shape_->config.fill_color[3] = static_cast<unsigned char>(current_fill_color_[3] * 255);
            }

    }
    else {
       if(shape_type_ == USTC_CG::Canvas::kPolygon){
            if(std::shared_ptr<Polygon> poly = std::dynamic_pointer_cast<Polygon>(current_shape_)) {     
                poly->add_point(end_point_.x, end_point_.y);
            }           //要转换一下才能调用否则会报错
       }
    } 
    //其余类型转移到release中
}

void Canvas::mouse_right_click_event(){
    if(draw_status_ == true && shape_type_ == USTC_CG::Canvas::kPolygon){
        draw_status_ = false;
        if (current_shape_)
        {
            if(std::shared_ptr<Polygon> poly = std::dynamic_pointer_cast<Polygon>(current_shape_)) {  
                poly->drop_last_point();    
                poly->set_closed();
            } 
            shape_list_.push_back(current_shape_);
            undo_list_.clear();     //右键封闭多边形后清空redo栈(也不是栈)
            current_shape_.reset();
        }
    }
}

void Canvas::mouse_move_event()
{
    // HW1_TODO: Drawing rule for more primitives，这里确实没想好要补充什么
    if (draw_status_)
    {
        end_point_ = mouse_pos_in_canvas();
        if (current_shape_)
        {
            current_shape_->update(end_point_.x, end_point_.y);
        }
    }
}

void Canvas::mouse_release_event()
{
    // HW1_TODO: Drawing rule for more primitives
    if(draw_status_ == true && shape_type_ != USTC_CG::Canvas::kPolygon){
        draw_status_ = false;
        if (current_shape_)
        {
            shape_list_.push_back(current_shape_);
            undo_list_.clear();     //每次新建图形后清空redo栈)
            current_shape_.reset();
        }
    }
}

ImVec2 Canvas::mouse_pos_in_canvas() const
{
    ImGuiIO& io = ImGui::GetIO();
    const ImVec2 mouse_pos_in_canvas(
        io.MousePos.x - canvas_min_.x, io.MousePos.y - canvas_min_.y);
    return mouse_pos_in_canvas;
}

void Canvas::undo() {
    if(!shape_list_.empty()){
        undo_list_.push_back(shape_list_.back());
        shape_list_.pop_back();
    }
}

void Canvas::redo() {
    if(!undo_list_.empty()){
        shape_list_.push_back(undo_list_.back());
        undo_list_.pop_back();
    }
}

}  // namespace USTC_CG