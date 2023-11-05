#include <iostream>
#include <fstream>
#include <string.h>
#include <filesystem>
#include <unistd.h>
#include "./include/lexer.hpp"
#include "./include/parser.hpp"
#include "./include/compiler.hpp"

using namespace std;

// Simple process file
void processFile(const std::string &file_path) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Could not open the file" << std::endl;
        std::exit(1);
    }

    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    Lexer lexer(input);
    std::vector<TOKEN> tokens = lexer.tokenize();

    // Вивід токенів не екран (коли буде готовий компілятор потрібно прибрати)
    std::cout << "Tokens:\n";
    for (const auto &token : tokens) {
        std::cout << "[" <<  "type:" << token.type << "value:" << token.value << "]\n";
    }

    Parser parser(tokens);
    parser.parse();
}


// TOKENS process file
void TokensProcessFile(const std::string &file_path) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Could not open the file" << std::endl;
        std::exit(1);
    }

    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    Lexer lexer(input);
    std::vector<TOKEN> tokens = lexer.tokenize();

    // Вивід токенів не екран (коли буде готовий компілятор потрібно прибрати)
    std::cout << "Tokens:\n";
    for (const auto &token : tokens) {
        std::cout << "[" << token.type << ": " << token.value << "]\n";
    }
}


// PARSER process file
void ParserProcessFile(const std::string &file_path) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Could not open the file" << std::endl;
        std::exit(1);
    }

    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    Lexer lexer(input);
    std::vector<TOKEN> tokens = lexer.tokenize();

    Parser parser(tokens);
    parser.parse();

    // std::cout << "AST:\n";
    // for (const auto &token : tokens) {
    //     // std::cout << token << '\n';
    //     cout << tokens << "\n";
    // }
}

