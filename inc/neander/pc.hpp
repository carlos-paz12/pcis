#ifndef NEANDER_PC_HPP
#define NEANDER_PC_HPP

namespace neander {

class PC {
public:
    PC();
    ~PC();

    void reset();
    void increment();
    void setAddress(unsigned int address);
    unsigned int getAddress() const;

private:
    unsigned int address;
};

} // namespace neander

#endif // NEANDER_PC_HPP