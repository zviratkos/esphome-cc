#include "sencor_sacmt12.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sencor_sacmt12 {

static const char *const TAG = "sencor_sacmt12";

void SencorSACMT12::control(const climate::ClimateCall &call) {
  uint64_t code = 0;

  // Mode
  if (call.get_mode().has_value()) {
    auto mode = call.get_mode().value();
    if (mode == climate::CLIMATE_MODE_OFF)
      code = 0xB24D7B84E01F;
    else if (mode == climate::CLIMATE_MODE_COOL)
      code = 0xB24DBF40708F;
    else if (mode == climate::CLIMATE_MODE_DRY)
      code = 0xB24D1FE0748B;
    else if (mode == climate::CLIMATE_MODE_FAN_ONLY)
      code = 0xB24DBF40E41B;
    else if (mode == climate::CLIMATE_MODE_AUTO)
      code = 0xB24D1FE07887;
    this->mode = mode;
  }

  // Fan
  if (call.get_fan_mode().has_value()) {
    auto fan = call.get_fan_mode().value();
    if (fan == climate::CLIMATE_FAN_LOW)
      code = 0xB24D9F60708F;
    else if (fan == climate::CLIMATE_FAN_MEDIUM)
      code = 0xB24D5FA0708F;
    else if (fan == climate::CLIMATE_FAN_HIGH)
      code = 0xB24D3FC0708F;
    else if (fan == climate::CLIMATE_FAN_AUTO)
      code = 0xB24DBF40708F;
    this->fan_mode = fan;
  }

  // Temperature
  if (call.get_target_temperature().has_value()) {
    int temp = static_cast<int>(call.get_target_temperature().value());
    // omezit na 17–28
    if (temp < 17) temp = 17;
    if (temp > 28) temp = 28;

    switch (temp) {
      case 17: code = 0xB24D3FC000FF; break;
      case 18: code = 0xB24D3FC010EF; break;
      case 19: code = 0xB24D3FC030CF; break;
      case 20: code = 0xB24D3FC020DF; break;
      case 21: code = 0xB24D3FC0609F; break;
      case 22: code = 0xB24D3FC0708F; break;
      case 23: code = 0xB24D3FC050AF; break;
      case 24: code = 0xB24D3FC040BF; break;
      case 25: code = 0xB24D3FC0C03F; break;
      case 26: code = 0xB24D3FC0D02F; break;
      case 27: code = 0xB24D3FC0906F; break;
      case 28: code = 0xB24D3FC0807F; break;
    }
    this->target_temperature = static_cast<float>(temp);
  }

  // Publikování stavu (UI se aktualizuje)
  this->publish_state();

  // Odeslání IR signálu
  if (code != 0 && this->transmitter_ != nullptr) {
    remote_base::ToshibaAcData data;
    data.rc_code_1 = code;
    ESP_LOGD(TAG, "Sending Toshiba AC rc_code_1=0x%llX", (unsigned long long) code);
    this->transmitter_->transmit<remote_base::ToshibaAcProtocol>(data);
  } else if (code == 0) {
    ESP_LOGD(TAG, "No IR code to send for this change.");
  } else {
    ESP_LOGW(TAG, "Transmitter not set, cannot send IR.");
  }
}

}  // namespace sencor_sacmt12
}  // namespace esphome

