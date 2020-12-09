#include <iostream>
#include "corretor.hpp"

int main(int argc, char const *argv[])
{
    std::string dicionario(argv[1]);
    std::string entrada(argv[2]);
    Corretor primeiro(dicionario,entrada);
    primeiro.run();
    primeiro.corrigir();
    return 0;
}