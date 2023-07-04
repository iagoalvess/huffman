#ifndef ARVORE_HPP
#define ARVORE_HPP

#include "node.hpp"
#include "lista_ordenada.hpp"

class Arvore {
private:
  Node* raiz;

public:
  Arvore();
  ~Arvore();

  void montarArvore(ListaOrdenada* lista);
  void destruirArvore(Node* raiz);

  Node* getRaiz();
};

#endif