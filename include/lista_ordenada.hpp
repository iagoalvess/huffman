#ifndef LISTA_ORDENADA_HPP
#define LISTA_ORDENADA_HPP

#include <iostream>

#include "node.hpp"
#include "tabela_frequencia.hpp"

class ListaOrdenada {
private:
  Node* inicio;
  int tamanho;

public:
  ListaOrdenada();

  void inserirOrdenado(Node* node);
  void preencherLista(unsigned int tabela[]);

  Node* removeInicio();

  int getTamanho() const;
  Node* getInicio() const;
};

#endif