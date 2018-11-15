#include <cmath>
#include <string>
#include <iostream>

template <class Type>
struct binTree{
	binTree(int n = 0): depth(n)
	{
		size=(int)pow(2.0,(double)depth)-1;
		storage = new bt_element[size];
		for (int i=0;i<size;i++){
			storage[i].value=0;
			storage[i].left=0;
			storage[i].right=0;
		}
	}
	~binTree()
	{
		delete [] storage;
	}
	void print_tree(int index,int depth){
		std::string tabs(depth,'-');
			if (storage[index].value){
				std::cout.width(this->depth+3);
				std::cout << storage[index].value + tabs << std::endl;
			}
			if (storage[index].left>0){
				binTree::print_tree(storage[index].left,depth-1);
			}
			if (storage[index].right>0){
				binTree::print_tree(storage[index].right,depth-1);
			}
	}
	struct bt_element{
		Type value;
		int left;
		int right;
	};
	int size;
	bt_element * storage; 
	int depth;
};

template <class Type>
struct Forest{
        Forest(int n = 0,int num_sons = 3,int fdepth=0): size(n),max_sons(num_sons+1),depth(fdepth)
        {
                storage = new forest_element[size];
                for (int i=0;i<size;i++){
                        storage[i].value=0;
			storage[i].sons = new int[max_sons];
                        for (int j=0;j<max_sons;j++)
                        	storage[i].sons[j]=-1;
                }
        }
        ~Forest()
        {
		for (int i=0;i<size;i++)
			delete [] storage[i].sons;
                delete [] storage;
        }
        void print_forest(int index,int depth){
                std::string tabs(depth+1,'-');
		int son_ind=0;
                        if (storage[index].value){
                                std::cout.width(this->depth+3);
                                std::cout << storage[index].value + tabs << std::endl;
                        }
			while (storage[index].sons[son_ind]>-1){
                                Forest::print_forest(storage[index].sons[son_ind],depth-1);
				son_ind++;
			}
        }
	void print_horizontal(std::string * out,int index, int level){
		int son_ind=0;
		while (storage[index].sons[son_ind]>-1){
			out[level]+=storage[storage[index].sons[son_ind]].value;
			son_ind++;
		}
		son_ind=0;
		while (storage[index].sons[son_ind]>-1){
                        Forest::print_horizontal(out,storage[index].sons[son_ind],level+1);
			son_ind++;
		}
		
	}
        struct forest_element{
                Type value;
                int * sons;
        };
        int size;
	int max_sons;
        forest_element * storage; 
	int depth;
};

int fill_from_str(const binTree<char> * bt,const std::string str_bt, int * position, int root);

void convert_bt_to_forest(const binTree<char> * bt, Forest<char> * bt_forest,int father,int num_son,int * posf,int pos);
