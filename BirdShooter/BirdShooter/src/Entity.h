#pragma once

#include "IObject.h"
#include "Transform.h"

namespace mEngine
{

	struct EntityData
	{
		EntityData(const std::string& textureID, const std::string& path, Math::Transform transform,
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
		Math::Transform Transform;
		float Width, Height;
		SDL_RendererFlip Flip;
		int Row, Frame, FrameCount;
	};

	class Entity : public IObject
	{
	public:
		Entity() = default;
		Entity(EntityData* data);

		void Log()
		{
			std::cout << m_TextureID << '\n';
			m_Transform.getPosition().Log("POS:");
			std::cout << "Scale: " << m_Transform.getScale() << '\n';
			std::cout << "Rotation: " << m_Transform.getRotation() << '\n';
			std::cout << "Width: " << m_Width << ' ' << "Height: " << m_Height << '\n';
		}

		virtual ~Entity();

		void Update(float deltaTime) override;
		void Render() override;
		void RenderFrame() override;
		void Clean() override;

		inline const Math::Vec2D GetPosition() const { return m_Transform.getPosition(); }
		inline const float& GetScale() const { return m_Transform.getScale(); }
		inline const double& GetRotation() const { return m_Transform.getRotation(); }
		inline const float& GetWidth() const { return m_Width; }
		inline const float& GetHeight() const { return m_Height; }
		inline const std::string& GetID() const { return m_TextureID; }

		inline const unsigned int GetEntityCount() { return EntityCount; }

	protected:
		std::string m_TextureID;
		Math::Transform m_Transform;
		float m_Width, m_Height;
		SDL_RendererFlip m_Flip;
		int m_Row, m_Frame, m_FrameCount;
		int m_AnimSpeed;
		float m_MoveDirection;
		float m_MoveSpeed;

		unsigned int EntityCount = 0;
	};
}