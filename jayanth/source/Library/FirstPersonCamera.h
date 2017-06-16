#pragma once

#include "Camera.h"

namespace Library
{
    class FirstPersonCamera : public Camera
    {
        RTTI_DECLARATIONS(FirstPersonCamera, Camera)

    public:
        FirstPersonCamera(Game& game);
        FirstPersonCamera(Game& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		FirstPersonCamera(const FirstPersonCamera&) = delete;
		FirstPersonCamera& operator=(const FirstPersonCamera&) = delete;
		FirstPersonCamera(FirstPersonCamera&&) = delete;
		FirstPersonCamera& operator=(FirstPersonCamera&&) = delete;
        virtual ~FirstPersonCamera() = default;

        float& MouseSensitivity();
        float& RotationRate();
        float& MovementRate();
        
        virtual void Initialize() override;
        virtual void Update(const GameTime& gameTime) override;

        static const float DefaultMouseSensitivity;
        static const float DefaultRotationRate;
        static const float DefaultMovementRate;        

    protected:
        float mMouseSensitivity;
        float mRotationRate;
        float mMovementRate;

    private:
		double mLastCursorX;
		double mLastCursorY;
    };
}

