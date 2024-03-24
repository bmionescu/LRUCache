#include <iostream>
#include <unordered_map>

struct cacheNode {
  cacheNode* prevNode;
  cacheNode* nextNode;
  int key;
  int value;
}; // for LRUCache's doubly-linked list (dll)

class LRUCache {
private:
  int capacity;
  int currentNumberOfNodes = 0;
  cacheNode* tailNode = nullptr; // most recently used
  cacheNode* headNode = nullptr; // least recently used
  cacheNode* tempNode; // for swapping
  std::unordered_map <int, cacheNode*> hashmap;
  void updateDLL(int key) {
    // This key's node is now the MRU. Update the dll
    if (currentNumberOfNodes == 1 || key == tailNode->key) {
      return;
    } else if (currentNumberOfNodes == 2) {
      tailNode->prevNode = nullptr;
      tailNode->nextNode = headNode;
      headNode->nextNode = nullptr;
      headNode->prevNode = tailNode;
      tempNode = tailNode;
      tailNode = headNode;
      headNode = tempNode;
    } else {
      if (hashmap[key]->nextNode != nullptr) {
        hashmap[key]->nextNode->prevNode = hashmap[key]->prevNode;
      }
      if (hashmap[key]->prevNode != nullptr) {
        hashmap[key]->prevNode->nextNode = hashmap[key]->nextNode;
      }
      // If updated node is the headNode, we need to reassign headNode
      if (key == headNode->key) {
        headNode = headNode->nextNode;
      }
      hashmap[key]->nextNode = nullptr;
      hashmap[key]->prevNode = tailNode;
      tailNode->nextNode = hashmap[key];
      tailNode = hashmap[key];
    }
  }
public:
  LRUCache(int capacity) : capacity(capacity) {
  }  
  int get(int key) {
    if (hashmap.find(key) != hashmap.end()) { // Key exists in map
      updateDLL(key);
      return hashmap[key]->value;
    } else {
      return -1;
    }
  }    
  void put(int key, int value) {
    if (hashmap.find(key) != hashmap.end()) { // Key exists in map
      hashmap[key]->value = value; // Update node's value
      updateDLL(key);
    } else { // Key isn't in map
      if (currentNumberOfNodes == 0) {
          headNode = new cacheNode{
          nullptr, // prevNode
          nullptr, // nextNode
          key,     // key
          value,   // value
        };
        currentNumberOfNodes++;
        hashmap.insert({key, headNode});
      } else if (currentNumberOfNodes == 1 && capacity > 1) {
        tailNode = new cacheNode{
          headNode, // prevNode
          nullptr,  // nextNode
          key,      // key
          value,    // value
        };
        headNode->nextNode = tailNode;
        currentNumberOfNodes++;
        hashmap.insert({key, tailNode});
      } else { // Cases other than adding first or second node to cache
        if (capacity == 1) { // Edge case, don't add a node
          hashmap.erase(headNode->key);
          hashmap.insert({key, headNode});
          headNode->key = key;
          headNode->value = value;
        } else { // Add a node that isn't first or second in the cache
          cacheNode* newNode = new cacheNode{
            tailNode, // prevNode, will be the old tail
            nullptr,  // nextNode
            key,      // key
            value,    // value
          };
          tailNode->nextNode = newNode;
          tailNode = newNode;
          if (currentNumberOfNodes < capacity) {
            currentNumberOfNodes++;
          } else {
            tempNode = headNode->nextNode; // new headNode
            tempNode->prevNode = nullptr;
            hashmap.erase(headNode->key); // Remove the headNode from the hashmap
            delete headNode;
            headNode = tempNode;
          }
          hashmap.insert({key, newNode});
        }
      }
    }    
  }
};
