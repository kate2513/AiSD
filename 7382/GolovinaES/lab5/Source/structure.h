//template for randomized treap, type of the key selectable
template <class elem>
struct randTreap{
	//struct for the node of the treap, which contains pair(key,priority)
	//and pointers to the sons
	struct node{

		elem key;
		double priority;
		node * left;
		node * right;
	};
	//pointer to the top node of the randomized treap
	node * top;
	//constructor
	randTreap(){
		top = NULL;
	}
	~randTreap(){
		if (top)
			randTreap::clean(top);
	}
	//release of the allocated memory, method for destructor
	void clean(node * temp){
		if (temp->left)
			randTreap::clean(temp->left);
		if (temp->right)
			randTreap::clean(temp->right);
		delete temp;
	}
	//adding new node, with correction
	void insert(elem key,node ** temp){
			if (!(*temp)){
				std::cout << "\nAdding " << key << "\n";
				*temp = new node;
				(*temp)->key=key;
				(*temp)->priority=(double)(rand() % 10)/10;
				(*temp)->left=NULL;
				(*temp)->right=NULL;
				std::cout << "Result:\n";
				randTreap::print(top,randTreap::height(top));
				//checking if treap is correct, if not
				//turning it to the right direction
				while(!(randTreap::iscorrect(top))){
					randTreap::check_heap(&top);
					std::cout << "After correction:\n";
					randTreap::print(top,randTreap::height(top));
				}
			}
			else if (key < (*temp)->key){
				randTreap::insert(key,&((*temp)->left));
			}
			else if (key > (*temp)->key){
				randTreap::insert(key,&((*temp)->right));
			}
	}
	//changing treap to correct one
	void check_heap(node ** temp, double max=1.0){
		if (*temp){
			if ((*temp)->right){
				if ((*temp)->priority < (*temp)->right->priority)
					randTreap::left_turn(temp);
			}
			if((*temp)->left){
				if ((*temp)->priority < (*temp)->left->priority)
					randTreap::right_turn(temp);
			}
			if ((*temp)->right)
				randTreap::check_heap(&((*temp)->right));
			if((*temp)->left)
				randTreap::check_heap(&((*temp)->left));
		}
	}
	//check if treap is correct
	bool iscorrect(node * temp){
		if (!temp) return true;
		if (temp->left){
			if (temp->priority < temp->left->priority) return false;
		}
		if (temp->right){
			if (temp->priority < temp->right->priority) return false;
		}
		return randTreap::iscorrect(temp->left) && randTreap::iscorrect(temp->right);
	}
	//printing treap
	void print(node * temp, int height){
		std::string dashes(height,'-');
		if (temp){
		//	std::cout.width(height+3);
			std::cout << dashes << temp->key << ", " << temp->priority << std::endl;
		}
		if (temp->left){
			randTreap::print(temp->left,height-1);
		}
		if (temp->right){
			randTreap::print(temp->right,height-1);
		}
	}
	//counting the height of the tree
	int height(node * temp){
		if (!temp) return 0;
		else return 1+std::max(randTreap::height(temp->left),randTreap::height(temp->right));
	}
	//making left turn of the treap
	void left_turn(node ** temp){
		node * forswap=NULL;
		if (*temp){
			forswap = (*temp)->right;
			(*temp)->right = forswap->left;
			forswap->left = (*temp);
			(*temp) = forswap;
		}
	}
	//making right turn of the treap
	void right_turn(node ** temp){
		node * forswap=NULL;
		if (*temp){
			forswap = (*temp)->left;
			(*temp)->left = forswap->right;
			forswap->right = (*temp);
			(*temp) = forswap;
		}
	}
	//searching for the key
	bool search(node * temp,elem key){
		if (!temp) return false;
		if (temp->key == key) return true;
		else return randTreap::search(temp->left,key) || randTreap::search(temp->right,key);
	}
};
