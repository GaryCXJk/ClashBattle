#include "CB_CollisionArea.h"

CB_CollisionArea::CB_CollisionArea()
{
    //ctor
}

CB_CollisionArea::CB_CollisionArea(vector<CB_Vector2D*> vec)
{
    vectors = vec;
}

CB_CollisionArea::~CB_CollisionArea()
{
    //dtor
}

void CB_CollisionArea::clear()
{
    vector<CB_Vector2D*>::iterator it;
    for(it = vectors.begin(); it < vectors.end(); it++)
    {
        delete *it;
    }
    vectors.clear();
}

void CB_CollisionArea::clearExcept(vector<CB_Vector2D*> vecs)
{
    vector<CB_Vector2D*>::iterator it;
    vector<CB_Vector2D*>::iterator it2;
    for(it = vectors.begin();it < vectors.end(); it++)
    {
        bool remove = true;
        for(it2 = vecs.begin();it2 < vecs.end(); it2++)
        {
            if(*it == *it2)
            {
                remove = false;
                break;
            }
        }
        if(remove)
        {
            delete *it;
        }
    }
    vectors.clear();
}

void CB_CollisionArea::setBox(double x, double y, double width, double height)
{
    vector<CB_Vector2D*> vecs;

    CB_Vector2D vec;

    vecs.push_back(new CB_Vector2D(x, y));
    vecs.push_back(new CB_Vector2D(x + width, y));
    vecs.push_back(new CB_Vector2D(x + width, y + height));
    vecs.push_back(new CB_Vector2D(x, y + height));

    vectors = vecs;

}

void CB_CollisionArea::addVector(CB_Vector2D * vecPtr)
{
    vectors.push_back(vecPtr);
}

void CB_CollisionArea::addVector(const CB_Vector2D& vecPtr)
{
    vectors.push_back((CB_Vector2D*)&vecPtr);
}

bool CB_CollisionArea::hasVector(CB_Vector2D * vec)
{
    vector<CB_Vector2D*>::iterator it;
    it = find(vectors.begin(), vectors.end(), vec);
    return (it < vectors.end());
}

uint32_t CB_CollisionArea::size()
{
    return vectors.size();
}

uint32_t CB_CollisionArea::getAngles()
{
    return getAngles(vectors);
}

uint32_t CB_CollisionArea::getAngles(vector<CB_Vector2D*> vecs)
{
    double tAngle = 0;
    vector<CB_Vector2D*>::iterator it = vecs.begin();
    for(uint32_t idx = 0; idx < vecs.size(); idx++)
    {
        CB_Vector2D * a = *(it + (idx + vecs.size() - 1) % vecs.size());
        CB_Vector2D * b = *(it + idx);
        CB_Vector2D * c = *(it + (idx + 1) % vecs.size());
        CB_Vector2D * vec1 = new CB_Vector2D(*b - *a);
        CB_Vector2D * vec2 = new CB_Vector2D(*c - *b);
        tAngle+= vec1->getAngle(*vec2);
        delete vec1;
        delete vec2;
    }
    return tAngle;
}

bool CB_CollisionArea::isConcave()
{
    return isConcave(vectors);
}

bool CB_CollisionArea::isConcave(vector<CB_Vector2D*> vecs)
{
    vector<CB_Vector2D*>::iterator it = vecs.begin();
    double pAngle = 0;
    for(uint32_t idx = 0; idx < vecs.size(); idx++)
    {
        CB_Vector2D * a = *(it + (idx + vecs.size() - 1) % vecs.size());
        CB_Vector2D * b = *(it + idx);
        CB_Vector2D * c = *(it + (idx + 1) % vecs.size());
        CB_Vector2D * vec1 = new CB_Vector2D(*b - *a);
        CB_Vector2D * vec2 = new CB_Vector2D(*c - *b);
        double angle = vec1->getAngle(*vec2);
        delete vec1;
        delete vec2;
        if((angle > 0 && pAngle < 0) || (angle < 0 && pAngle > 0))
        {
            return true;
        }
        pAngle = angle;
    }
    return false;
}

