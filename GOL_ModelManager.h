#ifndef GOL_MODEL_MANAGER_H_
#define GOL_MODEL_MANAGER_H_

#include "utility.h"
#include "GOL_Model.h"

class GOL_ModelManager
{
    public:
        void init(int gs);
        TextureDataBuffer generateSquareGridModel(int gs);
        TextureDataBuffer generateSquareOutlineGridModel(int gs);
        TextureDataBuffer readModelFromFile(string filename);

        GOL_Model* getDefaultGOLModel();
        GOL_Model* getModel(int index);
        vector<GOL_Model*> getModels();

    private:
        vector<GOL_Model*> m_GOLModels;
        string getFilePath(string filename);
};


#endif // GOL_MODEL_MANAGER_H_
