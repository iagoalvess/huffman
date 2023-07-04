#include "dicionario.hpp"

// Construtor padrão inicializa o dicionário com strings vazias
Dicionario::Dicionario() {
  dicionario = new std::string[TAM];

  for (int i = 0; i < TAM; i++) {
    dicionario[i] = "";
  }
}



Dicionario::~Dicionario() {
  delete[] dicionario;
}



// Gera o dicionário de códigos a partir da árvore de Huffman fornecida
void Dicionario::gerarDicionario(Node* raiz, std::string caminho) {
  // Define os caminhos para os filhos esquerdo e direito
  std::string esquerda = caminho + "0";
  std::string direita = caminho + "1";

  // Se o nó for uma folha, adiciona o caractere e o caminho ao dicionário
  if (raiz->getEsq() == nullptr && raiz->getDir() == nullptr) {
    dicionario[raiz->getCaracter()] = caminho;
  } 
  // Caso contrário, chama a função recursivamente para os filhos esquerdo e direito
  else {
    gerarDicionario(raiz->getEsq(), esquerda);
    gerarDicionario(raiz->getDir(), direita);
  }
}



std::string* Dicionario::getDicionario() {
  return dicionario;
}