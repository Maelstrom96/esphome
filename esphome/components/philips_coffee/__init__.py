from esphome.components import uart
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
    CONF_UART_ID,
)

CONF_UART_SCREEN = "uart_screen"
CONF_UART_CONTROLLER = "uart_controller"

CODEOWNERS = ["@Maelstrom96"]
ESP_PLATFORMS = ["esp-idf", "arduino"]
DEPENDENCIES = ["uart"]

philips_coffee_ns = cg.esphome_ns.namespace("philips_coffee")
PhilipsCoffeeComponent = philips_coffee_ns.class_(
    "PhilipsCoffeeComponent", cg.Component
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(PhilipsCoffeeComponent),
        cv.GenerateID(CONF_UART_SCREEN): cv.use_id(uart.UARTComponent),
        cv.GenerateID(CONF_UART_CONTROLLER): cv.use_id(uart.UARTComponent),
    },
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await register_uart_device(var, config, CONF_UART_SCREEN, "set_uart_screen")
    await register_uart_device(var, config, CONF_UART_CONTROLLER, "set_uart_controller")


# Redefining the register_uart_device function since we can't overwrite the config key and function.
async def register_uart_device(
    var, config, config_key=CONF_UART_ID, config_function="set_uart_parent"
):
    parent = await cg.get_variable(config[config_key])
    cg.add(var[config_function](parent))
