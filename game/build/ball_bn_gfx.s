
@{{BLOCK(ball_bn_gfx)

@=======================================================================
@
@	ball_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2023-06-07, 11:05:05
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global ball_bn_gfxTiles		@ 128 unsigned chars
	.hidden ball_bn_gfxTiles
ball_bn_gfxTiles:
	.word 0x11100000,0x22211000,0x22221100,0x22222110,0x22222210,0x22222221,0x22222221,0x22222221
	.word 0x00000111,0x00011222,0x00112211,0x01122112,0x01222222,0x12212222,0x12222222,0x12222222
	.word 0x22222221,0x22222221,0x22222221,0x22212210,0x22222110,0x22221100,0x22211000,0x11100000
	.word 0x12222222,0x12222222,0x12222222,0x01222222,0x01122222,0x00112222,0x00011222,0x00000111

	.section .rodata
	.align	2
	.global ball_bn_gfxPal		@ 32 unsigned chars
	.hidden ball_bn_gfxPal
ball_bn_gfxPal:
	.hword 0x0000,0x6E87,0x7FFF,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(ball_bn_gfx)