vector<CB_Vector2D*> CB_CollisionArea::optimize()
{
    vector<CB_Vector2D*>::iterator it;
    it = vectors.begin();
    vector<CB_Vector2D*> vecList;
    for(uint32_t idx = 0; idx < vectors.size(); idx++)
    {
        CB_Vector2D * a = *(it + (idx + vectors.size() - 1) % vectors.size());
        CB_Vector2D * b = *(it + idx);
        CB_Vector2D * c = *(it + (idx + 1) % vectors.size());
        CB_Vector2D * vec = new CB_Vector2D(*b - *a);
        CB_Vector2D * vec2 = new CB_Vector2D(*c - *b);
        double angle = vec->getAngle(*vec2);
        delete vec;
        delete vec2;
        if(angle != 0)
        {
            vecList.push_back(*(it + idx));
        }
    }
    return vecList;
}

vector<CB_Vector2D*> CB_CollisionArea::reverse()
{
    return reverse(vectors);
}

vector<CB_Vector2D*> CB_CollisionArea::reverse(vector<CB_Vector2D*> vecs)
{
    vector<CB_Vector2D*> rVecs;
    vector<CB_Vector2D*>::iterator it;
    for(it = vecs.end() - 1; it >= vecs.begin(); it--)
    {
        rVecs.push_back(*it);
    }
    return rVecs;
}

vector<CB_CollisionArea*> CB_CollisionArea::getConvexPolygons()
{
    vector<CB_CollisionArea*> areaList;

    vector<CB_Vector2D*> optimizedVectors = optimize();

    uint32_t angles = getAngles(optimizedVectors);

    if(angles > 0)
    {
        optimizedVectors = reverse(optimizedVectors);
    }

    if(!isConcave(optimizedVectors))
    {
        areaList.push_back(new CB_CollisionArea(*this));
        return areaList;
    }

    bool repeat = true;
    vector<CB_Vector2D*>::iterator it;
    vector<CB_Vector2D*>::iterator itConcave;
    itConcave = optimizedVectors.end();

    uint32_t pSize = optimizedVectors.size();
    uint32_t cit = -1;
    while(repeat)
    {
        vector<CB_Vector2D*> tList;
        uint32_t vSize = optimizedVectors.size();
        if(pSize == vSize)
        {
            cit++;
        }
        else
        {
            pSize = vSize;
            cit = 0;
        }
        for(uint32_t idx = 0; idx < (vSize = optimizedVectors.size()); idx++)
        {
            it = optimizedVectors.begin();
            CB_Vector2D * curVec = *(it + (vSize + idx - 1) % vSize);
            double curAngle = curVec->getAngle(**(it + idx));
            if(curAngle > 0)
            {
                if(tList.size() > 1)
                {
                    tList.push_back(*(it + idx));
                    areaList.push_back(new CB_CollisionArea(tList));
                    if(itConcave < it + idx)
                    {
                        idx = optimizedVectors.erase(itConcave + 1, it + idx) - optimizedVectors.begin();
                    }
                    else
                    {
                        optimizedVectors.erase(itConcave + 1);
                        it = optimizedVectors.erase(optimizedVectors.begin(), it + idx);
                        idx = 0;
                    }
                }
                tList.clear();
                tList.push_back(*(it + idx));
                itConcave = it + idx;
            }
            else if(itConcave < optimizedVectors.end())
            {
                tList.push_back(*(it + idx));
                if(tList.size() > 2)
                {
                    vector<CB_Vector2D*> ttList = tList;
                    ttList.push_back(*(it + (idx + 1) % vSize));
                    if(isConcave(ttList))
                    {
                        areaList.push_back(new CB_CollisionArea(tList));
                        tList.clear();
                        tList.push_back(*itConcave);
                        tList.push_back(*(it + idx));
                        if(itConcave < it + idx)
                        {
                            idx = optimizedVectors.erase(itConcave + 1, it + idx) - optimizedVectors.begin();
                        }
                        else
                        {
                            optimizedVectors.erase(itConcave + 1);
                            it = optimizedVectors.erase(optimizedVectors.begin(), it + idx);
                            idx = 0;
                        }
                    }
                }
            }
        }
        repeat = isConcave(optimizedVectors) && cit < 3;
    }
    if(optimizedVectors.size() > 2)
    {
        areaList.push_back(new CB_CollisionArea(optimizedVectors));
    }

    return areaList;
}


