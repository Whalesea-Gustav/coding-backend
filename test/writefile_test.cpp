#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>

using namespace std;


int main()
{
    std::filesystem::path fs_path("F:/Projects/Meeting-Archive/MasterDegree/Graduation/PaperLatex/ExperimentData/Linear.csv");

    std::ofstream app_csv;
    app_csv.open(fs_path, std::ios::app);

    app_csv << std::setprecision(20) << "beam" << "," << 132492 << "," << 1200 << ","
    << "," << ","
    << 5407.732 << "," << 135517.96 << "," << std::endl;

    return 0;
}