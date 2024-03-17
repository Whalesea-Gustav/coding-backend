#include <bits/stdc++.h>
#include <filesystem>

using namespace std;


int main()
{
    filesystem::path  p("E:/CrowdDetection/revaluate/APMRToolkits.joke");
    std::cout<<"Root Dir:"<<p.root_directory() << std::endl;
    std::cout << "Root Name:" << p.root_name() << std::endl;
    std::cout << "Root Path:" << p.root_path() << std::endl;
    std::cout << "File Name Without Extension:" << p.stem() << std::endl;
    std::cout << "File Extension:" << p.extension() << std::endl;
    std::cout << "File Name :" << p.filename() << std::endl;
    std::cout << "Relative Dir:" << p.relative_path() << std::endl;
    std::cout << "Parent Dir:" << p.parent_path()<< std::endl;

    p.replace_extension("jpg");

    std::cout << "Full String replace extension:" << p.string() << std::endl;

    p.replace_filename("hahahah");

    std::cout << "Full String replace filename:" << p.string() << std::endl;

    p.replace_extension("mesh");

    std::cout << "Full String replace extension:" << p.string() << std::endl;

   return 0;
}