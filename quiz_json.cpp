#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

json read_file(std::string path) {
    json j;
    
    std::ifstream file(path);
    if (!file.is_open()){
        std::cerr << "File open error." << std::endl;
    }

    file >> j;

    return j;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <json_file>" << std::endl;
        return 0;
    }

    json j = read_file(argv[1]);

    for (const auto& item : j) {
        std::string question = item["question"];

        std::cout << "Question:" << std::endl;
        std::cout << question << std::endl;
        std::cout << std::endl;

        std::cout << "Variants of answer:" << std::endl;
        for (int i = 0; i < item["variants"].size(); i++) {
            std::string variant = item["variants"][i];
            std::cout << variant << std::endl;
        }
        std::cout << std::endl;

        std::string answer;
        std::cout << "Enter your answer: ";
        std::cin >> answer;

        if (answer == item["answer"]){
            std::cout << "You are right." << std::endl;
        }

        std::cout << std::endl;
    }
}