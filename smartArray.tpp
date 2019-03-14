//submit this file
//you do NOT need to include any header in this file
//just write your SmartArray implementation here right away

template <typename KeyType, typename ValueType>
SmartArray<KeyType, ValueType>::SmartArray(): Container<KeyType, ValueType>(), data(nullptr), size(0){
}

template <typename KeyType, typename ValueType>
SmartArray<KeyType, ValueType>::~SmartArray(){
	for(int i = 0; i < size ; i++){
		delete data[i];
		data[i] = nullptr;
	}
	delete [] data;
	//delete data;
	data = nullptr;
}

template <typename KeyType, typename ValueType>
bool SmartArray<KeyType, ValueType>::add(KeyType key, ValueType value){

	int i;
	for(i = 0; i < size; i++){
		if(key == data[i]->key)
			return false;
		if(key < data[i]->key)
			break;
	}

	Pair<KeyType, ValueType>** newdata = new Pair<KeyType, ValueType>* [size+1];
	size++;

	for(int j = 0; j < i; j++)
		newdata[j] = new Pair<KeyType, ValueType>(data[j]->key, data[j]->value);

	newdata[i] = new Pair<KeyType, ValueType>(key, value);

	for(int j = size - 2; j >= i; j--)
		newdata[j+1] = new Pair<KeyType, ValueType>(data[j]->key, data[j]->value);

	for(int i = 0; i < size - 1 ; i++){
		delete data[i];
	}
	delete [] data;

	data = newdata;

	return true;

}

template <typename KeyType, typename ValueType>
bool SmartArray<KeyType, ValueType>::remove(KeyType key){
	int i;
	bool check = false;
	for(i = 0; i < size; i++){
		if(key == data[i]->key){
			check = true;
			break;
		}
	}
	if(check == false){
		return false;
	}


	Pair<KeyType, ValueType>** newdata = new Pair<KeyType, ValueType>* [size-1];
	size--;
	int j = 0;
	for(j = 0; j < i; j++)
		newdata[j] = new Pair<KeyType, ValueType>(data[j]->key, data[j]->value);

	for(j; j < size; j++)
		newdata[j] = new Pair<KeyType, ValueType>(data[j+1]->key, data[j+1]->value);


	for(int i = 0; i < size + 1 ; i++){
		delete data[i];
	}
	delete [] data;
	//delete data;

	data = newdata;

	return true;

}

template <typename KeyType, typename ValueType>
ValueType SmartArray<KeyType, ValueType>::get(KeyType key) const{
	for(int i = 0; i < size; i++){
		if(key == data[i]->key)
			return data[i]->value;
	}

	if (typeid(ValueType) == typeid(int))
		return 0;
	else
		return ValueType();

}

template <typename KeyType, typename ValueType>
int SmartArray<KeyType, ValueType>::count() const{
	return size;
}

template <typename KeyType, typename ValueType>
const Pair<KeyType, ValueType>* SmartArray<KeyType, ValueType>::operator[] (int n) const{
	if(size == 0) return nullptr;
	if(n < 0) return nullptr;
	if(n >= count()) return nullptr;

	return data[n];

}

template <typename KeyType, typename ValueType>
void SmartArray<KeyType, ValueType>::print(ostream& os) const{
	for(int i = 0; i < size; i++){
		os << "(" << data[i]->key << "," << data[i]->value << ")";
	}
	return;
}

template <typename KeyType, typename ValueType>
bool SmartArray<KeyType, ValueType>::has(KeyType key) const{
	for(int i = 0; i < size; i++){
		if(key == data[i]->key)
			return true;
	}
	return false;
}
