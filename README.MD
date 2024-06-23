# Description
This is 4 quiz programs

First one quiz_json.cpp uses json for create quiz

Second one quiz_yaml.cpp uses yaml file for quiz

Third one uses sqlite for print quiz

Last one just print question from sqlitea

# Run json quiz
```bash
# quiz_json.cpp
# you gotta install json lib on cpp
# for archlinux:
sudo pacman -S nlohmann-json
g++ quiz_json -o quiz
./quiz data.json
```

# Run yaml quiz
```bash
g++ quiz_yaml.cpp -o quiz -lyaml-cpp
./quiz data.yaml
```

# Run sqlite quiz
```bash
g++ quiz_yaml.cpp -o quiz -lsqlite3 -lreadline
```