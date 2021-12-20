#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/uart/uart_debugger.h"

#include <vector>

namespace esphome {
namespace philips_coffee {

class PhilipsCoffeeComponent : public Component{
 public:
  void dump_config() override;
  void set_uart_screen(uart::UARTComponent *uart) { this->uart_screen_ = uart; }
  void set_uart_controller(uart::UARTComponent *uart) { this->uart_controller_ = uart; }

  void setup() override;
  void loop() override;

 protected:
  void bridge_uart(uart::UARTComponent *origin, uart::UARTComponent *destination);

  uart::UARTComponent *uart_screen_{nullptr};
  uart::UARTComponent *uart_controller_{nullptr};
};

}  // namespace philips_coffee
}  // namespace esphome
