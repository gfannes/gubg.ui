#ifndef HEADER_gubg_imgui_SelectFile_hpp_ALREADY_INCLUDED
#define HEADER_gubg_imgui_SelectFile_hpp_ALREADY_INCLUDED

#include "gubg/imgui/State.hpp"
#include "imgui.h"
#include <string>

namespace gubg { namespace imgui { 

    inline bool select_file(const char *str_id, std::filesystem::path &path)
    {
        bool file_was_selected = false;

        State state(str_id);

        if (ImGui::Button(str_id))
            state.active(!state.active());

        if (state.active())
        {
            path = path.make_preferred();
            if (!std::filesystem::exists(path))
                path = std::filesystem::current_path();

            std::filesystem::path dir = path;
            std::filesystem::path fn;
            if (!std::filesystem::is_directory(dir))
            {
                fn = dir.filename();
                dir.remove_filename();
            }

            ImGui::Begin("Select file");

            if (ImGui::Button("Cancel"))
                state.active(false);
            if (!fn.empty())
            {
                ImGui::SameLine();
                if (ImGui::Button("Select"))
                {
                    file_was_selected = true;
                    state.active(false);
                }
            }

            if (ImGui::Button(".."))
            {
                auto new_dir = dir.parent_path();
                if (!new_dir.empty())
                {
                    dir = new_dir;
                    fn.clear();
                }
            }
            ImGui::SameLine();
            ImGui::Text("directory: %s", dir.string().c_str());
            ImGui::SameLine();
            ImGui::Text("filename: %s", fn.string().c_str());

            std::set<std::filesystem::path> directories, files;
            for (const auto &dirent: std::filesystem::directory_iterator(dir))
            {
                const auto p = dirent.path();
                const auto fn = p.filename();
                const auto fn_str = fn.string();
                if (!fn_str.empty() && fn_str[0] != '.')
                {
                    if (is_directory(p))
                        directories.insert(fn);
                    else if (is_regular_file(p))
                        files.insert(fn);
                }
            }

            auto size = ImGui::GetContentRegionAvail();
            size.x *= 0.5;
            ImGui::PushItemWidth(size.x*0.5);
            {
                ImGui::BeginChild("Directories", size);
                ImGui::Text("Directories:");
                try
                {
                    for (const auto &d: directories)
                        if (ImGui::Selectable(d.string().c_str()))
                            dir /= d;
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
                    for (const auto &f: files)
                        if (ImGui::Selectable(f.string().c_str()))
                            fn = f;
                }
                catch (const std::exception& exc)
                {
                    ImGui::Text("Cannot iterate this directory");
                }
                ImGui::EndChild();
            }
            ImGui::PopItemWidth();

            ImGui::End();

            path = dir / fn;
        }

        return file_was_selected;
    }

} } 

#endif
