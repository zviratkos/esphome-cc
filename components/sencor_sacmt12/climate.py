import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate
from esphome.const import CONF_ID

sencor_ns = cg.esphome_ns.namespace("sencor_sacmt12")
SencorSACMT12 = sencor_ns.class_("SencorSACMT12", climate.Climate, cg.Component)

CONFIG_SCHEMA = climate.climate_schema(
    SencorSACMT12
).extend({
    cv.GenerateID(): cv.declare_id(SencorSACMT12),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await climate.register_climate(var, config)

