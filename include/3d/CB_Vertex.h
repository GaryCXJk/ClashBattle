#ifndef CB_VERTEX_H
#define CB_VERTEX_H
#include "ClashBattle.h"
#include "util/CB_Vector3D.h"
#include "3d/CB_Bone.h"

struct CB_BoneRel
{
    CB_Bone * bone;
    double weight;
};

class CB_Vertex
{
    public:
        CB_Vertex();
        virtual ~CB_Vertex();
        void setPosition(CB_Vector3D _position){position = _position;};
        void setNormal(CB_Vector3D _normal){normal = _normal;};
        CB_Vector3D getPosition(){return position;};
        CB_Vector3D getNormal(){return normal;};
    protected:
    private:
        CB_Vector3D position;
        CB_Vector3D normal;
        uint8_t boneCount;
        CB_BoneRel bone[4];
};

#endif // CB_VERTEX_H
