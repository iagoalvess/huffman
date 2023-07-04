#include "huffman.hpp"

Huffman::Huffman(Dicionario* dicionario) : dicionario(dicionario), texto_codificado("") {}


// Obtém o código binário correspondente ao caractere atual usando o dicionário e adiciona-o ao texto codificado
void Huffman::codificar(std::string texto) {
  for (char c : texto) {
    texto_codificado += dicionario->getDicionario()[static_cast<unsigned char>(c)];
  }
}



// Cria um arquivo que armazena a frequencia do arquivo compactado para posterior descompactacao
void Huffman::arquivoParaDescompactar(TabelaFrequencia tabela) {
  std::ofstream arquivo("bin/arquivo_tabela.bin", std::ios::binary);

  // Verifica se o arquivo foi aberto corretamente
  if (!arquivo.is_open()) {
    std::cout << "Erro ao abir o arquivo em arquivoParaDescompactar: necessario para posterior descompactacao" << std::endl;
    return;
  }

  // Obtém a tabela de frequência
  const unsigned int* tabelaFrequencia = tabela.getTabela();

  // Escreve cada frequência no cabeçalho
  for (int i = 0; i < TAM; i++) {
    unsigned int frequencia = tabelaFrequencia[i];
    arquivo.write(reinterpret_cast<const char*>(&frequencia), sizeof(unsigned int));
  }

  arquivo.close();
}



void Huffman::compactar(std::string str, TabelaFrequencia tabela, std::string arquivoSaida) {
  std::ofstream arquivo(arquivoSaida, std::ios::binary);

  // Verifica se o arquivo foi aberto corretamente
  if (!arquivo.is_open()) {
    throw std::runtime_error ("Erro ao abrir/criar o arquivo para compactacao");
  }

  // Criacao de um arquivo que armazena a tabela necessaria para uma posterior descompactacao
  arquivoParaDescompactar(tabela);

  unsigned char byte = 0;
  int i = 0, j = 7;

  while (str[i] != '\0') {
    unsigned char mascara = 1;

    // Verifica se o caractere é '1' e realiza operações de máscara e bit a bit
    if (str[i] == '1') {
      mascara = mascara << j;
      byte = byte | mascara;
    }

    j--;

    // Escreve o byte no arquivo quando todos os bits foram preenchidos
    if (j < 0) {
      arquivo.write(reinterpret_cast<char *>(&byte), sizeof(unsigned char));
      byte = 0;
      j = 7;
    }

    i++;
  }

  // Se houver bits restantes no byte, escreve o byte no arquivo
  if (j != 7) {
    arquivo.write(reinterpret_cast<char *>(&byte), sizeof(unsigned char));
  }

  arquivo.close();
}



void Huffman::descompactar(Node* raiz, std::string arquivoEntrada, std::string arquivoSaida) {
  std::ifstream arquivo1(arquivoEntrada, std::ios::binary);
  std::ofstream arquivo2(arquivoSaida);
  Node* aux = raiz;

  // Verifica se os arquivos de entrada e saída foram abertos corretamente
  if (!arquivo1.is_open() || !arquivo2.is_open()) {
    throw std::runtime_error("Erro ao abrir arquivo na descompactacao");
  }

  unsigned char byte;
  int i;

  // Loop de leitura e descompactação dos bytes do arquivo de entrada
  while (arquivo1.read(reinterpret_cast<char *>(&byte), sizeof(unsigned char))) {
    for (i = 7; i >= 0; i--) {
      if (verificaBitUm(byte, i)) {
        aux = aux->getDir(); // Se o bit atual for 1, avança para o nó filho direito
      }
      else {
        aux = aux->getEsq(); // Se o bit atual for 0, avança para o nó filho esquerdo
      }

      // Verifica se chegou a um nó folha, ou seja, um caractere foi encontrado
      if (aux->getEsq() == nullptr && aux->getDir() == nullptr) {
        char caracter = aux->getCaracter();
        arquivo2 << caracter; // Escreve o caractere no arquivo de saída
        aux = raiz; // Reinicia a busca a partir da raiz da árvore
      }
    }
  }

  arquivo1.close();
  arquivo2.close();
}



unsigned int Huffman::verificaBitUm(unsigned char byte, int i) {
  unsigned char mascara = (1 << i);
  return byte & mascara;
}



std::string Huffman::getTextoCodificado() {
  return texto_codificado;
}