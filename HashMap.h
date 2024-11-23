#pragma once

template<typename K, typename V>
class HashNode {
public:
    V value; // kac kere kullanildigi
    K key; // string

    //constructor

    HashNode(K key, V value) {
        this->value = value;
        this->key = key;
    }
};


template<typename K, typename V>

class HashMap {
private:

    HashNode<K, V>** HMap;

    int capacity; // Max size
    int size;

    void insert(int hashIndex, HashNode<K, V>* node) {
        //find next free space
        while (HMap[hashIndex] != NULL && HMap[hashIndex]->key != node->key)
        {
            hashIndex++;
            hashIndex %= capacity;
        }

 
        size++;
        HMap[hashIndex] = node;
    }


    int calculateHashValue(K key) {

        unsigned int hashedWord = std::hash<K>{}(key);
        int address = hashedWord % capacity;

        return address;
    }

public:
    HashMap(int capacity) {
        this->capacity = capacity;
        size = 0;

        HMap = new HashNode<K, V>*[capacity];

        for (int i = 0; i < capacity; i++) {
            HMap[i] = NULL;
        }
    }

    // Put
    void put(K key, V value) {
        // hashing
        HashNode<K, V>* newNode = new HashNode<K, V>(key, value);

        int hashIndex = calculateHashValue(key);

        insert(hashIndex, newNode);
    }

    V get(K key) {
        int hashIndex = calculateHashValue(key);

        while (HMap[hashIndex] != NULL) {
            if (HMap[hashIndex]->key == key) {
                return HMap[hashIndex]->value;
            }
            else {
                hashIndex = (hashIndex + 1) % capacity;
            }
        }
        return NULL;
    }


    void display() {
        for (int i = 0; i < capacity; i++) {
            if (HMap[i] != NULL)
                std::cout << i << "key = " << HMap[i]->key
                << "  value = " << HMap[i]->value << std::endl;
        }
    }


    void calculateTopTen() {
        HashNode<K, V>** topTen = new HashNode<K, V>*[10];

        for (int i = 0; i < 10; i++) {
            topTen[i] = NULL;
        }

        for (int i = 0; i < capacity; i++) {
            if (HMap[i] != NULL) {
                int minIndex = 0;
                int minValue = 0;

                for (int j = 0; j < 10; ++j) {
                    if (topTen[j] != NULL) {
                        if (minValue == 0 || topTen[j]->value < minValue) {
                            minIndex = j;
                            minValue = topTen[j]->value;
                        }
                    }
                    else {
                        minValue = 0;
                        minIndex = j;
                        break;
                    }
                }
                if (minValue < HMap[i]->value) {
                    topTen[minIndex] = HMap[i];
                }
            }
        }
        for (int j = 0; j < 10; j++) {
            int maxIndex = 0;
            int maxValue = 0;
            for (int i = 0; i < 10; i++) {
                if (topTen[i] != NULL && topTen[i]->value > maxValue) {
                    maxIndex = i;
                    maxValue = topTen[i]->value;
                }
            }
            std::cout << topTen[maxIndex]->key << " " << topTen[maxIndex]->value << std::endl;
            topTen[maxIndex] = NULL;
        }
    }

    bool isExist(K key) {
        int hashIndex = calculateHashValue(key);

        while (HMap[hashIndex] != NULL) {
            if (HMap[hashIndex]->key == key) {
                return true;
            }
            else {
                hashIndex = (hashIndex + 1) % capacity;
            }
        }
        return false;
    }

};


