#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <iomanip>

using namespace std;

struct csv_output_data  {

    std::string model_name;
    int dof = 0;
    int patch_size = 0;

    double assembly_time = 0;
    std::string assembly_method;

    double solving_time = 0;
    std::string solver;
};

namespace std {
    template<>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int> &d) const {
            return hash<int>{}(d.first) ^ hash<int>{}(d.second - 100);
        }
    };
}

int main() {

    system("chcp 65001");

    std::cout << "中文测试" << std::endl;

    filesystem::path input_path(
            R"(C:\Projects\Meeting-Archive\MasterDegree\Graduation\PaperLatex\ExperimentData\Linear.csv)");
    filesystem::path output_path = input_path;
    std::string input_stem = input_path.stem().string();
    output_path.replace_filename(input_stem + "_convert");
    output_path.replace_extension("csv");

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
            "Model Name", "Degree of Freedom", "Spline Patch Number", "Assembly Time", "Solve Time", "Assembler",
            "Solver"
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

    std::unordered_map<std::pair<int, int>, std::string> size_2_modelname;

    std::vector<std::string> assembly_methods = {"GPU Assembler", "CPU Assembler"};
    std::vector<std::string> solvers = {"GPU Solver", "Eigen Parallel Conjugate Gradient Solver",
                                                "Pardiso Parallel Solver"};

    std::vector<csv_output_data> output_data_vec;

    while (!if_csv.eof())
    {

        line_str.clear();
        std::getline(if_csv, line_str);

        size_t line_last = 0;
        size_t line_next = 0;

        int id = 0;

        csv_output_data data;

        while ((line_next = line_str.find(delimiter, line_last)) != string::npos)
        {

            std::string data_name = line_str.substr(line_last, line_next - line_last);

            if(id == 0)
            {
                data.model_name = data_name;
            }
            else if (id == 1)
            {
                if(data_name.empty())
                {
                    data.dof = 0;
                }
                else
                {
                    data.dof = std::stoi(data_name);
                }
            }
            else if (id == 2)
            {
                if(data_name.empty())
                {
                    data.patch_size = 0;
                }
                else
                {
                    data.patch_size = std::stoi(data_name);
                }

                if(data.dof > 0 && data.patch_size > 0 && !data.model_name.empty())
                {
                    size_2_modelname[{data.dof, data.patch_size}] = data.model_name;
                }
            }
            else if (id == 3)
            {
                if(data_name.empty())
                {
                    data.assembly_time = 0;
                }
                else
                {
                    data.assembly_time = std::stod(data_name);
                }

                if(data.assembly_time != 0)
                {
                    data.assembly_method = assembly_methods[0];
                }
            }
            else if (id == 4)
            {
                if(data_name.empty())
                {
                    data.solving_time = 0;
                }
                else
                {
                    data.solving_time = std::stod(data_name);
                }

                if(data.solving_time != 0 || data.assembly_time != 0)
                {
                    data.assembly_method = assembly_methods[0];
                    data.solver = solvers[0];
                    output_data_vec.push_back(data);
                }
            }
            else if (id == 5)
            {
                if(data_name.empty())
                {
                    data.assembly_time = 0;
                }
                else
                {
                    data.assembly_time = std::stod(data_name);
                }

                if(data.assembly_time != 0)
                {
                    data.assembly_method = assembly_methods[1];
                }
            }
            else if (id == 6)
            {
                if(data_name.empty())
                {
                    data.solving_time = 0;
                }
                else
                {
                    data.solving_time = std::stod(data_name);
                }

                if(data.solving_time != 0 || data.assembly_time != 0)
                {
                    data.assembly_method = assembly_methods[1];
                    data.solver = solvers[1];
                    output_data_vec.push_back(data);
                }
            }

            line_last = line_next + 1;

            ++id;
        }

        std::string data_name = line_str.substr(line_last);

        if(data_name.empty())
        {
            data.solving_time = 0;
        }
        else
        {
            data.solving_time = std::stod(data_name);
        }

        if(data.solving_time != 0)
        {
            data.assembly_method = assembly_methods[1];
            data.solver = solvers[2];
            output_data_vec.push_back(data);
        }
    }

    for(int i = 0; i < output_data_vec.size(); ++i)
    {
        auto& data = output_data_vec[i];

        if(data.model_name.empty())
        {
            if(data.dof > 0 && data.patch_size > 0)
            {
                data.model_name = size_2_modelname[{data.dof, data.patch_size}];
            }
        }

        of_csv << std::setprecision(20) << data.model_name << "," <<data.dof << "," << data.patch_size << ","
               << data.assembly_time << "," << data.solving_time << ","
               << data.assembly_method << "," <<data.solver << std::endl;
    }

    return 0;
}