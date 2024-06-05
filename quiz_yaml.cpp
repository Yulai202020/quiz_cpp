#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <map>

class idk{
private:
    std::string question_;
    std::string answer_;
    std::vector<std::string> variants_;
public:
    std::string get_question() {
        return question_;
    }
    std::string get_answer() {
        return answer_;
    }
    std::vector<std::string> get_variants() {
        return variants_;
    }
    idk(std::string question, std::string answer, std::vector<std::string> variants) {
        question_ = question;
        variants_ = variants;
        answer_ = answer;
    }
};

int main(int argc, char* argv[]) {
    YAML::Node config;

    if (argc < 2) {
        std::cout << "Not many params." << std::endl;
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
    std::vector<idk> questions = config["questions"].as<std::vector<idk>>();

    for (idk i : questions) {
        std::string question = i.get_question();
        std::string ans = i.get_answer();
        std::vector<std::string> variants = i.get_variants();

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
}