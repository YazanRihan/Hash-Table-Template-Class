#ifndef _HASHTABLETYPE
#define _HASHTABLETYPE
#include <cassert>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

//***********************************************************
// Author: Yazan M Rihan
//
// This class specifies the members to implement the basic
// properties of a Chained Hash Table.
//***********************************************************

template <class T>
bool lstRetrieve(const list<T>& lst, string key, T& object) {

	list<T> tempL(lst);

	while (!tempL.empty()) {
		if (tempL.front().key == key) {
			object = tempL.front();
			return true;
		}

		tempL.pop_front();
	}
	return false;


}

template <class T>
struct elemType {
	string key;
	T data;

	friend ostream& operator<<(ostream& os, const elemType<T>& E) {
		os << "<Key,data>: <" << E.key << ", " << E.data << ">" << endl;
		return os;
	}

	friend bool operator==(const elemType<T>& E1, const elemType<T>& E2) {
		return E1.key == E2.key;
	}


	bool operator!=(const elemType<T>& other)
	{
		return key != other.key;
	}

};


template <class T>
class hashTableType
{
public:
	//Default constructor
	hashTableType(int bucketN = 101);

	//Copy constructor
	hashTableType(const hashTableType<T>& other);

	//Overloading the assignment operator to avoid shallow copies
	hashTableType<T> operator=(const hashTableType<T>& other);

	//Put the hash table object to the intial state
	void intialize();

	//Destructor
	~hashTableType();


	//Takes an objectand a keyand store the object in the hash table using the key
	bool insert(string key, const T& object);

	//Takes a key and delete the object that is associated with the key from the table
	bool remove(string key);

	//Takes a reference to an object and a key and retrieve the object stored using the key if it is found
	bool retrieve(string key, T& object);

	//Prints the contetnts of the  table
	void print() const;

private:
	list<elemType<T>>* HTable;
	int HTableSize;

	//return the hash function h(x)
	int hashFunction(string key);

};

//Put the hash table object to the intial state
template <class T>
void hashTableType<T>::intialize() {
	if (HTable != NULL)
		delete[] HTable;

	HTable = new list<elemType<T>>[HTableSize];
	assert(HTable != NULL);
}
//end of intialize()



//Default constructor
template <class T>
hashTableType<T>::hashTableType(int bucketN) {

	HTableSize = bucketN;
	HTable = NULL;
	intialize();
}
// end of hashTableType(int bucketN)



//Overloading the assignment operator to avoid shallow copies
template <class T>
hashTableType<T> hashTableType<T>::operator=(const hashTableType<T>& other) {

	hashTableType<T> temp;
	if (temp.HTable != NULL)
		delete[] temp.HTable;

	temp.HTableSize = other.HTableSize;
	temp.HTable = new list<elemType<T>>[HTableSize];
	assert(temp.HTable != NULL);



	for (int i = 0; i < HTableSize; i++) {
		list<elemType<T>> tempL(other.HTable[i]);
		while (!tempL.empty())
		{
			temp.HTable[i].push_back(tempL.front());
			tempL.pop_front();
		}
	}

	return temp;
}
//end of operator=(const hashTableType<T>& other)



//Destructor
template <class T>
hashTableType<T>::~hashTableType() {
	delete[] HTable;
	HTable = NULL;

}
//end of ~hashTableType()



//return the hash function h(x)
template <class T>
int hashTableType<T>::hashFunction(string key) {
	int sum = 0;
	
	for (unsigned i = 0; i < key.length(); i++) {
		sum += static_cast<int>(key[i]);
	}

	return sum % HTableSize;
}
//end of hashFunction(string key)



//Copy constructor
template <class T>
hashTableType<T>::hashTableType(const hashTableType<T>& other) {

	delete[] HTable;
	HTableSize = other.HTableSize;
	HTable = new list<elemType<T>>[HTableSize];
	assert(HTable != NULL);


	for (int i = 0; i < HTableSize; i++) {
		list<elemType<T>> tempL(other.HTable[i]);
		while (!tempL.empty())
		{
			HTable[i].push_back(tempL.front());
			tempL.pop_front();
		}
	}
}
//end of hashTableType(const hashTableType<T>& other)



//Takes an object and a key and store the object in the hash table using the key
template <class T>
bool hashTableType<T>::insert(string key, const T& object) {
	elemType<T> newElem;
	newElem.key = key;
	newElem.data = object;

	int hash = hashFunction(key);

	if (lstRetrieve(HTable[hash], key, newElem))
		return false;

	HTable[hash].push_back(newElem);


	return true;

}
//end of insert(string key, const T& object)

//Takes a key and delete the object that is associated with the key from the table
template <class T>
bool hashTableType<T>::remove(string key) {

	elemType<T> tempData;
	tempData.key = key;


	int hash = hashFunction(key);

	if (!lstRetrieve(HTable[hash] ,key, tempData))
		return false;

	HTable[hash].remove(tempData);

	return true;
}
//end of remove(string key)

//Takes a reference to an object and a key and retrieve the object stored using the key if it is found
template <class T>
bool hashTableType<T>::retrieve(string key, T& object) {

	elemType<T>tempData;
	tempData.key = key;
	tempData.data = object;

	int hash = hashFunction(key);

	if (lstRetrieve(HTable[hash], key, tempData)) {
		object = tempData.data;
		return true;
	}


	return false;

}// end of retrieve(string key, T& object)

/*//Prints the contetnts of the  table
template <class T>
void hashTableType<T>::print() const {

	for (int i = 0; i < HTableSize; i++) {

		for (list<elemType<T>>::const_iterator itr = Htable[i].begin(); itr != Htable[i].end(); ++itr)
			cout << *j << '\t';
		cout << endl;
	}
}*/

#endif