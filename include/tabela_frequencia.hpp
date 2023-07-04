#ifndef TABELA_FREQUENCIA_HPP
#define TABELA_FREQUENCIA_HPP

#include <iostream>
#include <string>
#include <algorithm>

#define TAM 256

class TabelaFrequencia {
private:
  unsigned int tabela[TAM];

public:
  TabelaFrequencia();

  void inicializaTabela();
  void preencheTabela(std::string texto);

  unsigned int* getTabela();
};

#endif