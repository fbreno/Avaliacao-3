#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <map>
#include <queue>
#include "levenshtein.hpp"

class Corretor
{
private:
    std::ifstream dic;
    std::ifstream ent;
    std::unordered_set <std::string> certas;
    std::unordered_set <std::string> erradas;
    
public:
    Corretor();
    Corretor(std::string dicionario,std::string entrada);
    ~Corretor();
    void run();
    void corrigir();
};

