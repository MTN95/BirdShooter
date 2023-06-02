#pragma once

#include <SDL.h>
#include <string>
#include "Transform.h"

class AnimationData
{
public:
	AnimationData operator=(const AnimationData& other)
	{
		TextureID = other.TextureID;
		Path = other.Path;
		Transform = other.Transform;
		Width = other.Width;
		Height = other.Height;
		Row = other.Row;
		Frame = other.Frame;
		FrameCount = other.FrameCount;
		Flip = other.Flip;
		AnimSpeed = other.AnimSpeed;
		Loop = other.Loop;
		return *this;
	}

	AnimationData(const std::string& textureID, const std::string& path, mEngine::Math::Transform transform,
		float width, float height, int row, int frame, int frameCount, int animSpeed, 
		const SDL_RendererFlip& flip = SDL_FLIP_NONE, bool loop = true)
	{
		TextureID = textureID;
		Path = path;
		Transform = transform;
		Width = width;
		Height = height;
		Row = row;
		Frame = frame;
		FrameCount = frameCount;
		AnimSpeed = animSpeed;
		Flip = flip;
		Loop = loop;
	}

	void HandleAnimationEnd()
	{
		// Reset all animation data members
		Frame = 0;
		// Reset other members
		TextureID.clear();
		Path.clear();
		Transform = mEngine::Math::Transform(); // Reset transform to default values
		Width = 0.0f;
		Height = 0.0f;
		Flip = SDL_FLIP_NONE;
		Row = 0;
		FrameCount = 0;

		// You can also implement additional logic here, such as deleting the animation object or removing it from the list of animations being played
	}
	
	std::string TextureID;
	std::string Path;
	mEngine::Math::Transform Transform;
	float Width, Height;
	SDL_RendererFlip Flip;
	int Row, Frame, FrameCount, AnimSpeed;
	bool Loop;
};