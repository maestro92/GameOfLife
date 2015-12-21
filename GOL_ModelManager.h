#ifndef GOL_MODEL_MANAGER_H_
#define GOL_MODEL_MANAGER_H_

#include "EG_Utility.h"
#include "GOL_Model.h"

class GOL_ModelManager
{
    public:
        void init(int gs);

        EG_TextureDataBuffer generateSquareGridModel(int gs);
        EG_TextureDataBuffer generateSquareOutlineGridModel(int gs);
        EG_TextureDataBuffer readModelFromFile(string filename);


        vector<GOL_Model*> m_GOLModels;

        string getFilePath(string filename);
        GOL_Model* getDefaultGOLModel();
        GOL_Model* getModel(int index);
};


#endif // GOL_MODEL_MANAGER_H_
