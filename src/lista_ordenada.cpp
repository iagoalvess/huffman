#include "lista_ordenada.hpp"

ListaOrdenada::ListaOrdenada() : inicio(nullptr), tamanho(0) {}



// Insere um nó na lista de forma ordenada
void ListaOrdenada::inserirOrdenado(Node* node) {
  Node *aux;

  // Se a lista estiver vazia, insere o nó no início
  if(inicio == nullptr) {
    inicio = node;
  }
  // Se a frequência do nó for menor que a frequência do primeiro nó da lista, insere o nó no início
  else if(node->getFrequencia() < inicio->getFrequencia()) {
    node->setProximo(inicio);
    inicio = node;
  }
  // Caso contrário, percorre a lista até encontrar a posição correta para inserir o nó
  else {
    aux = inicio;
    while (aux->getProximo() && aux->getProximo()->getFrequencia() <= node->getFrequencia()) {
      aux = aux->getProximo();
    }
    // Insere o nó na posição encontrada
    node->setProximo(aux->getProximo());
    aux->setProximo(node);
  }
  tamanho++;
}



// Preenche a lista com os valores da tabela de forma ordenada em relação a frequência
void ListaOrdenada::preencherLista(unsigned int tabela[]) {
  // Percorre a tabela de frequências
  for (int i = 0; i < TAM; i++) {
    // Se a frequência do caractere for maior que zero, cria um novo nó e insere na lista ordenada
    if(tabela[i] > 0) {
      Node* novo = new Node(static_cast<unsigned char>(i), tabela[i]);
      inserirOrdenado(novo);
    }
  }
}



// Remove o primeiro nó da lista
Node* ListaOrdenada::removeInicio() {
  if(inicio == nullptr) {
    return nullptr;
  }

  Node* aux = inicio;
  inicio = inicio->getProximo();
  tamanho--;

  return aux;
}



int ListaOrdenada::getTamanho() const {
  return tamanho;
}



Node* ListaOrdenada::getInicio() const {
  return inicio;
}