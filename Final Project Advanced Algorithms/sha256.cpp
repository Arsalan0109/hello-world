#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdint>

using namespace std;

uint32_t rotate_right(uint32_t number, int bits) {
    return (number >> bits) | (number << (32 - bits));
}

string sha256(const string& message) {
    uint32_t constants[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    
    uint32_t hash0 = 0x6a09e667;
    uint32_t hash1 = 0xbb67ae85;
    uint32_t hash2 = 0x3c6ef372;
    uint32_t hash3 = 0xa54ff53a;
    uint32_t hash4 = 0x510e527f;
    uint32_t hash5 = 0x9b05688c;
    uint32_t hash6 = 0x1f83d9ab;
    uint32_t hash7 = 0x5be0cd19;
    
    vector<uint8_t> data(message.begin(), message.end());
    uint64_t message_length = data.size() * 8;
    
    data.push_back(0x80);
    
    while ((data.size() * 8) % 512 != 448) {
        data.push_back(0x00);
    }
    
    for (int i = 7; i >= 0; i--) {
        data.push_back((message_length >> (i * 8)) & 0xff);
    }
    
    for (size_t i = 0; i < data.size(); i += 64) {
        uint32_t words[64];
        
        for (int j = 0; j < 16; j++) {
            words[j] = (data[i + j * 4] << 24) | 
                      (data[i + j * 4 + 1] << 16) | 
                      (data[i + j * 4 + 2] << 8) | 
                      (data[i + j * 4 + 3]);
        }
        
        for (int j = 16; j < 64; j++) {
            uint32_t sigma0 = rotate_right(words[j - 15], 7) ^ rotate_right(words[j - 15], 18) ^ (words[j - 15] >> 3);
            uint32_t sigma1 = rotate_right(words[j - 2], 17) ^ rotate_right(words[j - 2], 19) ^ (words[j - 2] >> 10);
            words[j] = words[j - 16] + sigma0 + words[j - 7] + sigma1;
        }
        
        uint32_t a = hash0;
        uint32_t b = hash1;
        uint32_t c = hash2;
        uint32_t d = hash3;
        uint32_t e = hash4;
        uint32_t f = hash5;
        uint32_t g = hash6;
        uint32_t h = hash7;
        
        for (int j = 0; j < 64; j++) {
            uint32_t sum1 = rotate_right(e, 6) ^ rotate_right(e, 11) ^ rotate_right(e, 25);
            uint32_t choice = (e & f) ^ (~e & g);
            uint32_t temp1 = h + sum1 + choice + constants[j] + words[j];
            uint32_t sum0 = rotate_right(a, 2) ^ rotate_right(a, 13) ^ rotate_right(a, 22);
            uint32_t majority = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = sum0 + majority;
            
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }
        
        hash0 += a;
        hash1 += b;
        hash2 += c;
        hash3 += d;
        hash4 += e;
        hash5 += f;
        hash6 += g;
        hash7 += h;
    }
    
    ostringstream result;
    result << hex << setfill('0');
    result << setw(8) << hash0;
    result << setw(8) << hash1;
    result << setw(8) << hash2;
    result << setw(8) << hash3;
    result << setw(8) << hash4;
    result << setw(8) << hash5;
    result << setw(8) << hash6;
    result << setw(8) << hash7;
    
    return result.str();
}

int main() {
    ifstream file("mark.txt");
    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();
    file.close();
    
    string result = sha256(text);
    cout << "SHA-256 hash of the Book of Mark:" << endl;
    cout << result << endl;
    
    ofstream output("hash_output.txt");
    output << "SHA-256 hash of the Book of Mark:" << endl;
    output << result << endl;
    output.close();
    
    cout << sha256("hello") << endl;
    
    return 0;
}
