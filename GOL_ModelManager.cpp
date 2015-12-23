
#include "GOL_ModelManager.h"
/*
    The SquareModel is in Grid coordinates
*/



void GOL_ModelManager::init(int gs)
{
    m_GOLModels.push_back(new GOL_Model("Dot", generateSquareGridModel(1), gs));
    m_GOLModels.push_back(new GOL_Model("Square Outline", generateSquareOutlineGridModel(5), gs));
    m_GOLModels.push_back(new GOL_Model("Glider", readModelFromFile("GOL_glider.txt"), gs));
    m_GOLModels.push_back(new GOL_Model("Lightweight Spaceship", readModelFromFile("GOL_lightweight_spaceship.txt"), gs));
    m_GOLModels.push_back(new GOL_Model("Blinker", readModelFromFile("GOL_blinker.txt"), gs));
    m_GOLModels.push_back(new GOL_Model("Beacon", readModelFromFile("GOL_beacon.txt"), gs));

}

string GOL_ModelManager::getFilePath(string filename)
{
    string path("./Assets/Models/");
    path = path + filename;
    return path;
}


EG_TextureDataBuffer GOL_ModelManager::readModelFromFile(string filename)
{
    string path = getFilePath(filename);
 //   EG_Utility::debug("path is", path);


    ifstream file(path);
    string str;

    int rows = 0;
    int cols = 0;
    while(getline(file, str))
    {
 //       EG_Utility::debug(str);
        cols = str.size();
        rows++;
    }
    EG_Utility::debug("cols, rows is", glm::vec2(rows, cols));
    EG_TextureDataBuffer buffer = EG_Utility::createEmptyBuffer(cols, rows);

    int y = 0;
    ifstream file1(path);
    while(getline(file1, str))
    {
        for(int x=0; x<str.size(); x++)
        {
            char c = str[x];
    //        EG_Utility::debug("c is", (c == '#'));

            buffer[y][x][0] = 255;
            buffer[y][x][1] = (c == '#') ? 0 : 255;
            buffer[y][x][2] = (c == '#') ? 0 : 255;
            buffer[y][x][3] = (c == '#') ? 0 : 255;
        }
        y++;
    }

    return buffer;
}


EG_TextureDataBuffer GOL_ModelManager::generateSquareGridModel(int size)
{
    EG_TextureDataBuffer gridData = EG_Utility::createEmptyBuffer(size, size);

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            gridData[y][x][0] = 255;
            gridData[y][x][1] = 0;
            gridData[y][x][2] = 0;
            gridData[y][x][3] = 0;
        }
    }
    return gridData;
}

/*
    The SquareOutlineModel is in Grid coordinates
*/
EG_TextureDataBuffer GOL_ModelManager::generateSquareOutlineGridModel(int size)
{
    EG_TextureDataBuffer gridData = EG_Utility::createEmptyBuffer(size, size);

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if(y == 0 || y == size-1 || x == 0 || x == size-1)
            {
                gridData[y][x][0] = 255;
                gridData[y][x][1] = 0;
                gridData[y][x][2] = 0;
                gridData[y][x][3] = 0;
            }
            else
            {
                gridData[y][x][0] = 255;
                gridData[y][x][1] = 255;
                gridData[y][x][2] = 255;
                gridData[y][x][3] = 255;
            }
        }
    }
    return gridData;
}


GOL_Model* GOL_ModelManager::getDefaultGOLModel()
{
    if(m_GOLModels.size()<=0 || m_GOLModels[0] == NULL)
    {
        EG_Utility::debug("Error in GOL_ModelManager getDefaultGOLModel");
        exit(1);
    }
    return m_GOLModels[0];
}

GOL_Model* GOL_ModelManager::getModel(int index)
{
    if(index >= m_GOLModels.size())
    {
        EG_Utility::debug("Error in GOL_ModelManager getModel");
        exit(1);
    }
    return m_GOLModels[index];
}

vector<GOL_Model*> GOL_ModelManager::getModels()
{
    return m_GOLModels;
}

