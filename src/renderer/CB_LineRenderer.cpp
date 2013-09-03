#include "renderer/CB_LineRenderer.h"

CB_LineRenderer::CB_LineRenderer()
{
    //ctor
}

CB_LineRenderer::~CB_LineRenderer()
{
    //dtor
}

void CB_LineRenderer::render(CB_RenderDataRel _data)
{
    glPushMatrix();
    CB_LineRendererData data = *((CB_LineRendererData*) _data.userdata);
    if(!_data.sharedUserdata)
    {
        delete((CB_LineRendererData*) _data.userdata);
    }
    double tileSize = _data.tileSize;
    double tileScale = CB_Renderer::getScale(tileSize);
    double thickness = data.width;
    double distRatio = getDistanceFromCamera(_data.position) / CB_Screen::getZ();
    double camRatio = CB_Screen::getOrthoZoom();
    double iPol = CB_Screen::getInterpolation();
    thickness *= 1 / (distRatio * iPol + camRatio * (1.0 - iPol));
    glLineWidth(thickness * tileScale);
    glPointSize(thickness * tileScale);

    GLdouble red = (double)((data.color >> 16) & 0xFF) / 255.0;
    GLdouble green = (double)((data.color >> 8) & 0xFF) / 255.0;
    GLdouble blue = (double)(data.color & 0xFF) / 255.0;
    GLdouble alpha = (double)((data.color >> 24) & 0xFF) / 255.0;

    glColor4d(red, green, blue, alpha);

    bool isTex2D = glIsEnabled(GL_TEXTURE_2D);
    bool isPointSmooth = glIsEnabled(GL_POINT_SMOOTH);
    bool isLineSmooth = glIsEnabled(GL_LINE_SMOOTH);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);

    data.start = data.start * tileScale;
    data.end = data.end * tileScale;

    glBegin(GL_POINTS);
    glVertex3d(data.start.x, data.start.y, data.start.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3d(data.start.x, data.start.y, data.start.z);
    glVertex3d(data.end.x, data.end.y, data.end.z);
    glEnd();

    glBegin(GL_POINTS);
    glVertex3d(data.end.x, data.end.y, data.end.z);
    glEnd();

    if(isTex2D)
    {
        glEnable(GL_TEXTURE_2D);
    }
    if(!isPointSmooth)
    {
        glDisable(GL_POINT_SMOOTH);
    }
    if(!isLineSmooth)
    {
        glDisable(GL_LINE_SMOOTH);
    }

    glPopMatrix();
}

void CB_LineRenderer::renderShader(CB_RenderDataRel data)
{
    render(data);
}

void CB_LineRenderer::addLine(double xOrig, double yOrig, double zOrig, double xStart, double yStart, double zStart, double xEnd, double yEnd, double zEnd)
{
    addLine(xOrig, yOrig, zOrig, xStart, yStart, zStart, xEnd, yEnd, zEnd, 1);
}

void CB_LineRenderer::addLine(double xOrig, double yOrig, double zOrig, double xStart, double yStart, double zStart, double xEnd, double yEnd, double zEnd, double width)
{
    addLine(xOrig, yOrig, zOrig, xStart, yStart, zStart, xEnd, yEnd, zEnd, width, 0xFFFFFFFF);
}

void CB_LineRenderer::addLine(double xOrig, double yOrig, double zOrig, double xStart, double yStart, double zStart, double xEnd, double yEnd, double zEnd, double width, uint32_t color)
{
    CB_RenderDataRel data = getLine(xOrig, yOrig, zOrig, xStart, yStart, zStart, xEnd, yEnd, zEnd, width, color);
    CB_Renderer::listRender(data);
}

CB_RenderDataRel CB_LineRenderer::getLine(double xOrig, double yOrig, double zOrig, double xStart, double yStart, double zStart, double xEnd, double yEnd, double zEnd, double width, uint32_t color)
{
    CB_LineRendererData * data = new CB_LineRendererData();
    data->start.x = xStart;
    data->start.y = yStart;
    data->start.z = zStart;
    data->end.x = xEnd;
    data->end.y = yEnd;
    data->end.z = zEnd;
    data->width = width;
    data->color = color;
    CB_RenderDataRel dataRel = CB_Renderer::getRenderData(this, data, CB_Screen::getTileSize(), CB_Vector3D(xOrig, yOrig, zOrig));
    double xMax = max(xStart, xEnd);
    double yMax = max(yStart, yEnd);
    double zMax = max(zStart, zEnd);
    dataRel.drawRadius = sqrt(xMax * xMax + yMax * yMax + zMax * zMax);
    return dataRel;
}
