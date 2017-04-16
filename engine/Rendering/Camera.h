﻿#ifndef CAMERA_h
#define CAMERA_h

#include <Rendering/rendering.hpp>
#include <Model/Component.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

enum class ClearMethod { DoNotClear, DepthOnly, SolidColor, SkyxBox };
class IRenderer;

class Camera: public Component
{
private:
	float horizontalFov;
	float ratio; // width/height;
	float nearClippingPlane;
	float farClippingPlane;
	ClearMethod clearMethod;
	std::unique_ptr<IRenderer> skyboxRenderer;
	mutable glm::mat4 viewMatrix;
	mutable glm::mat4 projectionMatrix;
public:
	void clearWithSkybox() const;
	void clearWithSolidColor() const;

	void recalculateMatrices() const;
public:
	explicit Camera(GameObject*);
	Camera(GameObject*, float, float, float, float);
	virtual void Update() override;
	virtual void Start() override;
	glm::mat4 getViewProjectionMatrix() const;
	glm::mat4 getOrientationMatrix() const;
	float getHorizontalFov() const { return horizontalFov; }
	float getRatio() const { return ratio; }
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	void loadSkybox(std::vector<std::string>& filenames);
	void setClearMethod(ClearMethod _clearMethod) { clearMethod = _clearMethod; }
	void clear() const;
};

#endif //CAMERA_h