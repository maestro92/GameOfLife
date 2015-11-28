#include "EG_Main.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "SDL\SDL.h"

using namespace std;



#define NBP_SMOKE_EFFECT 0
#define NBP_SMOKE_EFFECT_GPU 0
#define INSTANCED_RENDERING 1

// https://www.youtube.com/watch?v=tlXM8qDOS3U
// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// frame rate
// https://sites.google.com/site/sdlgamer/intemediate/lesson-7
// FPS is 50
const int FRAMES_PER_SECOND = 60;
// So Interval is 1000/50 which is 20ms
// meaning my while loop runs 50 frames per second
// which is every other 20 ms
const int INTERVAL = 1000 / FRAMES_PER_SECOND;

//display surface
SDL_Surface* pDisplaySurface = NULL;
//event structure
SDL_Event event;


static float runningTime = 0.0f;
bool space_bar = false;
int flag = 0;
int inc_flag = 1;


ExplosionGenerator::ExplosionGenerator()
{
    angle = 0;
    isRunning = true;
    isFirstPersonCamera     = false;
    isStencilTextureMode    = false;
    isDepthTextureMode      = false;
    dvel                    = false;
    addSmoke                = false;
    holdKeyFlag             = false;
    toggleFlag              = false;
    overrideAddSmokeFlag    = false;

    m_increaseFlag = false;
    m_decreaseFlag = false;
    m_explodeFlag = false;
    m_inputMode = true;
    m_switchFlag = false;

    m_GUIComponentsFlags = 0;
    m_GUIComponentsIDs = 0;


    initRenderers();
    initObjects();
    initModels();
    initGUI();

    m_smokeSize = 10;
    m_testintSmokeMode = false;


    SDL_WM_SetCaption("Template", NULL);
}



ExplosionGenerator::~ExplosionGenerator()
{

}

void ExplosionGenerator::initOpenGL()
{
    //Initialize clear color
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    m_pipeline.ortho(-1, 1, -1, 1, 0.5, 1000); //==glOrtho
    m_pipeline.matrixMode(MODEL_MATRIX);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}





void ExplosionGenerator::initRenderers()
{
    m_rm.init();
    r_instancedRenderer.init(2);

    m_board = GameBoard(SCREEN_WIDTH, SCREEN_HEIGHT, 50);

    tempTexture = EG_Utility::loadTexture("Assets/Images/Scroll.png");
}



void ExplosionGenerator::initObjects()
{

}


void ExplosionGenerator::initModels()
{

}


void ExplosionGenerator::initGUI()
{
    m_GUIComponentsFlags = 0;

    EG_Control::m_textEngine.initialize();

    int X_OFFSET = 10;

    int SLIDER_HEIGHT = 35;
    int BUTTON_WIDTH = 200;
    int BUTTON_HEIGHT = 35;

    m_particleCountSlider.setID(m_GUIComponentsIDs);
    m_particleCountSlider.setRect(X_OFFSET, 400, BUTTON_WIDTH, SLIDER_HEIGHT);
    m_particleCountSlider.setColor(DARK_GRAY);
    m_particleCountSlider.setSliderColor(GREEN);
    m_particleCountSlider.setLabel("Particle Count");
    m_particleCountSlider.setValue(&m_particleCount);
    m_particleCountSlider.setMaxValue(100);
    m_particleCountSlider.setMinValue(0.5);
    m_particleCountSlider.setValueType(EG_Slider::INT_TYPE);
    m_particleCountSlider.initColoredQuad();
    m_GUIComponents.push_back(&m_particleCountSlider);


    m_smokeSizeSlider.setID(m_GUIComponentsIDs);
    m_smokeSizeSlider.setRect(X_OFFSET, 250, BUTTON_WIDTH, SLIDER_HEIGHT);
    m_smokeSizeSlider.setColor(DARK_GRAY);
    m_smokeSizeSlider.setSliderColor(GREEN);
    m_smokeSizeSlider.setLabel("Smoke Size");
    m_smokeSizeSlider.setValue(&m_smokeSize);
    m_smokeSizeSlider.setMaxValue(20);
    m_smokeSizeSlider.setMinValue(2);
    m_smokeSizeSlider.initColoredQuad();
    m_GUIComponents.push_back(&m_smokeSizeSlider);


    m_resetButton.setID(m_GUIComponentsIDs);
    m_resetButton.setRect(X_OFFSET, 200, BUTTON_WIDTH, BUTTON_HEIGHT);
    m_resetButton.setLabel("Reset");
    m_resetButton.setColor(GRAY);
    m_resetButton.initColoredQuad();
    m_GUIComponents.push_back(&m_resetButton);


    m_triggerButton.setID(m_GUIComponentsIDs);
    m_triggerButton.setRect(X_OFFSET, 150, BUTTON_WIDTH, BUTTON_HEIGHT);
    m_triggerButton.setLabel("EXPLODE!");
    m_triggerButton.setColor(GRAY);
    m_triggerButton.initColoredQuad();
    m_GUIComponents.push_back(&m_triggerButton);
}


