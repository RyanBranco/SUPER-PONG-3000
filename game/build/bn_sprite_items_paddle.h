#ifndef BN_SPRITE_ITEMS_PADDLE_H
#define BN_SPRITE_ITEMS_PADDLE_H

#include "bn_sprite_item.h"

//{{BLOCK(paddle_bn_gfx)

//======================================================================
//
//	paddle_bn_gfx, 64x64@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 32 + 2048 = 2080
//
//	Time-stamp: 2023-06-07, 11:05:05
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PADDLE_BN_GFX_H
#define GRIT_PADDLE_BN_GFX_H

#define paddle_bn_gfxTilesLen 2048
extern const bn::tile paddle_bn_gfxTiles[64];

#define paddle_bn_gfxPalLen 32
extern const bn::color paddle_bn_gfxPal[16];

#endif // GRIT_PADDLE_BN_GFX_H

//}}BLOCK(paddle_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item paddle(sprite_shape_size(sprite_shape::WIDE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(paddle_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 2), 
            sprite_palette_item(span<const color>(paddle_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

