#include <bits/stdc++.h>
using namespace std;

string simple_hash(const string& input) {
    unsigned int hash = 0;
    for (char ch : input) {
        hash = (hash * 31 + ch) % 1000000007;
    }
    stringstream ss;
    ss << hex << hash;
    return ss.str();
}

string get_timestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

struct Block {
    int index;
    string timestamp;
    string data;
    string previousHash;
    string hash;
    int nonce;
    shared_ptr<Block> next;

    Block(int idx, const string& val, const string& prevHash, int difficulty) {
        index = idx;
        data = val;
        previousHash = prevHash;
        timestamp = get_timestamp();
        nonce = 0;
        hash = mine_block(difficulty);
        next = NULL;
    }

    string calculate_hash() const {
        string toHash = to_string(index) + timestamp + data + previousHash + to_string(nonce);
        return simple_hash(toHash);
    }

    string mine_block(int difficulty) {
        string prefix(difficulty, '0');
        string newHash;
        while (true) {
            newHash = calculate_hash();
            if (newHash.substr(0, difficulty) == prefix) {
                break;
            }
            nonce++;
        }
        return newHash;
    }
};

class Blockchain {
private:
    shared_ptr<Block> head;
    int difficulty;

public:
    Blockchain(int diff):difficulty(diff) {
        add_block("Genesis Block");
    }

    void add_block(const string& data) {
        if (!head) {
            head = make_shared<Block>(0, data, "0", difficulty);
        } else {
            shared_ptr<Block> current = head;
            while (current->next) {
                current = current->next;
            }
            int newIndex = current->index + 1;
            string newPrevHash = current->hash;
            current->next = make_shared<Block>(newIndex, data, newPrevHash, difficulty);
        }
    }

    bool is_chain_valid() const {
        shared_ptr<Block> current = head;
        while (current && current->next) {
            string recalculatedHash = current -> calculate_hash();
            if (current->hash != recalculatedHash) {
                cout << "Block at index " << current->index << " has been tampered with!\n";
                return false;
            }
            if (current->next->previousHash != current->hash) {
                cout << "Block at index " << current->next->index << " has incorrect previous hash!\n";
                return false;
            }
            current = current->next;
        }
        return true;
    }


    void print_chain() const {
        shared_ptr<Block> current = head;
        while (current) {
            cout << "Index: " << current->index << endl;
            cout << "Timestamp: " << current->timestamp << endl;
            cout << "Data: " << current->data << endl;
            cout << "Nonce: " << current->nonce << endl;
            cout << "Previous Hash: " << current->previousHash << endl;
            cout << "Hash: " << current->hash << endl;
            cout << "--------------------------" << endl;
            current = current->next;
        }
    }
};

int main() {
    Blockchain chain(2);
    chain.add_block("Transaction 1: Slok -> Vasu");
    chain.add_block("Transaction 2: Alice -> Bob");
    chain.add_block("Transaction 3: Coinbase -> Miner");

    chain.print_chain();

    if (chain.is_chain_valid()) {
        cout << "Blockchain is valid.\n";
    } else {
        cout << "Blockchain has been tampered with!\n";
    }

    return 0;
}
