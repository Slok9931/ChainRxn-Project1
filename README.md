# Simple Blockchain Implementation in C++

This project demonstrates a basic implementation of a blockchain using C++. It consists of two versions:

- **blockchainWithoutPoW.cpp** – Blockchain without Proof of Work (PoW)
- **blockchainWithPoW.cpp** – Blockchain with Proof of Work (PoW) to simulate mining

---

## 📁 Files

| File Name              | Description                               |
|------------------------|-------------------------------------------|
| `blockchainWithoutPoW.cpp`  | A simple blockchain without mining difficulty |
| `blockchainWithPoW.cpp` | A blockchain that includes Proof of Work (PoW) to validate blocks |

---

## 🧠 What is Proof of Work?

Proof of Work (PoW) is a consensus mechanism where miners must find a hash with a certain number of leading zeroes. This simulates real-world mining difficulty and ensures integrity through computational effort.

In this project:
- Difficulty is defined as the number of leading `0`s required in a block hash
- Higher difficulty → more computation time

---

## 🔧 How to Compile & Run

Make sure you have a C++ compiler installed (e.g., `g++`).

### 🚀 Without Proof of Work
```bash
g++ blockchainWithoutPoW.cpp -o blockchainWithoutPoW
./blockchainWithoutPoW
```

### 🚀 With Proof of Work
```bash
g++ blockchainWithPoW.cpp -o blockchainWithPoW
./blockchainWithPoW
```

### ⏱️ Performance Note

The version with PoW may take a few seconds per block depending on:
- Hashing function efficiency
- System performance
- Mining difficulty (default = 2)
You can reduce mining time by lowering the difficulty in the code:
```
Blockchain chain(1); // Lower difficulty for faster mining
```

### ✅ Features

- Custom hash function to simulate block hashing
- Timestamp for every block
- Blockchain validation function to detect tampering
- Optional mining (Proof of Work) for added realism
- Output includes all block details: index, data, timestamp, nonce, hash, previous hash

### 🤖 Author
Created by Slok Tulsyan