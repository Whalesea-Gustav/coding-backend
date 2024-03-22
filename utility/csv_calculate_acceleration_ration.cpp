#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <iomanip>

using namespace std;

struct model_data  {

    int dof = 0;
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



int main()
{
    filesystem::path input_path(
            R"(C:\Projects\Meeting-Archive\MasterDegree\Graduation\PaperLatex\ExperimentData\DataProcess0\Linear_convert_1.csv)");

    filesystem::path output_path = input_path;
    std::string input_stem = input_path.stem().string();
    output_path.replace_filename(input_stem + "_acceleration_ratio");
    output_path.replace_extension("csv");

    std::vector<std::string> assembly_methods = {"GPU Assembler", "CPU Assembler"};
    std::vector<std::string> solvers = {"GPU Solver", "Eigen Parallel Conjugate Gradient Solver",
                                        "Pardiso Parallel Solver"};

    std::ifstream if_csv;
    if_csv.open(input_path);

    std::string line_str;

    std::getline(if_csv, line_str);

    std::string delimiter = ",";

    std::vector<std::string> col_names;
    col_names.reserve(20);

    size_t last = 0;
    size_t next = 0;

    while ((next = line_str.find(delimiter, last)) != string::npos) {
        std::string col_name = line_str.substr(last, next - last);
        col_names.push_back(col_name);
        std::cout << col_name << std::endl;

        last = next + 1;
    }

    cout << line_str.substr(last) << endl;

    std::ofstream of_csv(output_path);

    std::vector<std::string> output_col_names = {
            "Degree of Freedom", "Acceleration Categories", "Acceleration Ratio"
    };

    for (int i = 0; i < output_col_names.size(); ++i) {
        if (i != 0) {
            of_csv << ",";
        }

        of_csv << output_col_names[i];

        if (i == output_col_names.size() - 1) {
            of_csv << std::endl;
        }
    }

    map<int, model_data> dof_model_map;

    while (!if_csv.eof())
    {

        line_str.clear();
        std::getline(if_csv, line_str);

        if(line_str.empty())
        {
            continue;
        }

        auto sub_strs = get_split_results(line_str, delimiter);
        //[1] dof
        //[3] assembly time
        //[4] solving time
        //[5] assembler
        //[6] solver

        int dof = stoi(sub_strs[1]);

        auto& ind_model_data = dof_model_map[dof];

        double assembly_time = stod(sub_strs[3]);
        double solving_time = stod(sub_strs[4]);

        if(sub_strs[5] == assembly_methods[0])
        {
            ind_model_data.gpu_assembly_time_avg += assembly_time;
            ind_model_data.gpu_assembly_count++;
        }
        else if (sub_strs[5] == assembly_methods[1])
        {
            ind_model_data.cpu_assembly_time_avg += assembly_time;
            ind_model_data.cpu_assembly_count++;
        }
        else
        {
            std::cout << "new assembly found : " << sub_strs[5] << std::endl;
        }

        if(sub_strs[6] == solvers[0])
        {
            ind_model_data.gpu_solving_time_avg += solving_time;
            ind_model_data.gpu_solving_count++;
        }
        else if (sub_strs[6] == solvers[1])
        {
            ind_model_data.eigen_solving_time_avg += solving_time;
            ind_model_data.eigen_solving_count++;
        }
        else if (sub_strs[6] == solvers[2])
        {
            ind_model_data.pardiso_solving_time_avg += solving_time;
            ind_model_data.pardiso_solving_count++;
        }
        else
        {
            std::cout << "new solver found : " << sub_strs[6] << std::endl;
        }
    }

    vector<string> acc_categories = {"Assembly Compare", "Eigen Compare", "Pardiso Compare"};

    for(auto& p : dof_model_map)
    {
        auto dof = p.first;
        auto& ind_model_data = p.second;

        if(ind_model_data.gpu_assembly_count > 0 && ind_model_data.cpu_assembly_count > 0)
        {
            double gpu_avg = ind_model_data.gpu_assembly_time_avg / ind_model_data.gpu_assembly_count;
            double cpu_avg = ind_model_data.cpu_assembly_time_avg / ind_model_data.cpu_assembly_count;

            double ratio = cpu_avg / gpu_avg;

            of_csv << dof << ","
            << acc_categories[0] << ","
            << ratio << std::endl;
        }

        if(ind_model_data.eigen_solving_count > 0 && ind_model_data.gpu_solving_count > 0)
        {
            double gpu_avg = ind_model_data.gpu_solving_time_avg / ind_model_data.gpu_solving_count;
            double cpu_avg = ind_model_data.eigen_solving_time_avg / ind_model_data.eigen_solving_count;

            double ratio = cpu_avg / gpu_avg;

            of_csv << dof << ","
                   << acc_categories[1] << ","
                   << ratio << std::endl;
        }

        if(ind_model_data.pardiso_solving_count > 0 && ind_model_data.gpu_solving_count > 0)
        {
            double gpu_avg = ind_model_data.gpu_solving_time_avg / ind_model_data.gpu_solving_count;
            double cpu_avg = ind_model_data.pardiso_solving_time_avg / ind_model_data.pardiso_solving_count;

            double ratio = cpu_avg / gpu_avg;

            of_csv << dof << ","
                   << acc_categories[2] << ","
                   << ratio << std::endl;
        }
    }

    return 0;
}