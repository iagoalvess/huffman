#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "tabela_frequencia.hpp"
#include "lista_ordenada.hpp"
#include "arvore.hpp"
#include "dicionario.hpp"
#include "huffman.hpp"

// Função para compactar um arquivo
void compactarArquivo(const std::string& arquivoEntrada, const std::string& arquivoSaida) {
  std::ifstream arquivo(arquivoEntrada);
  if (!arquivo.is_open()) {
    throw std::runtime_error("Erro ao abrir o arquivo de entrada.");
  }

  // Ler todo o conteúdo do arquivo de entrada em uma string
  std::stringstream buffer;
  buffer << arquivo.rdbuf();
  std::string texto = buffer.str();

  // Criação da tabela de frequência a partir do texto
  TabelaFrequencia tabela;
  tabela.preencheTabela(texto);

  // Criação da lista ordenada a partir da tabela de frequência
  ListaOrdenada lista;
  lista.preencherLista(tabela.getTabela());

  // Montagem da árvore de Huffman a partir da lista ordenada
  Arvore arvore;
  arvore.montarArvore(&lista);

  // Geração do dicionário de Huffman a partir da árvore
  Dicionario dicionario;
  dicionario.gerarDicionario(arvore.getRaiz(), "");

  // Criação do objeto Huffman com o dicionário gerado
  Huffman huffman(&dicionario);

  // Codificação do texto original usando o dicionário
  huffman.codificar(texto);

  // Compactação do texto codificado e gravação no arquivo de saída
  huffman.compactar(huffman.getTextoCodificado(), tabela, arquivoSaida);
}



// Função para descompactar um arquivo
void descompactarArquivo(const std::string& arquivoEntrada, const std::string& arquivoSaida) {
  std::ifstream arquivoCompactado(arquivoEntrada, std::ios::binary);
  if (!arquivoCompactado.is_open()) {
    throw std::runtime_error("Erro ao abrir o arquivo compactado.");
  }

  // Abertura do arquivo que contém a tabela de frequência
  std::ifstream arquivoTabela("bin/arquivo_tabela.bin", std::ios::binary);
  if (!arquivoTabela.is_open()) {
    throw std::runtime_error("Erro ao abrir o arquivo necessário para descompactar, verifique se a compactação foi feita corretamente.");
  } 
  // Verifica se o arquivo está vazio, caso o usuário compile e tente executar a descompactação sem compactar
  else if (arquivoTabela.peek() == std::ifstream::traits_type::eof()) {
    throw std::runtime_error("O arquivo tabela está vazio. Não é possível descompactar sem a tabela de frequência. Tente compactar o arquivo primeiro");
  }

  // Leitura da tabela de frequência do arquivo
  TabelaFrequencia tabela;
  unsigned int* tabelaFrequencia = tabela.getTabela();
  for (int i = 0; i < TAM; i++) {
    arquivoTabela.read(reinterpret_cast<char*>(&tabelaFrequencia[i]), sizeof(unsigned int));
  }

  // Criação da lista ordenada a partir da tabela de frequência
  ListaOrdenada lista;
  lista.preencherLista(tabela.getTabela());

  // Montagem da árvore de Huffman a partir da lista ordenada
  Arvore arvore;
  arvore.montarArvore(&lista);

  // Criação do objeto Huffman sem o dicionário, pois será lido do arquivo compactado
  Huffman huffman(nullptr);

  // Descompactação do arquivo e gravação do resultado no arquivo de saída
  huffman.descompactar(arvore.getRaiz(), arquivoEntrada, arquivoSaida);
}



int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Uso: " << argv[0] << " -c arquivo_entrada.txt arquivo_compactado.bin" << std::endl;
    std::cerr << "     " << argv[0] << " -d arquivo_compactado.bin arquivo_descompactado.txt" << std::endl;
    return 1;
  }

  std::string opcao = argv[1];
  std::string arquivoEntrada = argv[2];
  std::string arquivoSaida = argv[3];

  try {
    if (opcao == "-c") {
      compactarArquivo(arquivoEntrada, arquivoSaida);
      std::cout << "Arquivo compactado com sucesso!" << std::endl;
    } else if (opcao == "-d") {
      descompactarArquivo(arquivoEntrada, arquivoSaida);
      std::cout << "Arquivo descompactado com sucesso!" << std::endl;
    } else {
      std::cerr << "Opção inválida. Use -c para compactar ou -d para descompactar." << std::endl;
      return 1;
    }
  } catch (const std::exception& e) {
    std::cerr << "Erro: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
