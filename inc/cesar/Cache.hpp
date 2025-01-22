#ifndef CACHE_CESAR_HPP
#define CACHE_CESAR_HPP

class Cache
{
private:
    unsigned char data[64]; // Cache pequena
    unsigned char tags[64]; // Identificadores de endereço

public:
    unsigned char read(unsigned short address);
    void write(unsigned short address, unsigned char value);
};

#endif