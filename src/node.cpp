#include "node.hpp"

Node::Node() : 
  caracter(0), 
  frequencia(0), 
  esq(nullptr), 
  dir(nullptr), 
  proximo(nullptr) {}



Node::Node(unsigned char c, int f) : 
  caracter(c), 
  frequencia(f), 
  esq(nullptr), 
  dir(nullptr), 
  proximo(nullptr) {}



Node* Node::getProximo() const {
  return proximo;
}



void Node::setProximo(Node* novo) {
  proximo = novo;
}



int Node::getFrequencia() const {
  return frequencia;
}



void Node::setFrequencia(int nova) {
  frequencia = nova;
}



unsigned char Node::getCaracter() const {
  return caracter;
}



void Node::setCaracter(unsigned char novo) {
  caracter = novo;
}



Node* Node::getEsq() const {
  return esq;
}



void Node::setEsq(Node* nova) {
  esq = nova;
}



Node* Node::getDir() const {
  return dir;
}



void Node::setDir(Node* nova) {
  dir = nova;
}