void ExplosionGenerator::initFrameBuffers()
{

}


void ExplosionGenerator::start()
{
    cout << "Start" << endl;

    Uint32 startTime = SDL_GetTicks();
    Uint32 next_game_tick = 0;
    Uint32 delay_time = 0;

 //   m_timeManager.m_startTime = SDL_GetTicks();
    m_timeManager.setStartTime(SDL_GetTicks());
//    m_startTime = SDL_GetTicks();


    while(isRunning)
    {
        startTime = SDL_GetTicks();

        while(SDL_PollEvent(&event))
		{
            int tmpx,tmpy;
            switch(event.type)
			{
                case SDL_QUIT:
                    isRunning = false;
                    cout << "quitting game" << endl;
                    break;

                case SDL_MOUSEBUTTONUP:
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            cout << "clicking Up left" << endl;
                            m_orbitCamera.m_leftMouseDown = false;
                            m_mouseState.m_leftButtonDown = false;
                            SDL_GetMouseState(&tmpx,&tmpy);
                            m_orbitCamera.m_mousePrevious = glm::vec2(tmpx, tmpy);
                            break;

                        case SDL_BUTTON_RIGHT:
                            cout << "clicking Up right" << endl;
                            m_mouseState.m_rightButtonDown = false;
                            SDL_GetMouseState(&tmpx,&tmpy);
                            m_orbitCamera.m_mousePrevious = glm::vec2(tmpx, tmpy);
                            m_mouseState.m_rightButtonDown = false;

                            break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:

                    switch(event.button.button)
                    {
                        int tmpx,tmpy;
                        case SDL_BUTTON_LEFT:
                            cout << "clicking left" << endl;
                            m_orbitCamera.m_leftMouseDown = true;
                            SDL_GetMouseState(&tmpx,&tmpy);
                            m_mouseState.m_leftButtonDown = true;
                            break;

                        case SDL_BUTTON_RIGHT:
                            cout << "clicking right" << endl;
                            SDL_GetMouseState(&tmpx,&tmpy);
                            m_mouseState.m_rightButtonDown = true;
                            break;

                        case SDL_BUTTON_WHEELUP:
                            cout << "wheel up" << endl;
                            break;

                        case SDL_BUTTON_WHEELDOWN:
                            cout << "wheel down" << endl;
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_x:
                            overrideAddSmokeFlag = false;
                            addSmoke = false;
                            break;

                        case SDLK_o:
                            holdKeyFlag = false;
                            break;

                        case SDLK_e:
                            m_increaseFlag = false;
                            break;

                        case SDLK_q:
                            m_decreaseFlag = false;
                            break;
                    }
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:   isRunning = false;    break;
                        case SDLK_z:
                            m_orbitCamera.m_pivotOffset.y = 3.0f;


//                            space_bar = false;
                            m_explodeFlag = false;
                            addSmoke = false;
                            break;
                        case SDLK_SPACE:
                            m_explodeFlag = true;
                            m_smokeStartTime = SDL_GetTicks();
                            addSmoke = true;


                            if(m_inputMode)
                                m_switchFlag = true;
                            m_inputMode = !m_inputMode;

  //                          space_bar = true;
                            break;
                        case SDLK_v:
                            dvel = !dvel;
                            break;
                        case SDLK_e:
                            m_increaseFlag = true;
                     //       EG_Utility::printGlm("Here", m_orbitCamera.m_pivotOffset);
                            break;

                        case SDLK_q:
                            m_decreaseFlag = true;
                            break;


                        case SDLK_l:
                            isDepthTextureMode = !isDepthTextureMode;
                            break;
                        case SDLK_m:
                            isFirstPersonCamera = !isFirstPersonCamera;
                            break;
                        case SDLK_n:
                            isStencilTextureMode = !isStencilTextureMode;
                            break;

                        case SDLK_i:
                            toggleFlag = !toggleFlag;
                            break;

                        case SDLK_o:
                            holdKeyFlag = true;
                            break;

                        case SDLK_p:
                            firstPersonPovCamera.setMouseInFlag(false);
//                            myThirdPOV_camera.mouseIn(false);
                            break;
                        case SDLK_x:
                            cout << "here" << endl;
                            overrideAddSmokeFlag = true;
                            addSmoke = true;
                    }
                    break;
			}
        }
            update();
            forwardRender();
            SDL_GL_SwapBuffers();
    }
}


