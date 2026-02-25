#pragma once
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "driver/touch_pad.h"

namespace esphome {
namespace touch_sensor {

class TouchReadSensor : public sensor::Sensor, public PollingComponent {
 public:
  explicit TouchReadSensor(uint8_t touch_pad, uint32_t update_interval_s) 
    : touch_pad_((touch_pad_t)touch_pad), update_interval_s_(update_interval_s) {}

  void setup() override {
    touch_pad_init();
    touch_pad_config(touch_pad_, 0);
    touch_pad_filter_start(10);
    vTaskDelay(pdMS_TO_TICKS(50));  // pauza 50 ms pomocí FreeRTOS
    this->update(); 
  }

  void update() override {
    uint16_t val = 0;
    touch_pad_read_raw_data(touch_pad_, &val);
    publish_state((float) val);
  }

  uint32_t get_update_interval() const override { return update_interval_s_ * 1000; }  // v ms

 protected:
  touch_pad_t touch_pad_;
  uint32_t update_interval_s_;
};

}  // namespace touch_sensor
}  // namespace esphome

