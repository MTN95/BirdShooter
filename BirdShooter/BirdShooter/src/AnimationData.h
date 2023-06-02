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
		return *this;
	}

	AnimationData(const std::string& textureID, const std::string& path, mEngine::Math::Transform transform,
		float width, float height, int row, int frame, int frameCount, const SDL_RendererFlip& flip = SDL_FLIP_NONE)
	{
		TextureID = textureID;
		Path = path;
		Transform = transform;
		Width = width;
		Height = height;
		Row = row;
		Frame = frame;
		FrameCount = frameCount;
		Flip = flip;
	}

	std::string TextureID;
	std::string Path;
	mEngine::Math::Transform Transform;
	float Width, Height;
	SDL_RendererFlip Flip;
	int Row, Frame, FrameCount;
};