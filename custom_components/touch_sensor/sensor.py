import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

CONF_TOUCH_PAD = "touch_pad"
CONF_UPDATE_INTERVAL = "update_interval"

touch_sensor_ns = cg.esphome_ns.namespace("touch_sensor")
TouchReadSensor = touch_sensor_ns.class_(
    "TouchReadSensor", sensor.Sensor, cg.Component
)
CONFIG_SCHEMA = sensor.sensor_schema(unit_of_measurement="",
                                     accuracy_decimals=1).extend({
    cv.Required(CONF_TOUCH_PAD): cv.int_,
    cv.Optional(CONF_UPDATE_INTERVAL, default=60): cv.int_,  # default 60 s
    cv.GenerateID(): cv.declare_id(TouchReadSensor),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_TOUCH_PAD], config[CONF_UPDATE_INTERVAL])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

