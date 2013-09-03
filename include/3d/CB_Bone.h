#ifndef CB_BONE_H
#define CB_BONE_H
#include "ClashBattle.h"
#include "util/CB_Vector3D.h"
#include "util/CB_Quaternion.h"

class CB_Bone
{
    public:
        CB_Bone();
        virtual ~CB_Bone();
    protected:
    private:
        CB_Bone * parent;
        CB_Vector3D start;
        CB_Vector3D end;
        bool absolute;
};

#endif // CB_BONE_H
