#include "minidraw_window.h"

#include <iostream>

namespace USTC_CG
{
MiniDraw::MiniDraw(const std::string& window_name) : Window(window_name)
{
    p_canvas_ = std::make_shared<Canvas>("Widget.Canvas");
}

MiniDraw::~MiniDraw()
{
}

void MiniDraw::draw()
{
    draw_canvas();
}

void MiniDraw::draw_canvas()
{
    // Set a full screen canvas view
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    if (ImGui::Begin(
            "Canvas",
            &flag_show_canvas_view_,
            ImGuiWindowFlags_NoDecoration|ImGuiWindowFlags_NoBackground))
    {
        // Buttons for shape types
        if (ImGui::Button("Line"))
        {
            std::cout << "Set shape to Line" << std::endl;
            p_canvas_->set_line();
        }
        ImGui::SameLine();

        if (ImGui::Button("Rect"))
        {
            std::cout << "Set shape to Rect" << std::endl;
            p_canvas_->set_rect();
        }
        ImGui::SameLine();
        
        if (ImGui::Button("Ellipse"))
        {
            std::cout << "Set shape to Ellipse" << std::endl;
            p_canvas_->set_ellipse();
        }
        ImGui::SameLine();

        if(ImGui::Button("Polygon"))
        {
            std::cout << "Set shape to Polygon" << std::endl;
            p_canvas_->set_polygon();
        }
        ImGui::SameLine();
        
        if(ImGui::Button("Freehand"))
        {
            std::cout << "Set shape to Freehand" << std::endl;
            p_canvas_->set_freehand();
        }

        ImGui::SameLine();

        if(ImGui::Button("Default"))
        {
            std::cout << "Set shape to Default" << std::endl;
            p_canvas_->set_default();
        }
        ImGui::SameLine();

        if (ImGui::Button("Undo")) {

            std::cout << "Undo last shape" << std::endl;
            p_canvas_->undo();

        }
        ImGui::SameLine();
        
        if (ImGui::Button("Redo")) {

            std::cout << "Redo last undone shape" << std::endl;
            p_canvas_->redo();
        
        }
        ImGui::SameLine();

        if (ImGui::Button("Clear"))
        {
            std::cout << "Clear canvas" << std::endl;
            p_canvas_->clear_shape_list();
        }
        ImGui::Separator(); 

        if(ImGui::ColorEdit4("Shape Color", p_canvas_->current_color_)){
            std::cout << "the color changed to:" 
                      <<"R:"
                      << p_canvas_->current_color_[0] << ",G: "
                      << p_canvas_->current_color_[1] << ",B:"
                      << p_canvas_->current_color_[2] <<
                    std::endl;
        }
        ImGui::Separator();

        if(ImGui::SliderFloat("Thickness", &p_canvas_->current_thickness_, 1.0f, 10.0f)){
            std::cout << "the thickness changed to:" << p_canvas_->current_thickness_ << std::endl;
        }
        ImGui::Separator();

        if(ImGui::Checkbox("Enable Fill", &p_canvas_->show_fill_)) {
            std::cout << "Fill enabled: " << (p_canvas_->show_fill_ ? "Yes" : "No") << std::endl;
        }
        if(p_canvas_->show_fill_){
            ImGui::Text("(Note: Fill only supports convex polygons)");
            if(ImGui::ColorEdit4("Fill Color", p_canvas_->current_fill_color_)){
                std::cout << "the fill color changed to:" 
                          <<"R:"
                          << p_canvas_->current_fill_color_[0] << ",G: "
                          << p_canvas_->current_fill_color_[1] << ",B:"
                          << p_canvas_->current_fill_color_[2] <<
                        std::endl;
            }
        }


        // HW1_TODO: More primitives
        //    - Ellipse
        //    - Polygon
        //    - Freehand(optional)
        
        // Canvas component
        ImGui::Text("Press left mouse to add shapes.");
        ImGui::Text("Press right mouse to make the polygon closed.");
        // Set the canvas to fill the rest of the window
        const auto& canvas_min = ImGui::GetCursorScreenPos();
        const auto& canvas_size = ImGui::GetContentRegionAvail();
        p_canvas_->set_attributes(canvas_min, canvas_size);
        p_canvas_->draw();
    }
    ImGui::End();
}
}  // namespace USTC_CG