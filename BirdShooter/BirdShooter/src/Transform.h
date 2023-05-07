#include <iostream>
#include <string>
#include <SDL.h>
#include "TextureManager.h"
#include "Vec2D.h"

namespace mEngine
{
	namespace Math
	{
		class Transform
		{
		public:
			Transform() : m_Position({ 0, 0 }), m_Scale(1), m_Rotation(0) {}
			Transform(const Vec2D& position, const float& scale, double rotation)
				: m_Position(position), m_Scale(scale), m_Rotation(rotation) {}

			void Log(const std::string& msg = "") const {
				std::cout << msg << '\n';
				m_Position.Log("Position:");
				std::cout << "Scale: " << m_Scale << '\n';
				std::cout << "Rotation: " << m_Rotation << '\n';
			}


			inline const Vec2D& getPosition() const { return m_Position; }
			inline const float& getScale() const { return m_Scale; }
			inline const double& getRotation() const { return m_Rotation; }

			void setPosition(const Vec2D& position) { m_Position = position; }
			void setScale(const float &scale) { m_Scale = scale; }
			void setRotation(double rotation) { m_Rotation = rotation; }

			inline void TranslateXPosition(float x) 
			{
				m_Position.x += x;
			}

			inline void TranslateYPosition(float y)
			{
				m_Position.y += y;
			}

		private:
			Vec2D m_Position;
			float m_Scale;
			double m_Rotation;
		};
	}
}