#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>

class swag {
private:
    std::vector<unsigned char> swagmemory;
    size_t pointerggggg;
    
public:
    swag(size_t swagmemorySize = 30000) : swagmemory(swagmemorySize, 0), pointerggggg(0) {}
    
    void executeStuff(const std::string& code) {
        std::stack<size_t> gregloop;
        
        for (size_t i = 0; i < code.length(); ++i) {
            char instruction = code[i];
            
            switch (instruction) {
                case '>': 
                    ++pointerggggg;
                    if (pointerggggg >= swagmemory.size()) {
                        swagmemory.resize(swagmemory.size() * 2, 0);
                    }
                    break;
                    
                case '<': 
                    if (pointerggggg > 0) {
                        --pointerggggg;
                    } else {
                        std::cerr << "error: pointer out of bounds" << std::endl;
                        return;
                    }
                    break;
                    
                case '+': 
                    ++swagmemory[pointerggggg];
                    break;
                    
                case '-': 
                    --swagmemory[pointerggggg];
                    break;
                    
                case '.': 
                    std::cout << swagmemory[pointerggggg];
                    break;
                    
                case ',': 
                    {
                        char input;
                        std::cin.get(input);
                        swagmemory[pointerggggg] = input;
                    }
                    break;
                    
                case '[': 
                    if (swagmemory[pointerggggg] == 0) {
                        
                        int nestL = 1;
                        while (nestL > 0 && ++i < code.length()) {
                            if (code[i] == '[') {
                                ++nestL;
                            } else if (code[i] == ']') {
                                --nestL;
                            }
                        }
                        
                        if (nestL > 0) {
                            std::cerr << "error: unmatched '['" << std::endl;
                            return;
                        }
                    } else {
                        gregloop.push(i);
                    }
                    break;
                    
                case ']': 
                    if (gregloop.empty()) {
                        std::cerr << "error: unmatched ']'" << std::endl;
                        return;
                    }
                    
                    if (swagmemory[pointerggggg] != 0) {
                        i = gregloop.top(); 
                    } else {
                        gregloop.pop();
                    }
                    break;
            }
        }
        
        if (!gregloop.empty()) {
            std::cerr << "error: unmatched '['" << std::endl;
        }
    }
    
    bool bracketgreg(const std::string& code) {
        std::stack<size_t> bracketthing;
        
        for (size_t i = 0; i < code.length(); ++i) {
            if (code[i] == '[') {
                bracketthing.push(i);
            } else if (code[i] == ']') {
                if (bracketthing.empty()) {
                    std::cerr << "error: unmatched ']' at position " << i << std::endl;
                    return false;
                }
                bracketthing.pop();
            }
        }
        
        if (!bracketthing.empty()) {
            std::cerr << "error: unmatched '[' at position " << bracketthing.top() << std::endl;
            return false;
        }
        
        return true;
    }
    
    void fileexxxxxxxxx(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "error: could not open file " << filename << std::endl;
            return;
        }
        
        std::string code;
        char c;
        while (file.get(c)) {
            if (c == '>' || c == '<' || c == '+' || c == '-' || 
                c == '.' || c == ',' || c == '[' || c == ']') {
                code += c;
            }
        }
        
        if (bracketgreg(code)) {
            executeStuff(code);
        }
    }
};

int main(int argc, char* argv[]) {
    swag interpreter;
    
    if (argc > 1) {
        
        interpreter.fileexxxxxxxxx(argv[1]);
    } else {
        
        std::string code;
        std::string line;
        
        std::cout << "enter brainfucm coddde (tupen 'end' to stop):" << std::endl;
        
        while (std::getline(std::cin, line)) {
            if (line == "end") {
                break;
            }
            
            
            for (char c : line) {
                if (c == '>' || c == '<' || c == '+' || c == '-' || 
                    c == '.' || c == ',' || c == '[' || c == ']') {
                    code += c;
                }
            }
        }
        
        std::cout << "\nrunning\n";
        if (interpreter.bracketgreg(code)) {
            std::string g(60, '=');
            std::cout << g << std::endl;
            interpreter.executeStuff(code);
        }
    }
    
    std::cout << std::endl; 
    std::cout << "press enter to exit...";
    std::cin.get();
    return 0;
}
