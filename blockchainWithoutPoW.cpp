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
    shared_ptr<Block> next;

    Block(int idx, const string& d, const string& prevHash) {
        index = idx;
        data = d;
        previousHash = prevHash;
        timestamp = get_timestamp();
        string toHash = to_string(index) + timestamp + data + previousHash;
        hash = simple_hash(toHash);
        next = nullptr;
    }
};

class Blockchain {
private:
    shared_ptr<Block> head;

public:
    Blockchain() {
        add_block("Genesis Block");
    }

    void add_block(const string& data) {
        if (!head) {
            head = make_shared<Block>(0, data, "0");
        } else {
            shared_ptr<Block> current = head;
            while (current->next) {
                current = current->next;
            }
            int newIndex = current->index + 1;
            string newPrevHash = current->hash;
            current->next = make_shared<Block>(newIndex, data, newPrevHash);
        }
    }

    void print_chain() const {
        shared_ptr<Block> current = head;
        while (current) {
            cout << "Index: " << current->index << endl;
            cout << "Timestamp: " << current->timestamp << endl;
            cout << "Data: " << current->data << endl;
            cout << "Previous Hash: " << current->previousHash << endl;
            cout << "Hash: " << current->hash << endl;
            cout << "--------------------------" << endl;
            current = current->next;
        }
    }

    bool is_chain_valid() const {
        shared_ptr<Block> current = head;
        while (current && current->next) {
            string dataToHash = to_string(current->index) + current->timestamp + current->data + current->previousHash;
            string recalculatedHash = simple_hash(dataToHash);
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
};

int main() {
    Blockchain chain;
    chain.add_block("Transaction 1: Slok -> GPT");
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