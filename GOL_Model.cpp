#include "GOL_Model.h"

GOL_Model::GOL_Model()
{

}

GOL_Model::GOL_Model(string name, int gw, int gh, int gs)
{
    m_name = name;
    m_gridWidth = gw;
    m_gridHeight = gh;
    init(gs);
}

GOL_Model::GOL_Model(string name, EG_TextureDataBuffer gData, int gs)
{
    m_name = name;
    m_gridHeight = gData.size();
    m_gridWidth = gData[0].size();
    init(gs);
    initTexture(gData);
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            int num = (int)m_pixelData[y][x][3];
        //    cout << ((num == 255) ? 1 : 0);
        }
     //   cout << endl;
    }
}


void GOL_Model::init(int gs)
{
    m_height = m_gridHeight * gs;
    m_width = m_gridWidth * gs;

    m_gridSize = gs;

    m_pixelData.resize(m_height);
    for(int i=0; i<m_height; i++)
    {
        m_pixelData[i].resize(m_width);
        for(int j=0; j<m_width; j++)
            m_pixelData[i][j].resize(4);
    }
}


/*
    this function takes the gridData (which is in grid coordinate) and converts
    it into pixel coordinate
*/
void GOL_Model::initTexture(EG_TextureDataBuffer gridData)
{
    for (int y = 0; y < m_gridHeight; y++)
    {
        for (int x = 0; x < m_gridWidth; x++)
        {
            int sy = y * m_gridSize;
            int sx = x * m_gridSize;

            int ey = (y + 1) * m_gridSize;
            int ex = (x + 1) * m_gridSize;

            for(int py = sy; py < ey; py++)
            {
                for(int px = sx; px < ex; px++)
                {
                    m_pixelData[py][px][0] = gridData[y][x][0];
                    m_pixelData[py][px][1] = gridData[y][x][1];
                    m_pixelData[py][px][2] = gridData[y][x][2];
                    m_pixelData[py][px][3] = gridData[y][x][3];
                }
            }
        }
    }
    m_patternTexture = EG_Utility::loadTexture(m_pixelData, GL_NEAREST);
}


string GOL_Model::getName()
{
    return m_name;
}

GLuint GOL_Model::getTexture()
{
    return m_patternTexture;
}
