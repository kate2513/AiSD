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
		std::cout << "Удаление элементов пирамиды:\n";
		if (top)
			randTreap::clean(top);
	}
	//release of the allocated memory, method for destructor
	void clean(node * temp){
		if (temp->left)
			randTreap::clean(temp->left);
		if (temp->right)
			randTreap::clean(temp->right);
		std::cout << "Удаление (" << temp->key <<"; "<< temp->priority <<")\n";
		delete temp;
	}
	//adding new node, with correction
	void insert(elem key,node ** temp){
			if (!(*temp)){
				std::cout << "Место для нового элемента (по ключу) найдено!\n";
				*temp = new node;
				(*temp)->key=key;
				(*temp)->priority=(double)(rand() % 10)/10;
				std::cout << "Сгенерирован приоритет = "<< (*temp)->priority<<"\n";
				(*temp)->left=NULL;
				(*temp)->right=NULL;
				std::cout << "Вид пирамиды после вставки элемета (по ключу):\n";
				randTreap::print(top,randTreap::height(top));
				//checking if treap is correct, if not
				//turning it to the right direction
				if(randTreap::iscorrect(top)){
					std::cout << "По приоритету БДП соотвествует пирамиде! Дальнейших преобразований не требуется!\n";
				}
				else{
					std::cout << "=> по приоритету БДП не соотвествует пирамиде!\n";
					do{
						randTreap::check_heap(&top);
						std::cout << "Вид пирамиды после поворота:\n";
						randTreap::print(top,randTreap::height(top));
					}while(!(randTreap::iscorrect(top)));

					//	std::cout << "After correction:\n";
					//	randTreap::print(top,randTreap::height(top));
					
				}
			}
			else if (key < (*temp)->key){
				std::cout << "Новый ключ ("<<key<<") меньше " << (*temp)->key <<". Переходим на левую ветвь.\n";
				randTreap::insert(key,&((*temp)->left));
			}
			else if (key > (*temp)->key){
				std::cout << "Новый ключ ("<<key<<") больше " << (*temp)->key <<". Переходим на правую ветвь.\n";
				randTreap::insert(key,&((*temp)->right));
			}
	}
	//changing treap to correct one
	void check_heap(node ** temp, double max=1.0){
		if (*temp){
			if ((*temp)->right){
				if ((*temp)->priority < (*temp)->right->priority){
					std::cout << "Необходим поворот БДП налево, т.к. "
						<< (*temp)->priority <<" < " << (*temp)->right->priority
						<< std::endl;
					randTreap::left_turn(temp);
				}
			}
			if((*temp)->left){
				if ((*temp)->priority < (*temp)->left->priority){
					std::cout << "Необходим поворот БДП направо, т.к. "
						<< (*temp)->priority <<" < " << (*temp)->left->priority
						<< std::endl;
					randTreap::right_turn(temp);
				}
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
			if (temp->priority < temp->left->priority){
				std::cout << "Приоритет отца ("<< temp->priority <<") меньше приоритета левого сына ("<< temp->left->priority<<")\n";
				return false;
			}
		}
		if (temp->right){
			if (temp->priority < temp->right->priority){ 
				std::cout << "Приоритет отца ("<< temp->priority <<") меньше приоритета правого сына ("<< temp->right->priority<<")\n";
				return false;
			}
		}
		return randTreap::iscorrect(temp->left) && randTreap::iscorrect(temp->right);
	}
	//printing treap
	void print(node * temp, int height){
		char * fstr = new char[10];
		if (!height){
			std::cout << "Пустое БДП!\n";
			return;
		}
		std::string dashes(height,'-');
		if (temp){
			sprintf(fstr,"(%d; %.1lf)",temp->key,temp->priority);
//			std::cout.width(height+20);
			std::cout << std::setw(height+1)<<dashes << std::setw(12) <<fstr << std::endl;
			delete [] fstr;
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
		std::cout << "Поворот налево:\n";
		node * forswap=NULL;
		char * node_str = new char[10];
		if (*temp){
			sprintf(node_str,"(%d; %.1lf)",(*temp)->key,(*temp)->priority);
			std::cout << node_str << " становится левым сыном своего правого сына ";
			forswap = (*temp)->right;
			sprintf(node_str,"(%d; %.1lf)",forswap->key,forswap->priority);
			std::cout << node_str << "\nМесто его правого сына займет левый сын " << node_str
				<< " (если он есть, иначе он останется без правого сына).\n";
			(*temp)->right = forswap->left;
			forswap->left = (*temp);
			(*temp) = forswap;
		}
		delete [] node_str;
	}
	//making right turn of the treap
	void right_turn(node ** temp){
		std::cout << "Поворот направо:\n";
		node * forswap=NULL;
		char * node_str = new char[10];
		if (*temp){
			sprintf(node_str,"(%d; %.1lf)",(*temp)->key,(*temp)->priority);
			std::cout << node_str << " становится правым сыном своего левого сына ";
			forswap = (*temp)->left;
			sprintf(node_str,"(%d; %.1lf)",forswap->key,forswap->priority);
			std::cout << node_str << "\nМесто его леввого сына займет правый сын " << node_str
				<< " (если он есть, иначе он останется без левого сына).\n";
			(*temp)->left = forswap->right;
			forswap->right = (*temp);
			(*temp) = forswap;
		}
		delete [] node_str;
	}
	//searching for the key
	bool search(node * temp,elem key){
		if (!temp) return false;
		if (temp->key == key) return true;
		else if (key< temp->key) randTreap::search(temp->left,key);
		else if (key > temp->key) randTreap::search(temp->right,key);
	//	else return randTreap::search(temp->left,key) || randTreap::search(temp->right,key);
	}
};
