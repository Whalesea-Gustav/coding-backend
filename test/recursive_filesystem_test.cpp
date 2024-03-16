#include <bits/stdc++.h>
#include <filesystem>
#include <functional>
#include <cctype>

using namespace std;

namespace fs = std::filesystem;

int main()
{

    std::string dirname = "F:\\Projects\\LabViewer-dev\\input\\HexMesh"; // 替换为你的目录路径

    std::function<void(std::string&)> dfs = [&](std::string& filename) -> void
    {
        fs::path p(filename);

        if(!(fs::exists(p) && fs::is_directory(p)))
        {
            return;
        }

        std::vector<string> dir_vector;

        std::unordered_set<std::string> mesh_set;
        std::unordered_set<std::string> bdy_set;


        for (const auto& entry : fs::directory_iterator(p)) {
            if (fs::is_regular_file(entry.status())) {

                fs::path sub_path = entry.path();

                std::string sub_extension = sub_path.extension().string();

                std::transform(sub_extension.begin(), sub_extension.end(),
                               sub_extension.begin(), ::toupper);

                if(sub_extension == ".MESH")
                {
                    sub_path.replace_filename(sub_path.stem());
                    mesh_set.insert(sub_path.string());
                }
                else if (sub_extension == ".BDY")
                {
                    sub_path.replace_filename(sub_path.stem());
                    bdy_set.insert(sub_path.string());
                }

            } else if (fs::is_directory(entry.status())) {
                auto& sub_path = entry.path();
                dir_vector.push_back(sub_path.string());
            }
        }

        if(!mesh_set.empty() && !bdy_set.empty())
        {
            for(auto& mesh_file : mesh_set)
            {
                if(bdy_set.count(mesh_file))
                {
                    fs::path work_path(mesh_file);

                    std::cout << work_path.stem().string()
                    << ".mesh and .bdy is found in " << std::endl;
                    std::cout << work_path.parent_path().string() << std::endl;


                }
            }
        }

        if(!dir_vector.empty())
        {
            for(auto& dir : dir_vector)
            {
                dfs(dir);
            }
        }
    };

    dfs(dirname);

    return 0;
}