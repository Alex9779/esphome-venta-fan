#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/fan/fan.h"
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace venta_fan {

class VentaFan : public fan::Fan, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  void set_switch_fanspeed_pin(GPIOPin *switch_fanspeed_pin) {
    this->switch_fanspeed_pin_ = switch_fanspeed_pin;
  }
  void set_switch_power_pin(GPIOPin *switch_power_pin) {
    this->switch_power_pin_ = switch_power_pin;
  }
  void set_led_power_pin(GPIOPin *led_power_pin) {
    this->led_power_pin_ = led_power_pin;
  }
  void set_led_low_pin(GPIOPin *led_low_pin) {
    this->led_low_pin_ = led_low_pin;
  }
  void set_led_mid_pin(GPIOPin *led_mid_pin) {
    this->led_mid_pin_ = led_mid_pin;
  }
  void set_led_high_pin(GPIOPin *led_high_pin) {
    this->led_high_pin_ = led_high_pin;
  }
  void set_error_status_sensor(binary_sensor::BinarySensor *sensor) {
    this->error_status_sensor_ = sensor;
  }
  fan::FanTraits get_traits() override;

 protected:
  void control(const fan::FanCall &call) override;
  void click_switch_(GPIOPin *output);
  void write_state_();
  bool is_internal_error_();
  void read_current_state_();
  void on_state_change_();
  
  static void IRAM_ATTR gpio_intr(VentaFan *arg);

  GPIOPin *switch_fanspeed_pin_;
  GPIOPin *switch_power_pin_;
  GPIOPin *led_power_pin_;
  GPIOPin *led_low_pin_;
  GPIOPin *led_mid_pin_;
  GPIOPin *led_high_pin_;
  binary_sensor::BinarySensor *error_status_sensor_;
  volatile bool state_changed_ = false;
  bool error_{false};
};

class VentaFanBinaryComponent : public Component {
 public:
  VentaFanBinaryComponent(VentaFan *parent) {}
};

}  // namespace venta_fan
}  // namespace esphome
