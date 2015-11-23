#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_


#include "define.h"
#include "EG_QuadModelABS.h"
#include "EG_GeneralRenderer.h"
#include "EG_WorldObject.h"

using namespace std;

enum BufferId
{
    FRONT = 0,
    BACK
};

class GameBoard
{
    private:
        int m_numGridsX;
        int m_numGridsY;
        float m_width;
        float m_height;
        float m_inverseWidth;
        float m_inverseHeight;

        int m_gridSize;

        WorldObject o_quadObject;
        EG_QuadModelABS m_boardQuadModel;

        vector<vector<bool>> m_grids;

    public:
        EG_DoubleFrameBufferObject m_boardDisplayBuffer;
        EG_DoubleFrameBufferObject m_simulationDoubleBuffer;

        GameBoard() : GameBoard(20, 20, 1)
        {}

        GameBoard(int w, int h, int s);

        int getWidth();
        int getHeight();
        int getGridSize();

        void setWidth(int w);
        void setHeight(int h);
        void setGridSize(int s);

        bool getBoard(int x, int y);


        GLuint getColorTexture(int id);
        void attachFBO(int id);
//        void initUserInput(EG_GeneralRenderer* renderer);
//        void initUserInput(EG_GeneralRenderer& renderer, glm::vec2 pos);
        void initUserInput(EG_GeneralRenderer& renderer, MouseState& mouseState);

        void update(EG_GeneralRenderer& renderer);
        void render(EG_GeneralRenderer& renderer);


};


#endif
