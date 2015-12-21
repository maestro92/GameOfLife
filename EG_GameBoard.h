#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_


#include "define.h"
#include "EG_QuadModelABS.h"
#include "EG_GeneralRenderer.h"
#include "EG_WorldObject.h"
#include "GOL_Model.h"

using namespace std;

enum BufferId
{
    FRONT = 0,
    BACK
};

enum FBOTargetId
{
    INPUT = 0,
    SIMULATION
};

class GameBoard
{
    // private:
    public:
        struct RenderInfo
        {
            int width;
            int height;
            GLuint srcTexture;
            GLuint FBOtarget;
            int srcPresentValue;
            int srcEmptyValue;
            int dstPresentValue;
            int dstEmptyValue;

            RenderInfo()
            { }

            void set(int w, int h, GLuint srcTx, GLuint fbo, int rpv, int wpv)
            {
                width = w;
                height = h;

                srcTexture = srcTx;
                FBOtarget = fbo;

                srcPresentValue = rpv;
                srcEmptyValue = 1 - rpv;

                dstPresentValue = wpv;
                dstEmptyValue = 1 - wpv;
            }
        };

        int m_numGridsX;
        int m_numGridsY;
        float m_width;
        float m_height;
        float m_inverseWidth;
        float m_inverseHeight;

        int m_gridSize;
        float m_invGridSize;

        RenderInfo m_inputToSimulationRenderInfo;
        RenderInfo m_simulationToInputRenderInfo;

        WorldObject o_quadObject;
        EG_QuadModelABS m_boardQuadModel;

        vector<vector<bool>> m_grids;

    public:
        EG_DoubleFrameBufferObject m_userInputBoardDoubleBuffer;
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

        void inputToSimluationBoard(EG_Renderer* renderer);
        void initUserInput(EG_Renderer* renderer, MouseState& mouseState, GOL_Model* pattern);
        void initUserInput(EG_Renderer* renderer, MouseState& mouseState, GOL_Model* pattern, GLuint texture);
        void update(EG_Renderer* renderer);

        void renderInput(EG_Renderer* renderer, MouseState& mouseState, GOL_Model* pattern);
        void renderInput(EG_Renderer* renderer, MouseState& mouseState, GOL_Model* pattern, GLuint texture);


        void renderInputToSimulation(EG_Renderer* renderer);
        void renderSimulationToInput(EG_Renderer* renderer);
        void renderIntermediate(EG_Renderer* renderer, RenderInfo& rInfo);

        void renderSimulation(EG_Renderer* renderer, FBOTargetId target);
        void renderSimulation(EG_Renderer* renderer, GLuint fboTarget);
        void renderSimulation(EG_Renderer* renderer);
        glm::vec2 screenCoordToBoardCoord(glm::vec2 pos);
};


#endif
