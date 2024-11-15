#include "World.h"
#include "black_box/Application.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Please, call with one argument " << "( example: " << argv[0] << " <path to file smile.txt> )";
        return 1;
    }
    try {
        World w(argv[1]);
        // Код ниже запускает выполнение приложения. 
        Application app("physics");
        app.run(w);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 2;
    }
    return 0;
}