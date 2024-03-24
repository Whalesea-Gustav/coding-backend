#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <iomanip>

using namespace std;

struct model_data  {

    int cpu_assembly_count = 0;
    double cpu_assembly_time_avg = 0;

    int gpu_assembly_count = 0;
    double gpu_assembly_time_avg = 0;

    int eigen_solving_count = 0;
    double eigen_solving_time_avg = 0;

    int pardiso_solving_count = 0;
    double pardiso_solving_time_avg = 0;

    int gpu_solving_count = 0;
    double gpu_solving_time_avg = 0;
};

namespace std {
    template<>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int> &d) const {
            return hash<int>{}(d.first) ^ hash<int>{}(d.second - 100);
        }
    };
}

vector<string> get_split_results(string input_str, string delimiter)
{
    size_t last = 0;
    size_t next = 0;

    vector<string> output_results;

    while ((next = input_str.find(delimiter, last)) != string::npos) {
        std::string sub_name = input_str.substr(last, next - last);
        output_results.push_back(sub_name);

        last = next + 1;
    }

    output_results.push_back(input_str.substr(last));

    return output_results;
}


int main() {

    std::ifstream if_csv;

    filesystem::path input_info_path(
            R"(F:\Projects\Meeting-Archive\MasterDegree\Graduation\PaperLatex\ExperimentData\SplineModelInfo.csv)");


    if_csv.open(input_info_path);

    std::string line_str;
    std::string delimiter = ",";

    unordered_map<pair<int,int>,string> size_2_name_map;

    while (!if_csv.eof()) {

        line_str.clear();
        std::getline(if_csv, line_str);

        if (line_str.empty()) {
            continue;
        }

        auto sub_strs = get_split_results(line_str, delimiter);

        int patch_size = stoi(sub_strs[0]);
        int dof = stoi(sub_strs[1]);
        string model_name = sub_strs[2];

        size_2_name_map[{patch_size,dof}] = model_name;
    }

    if_csv.close();

    filesystem::path input_path(
            R"(F:\Projects\Meeting-Archive\MasterDegree\Graduation\PaperLatex\ExperimentData\DataProcess1\Hyperelasticity_GPU_Solving_acceleration_fulldata.csv)");

    filesystem::path output_path = input_path;
    std::string input_stem = input_path.stem().string();
    output_path.replace_filename(input_stem + "_with_name");
    output_path.replace_extension("csv");

    if_csv.open(input_path);

    std::ofstream of_csv;
    of_csv.open(output_path);

    line_str.clear();
    std::getline(if_csv, line_str);

    auto sub_strs = get_split_results(line_str, delimiter);

    for(int i = 0; i < sub_strs.size(); ++i)
    {
        of_csv << sub_strs[i];

        if((i + 1) != sub_strs.size())
        {
            of_csv << ",";
        }
    }

    of_csv << std::endl;

    while (!if_csv.eof()) {

        line_str.clear();
        std::getline(if_csv, line_str);

        if (line_str.empty()) {
            continue;
        }

        sub_strs = get_split_results(line_str, delimiter);

        int patch_size = stoi(sub_strs[0]);
        int dof = stoi(sub_strs[1]);


        auto model_name = size_2_name_map[{patch_size,dof/3}];

        of_csv << model_name << ",";

        for(int i = 0; i < sub_strs.size(); ++i)
        {
            of_csv << sub_strs[i];

            if((i + 1) != sub_strs.size())
            {
                of_csv << ",";
            }
        }

        of_csv << std::endl;
    }

    of_csv.close();
    if_csv.close();
}