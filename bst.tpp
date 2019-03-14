//submit this file
//you do NOT need to include any header in this file
//just write your BST implementation here right away


template <typename KeyType, typename ValueType>
BST<KeyType, ValueType>::BST(const BST<KeyType, ValueType>& another){
	//cout << "cons " << another.root->data.key << endl;

	if(!another.isEmpty()){
		root = new BSTNode<KeyType, ValueType>(another.root->data.key, another.root->data.value);
		BST<KeyType, ValueType>* lefttree = new BST<KeyType, ValueType>(another.leftSubtree());

		root->left = *lefttree;
		BST<KeyType, ValueType>* righttree = new BST<KeyType, ValueType>(another.rightSubtree());

		root->right = *righttree;
	}else{
		root = nullptr;
		return;
	}
	size = another.size;
	return;
}

template <typename KeyType, typename ValueType>
bool BST<KeyType, ValueType>::isEmpty() const{
	if(root == nullptr) return true;
	return false;
}

template <typename KeyType, typename ValueType>
const BST<KeyType, ValueType>* BST<KeyType, ValueType>::findMin() const{
	if(!this->root->left.isEmpty())
		return this->root->left.findMin();

	return this;
}

template <typename KeyType, typename ValueType>
const BST<KeyType, ValueType>& BST<KeyType, ValueType>::rightSubtree() const{
	return (root->right);
}

template <typename KeyType, typename ValueType>
const BST<KeyType, ValueType>& BST<KeyType, ValueType>::leftSubtree() const{
	return (root->left);
}

template <typename KeyType, typename ValueType>
bool BST<KeyType, ValueType>::add(KeyType key, ValueType value){
	if (isEmpty()){
		root = new BSTNode<KeyType, ValueType>(key, value);
		size++;
		return true;
	}
	//cout << "add" << key << "to" << root->data.key<< endl;

	if(key == root->data.key){
		return false;
	}
	else if (key < this->root->data.key){
		//cout << "go left\n";
		return root->left.add(key, value);
	}
	else if (key > this->root->data.key){
		//cout << "go right\n";
		return root->right.add(key, value);
	}
	return false;
}

template <typename KeyType, typename ValueType>
bool BST<KeyType, ValueType>::remove(KeyType key){
	//cout << this->root->data.key << key << endl;

	if (isEmpty())
		return false;
	if (key < root->data.key)
		return root->left.remove(key);
	else if (key > root->data.key)
		return root->right.remove(key);
	else if (!root->left.isEmpty() && !root->right.isEmpty()) // Found node has 2 children
	{
		//cout << "two\n";
	root->data.value = root->right.findMin()->root->data.value;
	root->data.key = root->right.findMin()->root->data.key;
	return root->right.remove(root->data.key);
	}
	else
	{
	BSTNode<KeyType, ValueType>* deleting_node = root; // Save the root to delete first
	root = (root->left.isEmpty()) ? root->right.root : root->left.root;
	deleting_node->left.root = nullptr;
	deleting_node->right.root = nullptr;
	delete deleting_node;
	return true;
	}
}

template <typename KeyType, typename ValueType>
ValueType BST<KeyType, ValueType>::get(KeyType key) const{
	if(!isEmpty()){
		BST<KeyType, ValueType>* current = new BST<KeyType, ValueType>(*this);
		BST<KeyType, ValueType>* deleteP = current;
		while(1){
			if(key < current->root->data.key){
				if(current->root->left.isEmpty())
					break;
				current = &(current->root->left);
				continue;
			}
			if(key > current->root->data.key){
				if(current->root->right.isEmpty())
					break;
				current = &(current->root->right);
				continue;
			}
			if(key == current->root->data.key){
				ValueType R = current->root->data.value;
				delete deleteP;
				return R;
			}
		}
		delete deleteP;
	}


	if (typeid(ValueType) == typeid(int))
		return 0;
	else
		return ValueType();
}

template <typename KeyType, typename ValueType>
int BST<KeyType, ValueType>::count() const{
	if(isEmpty())
		return 0;

	return this->root->left.count() + this->root->right.count() + 1;
}

template <typename KeyType, typename ValueType>
int BST<KeyType, ValueType>::height() const{
	if (isEmpty()) return 0;
	if(this->root->left.isEmpty() && this->root->right.isEmpty()) return 0;
	return 1 + (this->root->left.height() <= this->root->right.height() ? this->root->right.height() : this->root->left.height());
}

template <typename KeyType, typename ValueType>
const Pair<KeyType, ValueType>* BST<KeyType, ValueType>::operator[] (int n) const{

	if(isEmpty()) return nullptr;
	if(n < 0) return nullptr;
	if(n >= count()) return nullptr;
	//cout << "to cons " << this->root->data.key << endl;
	BST<KeyType, ValueType>* current = new BST<KeyType, ValueType>(*this);
	BST<KeyType, ValueType>* currentD = current;

	while(current->root->left.count() >= n + 1){
		current = &(current->root->left);
	}

	if(current->root->left.count() == n){
		Pair<KeyType, ValueType>* R = new Pair<KeyType, ValueType>(current->root->data.key, current->root->data.value);
		delete currentD;
		current = nullptr;
		return R;
	}

	const Pair<KeyType, ValueType>* R = current->root->right.operator[](n - current->root->left.count() - 1);
	delete currentD;
	current = nullptr;
	return R;
}

template <typename KeyType, typename ValueType>
void BST<KeyType, ValueType>::print(ostream& os) const{
	for(int i = 0; i < count(); i++)
	os << "(" << this->operator [](i)->key << "," << this->operator [](i)->value << ")";
}
