#include <Urho3D/Graphics/Graphics.h>
#include <iostream>

#include <Urho3D/Core/Context.h>
#include <Urho3D/Input/InputConstants.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/UI/UI.h>

#include "CameraController.h"

using namespace ProcGen;

CameraController::CameraController(Context *context) : LogicComponent(context) {
    SetUpdateEventMask(USE_UPDATE);
}

void CameraController::DelayedStart() {
    node_->SetPosition(Vector3(0.0f, 2.f, -3.0f));
    node_->LookAt(Vector3::ZERO);
}

void CameraController::Update(float timeStep) {
    if (GetSubsystem<Urho3D::UI>()->GetFocusElement())
        return;

    auto* input = GetSubsystem<Urho3D::Input>();

    // Movement speed as world units per second    
    const float MOVE_SPEED = 5.0f;

    using namespace Urho3D;
    
    if (input->GetKeyDown(KEY_W))
        node_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_S))
        node_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_A))
        node_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_D))
        node_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_Q))
        node_->Translate(Vector3::DOWN * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_E))
        node_->Translate(Vector3::UP * MOVE_SPEED * timeStep);


    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.3f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);
    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    // node_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    
    if (input->GetKeyDown(KEY_J)) {
        node_->Rotate(Quaternion(0, -MOUSE_SENSITIVITY, 0));
    }
    if (input->GetKeyDown(KEY_L)) {
        node_->Rotate(Quaternion(0, MOUSE_SENSITIVITY, 0));
    }
    if (input->GetKeyDown(KEY_I)) {
        node_->Rotate(Quaternion(-MOUSE_SENSITIVITY, 0, 0));
    }
    if (input->GetKeyDown(KEY_K)) {
        node_->Rotate(Quaternion(MOUSE_SENSITIVITY, 0, 0));
    }    
}
