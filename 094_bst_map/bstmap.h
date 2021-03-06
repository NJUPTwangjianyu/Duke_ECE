#include "map.h"
#include <exception>

template<typename K,typename V>
class BstMap: public Map<K,V> {
protected:
  struct Node{
    K & key;
    V & value;
    Node * left;
    Node * right;
    Node(const K & k, const K & v): key(k), value(v), left(NULL),right(NULL){}
  };
  void deleteTree(Node * node);
  void copyTree(Node ** node, Node * rt);
  Node * root;
  Node ** searchNode(const K & k) const;
public:
  virtual void add(const K & key,const V & value);
  virtual const V & lookup(const K& key) const throw (std::invalid_argument);
  virtual void remove(const K& key);
  BstMap(const BstMap & rhs){  //deep copy
    copyTree(&root, rhs.root); 
  }
  const BstMap & operator=(const BstMap & rhs){ //shallow copy
    if (&rhs != this){
      root = rhs.root;
    }
    return *this;
  }
  virtual ~BstMap(){
    deleteTree(root);
  }
};

template<typename K, typename V>
void BstMap<K,V>::deleteTree(Node * node){
  if (node == NULL){
    return;
  }
  if (!(node->left) && !(node->right)){
    delete node;
    return;
  }
  deleteTree(node->left);
  deleteTree(node->right);
}

template<typename K, typename V>
void BstMap<K,V>::copyTree(Node ** node, Node*rt){
  if(rt!=NULL){
    *node = new Node(rt->key,rt->value);
    copyTree(&(*node->left),rt->left);
    copyTree(&(*node->right),rt->right);
  }
}

template<typename K,typename V>      //Node **, stop default constructor
typename BstMap<K,V>::Node ** BstMap<K,V>::searchNode(const K & k)const{
  Node ** n =const_cast<Node**>(&root);
  while(*n!=NULL){
    if(*n->key < k){
      *n = *n->right;
    }else if(*n->key > k){
      *n = *n->left;
    }else{
      break;
    }
  }
  return *n;
}
template<typename K,typename V>
void BstMap<K,V>::add(const K & key,const V & value){
  Node ** n = searchNode(key);
  if(*n == NULL){
    *n = new Node(key,value);
  }else{
    *n->value = value;
  }
  return;
}

template<typename K, typename V>
const V & BstMap<K,V>::lookup(const K&key) const throw (std::invalid_argument){
  Node ** n = searchNode(key);
  if (*n==NULL){
    throw std::invalid_argument("key is not there!");
  }
  return (*n)->value;
}

template<typename K, typename V>
void BstMap<K,V>::remove(const K & key){
  Node ** n = searchNode(key);
  if (*n==NULL){
    return;
  }
  if(((*n)->left==NULL)&&((*n)->right==NULL)){
    delete *n;
  }else if(((*n)->left!=NULL)&&((*n)->right==NULL)){
    *n = (*n)->left;
  }else if(((*n)->left==NULL)&&((*n)->right!=NULL)){
    *n = (*n)->right;
  }else{
    Node * swap = (*n)->right;
    while(swap->left!=NULL){
      swap = swap->left;
    }
    Node * temp = *n;
    *n = swap;
    (*n)->left = temp->left;
    (*n)->right = temp->right;
  }
  return;
}


  
  

  
    
 
    
  
  
