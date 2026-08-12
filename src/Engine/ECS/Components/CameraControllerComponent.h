#pragma once

#include <memory>

#include <Engine/CameraController/CameraController.h>

struct CameraControllerComponent {
    std::unique_ptr<CameraController> camera_controller;
};

