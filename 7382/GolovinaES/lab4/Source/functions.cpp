#include "structures.h"

//filling binary tree from string with bracket binary tree
int fill_from_str(const binTree<char> * bt,const std::string str_bt, int * position, int root){
		int curr_pos=0;
		int left_son=2*root+1;
		int right_son=2*root+2;
		if (root>-1){
			if (bt->storage[root].left==0)
				curr_pos=left_son;
			else
				curr_pos=right_son;

		}

		if (curr_pos>=bt->size) return 0;
		while(1){
			if (str_bt[*position]==')'){
				(*position)++;
				if (bt->storage[curr_pos].left==0)
					bt->storage[curr_pos].left=-1;
				if (bt->storage[curr_pos].right==0)
					bt->storage[curr_pos].right=-1;
				break;
			}
			if (str_bt[*position]=='#'){
				(*position)++;
				bt->storage[curr_pos].left=-1;
				std::cout << "Father " << bt->storage[curr_pos].value << " has no left son."<< std::endl;
				continue;
			}
			if (str_bt[*position]=='('){
				(*position)++;
				fill_from_str(bt,str_bt,position,curr_pos);
				continue;
			}
			if (isalpha(str_bt[*position])){
				bt->storage[curr_pos].value=str_bt[*position];
				(*position)++;
				if (root==-1){
					std::cout << bt->storage[curr_pos].value << " in the top of the tree." << std::endl;
					continue;
				}
				if (curr_pos==left_son){
					std::cout << "Father " << bt->storage[root].value;
					std::cout << " has left son = " << bt->storage[curr_pos].value << std::endl;
					bt->storage[root].left=left_son;
				}
				if (curr_pos==right_son){
					std::cout << "Father " << bt->storage[root].value;
					std::cout << " has right son = " << bt->storage[curr_pos].value << std::endl;
					bt->storage[root].right=right_son;
				}
				continue;
			}
			(*position)++;
		}
		return 0;
	}

// convertation binaty tree into forest
void convert_bt_to_forest(const binTree<char> * bt, Forest<char> * bt_forest,int father,int num_son,int * posf,int pos){
	bt_forest->storage[*posf].value=bt->storage[pos].value;
	bt_forest->storage[father].sons[num_son]=*posf;
	if (bt->storage[pos].left>-1){
		(*posf)++;
		convert_bt_to_forest(bt,bt_forest,(*posf)-1,0,posf,bt->storage[pos].left);
	}
	if (bt->storage[pos].right>-1){
		(*posf)++;
		convert_bt_to_forest(bt,bt_forest,father,num_son+1,posf,bt->storage[pos].right);
	}
	return;
}
