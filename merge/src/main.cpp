#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Read in a data file
bool readFile(const std::string &filename, std::vector<int> &data);
// Merge two vectors
bool mergeVectors(const std::vector<int> &first, const std::vector<int> &second);  /* NOLINT(whitespace/line_length) */

const std::string filename1 = "data1.dat";
const std::string filename2 = "data2.dat";

int main() {
    // Data vectors
    std::vector<int> data1, data2;

    // Read in data
    if (!readFile(filename1, data1)) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    if (!readFile(filename2, data2)) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    if (!mergeVectors(data1, data2)) {
        std::cerr << "Error merging vectors" << std::endl;
        return 1;
    }
    return 0;
}

bool readFile(const std::string &filename, std::vector<int> &data) {
    // Try to open file
    std::fstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    while (!file.eof()) {
        int tmp;
        file >> tmp;
        data.push_back(tmp);
    }

    file.close();

    return true;
}

bool mergeVectors(const std::vector<int> &first, const std::vector<int> &second) {  /* NOLINT(whitespace/line_length) */
    std::ofstream outfile("output.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return false;
    }

    unsigned int i1 = 0, i2 = 0;
    while (i1 < first.size() || i2 < second.size()) {
        int num1 = first[i1];
        int num2 = second[i2];

        if (num1 >= num2 || i1 == first.size()) {
            outfile << num2 << std::endl;
            i2++;
        } else if (num2 > num1 || i2 == second.size()) {
            outfile << num1 << std::endl;
            i1++;
        } else {
            return false;
        }
    }

    outfile.close();

    return true;
}
