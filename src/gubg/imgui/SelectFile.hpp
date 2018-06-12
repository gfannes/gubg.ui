#ifndef HEADER_gubg_imgui_SelectFile_hpp_ALREADY_INCLUDED
#define HEADER_gubg_imgui_SelectFile_hpp_ALREADY_INCLUDED

#include "gubg/imgui/State.hpp"
#include "imgui.h"
#include <string>

namespace gubg { namespace imgui { 

    inline bool select_file(const char *str_id, std::filesystem::path &filename)
    {
        State state(str_id);
        if (state.first())
        {
            state.directory(std::filesystem::current_path());
        }

        auto dir = state.directory();

        if (ImGui::Button(str_id))
            state.active(!state.active());

        bool file_was_selected = false;

        if (state.active())
        {
            ImGui::SetNextWindowSize(ImGui::GetWindowSize());
            ImGui::Begin("Select file");

            if (ImGui::Button("Cancel"))
                state.active(false);

            if (ImGui::Button(".."))
            {
                auto new_dir = dir.parent_path();
                if (!new_dir.empty())
                    dir = new_dir;
            }
            ImGui::SameLine();
            ImGui::Text("directory: %s", dir.string().c_str());

            auto size = ImGui::GetContentRegionAvail();
            size.x *= 0.5;
            ImGui::PushItemWidth(size.x*0.5);
            {
                ImGui::BeginChild("Directories", size);
                ImGui::Text("Directories:");
                try
                {
                    for (const auto &dirent: std::filesystem::directory_iterator(dir))
                    {
                        const auto new_dir = dirent.path();
                        if (is_directory(new_dir))
                            if (ImGui::Selectable(new_dir.string().c_str()))
                                dir = new_dir;
                    }
                }
                catch (const std::exception& exc)
                {
                    ImGui::Text("Cannot iterate this directory");
                }
                ImGui::EndChild();
            }
            ImGui::SameLine();
            {
                ImGui::BeginChild("Files", size);
                ImGui::Text("Files:");
                try
                {
                    for (const auto &dirent: std::filesystem::directory_iterator(dir))
                    {
                        const auto fn = dirent.path();
                        if (is_regular_file(fn))
                            if (ImGui::Selectable(fn.string().c_str()))
                            {
                                filename = fn;
                                file_was_selected = true;
                                state.active(false);
                            }
                    }
                }
                catch (const std::exception& exc)
                {
                    ImGui::Text("Cannot iterate this directory");
                }
                ImGui::EndChild();
            }
            ImGui::PopItemWidth();

            ImGui::End();
        }

        state.directory(dir);

        return file_was_selected;
    }

} } 

#endif
