#include "bn_core.h"
#include <bn_sprite_ptr.h>
#include "bn_regular_bg_ptr.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "common_info.h"
#include "common_variable_8x8_sprite_font.h"

#include "bn_regular_bg_items_bg.h"
#include "bn_sprite_items_paddle.h"
#include "bn_sprite_items_ball.h"

int main() {
    bn::core::init();

    bn::regular_bg_ptr bg = bn::regular_bg_items::bg.create_bg(0, 0);

    bn::sprite_ptr left_paddle = bn::sprite_items::paddle.create_sprite(-140, 0);
    bn::sprite_ptr right_paddle = bn::sprite_items::paddle.create_sprite(140, 0);
    right_paddle.set_horizontal_flip(true);

    bn::sprite_ptr ball = bn::sprite_items::ball.create_sprite(0, 0);
    bn::sprite_text_generator text_generator(common::variable_8x8_sprite_font);
    bn::vector<bn::sprite_ptr, 16> text_sprites;
    text_generator.generate(-6 * 16, -68, "Not functional... This is a template to create GBA games!", text_sprites);

    while(true)
    {
        bn::core::update();
    }
}