bool CB_CollisionArea::isOverlap(const CB_CollisionArea& cVecs)
{
    vector<CB_Vector2D*>::iterator it = vectors.begin();

    //It first checks using a box if the other collision shape is within the area of the current shape.
    double xMin = ((CB_Vector2D*)*it)->x;
    double yMin = ((CB_Vector2D*)*it)->y;
    double xMax = xMin;
    double yMax = yMin;
    for(uint32_t idx = 1; idx < vectors.size(); idx++)
    {
        CB_Vector2D * tV = *(it + idx);
        if(tV->x < xMin)
        {
            xMin = tV->x;
        }
        if(tV->x > xMax)
        {
            xMax = tV->x;
        }
        if(tV->y < yMin)
        {
            yMin = tV->y;
        }
        if(tV->y > yMax)
        {
            yMax = tV->y;
        }
    }
    if(!((CB_CollisionArea)cVecs).isInRange(xMin, yMin, xMax, yMax))
    {
        return false;
    }

    /* Now it iterates through each face of the shape and check if there is a collision along
    this line or not, otherwise it checks if the projection overlaps. */
    for(uint32_t idx = 0; idx < vectors.size(); idx++)
    {
        CB_Vector2D a = **(it + idx);
        CB_Vector2D b = **(it + (idx + 1) % vectors.size());
        if(((CB_CollisionArea)cVecs).isBoundsCollide(a, b))
        {
            continue;
        }
        b = b - a;
        b = b.getRightNormal();
        b = b + a;
        vector<CB_Vector2D*>::iterator it2;
        CB_Vector2D vMin = a;
        CB_Vector2D vMax = a;
        for(it2 = vectors.begin(); it2 < vectors.end(); it2++)
        {
            CB_Vector2D c = **it2;
            c = getProjection(a, b, c);
            if(c.x < vMin.x)
            {
                vMin = c;
            }
            else if(c.x > vMax.x)
            {
                vMax = c;
            }
            else if(c.x == vMax.x)
            {
                if(c.y < vMin.y)
                {
                    vMin = c;
                }
                else if(c.y > vMax.y)
                {
                    vMax = c;
                }
            }
        }
        if(!((CB_CollisionArea)cVecs).isProjectionOverlap(a, b, vMin, vMax))
        {
            return false;
        }
    }
    return true;
}

CB_Vector2D CB_CollisionArea::getProjection(const CB_Vector2D& a, const CB_Vector2D& b, const CB_Vector2D& c)
{
    CB_Vector2D vec = c;
    vec = vec - a;
    vec = vec.projection((CB_Vector2D)b - a);
    vec = vec + a;
    return vec;
}

bool CB_CollisionArea::isInRange(double xMin, double yMin, double xMax, double yMax)
{
    vector<CB_Vector2D*>::iterator it;
    for(it = vectors.begin(); it < vectors.end(); it++)
    {
        CB_Vector2D vec = **it;
        if(vec.x >= xMin && vec.x <= xMax && vec.y >= yMin && vec.y <= yMax)
        {
            return true;
        }
    }
    return false;
}

