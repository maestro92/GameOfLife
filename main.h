#ifndef _MAIN_H_
#define _MAIN_H_

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include "define.h"

#include "GOL_ModelManager.h"
#include "game_board.h"
#include "EG_Emitter.h"


#include "EG_Model.h"
#include "EG_ImportedModel.h"
#include "EG_InstancedModel.h"

#include "EG_GBuffer.h"

#include "utility.h"
#include "shader.h"
#include "sceneLoader.h"


#include "EG_Label.h"



#include "EG_RendererManager.h"

#include "EG_WorldAnimatedObject.h"

#include "gui_manager.h"
#include "EG_Button.h"
#include "EG_XYZAxisModel.h"
#include "EG_WorldBox.h"
#include "EG_WorldSphere.h"
#include "EG_ListBox.h"
#include "EG_Slider.h"

#include "pipeline.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "general_renderer.h"


#define NO_SDL_GLEXT
#include <GL/glew.h>
#include "SDL/SDL_opengl.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "EG_TimeManager.h"

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
        EG_RendererManager              m_rm;
        Renderer*                    r_Technique;


        /// GUI
        EG_Label m_GUIPanel;

        EG_Button m_triggerButton;
        EG_Button m_resetButton;
        EG_Button m_minimizeButton;
        EG_Button m_pauseButton;


        EG_Slider m_smokeSizeSlider;
        float m_smokeSize;
        bool m_testintSmokeMode;

        EG_Slider m_particleCountSlider;    float m_particleCount;
        EG_Slider m_velocitySlider;         float m_velocity;
        EG_Slider m_maxRadiusSlider;        float m_maxRadius;
        EG_ListBox m_listBox;




        int m_GUIComponentsIDs;
        unsigned int m_GUIComponentsFlags;
        vector<EG_Control*> m_GUIComponents;


        EG_TimeManager m_timeManager;
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


        GOL_Model* m_GOLModelPtr;
        GOL_Model m_GOLSquare;
        GOL_Model m_GOLSquareOutline;
        GOL_Model m_GOLSpaceShip;

   //     vector<string> m_GOLModelTitles;
   //     vector<GOL_Model*> m_GOLModels;


        //GOL_Square m_GOLSquare;
        //GOL_SquareOutline m_GOLSquareOutline;

        int m_gridSize;
        EG_Label m_lb;

        GLuint tempTexture;
        GLuint tex;

        GameBoard m_board;

        TextEngine m_text;
        GUIManager m_gui;
        GOL_ModelManager m_GOLModelManager;
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
};





#endif
