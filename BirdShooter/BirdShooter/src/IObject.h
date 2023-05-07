#pragma once

class IObject
{
public:
	virtual void Update(float DeltaTime) = 0;
	virtual void Render() = 0;
	virtual void RenderFrame() = 0;
	virtual void Clean() = 0;
};