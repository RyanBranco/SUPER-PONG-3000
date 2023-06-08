#include "bn_core.h"
#include <bn_sprite_ptr.h>
#include "bn_regular_bg_ptr.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "common_info.h"
#include "bn_keypad.h"
#include "bn_string.h"
#include "common_variable_8x8_sprite_font.h"
#include "bn_sprite_text_generator.h"

// #include "bn_regular_bg_items_bg.h"
#include "bn_sprite_items_paddle.h"
#include "bn_sprite_items_ball.h"

bn::random random;
bn::sprite_text_generator text_generator(common::variable_8x8_sprite_font);
bn::vector<bn::sprite_ptr, 16> text_sprites;

namespace game_state {
    int round_started = false;

    int left_paddle_score = 0;
    int right_paddle_score = 0;

    int new_ball_location_x = 0;
    int new_ball_location_y = 0;

    int left_paddle_location = 0;
    int right_paddle_location = 0;

    int left_paddle_speed = 2;
    int right_paddle_speed =2;
}

namespace game_utils {
    void begin_round() {
        game_state::round_started = true;
        text_sprites.clear();

        bn::string<32> left_paddle_text = "SCORE: " + bn::to_string<32>(game_state::left_paddle_score);
        bn::string<32> right_paddle_text = "SCORE: " + bn::to_string<32>(game_state::right_paddle_score);

        text_generator.generate(-7 * 14, -68, left_paddle_text, text_sprites);
        text_generator.generate(4 * 10, -68, right_paddle_text, text_sprites);

        // send ball in random direction that is not a straight Y or striaght X
        while(game_state::new_ball_location_x == 0 || game_state::new_ball_location_y == 0) {
            game_state::new_ball_location_x = (random.get_int() % 5) - 2;
            game_state::new_ball_location_y = (random.get_int() % 5) - 2;
        }
    }

    void update_ball_location(bn::sprite_ptr ball) {
        ball.set_x(ball.x() + game_state::new_ball_location_x);
        ball.set_y(ball.y() + game_state::new_ball_location_y);
    }

    void button_listener(bn::sprite_ptr left_paddle) {
        if (bn::keypad::a_pressed() && game_state::round_started == false) {
            begin_round();
        }

        if (game_state::round_started == true) {
            if (bn::keypad::up_held() && left_paddle.y() > -48) {
                left_paddle.set_y(left_paddle.y() - game_state::left_paddle_speed);
                
            } else if (bn::keypad::down_held() && left_paddle.y() < 48) {
                left_paddle.set_y(left_paddle.y() + game_state::left_paddle_speed);
            }
        }
    }

}


int main() {
    bn::core::init();

    bn::sprite_ptr ball = bn::sprite_items::ball.create_sprite(0, 0);

    bn::sprite_ptr left_paddle = bn::sprite_items::paddle.create_sprite(-130, 0);
    bn::sprite_ptr right_paddle = bn::sprite_items::paddle.create_sprite(130, 0);
    right_paddle.set_horizontal_flip(true);

    text_generator.generate(-6 * 12, -68, "Press 'A' to start the round", text_sprites);

    while(true)
    {
        game_utils::button_listener(left_paddle);
        game_utils::update_ball_location(ball);

        bn::core::update();
    }
}