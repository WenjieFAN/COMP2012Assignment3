//submit this file
//you do NOT need to include any header in this file
//just write your HashingVault implementation here right away

template <typename KeyType, typename ValueType>
HashingVault<KeyType, ValueType>::HashingVault(int size, Container<KeyType, ValueType>** table, int (*fun)(KeyType)){
	this->size = size;
	this->table = table;
	this->fun = fun;
}

template <typename KeyType, typename ValueType>
HashingVault<KeyType, ValueType>::~HashingVault(){
	for(int i = 0; i < size; i++){
		delete table[i];
	}
	delete [] table;
	table = nullptr;
}

template <typename KeyType, typename ValueType>
bool HashingVault<KeyType, ValueType>::add(KeyType key, ValueType value){
	int k;
	k = fun(key);
	return table[k]->add(key, value);
}

template <typename KeyType, typename ValueType>
ValueType HashingVault<KeyType, ValueType>::get(KeyType key) const{
	int k = fun(key);

	if(table[k] == nullptr){
		if (typeid(ValueType) == typeid(int))
			return 0;
		else
			return ValueType();
	}

	return table[k]->get(key);
}

template <typename KeyType, typename ValueType>
bool HashingVault<KeyType, ValueType>::remove(KeyType key){
	for(int i = 0; i < size; i++){
		if(table[i] == nullptr)
			continue;
		if(table[i]->has(key)){
			return table[i]->remove[key];

		}
	}

		return false;
}

template <typename KeyType, typename ValueType>
void HashingVault<KeyType, ValueType>::rehash(int size, Container<KeyType, ValueType>** table, int (*fun)(KeyType)){
	Container<KeyType, ValueType>** noobtable = this->table;
	int noobsize = this->size;
	this->table = table;
	this->fun = fun;
	this->size = size;



	for(int i = 0; i < noobsize; i++){
		if(noobtable[i] == nullptr)
			continue;
		//cout << i << " count() " << table[i]->count() << endl;
		for(int j = 0; j < noobtable[i]->count(); j++){
			this->add(noobtable[i]->operator[](j)->key, noobtable[i]->operator[](j)->value);
		}
		delete noobtable[i];
	}

	delete [] noobtable;

	return;

}
