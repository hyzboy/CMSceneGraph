#include<hgl/graph/BoundingVolumes.h>

namespace hgl::graph
{
    AABB ToAABB(const OBB &obb)
    {
        if(obb.IsEmpty())
        {
            AABB aabb;
            aabb.Clear();
            return aabb;
        }

        // Get the absolute values of the OBB's axes
        const glm::vec3 ax = glm::abs(obb.GetAxis(0));
        const glm::vec3 ay = glm::abs(obb.GetAxis(1));
        const glm::vec3 az = glm::abs(obb.GetAxis(2));
        
        // Calculate the extent by projecting OBB half-lengths onto world axes
        const Vector3f half_extent = obb.GetHalfExtend();
        const glm::vec3 e = ax * half_extent.x + ay * half_extent.y + az * half_extent.z;

        AABB aabb;
        aabb.SetMinMax(obb.GetCenter() - e, obb.GetCenter() + e);
        return aabb;
    }

    OBB ToOBB(const AABB &aabb)
    {
        OBB obb;
        obb.Set(aabb.GetCenter(), aabb.GetLength() * 0.5f);
        return obb;
    }

    OBB ToOBB(const AABB &aabb, const Matrix4f &transform)
    {
        // Transform the center
        Vector3f center = Vector3f(transform * Vector4f(aabb.GetCenter(), 1.0f));
        
        // Extract rotation and scale from transform
        const float s0 = glm::length(glm::vec3(transform[0]));
        const float s1 = glm::length(glm::vec3(transform[1]));
        const float s2 = glm::length(glm::vec3(transform[2]));

        // Extract and normalize axes
        Vector3f a0 = (s0 > 0.0f) ? (glm::vec3(transform[0]) / s0) : Vector3f(1, 0, 0);
        Vector3f a1 = (s1 > 0.0f) ? (glm::vec3(transform[1]) / s1) : Vector3f(0, 1, 0);
        Vector3f a2 = (s2 > 0.0f) ? (glm::vec3(transform[2]) / s2) : Vector3f(0, 0, 1);

        // Apply scale to half extents
        Vector3f half_length = aabb.GetLength() * 0.5f * Vector3f(s0, s1, s2);

        OBB obb;
        obb.Set(center, a0, a1, a2, half_length);
        return obb;
    }

    void BoundingVolumes::Pack(BoundingVolumesData *packed) const
    {
        if(!packed)
            return;

        packed->aabbMin[0] = aabb.minPoint.x;
        packed->aabbMin[1] = aabb.minPoint.y;
        packed->aabbMin[2] = aabb.minPoint.z;
        packed->aabbMax[0] = aabb.maxPoint.x;
        packed->aabbMax[1] = aabb.maxPoint.y;
        packed->aabbMax[2] = aabb.maxPoint.z;
    
        packed->obbCenter[0] = obb.center.x;
        packed->obbCenter[1] = obb.center.y;
        packed->obbCenter[2] = obb.center.z;
    
        packed->obbAxisX[0] = obb.axis[0].x;
        packed->obbAxisX[1] = obb.axis[0].y;
        packed->obbAxisX[2] = obb.axis[0].z;
    
        packed->obbAxisY[0] = obb.axis[1].x;
        packed->obbAxisY[1] = obb.axis[1].y;
        packed->obbAxisY[2] = obb.axis[1].z;
    
        packed->obbAxisZ[0] = obb.axis[2].x;
        packed->obbAxisZ[1] = obb.axis[2].y;
        packed->obbAxisZ[2] = obb.axis[2].z;
    
        packed->obbHalfSize[0] = obb.half_length.x;
        packed->obbHalfSize[1] = obb.half_length.y;
        packed->obbHalfSize[2] = obb.half_length.z;
    
        packed->sphereCenter[0] = bsphere.center.x;
        packed->sphereCenter[1] = bsphere.center.y;
        packed->sphereCenter[2] = bsphere.center.z;
        packed->sphereRadius = bsphere.radius;
    }
    
    void BoundingVolumesData::To(BoundingVolumes *bounds)
    {
        bounds->aabb.SetMinMax(
            Vector3f(aabbMin[0], aabbMin[1], aabbMin[2]),
            Vector3f(aabbMax[0], aabbMax[1], aabbMax[2]));

        bounds->obb.Set(
            Vector3f(obbCenter[0],  obbCenter[1],   obbCenter[2]),
            Vector3f(obbAxisX[0],   obbAxisX[1],    obbAxisX[2]),
            Vector3f(obbAxisY[0],   obbAxisY[1],    obbAxisY[2]),
            Vector3f(obbAxisZ[0],   obbAxisZ[1],    obbAxisZ[2]),
            Vector3f(obbHalfSize[0],obbHalfSize[1], obbHalfSize[2]));

        bounds->bsphere.center = Vector3f(sphereCenter[0], sphereCenter[1], sphereCenter[2]);
        bounds->bsphere.radius = sphereRadius;
    }
}//namespace hgl::graph
