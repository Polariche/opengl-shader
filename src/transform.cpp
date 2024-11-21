#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "transform.h"


Transform::Transform()
{
    position = glm::vec3(0.0F);
    rotation = glm::quat();
    scale = glm::vec3(1.0f);
}

glm::vec3 Transform::GetPosition()
{
    return position;
}
glm::quat Transform::GetRotation()
{
    return rotation;
}
glm::vec3 Transform::GetScale()
{
    return scale;
}

glm::mat4 Transform::GetMatrix()
{
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMat = glm::toMat4(rotation);
    glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale);

    return translation * rotationMat * scaling;
}

void Transform::SetPosition(glm::vec3 position)
{
    this->position = position;
}
void Transform::SetRotation(glm::quat quaternion)
{
    this->rotation = quaternion;
}
void Transform::SetRotation(glm::vec3 eulerAngles)
{
    this->rotation = glm::quat(eulerAngles);
}
void Transform::SetScale(glm::vec3 scale)
{
    this->scale = scale;
}