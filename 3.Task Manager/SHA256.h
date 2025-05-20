#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <array>
#include <vector>

class SHA256 {
public:
    SHA256();
    void update(const std::string& data);
    std::array<unsigned char, 32> digest();
    std::string toString(const std::array<unsigned char, 32>& hash);

private:
    void transform(const uint8_t* chunk);
    void finalize();

    static constexpr size_t ChunkSize = 64;

    std::array<uint32_t, 8> state;
    std::vector<uint8_t> buffer;
    uint64_t bitCount;
    bool finalized;
};

// Constants defined by the SHA-256 algorithm
constexpr uint32_t k[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,
    0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
    0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,
    0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,
    0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
    0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,
    0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,
    0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
    0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

inline uint32_t rotr(uint32_t x, uint32_t n) {
    return (x >> n) | (x << (32 - n));
}

inline uint32_t ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}

inline uint32_t maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

inline uint32_t sigma0(uint32_t x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

inline uint32_t sigma1(uint32_t x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

inline uint32_t gamma0(uint32_t x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

inline uint32_t gamma1(uint32_t x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

SHA256::SHA256()
    : buffer(), bitCount(0), finalized(false) {
    state = {
        0x6a09e667, 0xbb67ae85,
        0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c,
        0x1f83d9ab, 0x5be0cd19
    };
}

void SHA256::update(const std::string& data) {
    if (finalized) return;
    buffer.insert(buffer.end(), data.begin(), data.end());
    bitCount += data.size() * 8;

    while (buffer.size() >= ChunkSize) {
        transform(buffer.data());
        buffer.erase(buffer.begin(), buffer.begin() + ChunkSize);
    }
}

void SHA256::finalize() {
    if (finalized) return;
    size_t originalSize = buffer.size();

    buffer.push_back(0x80);
    while ((buffer.size() + 8) % ChunkSize != 0)
        buffer.push_back(0x00);

    uint64_t totalBits = bitCount;
    for (int i = 7; i >= 0; --i)
        buffer.push_back((totalBits >> (i * 8)) & 0xFF);

    for (size_t i = 0; i < buffer.size(); i += ChunkSize)
        transform(&buffer[i]);

    finalized = true;
}

void SHA256::transform(const uint8_t* chunk) {
    uint32_t w[64];
    for (int i = 0; i < 16; ++i)
        w[i] = (chunk[i * 4] << 24) |
               (chunk[i * 4 + 1] << 16) |
               (chunk[i * 4 + 2] << 8) |
               (chunk[i * 4 + 3]);

    for (int i = 16; i < 64; ++i)
        w[i] = gamma1(w[i - 2]) + w[i - 7] + gamma0(w[i - 15]) + w[i - 16];

    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];
    uint32_t e = state[4];
    uint32_t f = state[5];
    uint32_t g = state[6];
    uint32_t h = state[7];

    for (int i = 0; i < 64; ++i) {
        uint32_t t1 = h + sigma1(e) + ch(e, f, g) + k[i] + w[i];
        uint32_t t2 = sigma0(a) + maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

std::array<unsigned char, 32> SHA256::digest() {
    finalize();
    std::array<unsigned char, 32> hash;
    for (size_t i = 0; i < 8; ++i) {
        hash[i * 4]     = (state[i] >> 24) & 0xFF;
        hash[i * 4 + 1] = (state[i] >> 16) & 0xFF;
        hash[i * 4 + 2] = (state[i] >> 8) & 0xFF;
        hash[i * 4 + 3] = state[i] & 0xFF;
    }
    return hash;
}

std::string SHA256::toString(const std::array<unsigned char, 32>& hash) {
    std::stringstream ss;
    for (auto byte : hash)
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    return ss.str();
}
