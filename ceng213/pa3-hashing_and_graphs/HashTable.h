#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"
#include "ItemNotFoundException.h"

/* Do not add new libraries or files */

#define BUCKET_SIZE 2

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class K, class T>
class HashTable {
    struct Entry {
        K Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[BUCKET_SIZE];
    };

    int _capacity; // INDICATES THE TOTAL CAPACITY OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // THE HASH TABLE

    // == DEFINE HELPER METHODS & VARIABLES BELOW ==


public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    // COPY THE WHOLE CONTENT OF RHS INCLUDING THE KEYS THAT WERE SET AS DELETED
    HashTable(const HashTable<K, T>& rhs);
    HashTable<K, T>& operator=(const HashTable<K, T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. IF THE LOAD FACTOR OF THE TABLE IS GREATER THAN 0.6,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(const K& key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, THROW ItemNotFoundException()
    void Delete(const K& key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THROW ItemNotFoundException()
    T& Get(const K& key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES
    void Resize(int newCapacity);

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const; // RETURN THE TOTAL CAPACITY OF THE TABLE
    int Size() const; // RETURN THE NUMBER OF ACTIVE ITEMS
    void getKeys(K* keys); // PUT THE ACTIVE KEYS TO THE GIVEN INPUT PARAMETER
};


template <class K, class T>
HashTable<K, T>::HashTable() {
    _capacity = 7;
    _table = new Bucket[_capacity];
    _size = 0;

}

template <class K, class T>
HashTable<K, T>::HashTable(const HashTable<K, T>& rhs) {
    _capacity = rhs.Capacity();
    _size = rhs.Size();
    _table = new Bucket[_capacity];
    for(int i = 0; i < _capacity; i++){
        if(rhs._table[i].entries[0].Active){
            _table[i].entries[0].Key = rhs._table[i].entries[0].Key;
            _table[i].entries[0].Value = rhs._table[i].entries[0].Value;
            _table[i].entries[0].Deleted = rhs._table[i].entries[0].Deleted;
            _table[i].entries[0].Active = rhs._table[i].entries[0].Active;
        }
        if(rhs._table[i].entries[1].Active){
            _table[i].entries[1].Key = rhs._table[i].entries[1].Key;
            _table[i].entries[1].Value = rhs._table[i].entries[1].Value;
            _table[i].entries[1].Deleted = rhs._table[i].entries[1].Deleted;
            _table[i].entries[1].Active = rhs._table[i].entries[1].Active;
        }
    }

}

template <class K, class T>
HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& rhs) {
    delete [] _table;
    _capacity = rhs.Capacity();
    _size = rhs.Size();
    _table = new Bucket[_capacity];
    for(int i = 0; i < _capacity; i++){
        if(rhs._table[i].entries[0].Active){
            _table[i].entries[0].Key = rhs._table[i].entries[0].Key;
            _table[i].entries[0].Value = rhs._table[i].entries[0].Value;
            _table[i].entries[0].Deleted = rhs._table[i].entries[0].Deleted;
            _table[i].entries[0].Active = rhs._table[i].entries[0].Active;
        }
        if(rhs._table[i].entries[1].Active){
            _table[i].entries[1].Key = rhs._table[i].entries[1].Key;
            _table[i].entries[1].Value = rhs._table[i].entries[1].Value;
            _table[i].entries[1].Deleted = rhs._table[i].entries[1].Deleted;
            _table[i].entries[1].Active = rhs._table[i].entries[1].Active;
        }
    }
    return *this;
}

template <class K, class T>
HashTable<K, T>::~HashTable() {
    delete [] _table;
}

template <class K, class T>
void HashTable<K, T>::Insert(const K& key, const T& value) {
    double loadfactor = (double)_size / (double)(BUCKET_SIZE * _capacity);

    if(loadfactor > 0.6){
        Resize(NextCapacity(_capacity));
    }

    int hashcode = Hash(key);
    hashcode %= _capacity;

    if(!_table[hashcode].entries[0].Active){
        _table[hashcode].entries[0].Key = key;
        _table[hashcode].entries[0].Value = value;
        _table[hashcode].entries[0].Active = true;
        _table[hashcode].entries[0].Deleted = false;
        _size++;
    }
    else if(!_table[hashcode].entries[1].Active){
      if(_table[hashcode].entries[0].Key == key){
        _table[hashcode].entries[0].Value = value;
        return;
      }
        _table[hashcode].entries[1].Key = key;
        _table[hashcode].entries[1].Value = value;
        _table[hashcode].entries[1].Active = true;
        _table[hashcode].entries[1].Deleted = false;
        _size++;
    }
    else{
        int k = 1;
        int hashp = hashcode;
        while(_table[hashp].entries[0].Active && _table[hashp].entries[1].Active){
            if(_table[hashp].entries[0].Key == key){
                _table[hashp].entries[0].Value = value;
                return;
            }
            if(_table[hashp].entries[1].Key == key){
                _table[hashp].entries[1].Value = value;
                return;
            }
            hashp = hashcode + (k*k);
            hashp %= _capacity;
            k++;
        }
        if(!_table[hashp].entries[0].Active){
            _table[hashp].entries[0].Key = key;
            _table[hashp].entries[0].Value = value;
            _table[hashp].entries[0].Active = true;
            _table[hashp].entries[0].Deleted = false;
            _size++;
        }
        else{
            _table[hashp].entries[1].Key = key;
            _table[hashp].entries[1].Value = value;
            _table[hashp].entries[1].Active = true;
            _table[hashp].entries[1].Deleted = false;
            _size++;
        }
    }

}

template <class K, class T>
void HashTable<K, T>::Delete(const K& key) {
    int hashcode = Hash(key);
    hashcode %= _capacity;

    if(!_table[hashcode].entries[0].Active){
        throw ItemNotFoundException();
    }
    else if(_table[hashcode].entries[0].Key == key){
        _table[hashcode].entries[0].Deleted = true;
        _table[hashcode].entries[0].Active = false;
        _size--;
        return;
    }
    else if(!_table[hashcode].entries[1].Active){
        throw ItemNotFoundException();
    }
    else if(_table[hashcode].entries[1].Key == key){
        _table[hashcode].entries[1].Deleted = true;
        _table[hashcode].entries[1].Active = false;
        _size--;
        return;
    }
    else{
        int k = 1;
        int hashp = hashcode;
        while(_table[hashp].entries[0].Active && _table[hashp].entries[1].Active){
            if(_table[hashp].entries[0].Key == key){
                _table[hashp].entries[0].Deleted = true;
                _table[hashp].entries[0].Active = false;
                _size--;
                return;
            }
            if(_table[hashp].entries[1].Key == key){
                _table[hashp].entries[1].Deleted = true;
                _table[hashp].entries[1].Active = false;
                _size--;
                return;
            }
            hashp = hashcode + (k*k);
            hashp %= _capacity;
            k++;
        }
        if(_table[hashp].entries[0].Active){
            if(_table[hashp].entries[0].Key == key){
                _table[hashp].entries[0].Deleted = true;
                _table[hashp].entries[0].Active = false;
                _size--;
                return;
            }
        }
    }

    throw ItemNotFoundException();
}

template <class K, class T>
T& HashTable<K, T>::Get(const K& key) const {
    int hashcode = Hash(key);
    hashcode %= _capacity;
    if(!_table[hashcode].entries[0].Active){
        throw ItemNotFoundException();
    }
    else if(_table[hashcode].entries[0].Key == key){
        return _table[hashcode].entries[0].Value;
    }
    else if(!_table[hashcode].entries[1].Active){
        throw ItemNotFoundException();
    }
    else if(_table[hashcode].entries[1].Key == key){
        return _table[hashcode].entries[1].Value;
    }
    else{
        int k = 1;
        int hashp = hashcode;
        while(_table[hashp].entries[0].Active && _table[hashp].entries[1].Active){
            if(_table[hashp].entries[0].Key == key){
                return _table[hashp].entries[0].Value;
            }
            if(_table[hashp].entries[1].Key == key){
                return _table[hashp].entries[1].Value;
            }
            hashp = hashcode + (k*k);
            hashp %= _capacity;
            k++;
        }
        if(_table[hashp].entries[0].Active){
            if(_table[hashp].entries[0].Key == key){
                return _table[hashp].entries[0].Value;
            }
        }
    }

    throw ItemNotFoundException();
}


template <class K, class T>
void HashTable<K, T>::Resize(int newCapacity) {
    Bucket* resized = new Bucket[newCapacity];
    Bucket* oldtable = _table;
    int oldcap = _capacity;
    int oldsize = _size;
    _table = resized;
    _capacity = newCapacity;
    _size = 0;

    for(int i = 0; i < oldcap; i++){
        for(int j = 0; j < BUCKET_SIZE; j++){
            if(oldtable[i].entries[j].Active){
                Insert(oldtable[i].entries[j].Key, oldtable[i].entries[j].Value);
                oldsize--;
            }
            if(oldsize == 0) break;
        }
    }

    delete [] oldtable;

}


template <class K, class T>
int HashTable<K, T>::Capacity() const {
    return _capacity;
}

template <class K, class T>
int HashTable<K, T>::Size() const {
    return _size;
}


template <class K, class T>
void HashTable<K, T>::getKeys(K* keys) {
    int index = 0;

    for (int i = 0; i < _capacity; i++) {
        Bucket& bucket = _table[i];
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted) {
                keys[index++] = bucket.entries[j].Key;
            }
        }
    }
}

#endif
