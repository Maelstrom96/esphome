#include "philips_coffee.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace philips_coffee {

static const char *const TAG = "philips_coffee";

void PhilipsCoffeeComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Philips Coffee");
}

void PhilipsCoffeeComponent::setup() {
  ESP_LOGV(TAG, "SETUP");
  return;
}

void PhilipsCoffeeComponent::loop() {
  this->bridge_uart(this->uart_screen_, this->uart_controller_);
  this->bridge_uart(this->uart_controller_, this->uart_screen_);
}

void PhilipsCoffeeComponent::bridge_uart(uart::UARTComponent *origin, uart::UARTComponent *destination) {
  std::vector<uint8_t> read_uart_data;

  int available_data = origin->available();
  // Check if message is available
  if(available_data) {
    read_uart_data.resize(available_data);
    origin->read_array(read_uart_data.data(), available_data);
    destination->write_array(read_uart_data.data(), available_data);
  }
}

}  // namespace philips_coffee
}  // namespace esphome