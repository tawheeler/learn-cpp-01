/*
========================================================================

	A visual which shows animations

========================================================================
*/

#include "AnimationVisual.h"
#include "Globals.h"

AnimationVisual::AnimationVisual( Vec2i * pos, ALLEGRO_BITMAP * bitmap ) {
	AnimationVisual::pos = pos;
	AnimationVisual::bitmap = bitmap;
	AnimationVisual::halfWidth  = al_get_bitmap_width( AnimationVisual::bitmap ) / 2;
	AnimationVisual::halfHeight = al_get_bitmap_height( AnimationVisual::bitmap ) / 2;

	AnimationVisual::animation  = 0;
	AnimationVisual::frameIndex = 0;
	AnimationVisual::frameTick  = 0;
}

AnimationVisual::~AnimationVisual() {
	// do nothing
}

void AnimationVisual::Cleanup() {
	bitmap = 0;    // someone else will delete the bitmap
	pos = 0;       // someone else will delete pos
	animation = 0; // someone else will delete the animation
}

void AnimationVisual::Render() {

	bool renderAnim = false;
	if ( animation != 0 ) {
		frameTick --;
		if ( frameTick <= 0 ) { // move to a new frame, if possible
			frameIndex ++; // move to next frame
			if ( frameIndex >= animation->numFrames ) { // ran out of frames
				animation = 0; // done with animations
			} else {
				frameTick = animation->frameDurations[frameIndex];
				renderAnim = true;
			}
		} else {
			renderAnim = true;
		}
	}

	if ( renderAnim ) {
		animation->tex->RenderTexture( animation->frameIDs[frameIndex], pos->x, pos->y );
	} else {
		al_draw_bitmap( bitmap, pos->x, pos->y, 0 );
	}
}

void AnimationVisual::PlayAnimation( Animation * anim ) {
	AnimationVisual::animation = anim;
	frameIndex = 0;
	frameTick = animation->frameDurations[0];
}

void AnimationVisual::SetBitmap( ALLEGRO_BITMAP * bitmap ) {
	AnimationVisual::bitmap = bitmap;
	AnimationVisual::halfWidth = al_get_bitmap_width( AnimationVisual::bitmap ) / 2;
	AnimationVisual::halfHeight = al_get_bitmap_height( AnimationVisual::bitmap ) / 2;
}

bool AnimationVisual::IsPlayingAnimation() {
	return (animation != 0);
}