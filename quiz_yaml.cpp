#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

class quiz {
public:
    std::string question;
    std::string answer;
    std::vector<std::string> variants;

    friend void operator>>(const YAML::Node& node, quiz& address) {
        address.question = node["question"].as<std::string>();
        address.answer = node["answer"].as<std::string>();
        address.variants = node["variants"].as<std::vector<std::string>>();
    }
};

int main(int argc, char* argv[]) {
    YAML::Node config;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <yaml_file>" << std::endl;
        return 0;
    }

    try {
        config = YAML::LoadFile(argv[1]);
    } catch (const YAML::Exception& e) {
        // Handle YAML parsing errors
        std::cerr << "YAML parsing error: " << e.what() << std::endl;
        return 1;
    }

    int questions_count = config.size();

    const YAML::Node& alldata = config["questions"];
    std::vector<quiz> questions;

    for (std::size_t i = 0; i < alldata.size(); ++i) {
        quiz tmp;
        alldata[i] >> tmp;
        questions.push_back(tmp);
    }

    for (quiz i : questions) {
        std::string question = i.question;
        std::string ans = i.answer;
        std::vector<std::string> variants = i.variants;

        std::cout << "Question:" << std::endl;
        std::cout << question << std::endl;
        std::cout << std::endl;

        std::cout << "Variants of answer:" << std::endl;
        for (int i = 0; i < variants.size(); i++) {
            std::cout << variants[i] << std::endl;
        }
        std::cout << std::endl;

        std::string answer;
        std::cout << "Enter your answer: ";
        std::cin >> answer;

        if (answer == ans){
            std::cout << "You are right." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}