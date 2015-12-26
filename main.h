#ifndef MAIN_H_
#define MAIN_H_

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include "define.h"

#include "gol_model_manager.h"
#include "game_board.h"

#include "utility.h"
#include "shader.h"
#include "sceneLoader.h"


#include "label.h"


#include "gui_manager.h"
#include "slider.h"
#include "EG_Model.h"

#include "pipeline.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include "renderer_manager.h"
#include "general_renderer.h"


#define NO_SDL_GLEXT
#include <GL/glew.h>
#include "SDL/SDL_opengl.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "text_engine.h"




#define FRAME_VALUES 10

using namespace std;

/// For style
/// use http://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Function_Names


/// C++ style
/// http://geosoft.no/development/cppstyle.html


/// http://stackoverflow.com/questions/1228161/why-use-prefixes-on-member-variables-in-c-classes
///
/*
I use:

m for members
c for constants/readonlys
p for pointer (and pp for pointer to pointer)
v for volatile
s for static
i for indexes and iterators
e for events
*/



class ExplosionGenerator
{
    private:
        RendererManager              m_rm;
        Renderer*                    r_Technique;


        /// GUI
        Label m_GUIPanel;

        Button m_triggerButton;
        Button m_resetButton;
        Button m_minimizeButton;
        Button m_pauseButton;


        Slider m_smokeSizeSlider;
        float m_smokeSize;
        bool m_testintSmokeMode;

        Slider m_particleCountSlider;    float m_particleCount;
        Slider m_velocitySlider;         float m_velocity;
        Slider m_maxRadiusSlider;        float m_maxRadius;
        ListBox m_listBox;




        int m_GUIComponentsIDs;
        unsigned int m_GUIComponentsFlags;
        vector<Control*> m_GUIComponents;


        long long m_runningTime;
        MouseState m_mouseState;

        pipeline m_pipeline;


        bool m_inputMode;
        bool m_switchFlag;



        EG_Model*   modelPtr;
        EG_ModelABS*    p_modelPtr;


        float m_fps;
        float m_iterRefreshRate;
        float m_curIter;
        unsigned int m_frameCount;
        unsigned int m_frameTicks[FRAME_VALUES];
        unsigned int m_frameTicksIndex;
        unsigned int m_prevFrameTick;

        bool isRunning;


        GOLModel* m_GOLModelPtr;


   //     vector<string> m_GOLModelTitles;
   //     vector<GOLModel*> m_GOLModels;


        //GOL_Square m_GOLSquare;
        //GOL_SquareOutline m_GOLSquareOutline;

        int m_gridSize;

        GLuint tempTexture;


        GameBoard m_board;

        GUIManager m_gui;
        GOLModelManager m_GOLModelManager;
    public:



        ExplosionGenerator();
        ~ExplosionGenerator();

        /// init functions
        void initOpenGL();
        void initObjects();
        void initModels();
        void initRenderers();

        void initGUI();

        void start();
        void update();

        void forwardRender();
        void renderScene();
        void initGUIRenderStage();
        void getUserInput(glm::vec2 position);

        void renderGUI();

        void RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

        void startCB();
        void resetGameBoardCB();
        void GOLModelListBoxCB();
};





#endif
