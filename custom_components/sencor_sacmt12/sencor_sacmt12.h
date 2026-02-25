#pragma once

#include "esphome.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/remote_base/toshiba_ac_protocol.h"
#include "esphome/components/remote_transmitter/remote_transmitter.h"

namespace esphome {
namespace sencor_sacmt12 {

class SencorSACMT12 : public climate::Climate, public Component {
 public:
  void setup() override {
    // Výchozí stav – díky tomu se v HA zobrazí slider teploty hned po startu
    this->target_temperature = 24.0f;
    this->mode = climate::CLIMATE_MODE_COOL;
    this->fan_mode = climate::CLIMATE_FAN_AUTO;
    this->publish_state();
  }

  climate::ClimateTraits traits() override {
    auto t = climate::ClimateTraits();
    // Jednobodový cíl (ne heat/cool range)
    t.set_supports_two_point_target_temperature(false);

    // Vizuální rozsah & krok
    t.set_visual_min_temperature(17);
    t.set_visual_max_temperature(28);
    t.set_visual_temperature_step(1.0f);

    // Zobrazit aktuální teplotu (může být NaN, nevadí)
    t.set_supports_current_temperature(true);

    // Režimy a ventilátor
    t.set_supported_modes({
      climate::CLIMATE_MODE_OFF,
      climate::CLIMATE_MODE_COOL,
      climate::CLIMATE_MODE_DRY,
      climate::CLIMATE_MODE_FAN_ONLY,
      climate::CLIMATE_MODE_AUTO
    });
    t.set_supported_fan_modes({
      climate::CLIMATE_FAN_LOW,
      climate::CLIMATE_FAN_MEDIUM,
      climate::CLIMATE_FAN_HIGH,
      climate::CLIMATE_FAN_AUTO
    });
    return t;
  }

  void set_transmitter(remote_transmitter::RemoteTransmitterComponent *transmitter) {
    this->transmitter_ = transmitter;
  }

  void control(const climate::ClimateCall &call) override;

 protected:
  remote_transmitter::RemoteTransmitterComponent *transmitter_{nullptr};
};

}  // namespace sencor_sacmt12
}  // namespace esphome

