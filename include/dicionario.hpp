#ifndef DICIONARIO_HPP
#define DICIONARIO_HPP

#include <iostream>
#include <string>

#include "tabela_frequencia.hpp"
#include "node.hpp"

class Dicionario {
private:
  std::string* dicionario;

public:
  Dicionario();
  ~Dicionario();

  void gerarDicionario(Node* raiz, std::string caminho);

  std::string* getDicionario();
};

#endif