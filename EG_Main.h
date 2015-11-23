#ifndef _MAIN_H_
#define _MAIN_H_

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include "define.h"

#include "EG_PointLight.h"
#include "EG_SpotLight.h"
#include "EG_DirectionalLight.h"
#include "EG_AllLights.h"
#include "EG_ImportedAnimatedModel.h"
#include "EG_BillboardList.h"


#include "EG_DeferredShadingGeometryPass.h"
#include "EG_DeferredShadingSkybox.h"
#include "EG_DeferredShadingReflection.h"
#include "EG_DeferredShadingLightPos.h"
#include "EG_DeferredShadingStencilPass.h"
#include "EG_DeferredShadingPointLightPass.h"
#include "EG_DeferredShadingDirectionalLightPass.h"

#include "EG_GameBoard.h"

#include "EG_Emitter.h"



#include "EG_Camera.h"
#include "EG_FirstPersonPovCamera.h"
#include "EG_ThirdPersonPovCamera.h"
#include "EG_OrbitCamera.h"

#include "EG_Model.h"
#include "EG_ImportedModel.h"
#include "EG_InstancedModel.h"

#include "EG_DeferredShading.h"
#include "EG_GBuffer.h"

#include "EG_utility.h"
//#include "EG_Renderers/EG_Skybox.h"
#include "EG_Skybox.h"
#include "EG_Shader.h"
#include "sceneLoader.h"


/// GUI
#include "EG_Label.h"


/// Renderers
#include "EG_TwoPassRayCastingRenderer.h"
#include "EG_SceneRenderer.h"
#include "EG_ReflectionRenderer.h"
#include "EG_TextureRenderer.h"
#include "EG_SkinningRenderer.h"

#include "EG_InstancedRenderer.h"
#include "EG_BillboardRenderer.h"
#include "EG_ParticleSystemRenderer.h"
#include "EG_NoiseBasedParticleEffectRenderer.h"
#include "EG_NoiseBasedParticleEffectRendererGPU.h"

#include "EG_RendererManager.h"

#include "EG_WorldAnimatedObject.h"
#include "EG_FullScreenQuad.h"

#include "EG_Button.h"
#include "EG_XYZAxisModel.h"
#include "EG_WorldBox.h"
#include "EG_WorldSphere.h"
#include "EG_ListBox.h"
#include "EG_Slider.h"

#include "pipeline.h"

#include "EG_GeneralRenderer.h"

#include "L_Cube_Sphere_ParticleEffect.h"

#define NO_SDL_GLEXT
#include <GL/glew.h>
#include "SDL/SDL_opengl.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "EG_TimeManager.h"



#include "EG_Smoke.h"
#include "CollisionDetection_HGrid.h"


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
        EG_Renderer*                    r_Technique;
        EG_SceneRenderer                r_sceneRenderer;



        EG_SkinningRenderer                     r_skinning;
        EG_InstancedRenderer                    r_instancedRenderer;

        EG_BillboardRenderer                    r_billBoardRenderer;
        EG_TextureRenderer                      r_textureRenderer;



        /// GUI
        EG_Label m_frameRateLabel;
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

        EG_AllLights allLights;


        MouseState m_mouseState;
        GLuint VBO;
        GLuint FBO;
        GLuint FBO1;
        pipeline m_pipeline;

        // Material Property
        float m_specularIntensity;
        float m_specularPower;



        Smoke smoke;


        EG_FirstPersonPovCamera firstPersonPovCamera;
        EG_ThirdPersonPovCamera thirdPersonPovCamera;
        EG_OrbitCamera m_orbitCamera;




        EG_Model*   modelPtr;
        EG_ModelABS*    p_modelPtr;
        EG_XYZAxisModel m_axisModel;


        EG_InstancedModel  instancedSphere;


        EG_WorldAnimatedObject  o_animatedLegoMan;
        EG_WorldAnimatedObject  o_animatedBob;
        EG_FullScreenQuad       o_fullScreenQuad;

//        EG_QuadModelABS     o_fullScreenQuad;

        WorldObject     o_worldAxis;
        WorldBox        o_wall;

//        meshLoader* deferredShadingQuad;

        bool holdKeyFlag;
        bool toggleFlag;

        bool overrideAddSmokeFlag;

        float m_fps;
        float m_iterRefreshRate;
        float m_curIter;
        unsigned int m_frameCount;
        unsigned int m_frameTicks[FRAME_VALUES];
        unsigned int m_frameTicksIndex;
        unsigned int m_prevFrameTick;


        bool isRunning;
        bool isFirstPersonCamera;
        bool dvel;
        bool addSmoke;
        bool isStencilTextureMode;
        bool isDepthTextureMode;

        bool m_explodeFlag;

        float m_smokeStartTime;
        float m_smokeDuration;

        /// textures
        unsigned int depthTexture;






        /// Matrices
        bool m_increaseFlag;
        bool m_decreaseFlag;

        float angle;
        EG_Label m_lb;




        GLuint tempTexture;

        GameBoard m_board;
    public:
        ExplosionGenerator();
        ~ExplosionGenerator();


        /// init functions
        void initOpenGL();
        void initObjects();
        void initModels();
        void initRenderers();


        void initGUI();
        void initFrameBuffers();

        void start();
        void update();

        void forwardRender();
        void renderScene();
        void initGUIRenderStage();
        void getUserInput(glm::vec2 position);

        void renderShadowMap();
        void renderGUI();


        void initTransformFeedBackTest();
        void initTransformFeedBackTestBackup();

        void updateTransformFeedbackTest();
        void transformFeedBackTest();

};





#endif
