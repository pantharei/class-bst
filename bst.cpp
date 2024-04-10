#include <iostream>
#include <time.h>
class bst{
    struct node{ //struttura che rappresenta un nodo del bst
        int label;
        struct node* left{nullptr};
        struct node* right{nullptr};

        node(int k):label(k){} //parametrized constructor

        void print_node()const{
            std::cout << label << ' ';
        }
    };

    node* root{nullptr}; //node root of bst

    node* insert(node* root, int, bool&); //returns true if the node is inserted
    //false if the node already exists
    node* dealloca(node* root); //deallocates from the heap all nodes
    node* deleteNode(node* root, int, bool& ret); //deletes a node with a given label
    void inOrder(const node*)const; //simmetric visit

    public:

    bool add(int k){
        bool ret{}; //flag that is true if the insertion is executed
        //false if already exists a node with label equal to k
        root = insert(root,k,ret); //k is the label to insert
        return ret;
    }

    void simmetric()const{
        inOrder(root);
        std::cout << std::endl;
    }

    ~bst(){
        root = dealloca(root);
    }

    bool cancelNode(int k){
        bool ret{};
        deleteNode(root,k,ret);
        return ret;
    }
};

bst::node* bst::insert(node* root, int k, bool& ret){
    if(!root){
        root = new bst::node(k);
        ret = true;
        return root;
    };
    if(root->label == k){
        ret = false;
        return root;
    }else if(k < root->label)root->left = insert(root->left,k,ret);
    else root->right = insert(root->right,k,ret);

    return root;
}

void bst::inOrder(const bst::node* root)const{
    if(root){
        inOrder(root->left);
        root->print_node();
        inOrder(root->right);
    }
}

bst::node* bst::dealloca(bst::node* root){
    if(!root)return root;
    root->left = dealloca(root->left);
    root->right = dealloca(root->right);
    delete root;
    return nullptr;
}

bst::node* bst::deleteNode(node* root, int k, bool&ret){
    if(!root){
        ret = false;
        return root;
    }
    if(k < root->label) root->left = deleteNode(root->left,k,ret);
    else if(k > root->label) root->right = deleteNode(root->right,k,ret);
    else{
        ret = true;
        //found!
        if(!root->left){
            node* tmp{root};
            root = root->right;
            delete tmp;
            return root;
        }else if(!root->right){
            node* tmp{root};
            root = root->left;
            delete tmp;
            return root;
        }else{
            //2 figli
            node* prec{nullptr}, *succ{prec};
            succ = root->left;

            //trovo il più grande elemento del sottoalbero sx
            while(succ->right){
                prec = succ;
                succ = succ->right;
            }
            if(!prec){
                //succ è il più grande del st. sx
                root->left = succ->left;
                delete succ;
                return root;
            }else{
                prec->right = succ->right;
                //succ nodo da eliminare
                root->label = succ->label;
                delete succ;
                return root;
            }
        }
    }
}

//main function to test all the methods
int main(){

    bst b;
    srand(time(NULL)); //init random

    //random number of elements between 1 and 20
    int n{rand()%20+1};
    std::cout << "n:" << n << std::endl;

    for(int i = 0;i < n; ++i){
        //every element is a random number from [0,255]
        int number{rand()%256};
        if(!b.add(number))
            std::cout << "Inserimento non eseguito : " << number << "\n";
    }

    
    b.simmetric();

    //input from user to select the node that will be deleted
    int deleteTarget{};
    std::cout << "Digita nodo da eliminare..";
    std::cin >> deleteTarget;

    bool flag{b.cancelNode(deleteTarget)};
    if(!flag)
        std::cout << "Cancellazione Non Eseguita!\n";
    else std::cout << "Nodo Cancellato\n";

    std::cout << "Stampa di verifica:\n";
    b.simmetric();

    return 0;
}