// Main
int main(int argc, char *argv[]) {
    // Перевірка чи є якісь аргументи після виклику програми
    if (argc < 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }
    
    // Запис шляху до файлу
    std::string file_path = argv[1];
    
    // Створення змінної для прапорця тестування
    std::string testKey = "";

    // Перевірка чи є якісь прапорці
    if(argc == 3)
    {
        testKey = argv[2];
    }
    
    // Перевірка чи передали файл .nl, або аргумент test_all
    if (file_path.find(".nl") == std::string::npos && file_path != "test_all" && file_path != "--help" && file_path != "-h" && file_path != "--init" && file_path != "-i" && file_path != "--uninit" && file_path != "-u") {
        std::cout << "There is no file with the extension '.nl'" << std::endl;
        return 1;
    }
    
    // Перевірка чи другий аргумент не містить прапорця
    if (argc == 3 && testKey != "-t" && testKey != "-p" && testKey != "--tokenize" && testKey != "--parse")
    {
        std::cout << "The key was entered incorrectly, you may have meant \"-t'\" (--tokenize) or \"-p\" (--parse)" << std::endl;
        return 1;
    }

    // Команда --init
    if (file_path == "--init")
    {
        // Перевіряємо, чи існує файл niklang у usr/bin
        if (std::filesystem::exists("/usr/bin/niklang")) {
            // Файл niklang існує
            std::cout << "niklang is already initialised" << std::endl;
        } else {
            // Файл niklang не існує
            system("sudo cp niklang /usr/bin");
            cout << "niklang initialised" << endl;
        }

        return 0;
    }

    // Команда --uninit
    if (file_path == "--uninit") {
        // Перевіряємо, чи існує файл niklang у usr/bin
        if (std::filesystem::exists("/usr/bin/niklang")) {
            // Файл niklang існує в usr/bin
            system("sudo rm /usr/bin/niklang");
            cout << "Is work" << endl;
        } 
        else 
        {
            // Файл niklang не існує в usr/bin
            std::cout << "niklang is not initialised, you do not need to use --uninit" << std::endl;
        }

        return 0;
    }
    
    // Команда -h та --help
    if (file_path == "--help" || file_path == "-h")
    {
        cout << "\e[1mUsage: ./niklang [options]\e[0m" << endl;
        cout << "\n";

        cout << "\e[1mOptions:\e[0m" << endl;
        cout << "\n";
        cout << "  -h --help       Display this help message" << endl;
        cout << "  -i --init       Initialising niklang to use it in any folder" << endl;
        cout << "  -u --uninit     Cancel initialization niklang if you no longer need to use it" << endl;
        cout << "  -t, --tokenize  Generate a list of tokens for the specified file" << endl;
        cout << "  -p, --parse     Generate an abstract syntax tree (AST) for the specified file" << endl;
        cout << "\n";

        cout << "\e[1mInitialization:\e[0m" << endl;
        cout << "\n";
        cout << "  To use niklang in any folder, you need to initialise it.\n  This can be done with the command:" << endl;
        cout << "\n";
        cout << "  \e[1m./niklang --init\e[0m or \e[1m./niklang -i\e[0m" << endl;
        cout << "\n";
        cout << "  If you don't plan to use niklang anymore, you should cancel initialization\n  it, which can be done with the following command" << endl;
        cout << "\n";
        cout << "  \e[1m./niklang --uninit\e[0m or \e[1m./niklang -u\e[0m" << endl;
        cout << "\n";
        
        cout << "\e[1mExamples:\e[0m" << endl;
        cout << "\n";
        cout << "  Standard run for the file \"example.nl\":" << endl;
        cout << "\n";
        cout << "    \e[1mniklang example.nl\e[0m" << endl;
        cout << "\n";
        cout << "  Generate a list of tokens for the file \"example.nl\":" << endl;
        cout << "\n";
        cout << "    \e[1niklang example.nl -t\e[0m" << endl;
        cout << "\n";
        cout << "    or" << endl;
        cout << "\n";
        cout << "    \e[1mniklang example.nl --tokenize\e[0m" << endl;
        cout << "\n";
        cout << "  Generate an abstract syntax tree for the file \"example.nl\":" << endl;
        cout << "\n";
        cout << "    \e[1mniklang example.nl -p\e[0m" << endl;
        cout << "\n";
        cout << "    or" << endl;
        cout << "\n";
        cout << "    \e[1mniklang example.nl --parse\e[0m" << endl;
        cout << "\n";
        cout << "  Test the niklang on all test files:" << endl;
        cout << "\n";
        cout << "    \e[1mniklang test_all\e[0m" << endl;
        cout << "    \e[1mniklang test_all -t\e[0m" << endl;
        cout << "    \e[1mniklang test_all -p\e[0m" << endl;
        cout << "    \e[1mniklang test_all --tokenize\e[0m" << endl;
        cout << "    \e[1mniklang test_all --parse\e[0m" << endl;
        cout << "\n";

        cout << "\e[1mDescription:\e[0m" << endl;
        cout << "\n";
        cout << "  niklang is a utility for executing code\n  written in the NikLang programming language.\n  It has several modes of operation that allow\n  the user to perform various tasks and test\n  the correctness of the code execution mechanisms." << endl;
        return 0;
    }
    
    // Якщо передано файл .nl, а другий аргумент не test_all
    if (file_path.find(".nl") != std::string::npos && file_path != "test_all") {
        if (testKey == "-t" || testKey == "--tokenize")
        {
            TokensProcessFile(file_path);
        }
        else if(testKey == "-p" || testKey == "-parse")
        {
            ParserProcessFile(file_path);
        }
        else
        {
            processFile(file_path);
        }
        return 0;
    }
    
    // Якщо аргумент test_all
    else if(file_path == "test_all" && file_path.find(".nl") == std::string::npos) {
        std::string testFile [] = {"../test/mainTest.nl", "../test/subTest_1.nl", "../test/subTest_2.nl", "../test/subTest_3.nl"};
        for (int i = 0; i < sizeof(testFile) / sizeof(testFile[0]); i++)
        {
            cout << "___________________Test №" << i << "___________________" << endl;
            cout << "\n";
            file_path = testFile[i];
            if (testKey == "-t" || testKey == "--tokenize")
            {
                TokensProcessFile(file_path);
            }
            else if(testKey == "-p" || testKey == "-parse")
            {
                ParserProcessFile(file_path);
            }
            else
            {
                processFile(file_path);
            }

            if(i + 1 != sizeof(testFile) / sizeof(testFile[0]))
            {
                cout << "\n\n\n";
            }
        }      
        return 0;
    }
}