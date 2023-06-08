#ifndef BN_SPRITE_ITEMS_PADDLE_H
#define BN_SPRITE_ITEMS_PADDLE_H

#include "bn_sprite_item.h"

//{{BLOCK(paddle_bn_gfx)

//======================================================================
//
//	paddle_bn_gfx, 32x32@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles not compressed
//	Total size: 32 + 512 = 544
//
//	Time-stamp: 2023-06-08, 14:04:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PADDLE_BN_GFX_H
#define GRIT_PADDLE_BN_GFX_H

#define paddle_bn_gfxTilesLen 512
extern const bn::tile paddle_bn_gfxTiles[16];

#define paddle_bn_gfxPalLen 32
extern const bn::color paddle_bn_gfxPal[16];

#endif // GRIT_PADDLE_BN_GFX_H

//}}BLOCK(paddle_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item paddle(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(paddle_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(paddle_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

