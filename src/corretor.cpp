#include "corretor.hpp"
using std::cout;
using std::endl;

std::string palavra(std::string str)
{
    std::string convertida;
    std::string remover = " [];',./(){}:\"?><`~!-_";
    for (auto &&i : str)
    {
        bool flag = false;

        for (auto &&j : remover)
        {
            if (i == j)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            convertida += tolower(i);
        }
    }

    return convertida;
}

Corretor::Corretor(std::string dicionario, std::string entrada)
{
    dic.open(dicionario);
    ent.open(entrada);
}

Corretor::Corretor()
{
}

Corretor::~Corretor()
{
    dic.close();
    ent.close();
}

void Corretor::run()
{
    if (dic.is_open())
    {
        std::string cword;
        while (!dic.eof())
        {
            getline(dic, cword);
            if (cword != "")
            {
                cword = cword.substr(0, cword.size() - 1);
                certas.insert(cword);
            }
        }
    }
    else
    {
        std::cout << "Erro na abertura de arquivo.";
    }

    if (ent.is_open())
    {
        std::string cline;
        while (!ent.eof())
        {
            getline(ent, cline);
            if (!cline.empty())
            {
                std::stringstream ss(cline);
                std::string cword;
                while (!ss.eof())
                {
                    ss >> cword;
                    cword = palavra(cword);
                    auto matico = certas.find(cword);

                    if (matico == certas.end())
                    {
                        erradas.insert(cword);
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "Erro na abertura de arquivo.";
    }

    for (auto &&i : erradas)
    {
        cout << i << endl;
    }
}

void Corretor::corrigir()
{
    std::vector<std::string> sugs;
    for (auto &&i : erradas)
    {
        for (auto &&j : certas)
        {
            if (levenshtein(i, j) < 3)
            {
                
            }
        }
    }
}