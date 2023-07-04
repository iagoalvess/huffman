#include "arvore.hpp"

Arvore::Arvore() : raiz(nullptr) {}



Arvore::~Arvore() {
  destruirArvore(raiz);
}



// Monta a árvore a partir da lista ordenada
void Arvore::montarArvore(ListaOrdenada* lista) {
  Node* primeiro;
  Node* segundo;
  Node* novo;

  // Enquanto a lista tiver mais de um elemento
  while(lista->getTamanho() > 1) {
    primeiro = lista->removeInicio();
    segundo = lista->removeInicio();
    novo = new Node();

    if(novo) {
      // Define o caractere como '+' e a frequência como a soma das frequências dos dois primeiros elementos
      novo->setCaracter('+');
      novo->setFrequencia(primeiro->getFrequencia() + segundo->getFrequencia());

      // Define os filhos esquerdo e direito do novo nó
      novo->setEsq(primeiro);
      novo->setDir(segundo);
      novo->setProximo(nullptr);

      // Insere o novo nó na lista ordenada
      lista->inserirOrdenado(novo);
    }
    // Lança uma exceção em caso de erro ao alocar memória
    else {
      throw std::runtime_error("Erro ao alocar memória em montarArvore");
    }
  }

  raiz = lista->getInicio();
}



// Destroi a árvore liberando a memória alocada
void Arvore::destruirArvore(Node* raiz) {
  if (raiz != nullptr) {
    destruirArvore(raiz->getEsq());
    destruirArvore(raiz->getDir());
    delete raiz;
  }
}



Node* Arvore::getRaiz() {
  return raiz;
}