bool CB_CollisionArea::isBoundsCollide(const CB_Vector2D& a, const CB_Vector2D& b)
{
    CB_CollisionBound mainBound;
    mainBound.setBound(a.x, a.y, b.x, b.y);
    vector<CB_Vector2D*>::iterator it = vectors.begin();
    for(uint32_t idx = 0; idx < size(); idx++)
    {
        CB_Vector2D c = **(it + idx);
        CB_Vector2D d = **(it + (idx + 1) % size());
        CB_CollisionBound testBound;
        testBound.setBound(c.x, c.y, d.x, d.y);
        CB_Vector2D e = mainBound.getIntersection(testBound);
        if(mainBound.intersects(e))
        {
            return true;
        }
    }
    return false;
}

bool CB_CollisionArea::isProjectionOverlap(const CB_Vector2D& a, const CB_Vector2D& b, const CB_Vector2D& first, const CB_Vector2D& second)
{
    double xMin = min(first.x, second.x);
    double yMin = min(first.y, second.y);
    double xMax = max(first.x, second.x);
    double yMax = max(first.y, second.y);

    vector<CB_Vector2D*>::iterator it;
    for(it = vectors.begin(); it < vectors.end(); it++)
    {
        CB_Vector2D vec = **it;
        vec = vec - a;
        vec = vec.projection((CB_Vector2D)b - a);
        vec = vec + a;
        if(vec.x >= xMin && vec.x <= xMax && vec.y >= yMin && vec.y <= yMax)
        {
            return true;
        }
    }
    return false;
}

CB_CollisionArea CB_CollisionArea::sweep(const CB_Vector2D& direction)
{
    vector<CB_Vector2D*> optimizedVectors = optimize();
    vector<CB_Vector2D*> optimizedVectors2 = optimize();

    uint32_t angles = getAngles(optimizedVectors);

    if(angles > 0)
    {
        optimizedVectors = reverse(optimizedVectors);
    }
    vector<CB_Vector2D*> vectors2;
    float angle = ((CB_Vector2D)direction).getAngle();
    float nAngle = angle + PI;
    if(nAngle > PI)
    {
        nAngle-= 2 * PI;
    }
    for(uint32_t idx = 0; idx < optimizedVectors.size(); idx++)
    {
        uint32_t pIdx = (idx + optimizedVectors.size() - 1) % optimizedVectors.size();
        CB_Vector2D * a = *(optimizedVectors.begin() + pIdx);
        CB_Vector2D * b = *(optimizedVectors.begin() + idx);
        CB_Vector2D * c = new CB_Vector2D(*a + direction);
        CB_Vector2D * d = new CB_Vector2D(*b + direction);
        CB_Vector2D * curVec = new CB_Vector2D(*b - *a);
        double angleDiff = curVec->getAngle();
        delete curVec;
        if(angleDiff - angle > PI)
        {
            angleDiff-= 2 * PI;
        }
        if(angleDiff - angle < -PI)
        {
            angleDiff+= 2 * PI;
        }
        if(angleDiff >= angle)
        {
            if(vectors2.end() == vectors2.begin() || *(vectors2.end() - 1) != a)
            {
                vectors2.push_back(a);
            }
            vectors2.push_back(b);
        }
        curVec = new CB_Vector2D(*d - *c);
        angleDiff = curVec->getAngle();
        delete curVec;
        if(angleDiff - nAngle > PI)
        {
            angleDiff-= 2 * PI;
        }
        if(angleDiff - nAngle < -PI)
        {
            angleDiff+= 2 * PI;
        }
        if(angleDiff >= nAngle)
        {
            if(vectors2.end() == vectors2.begin() || (((CB_Vector2D)**(vectors2.end() - 1)).x != c->x && ((CB_Vector2D)**(vectors2.end() - 1)).y != c->y))
            {
                vectors2.push_back(c);
            }
            else
            {
                delete c;
            }
            vectors2.push_back(d);
        }
        else
        {
            delete c;
            delete d;
        }
    }
    optimizedVectors.clear();
    return CB_CollisionArea(vectors2);
}
