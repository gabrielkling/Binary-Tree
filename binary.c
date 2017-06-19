#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <stdbool.h>

struct tree{

  int info;
  struct tree *left;
  struct tree *right;

};

typedef struct tree Tree;

struct List{
  Tree *root;
  int qtd;
};

typedef struct List list;

// Vefirica se a árvore é nula
int arvore_vazia(Tree *t){
    return (t == NULL);
}

Tree *minimo(Tree *T){// procura o nó com valor mínimo
    if(arvore_vazia(T)){
       return NULL;
    }else{
          if( arvore_vazia(T->left) ){
              return T;
          }else{
              return minimo(T->left);
          }
    }
}

// NOT WORKING

void delete(Tree *root, int valor){
    Tree *aux;
    if(!arvore_vazia(root)){
       if(valor < root->info){ // se o valor que será removido for menor que o nó atual,
           delete(root->left, valor); // faz recursividade á left
       }else{
            if(valor > root->info){ // se o valor que será removido for menor que o nó atual,
                 delete(root->right, valor); // faz recursividade á right.
             }else{ // encontrou
                if( !arvore_vazia(root->left) && !arvore_vazia(root->right) ){ // quando o nó a ser removido for encontrado,
                                                // verificamos se os nós filhos da left e right não são null.
                     aux = minimo(root->right); // se não forem null, buscamos o menor nó a artir do nó da right.
                     root->info = (aux->info);
                     delete(root->right, root->info);
                }else{
                       aux = root; // caso os nó da right e da left, ou somente o da right, precisamos apenas remover
                                    // o nó atual e fazer ajustar os ponteiros
                       if(arvore_vazia(root->left)){ // se o nó da left for vazio
                           root = root->right;
                        } // o nó pai do atual, apontará para o filho da right do nó atual.
                       else root = root->left; // se o nó da left não for vazio.
                                                  // o nó pai do atual, apontará para o filho da left do nó atual.
                free(aux);
                }
            }
       }
    }
}

list *new_tree(int k){

  list *new = (list*)(malloc(sizeof(list*)));

  new->root = (Tree*)(malloc(sizeof(Tree*)));
  new->qtd = 1;
  new->root->info = k;
  new->root->left = NULL;
  new->root->right = NULL;

  return new;
}

int cont = 0;

void pre_order(Tree *root){

  if(root){
    printf("Index: %i Element: %i\n", cont, root->info);
    cont++;
    pre_order(root->left);
    pre_order(root->right);
  }
}

void in_order(Tree *root){

  if(root){
    in_order(root->left);
    printf("Index: %i Element: %i\n", cont, root->info);
    cont++;
    in_order(root->right);
  }
}

void post_order(Tree *root){

  if(root){
    post_order(root->left);
    post_order(root->right);
    printf("Index: %i Element: %i\n", cont, root->info);
    cont++;
  }
}

void add(Tree *root, int info){

  if(!root->left && info < root->info){

    Tree *new = (Tree*)(malloc(sizeof(Tree*)));
    if(!root) return;
    root->left = new;
    new->left = NULL;
    new->right = NULL;
    new->info = info;
    return;
  }

  if(!root->right && info >= root->info){

    Tree *new = (Tree*)(malloc(sizeof(Tree*)));
    if(!root) return;
    root->right = new;
    new->left = NULL;
    new->right = NULL;
    new->info = info;
    return;
  }

  if(info < root->info){
    add(root->left, info);
  }

  else{
    if(info > root->info){
      add(root->right, info);
    }
  }
}

bool search(Tree *root, int info){

  if(root->info == info) return true;

  else if(info > root->info){
    search(root->right, info);
  }

  else if(info < root->info){
    search(root->left, info);
  }

  else return false;

}

void main(){

  int info, k, test;

  int c;

  printf("Type an element to the root:\n");
  scanf("%d", &info);

  list *new = new_tree(info);

  Tree *p = new->root;

  while(5){

    printf("Please type the option that you want:\n\n");

    printf("\t\t1 - Add.\n\t\t2 - Delete.\n\t\t3 - Search.\n\t\t4 - Print.\n\t\t5 - Exit.\n");
    scanf("%d", &c);

    if(c > 5){
      printf("Invalid option, type again!\n");
    }

    switch(c){

      system("clear");

      case 1:

      printf("Type an element to add:\n");
      scanf("%d", &info);

      system("clear");

      add(p, info);

      break;

      case 2:

      printf("Type an element to delete:\n");
      scanf("%d", &info);
      delete(p, info);

      break;

      case 3:

      printf("Type an element to search:\n");
      scanf("%d", &info);

      system("clear");

      bool ver = search(p, info);

      if(ver) printf("Element found!\n");

      if(!ver) printf("Element not found!\n");

      break;

      case 4:

      printf("1 - Pre Order.\n2 - In Order.\n3 - Post Order.\n");
      scanf("%d", &k);

      system("clear");

      switch(k){
        case 1:

        cont = 0;
        pre_order(p);
        break;

        case 2:

        cont = 0;
        in_order(p);
        break;

        case 3:

        cont = 0;
        post_order(p);
        break;
      }

      break;

      case 5:

      exit(1);
    }
  }
}
