#ifndef GOL_MODEL_H_
#define	GOL_MODEL_H_

#include "utility.h"


class GOLModel
{
    public:
        GOLModel();
        GOLModel(string name, int gw, int gh, int gs);
        GOLModel(string name, TextureDataBuffer gData, int gs);

        int m_width;
        int m_height;

        string getName();
        GLuint getTexture();
        GLuint m_patternTexture;

    private:
        void init(int gs);
        void initTexture(TextureDataBuffer pData);

        TextureDataBuffer m_pixelData;


        string m_name;


        int m_gridSize;
        int m_gridWidth;
        int m_gridHeight;
};


#endif
