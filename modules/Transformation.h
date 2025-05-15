#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>


class Transform3D{

public:
    Transform3D();
    Transform3D(const glm::vec3& location, const glm::quat& rotation, const glm::vec3& scale);

    glm::vec3 location;
    glm::quat rotation;
    glm::vec3 scale;

    glm::mat4 getModelMatrix() const;
};

class Transform2D{
    public:
    Transform2D();
    Transform2D(const glm::vec2& location, float rotation, const glm::vec2& scale);

    glm::vec2 location;
    float rotation; // in radians
    glm::vec2 scale;

    glm::mat3 getModelMatrix() const;
};