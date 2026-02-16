#ifndef VU_METER_H
#define VU_METER_H

#include <stdbool.h>
#include <stdint.h>

#include "display.h"
#include "progmem_image_sprite.h"
#include "needle_sprite.h"

typedef struct vu_meter_t_ {
  display_t display;
  // calibration_t calibration;
  bool flipped;
  progmem_image_sprite_t background;
  needle_sprite_t needle;
  progmem_image_sprite_t peak_indicator;
#if ENABLE_WATERMARK
  progmem_image_sprite_t watermark;
#endif
  uint8_t peak_timer;
} vu_meter_t;

void
vu_meter_init(vu_meter_t *meter,
              int8_t address,
              // calibration_data_t *calibration_eeprom,
              bool flipped,
              const uint8_t *background_image,
              const uint8_t *peak_indicator_image,
              const uint8_t *watermark_image);
void vu_meter_update(vu_meter_t *meter, uint16_t needle_level, uint16_t peak_level);
void vu_meter_splash(vu_meter_t *meter, const uint8_t *image);

#endif