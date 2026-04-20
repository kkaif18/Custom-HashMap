//We will be making an open-addressing map that uses a flat array of some size N, Every slot in that array is one of three states:

// Empty — nothing ever touched this slot
// Occupied — a key lives here
// Tombstone — something was here, got deleted, left a marker behind

//If we find an empty slot after hashing to get an index, that's the perfect case scenario , or else we hit a collision

//A collision is solved using linear probing(searching for an empty slot linearly(in circlular array))

//tombstones must exist — if you erased a slot completely (made it truly empty), a search would stop there and falsely conclude the key doesn't exist, even if that key was pushed past this slot during insertion.

//while deleting a slot, we don't make it empty rather mark it as tombstone

// As you fill the table, probe chains get longer because there are fewer gaps for probing to land on. This is called primary clustering
#include <iostream>
#include <vector>
#include <optional>
#include <stdexcept>

using namespace std;

template <typename K, typename V>
class FlatHashMap{
    //Instead of list, we would assign slots in the vector
    struct Slot{
        K key;
        V val;
        bool occupied = false; //Marks for Occupancy
        bool tombstone = false; // tombstone marks "keep probing past me, but you can reuse this slot for a future insert."
    };

    vector<Slot> table; //Main vector
    int count = 0;//Size of the MAP
    float max_load = 0.6f; //threshold factor (λ)
    /*The Threshold Factor is less than the chaining Map because here for 1.0 λ , it faces clustering (adjacent occupied slots start forming long runs and probe counts shoot up), hence we keep it lower at 0.6 for safe ceiling*/

    int home(const K& key) const{
        return hash<K>{}(key)% table.size();
        //Finding the home index
    }
    void rehash() {
        //resetting the array
        auto old = std::move(table);
        table.assign(old.size() * 2, Slot{});
        count = 0;
        for (auto& s : old)
            if (s.occupied) insert(s.key, s.val);
            //marking up the new array with older data
    }
public:
    explicit FlatHashMap(size_t cap = 16) : table(cap) {}

    void insert(const K& key,const V& val){
        if((float)(count+1) / table.size() > max_load)
            rehash();

        int i = home(key);

        int first_tomb = -1;

        for(int step = 0; step < table.size();step++, i = (i + 1) % table.size()){
            if(table[i].tombstone){
                if(first_tomb == -1) first_tomb = (int)i; // Marking the first tombstone
                continue;
            }
            if(!table[i].occupied){
                // empty slot - insert here, or reusing the earlier tombstone
                int at = (first_tomb != -1) ? (int)first_tomb : i;
                table[at] = {key, val, true, false};
                count++;
                return;
            }

            if(table[i].key == key){
                table[i].val = val; // update in place
                return;
            }
        }
    }

    V *find(const K& key){
        int i = home(key);
        for(int step = 0; step < table.size();step++, i = (i + 1) % table.size()){
            if(!table[i].occupied && !table[i].tombstone) return nullptr; //not present

            if(table[i].occupied && table[i].key == key){
                return &table[i].val;
            }
        }
        return nullptr;
    }

    bool erase(const K& key){
        int i = home(key);
        for(int step = 0; step < table.size();step++, i = (i + 1)%table.size()){
            if(!table[i].occupied && !table[i].tombstone) return false;
            if(table[i].occupied && table[i].key == key){
                table[i].occupied = false;
                table[i].tombstone = true;
                count--;
                return true;
            }
        }

        return false;
    }
};

int main() {
    FlatHashMap<string, int> map;

    map.insert("alice", 25);
    map.insert("bob",   30);
    map.insert("carol", 27);

    // search
    int* v = map.find("alice");
    if (v) cout << "alice -> " << *v << "\n";
    else   cout << "alice not found\n";

    // update
    map.insert("alice", 99);
    v = map.find("alice");
    if (v) cout << "alice (updated) -> " << *v << "\n";

    // delete
    map.erase("bob");
    v = map.find("bob");
    cout << "bob after erase: " << (v ? "found" : "not found") << "\n";

    // miss
    v = map.find("dave");
    cout << "dave: " << (v ? "found" : "not found") << "\n";

    return 0;
}

