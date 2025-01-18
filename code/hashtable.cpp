#include <iostream>
#include <vector>
#include <string>
using namespace std;

// colorscheme slate

const string DELETED = "DELETED";

class HashTable{

	private:
		vector<string> table; // hashtable to store keys
		int size;
		int currentSize;     // current no of elements in HT


		int hashFunction(const string& key){
                   int hash = 0;
		   for(char ch: key){
                      hash = (hash *31+ ch)%size;
		   }

		   return hash;
		}

	public: 
		// accessible to the user 

		HashTable(int capacity): size(capacity), currentSize(0){
  			table.resize(size,"");       // initialized the table with empty strings
		}

		
		// Insert a new key into hashtable 
		
		bool insert(const string& key){
 			if(currentSize == size){
 				cout << "hashtable is full\n";
				return false;
			}

			int index = hashFunction(key);
			while (table[index] != "" && table[index] != DELETED) {
				if(table[index] == key){
					cout << "key already exists\n";
					return false;
			        }

				// if the slot is already taken by another key 
				// Linear Probing 
				index = (index + 1) % size; 


			}

			// if slot is either empty or DELETED tag then insert here
			table[index] = key;
			currentSize++;
			return true;

		}

		
		// Search in the hashtable 
                bool search(const string& key){
                	int index = hashFunction(key);
			int startIndex = index;   // To prevent infinite loops 
			
			while(table[index] != ""){
				if(table[index] == key){
					return true;
				}

				// linear probe while searching
				index = (index + 1)%size;
				if(index == startIndex){
					break;
				}
			}

			return false;      // when the slot is empty it ensures 
					  // the key doesn't exist.
		}


		// Delete a key from hashtable 

		bool remove(const string& key){
 			int index = hashFunction(key);
			int startIndex = index;

			while(table[index] != ""){
                        	if(table[index] == key){
					// then DELETE
					table[index] = DELETED;
					currentSize--;
					return true;
				}
				// else probe until the startIndex

				index = (index+1)%size;
				if(index == startIndex) break;

			}
 			cout << "Key not found\n";	
			return false;
		}
		
         	void display() {
			for (int i = 0; i < size; i++) {
            			if (table[i] == "" || table[i] == DELETED) {
                			cout << i << ": [ ]\n";
            			} else {
                			cout << i << ": " << table[i] << "\n";
            			}
        		}
    		}
};		






int main() {
    HashTable hashTable(7); // Create a hash table with size 7

    // Insert keys
    hashTable.insert("apple");
    hashTable.insert("banana");
    hashTable.insert("cherry");
    hashTable.insert("date");
    hashTable.insert("elderberry");

    cout << "Initial table:\n";
    hashTable.display();

    // Search for keys
    cout << "\nSearching for 'banana': " << (hashTable.search("banana") ? "Found" : "Not Found") << "\n";
    cout << "Searching for 'fig': " << (hashTable.search("fig") ? "Found" : "Not Found") << "\n";

    // Delete a key
    cout << "\nDeleting 'cherry'\n";
    hashTable.remove("cherry");

    cout << "\nTable after deletion:\n";
    hashTable.display();

    return 0;
}










