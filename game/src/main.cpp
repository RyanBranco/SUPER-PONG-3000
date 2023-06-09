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
#include "bn_log.h"

#include "bn_regular_bg_items_bg.h"
#include "bn_sprite_items_paddle.h"
#include "bn_sprite_items_ball.h"

// 🥾 🐛 update debug mode here!
bool debug_mode = true;

bn::random random;
bn::sprite_text_generator text_generator(common::variable_8x8_sprite_font);
bn::vector<bn::sprite_ptr, 16> text_sprites;

namespace game_state {
    int round_started = false;

    int left_paddle_score = 0;
    int right_paddle_score = 0;

    int new_ball_location_x = 0;
    int new_ball_location_y = 0;

    bool right_paddle_ascending = true;

    int left_paddle_speed = 2;
    int right_paddle_speed = 2;
}

namespace game_utils {
    void handle_score_text_update() {
        bn::string<32> left_paddle_text = "SCORE: " + bn::to_string<32>(game_state::left_paddle_score);
        bn::string<32> right_paddle_text = "SCORE: " + bn::to_string<32>(game_state::right_paddle_score);

        text_generator.generate(-7 * 14, -71, left_paddle_text, text_sprites);
        text_generator.generate(4 * 10, -71, right_paddle_text, text_sprites);
    }

    void handle_timout_text() {
        if (game_state::round_started == false) {
            text_generator.generate(-6 * 10, -50, "PRESS 'A' TO START", text_sprites);
        }
    }

    void begin_round() {
        game_state::round_started = true;
        text_sprites.clear();
        handle_score_text_update();

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

    void handle_right_paddle(bn::sprite_ptr right_paddle) {
        if (game_state::right_paddle_ascending == true) {
            if (right_paddle.y() > -48) {
                right_paddle.set_y(right_paddle.y() - game_state::right_paddle_speed);
            } else {
                game_state::right_paddle_ascending = false;
            }
        } else {
            if (right_paddle.y() < 48) {
                right_paddle.set_y(right_paddle.y() + game_state::right_paddle_speed);
            } else {
                game_state::right_paddle_ascending = true;
            }
        }
    }

    void check_and_handle_potential_score(bn::sprite_ptr ball) {
        bool score_made = false;

        if (ball.x() >= 124) {
            score_made = true;
            game_state::left_paddle_score += 1;
        } else if (ball.x() <= -124) {
            score_made = true;
            game_state::right_paddle_score += 1;
        }

        if (score_made == true) {
            score_made = false;
            ball.set_position(0, 0);
            game_state::new_ball_location_x = 0;
            game_state::new_ball_location_y = 0;
            game_state::round_started = false;
            text_sprites.clear();
            handle_score_text_update();
            handle_timout_text();
        }
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

    void debug_listener() {
        // add any debugging functionality here...
    }
}

int main() {
    bn::core::init();

    bn::regular_bg_ptr bg = bn::regular_bg_items::bg.create_bg(0, 0);
    bn::sprite_ptr ball = bn::sprite_items::ball.create_sprite(0, 0);
    bn::sprite_ptr left_paddle = bn::sprite_items::paddle.create_sprite(-130, 0);
    bn::sprite_ptr right_paddle = bn::sprite_items::paddle.create_sprite(130, 0);
    right_paddle.set_horizontal_flip(true);

    game_utils::handle_score_text_update();
    game_utils::handle_timout_text();

    while(true)
    {
        game_utils::button_listener(left_paddle);
        game_utils::handle_right_paddle(right_paddle);
        game_utils::update_ball_location(ball);
        game_utils::check_and_handle_potential_score(ball);
        if (debug_mode) {
            game_utils::debug_listener();
        }
        bn::core::update();
    }
}