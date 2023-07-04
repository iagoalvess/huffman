#ifndef NODE_HPP
#define NODE_HPP

class Node {
private:
  unsigned char caracter;
  int frequencia;

  Node* esq;
  Node* dir;
  Node* proximo;

public:
  Node();
  Node(unsigned char c, int f);

  Node* getProximo() const;
  void setProximo(Node* novo);

  int getFrequencia() const;
  void setFrequencia(int nova);

  unsigned char getCaracter() const;
  void setCaracter(unsigned char novo);

  Node* getEsq() const;
  void setEsq(Node* nova);

  Node* getDir() const;
  void setDir(Node* nova);
};

#endif