#ifndef GOL_MODEL_H_
#define	GOL_MODEL_H_

#include "EG_Utility.h"

class GOL_Model
{
    public:
        GOL_Model();
        GOL_Model(string name, int gw, int gh, int gs);
        GOL_Model(string name, EG_TextureDataBuffer gData, int gs);

        int m_width;
        int m_height;

        string getName();
        GLuint getTexture();
        GLuint m_patternTexture;

    private:
        void init(int gs);
        void initTexture(EG_TextureDataBuffer pData);

        EG_TextureDataBuffer m_pixelData;


        string m_name;


        int m_gridSize;
        int m_gridWidth;
        int m_gridHeight;
};


#endif
