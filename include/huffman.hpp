#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <fstream>
#include <string>

#include "tabela_frequencia.hpp"
#include "dicionario.hpp"

class Huffman {
private:
  Dicionario* dicionario;
  
  std::string texto_codificado;

public:
  Huffman(Dicionario* dicionario);

  void arquivoParaDescompactar(TabelaFrequencia tabela);
  void codificar(std::string texto);
  void compactar(std::string str, TabelaFrequencia tabela, std::string arquivoSaida);
  void descompactar(Node* raiz, std::string arquivoEntrada, std::string arquivoSaida);

  unsigned int verificaBitUm(unsigned char byte, int i);

  std::string getTextoCodificado();
};

#endif