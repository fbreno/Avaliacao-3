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
    for (auto &&i : certas)
    {
        certas.erase(i);
    }
    for (auto &&i : erradas)
    {
        erradas.erase(i);
    }       
    
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
                cword = palavra(cword);
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
}

void Corretor::corrigir()
{
    for (auto &&i : erradas)
    {
        std::map<int, std::string> sugs;
        for (auto &&j : certas)
        {
            int x = levenshtein(i, j);
            if (x < 4)
            {
                sugs.insert(std::make_pair(x, j));
            }
        }
        std::cout << i << ": " << std::endl;
        int fim = 0;
        for (auto &&elem : sugs)
        {
            if (fim >= 5)
            {
                break;
            }
            std::cout << " -" << elem.second << std::endl;
            ++fim;
        }
    }
}