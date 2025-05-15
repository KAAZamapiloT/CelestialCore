#include "Transformation.h"

Transform3D::Transform3D() : location(0.0f), rotation(1.0f, 0.0f, 0.0f, 0.0f), scale(1.0f) {}

Transform3D::Transform3D(const glm::vec3& location, const glm::quat& rotation, const glm::vec3& scale)
    : location(location), rotation(rotation), scale(scale) {}

glm::mat4 Transform3D::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, location);
    model = model * glm::mat4_cast(rotation);
    model = glm::scale(model, scale);
    return model;
}

Transform2D::Transform2D() : location(0.0f), rotation(0.0f), scale(1.0f) {}

Transform2D::Transform2D(const glm::vec2& location, float rotation, const glm::vec2& scale)
    : location(location), rotation(rotation), scale(scale) {}

glm::mat3 Transform2D::getModelMatrix() const {
    glm::mat3 model = glm::mat3(1.0f);
    
    // Apply translation
    model[2][0] = location.x;
    model[2][1] = location.y;
    
    // Apply rotation
    float cosTheta = cos(rotation);
    float sinTheta = sin(rotation);
    glm::mat3 rotMatrix(
        cosTheta, sinTheta, 0.0f,
        -sinTheta, cosTheta, 0.0f,
        0.0f, 0.0f, 1.0f
    );
    model = model * rotMatrix;
    
    // Apply scale
    glm::mat3 scaleMatrix(
        scale.x, 0.0f, 0.0f,
        0.0f, scale.y, 0.0f,
        0.0f, 0.0f, 1.0f
    );
    model = model * scaleMatrix;
    
    return model;
}