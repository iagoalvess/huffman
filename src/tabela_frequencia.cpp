#include "tabela_frequencia.hpp"

TabelaFrequencia::TabelaFrequencia() {
  inicializaTabela();
}



// Inicializa a tabela de frequência com zeros
void TabelaFrequencia::inicializaTabela() {
  std::fill(tabela, tabela + TAM, 0);
}



// Preenche a tabela de frequência com base no texto fornecido
void TabelaFrequencia::preencheTabela(std::string texto) {
  for (char c : texto) {
    tabela[static_cast<unsigned char>(c)]++;
  }
}



unsigned int* TabelaFrequencia::getTabela() {
  return tabela;
}