void ExplosionGenerator::update()
{
  //  m_GUIComponentsFlags = 0;
    float fDeltaTime = m_timeManager.GetElapsedTime();
    angle+=0.05f;

    int mx, my;
    SDL_GetMouseState(&mx,&my);
    m_mouseState.m_pos = glm::vec2(mx, SCREEN_HEIGHT - my);


    // r_Technique = &m_rm.r_GOLUpdate;


    if(m_inputMode)
    {
        r_Technique = &m_rm.r_GOLUserInput;
        m_board.initUserInput(r_Technique, m_mouseState);
        m_board.m_userInputBoardDoubleBuffer.swapFrontBack();
    }
    else
    {
        if(m_switchFlag)
        {
            r_Technique = &m_rm.r_GOLRenderIntermediate;
            m_board.renderInputToSimulation(r_Technique, m_board.m_inputToSimulationRenderInfo);
            m_switchFlag = false;
        }

//        cout << "update not inputMode" << endl;


        r_Technique = &m_rm.r_GOLUpdate;
        m_board.update(r_Technique);
        m_board.m_simulationDoubleBuffer.swapFrontBack();
    }
    // smoke.SwapSurfaces(&VelocityField);
/*
    r_Technique = &m_rm.r_textureRenderer;
    m_rm.r_textureRenderer.setData(RENDER_PASS1, "u_texture", 0,
                                                  GL_TEXTURE0,
                                                  m_board.getColorTexture(0));
    o_fullScreenQuad.render(r_Technique, RENDER_PASS1, RENDER_TO_SCREEN);
*/
    runningTime = (float)((double)SDL_GetTicks() - (double)m_timeManager.getStartTime()) / 1000.0f;
}






int main(int argc, char *argv[])
{
    EG_Utility::initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, pDisplaySurface);
    EG_Utility::initGLEW();

    ExplosionGenerator Martin;
    Martin.start();

    EG_Utility::exitSDL(pDisplaySurface);
    //normal termination
    cout << "Terminating normally." << endl;
    return EXIT_SUCCESS;
}





void ExplosionGenerator::forwardRender()
{
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(1.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if(m_inputMode)
    {
        r_Technique = &m_rm.r_GOLRenderInput;
        m_board.renderInput(r_Technique);
    }
    else
    {
        r_Technique = &m_rm.r_GOLRenderSimluation;
        m_board.renderSimulation(r_Technique);
    }
/*
        pipeline temp_pipeline;
        temp_pipeline.loadIdentity();
        temp_pipeline.ortho(-1,1,-1,1,-1,1);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        m_rm.r_GOLRender.enableShader(RENDER_PASS1);
            m_rm.r_GOLRender.loadUniformLocations(temp_pipeline, RENDER_PASS1);
            m_board.m_boardQuadModel.render();
        m_rm.r_GOLRender.disableShader(RENDER_PASS1);
*/

    // m_board.m_boardQuadModel.render();



    /*
    glDisable(GL_CULL_FACE);
    glViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);


    m_pipeline.reset();
    m_pipeline.matrixMode(PROJECTION_MATRIX);
    m_pipeline.loadIdentity();
    m_pipeline.ortho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);

    m_pipeline.matrixMode(MODEL_MATRIX);
    m_pipeline.loadIdentity();


    board.render(m_rm.r_GOLRender);
*/
  //  renderGUI();
}



void ExplosionGenerator::getUserInput(glm::vec2 position)
{
    /*
    GLuint p = ApplyImpulse_shader->getProgramId();
    glUseProgram(p);

    GLint pointLoc = glGetUniformLocation(p, "Point");
    GLint radiusLoc = glGetUniformLocation(p, "Radius");
    GLint fillColorLoc = glGetUniformLocation(p, "FillColor");

    glUniform2f(pointLoc, (float) position.x, (float) position.y);
    glUniform1f(radiusLoc, SplatRadius);
    glUniform3f(fillColorLoc, value, value, value);

    glBindFramebuffer(GL_FRAMEBUFFER, dest.FboHandle);
    glEnable(GL_BLEND);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    ResetState();
    */
}




void ExplosionGenerator::renderGUI()
{
  //  initGUIRenderStage();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    /// http://sdl.beuc.net/sdl.wiki/SDL_Average_FPS_Measurement
    unsigned int getTicks = SDL_GetTicks();
    m_timeManager.addTick(getTicks);
    m_fps = m_timeManager.computeAverageFPS();

    string final_str = "Explosion Generator  FPS:" + EG_Utility::floatToStr(m_fps);
    EG_Control::m_textEngine.render(m_pipeline, 0, 10, final_str.c_str());

    /// render Each GUI component
    r_Technique = &m_rm.r_GUIRenderer;
    for(int i=0; i<m_GUIComponents.size(); i++)
    {
        EG_Control* control = m_GUIComponents[i];
        control->render(m_pipeline, r_Technique, RENDER_PASS1);
    }
}
