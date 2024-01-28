#pragma once

#include <buffalo/types.h>

namespace buffalo {

class Port {
protected:
    uint16_t port_number;
    Port(uint16_t port_number);
    virtual ~Port() = 0;
};

class Port8Bit : public Port {
public:
  Port8Bit(uint16_t port_number);
  ~Port8Bit();
  virtual void Write(uint8_t data);
  virtual uint8_t Read();
};
} // namespace buffalo