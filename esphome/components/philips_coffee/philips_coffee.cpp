#include "philips_coffee.h"
#include "esphome/components/uart/uart_debugger.h"
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
  //this->bridge_uart(this->uart_controller_, this->uart_screen_);
}

void PhilipsCoffeeComponent::bridge_uart(uart::UARTComponent *origin, uart::UARTComponent *destination) {
  // uint8_t data_buffer[256];

  // int available_data = origin->available();

  // if(available_data) {
  //   origin->read_array(data_buffer, available_data);
  //   uart::UARTDebug::log_hex(uart::UARTDirection::UART_DIRECTION_RX, data_buffer, ':');
  //   destination->write_array(data_buffer, available_data);
  // }

  std::vector<uint8_t> read_uart_data;
  std::vector<uint8_t> write_uart_data;

  int available_data = origin->available();
  // Check if message is available
  if(available_data) {
    read_uart_data.resize(available_data);
    origin->read_array(read_uart_data.data(), available_data);
    uart::UARTDebug::log_hex(uart::UARTDirection::UART_DIRECTION_RX, read_uart_data, ':');
    //write_uart_data = read_uart_data;
    //destination->write_array(write_uart_data.data(), available_data);
  }
}

}  // namespace philips_coffee
}  // namespace esphome