#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <iomanip>
#include <windows.h>

using namespace std;
namespace fs = std::filesystem;

int main()
{
    string dir_str = "E:\\Games\\Bloodborne\\Image0\\dvdroot_ps4\\parts\\am\\flver";
    string exe_name_str = "BloodBorne_model_v3.exe";

    fs::path dir_path(dir_str);
    fs::path exe_path = dir_path / exe_name_str;

    string execute_extension_str = ".flver";

    // Check Dir and Exe
    if(!fs::exists(dir_path))
    {
        cout << "dir not exists" << endl;
        return 0;
    }

    if(!fs::exists(exe_path))
    {
        cout << "exe not exists" << endl;
        return 0;
    }

    cout << "find " << exe_path.string() << endl;

    //Iter Through Dir
    for (auto const& dir_entry : fs::directory_iterator(dir_path))
    {
        // Not Recursively
        if(dir_entry.is_directory())
        {
            continue;
        }
        auto const& iter_path = dir_entry.path();
        // cout << iter_path.extension().string() << endl;
        if(iter_path.extension().string() == execute_extension_str)
        {
            cout << "Calling " << exe_path.filename() << " to " << iter_path.filename() << "........" << endl;
            string full_command = exe_path.string() + " " + iter_path.string();
            system(full_command.c_str());
        }
    }

}