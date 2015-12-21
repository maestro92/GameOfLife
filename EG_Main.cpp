#include "EG_Main.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "SDL\SDL.h"

using namespace std;

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


ExplosionGenerator::ExplosionGenerator()
{
    isRunning = true;
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
    m_rm.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    tempTexture = EG_Utility::loadTexture("Assets/Images/tank1B.png");
}


void ExplosionGenerator::initObjects()
{
    m_gridSize = 5;
    m_board = GameBoard(SCREEN_WIDTH-200, SCREEN_HEIGHT, m_gridSize);

    int x = SCREEN_WIDTH - 200;
    int y = 0;
    int w = 200;
    int h = SCREEN_HEIGHT;
    m_GUIManager.init(SCREEN_WIDTH, SCREEN_HEIGHT, x, y, w, h);

  //  m_GOLSquare = GOL_Square(1, 1, m_gridSize);
  //  m_GOLSquareOutline = GOL_SquareOutline(5, 5, m_gridSize);
}


void ExplosionGenerator::initModels()
{
//    m_GOLSquare = GOL_Model(GOL_Model::generateSquareGridModel(1), m_gridSize);
//    m_GOLSquareOutline = GOL_Model(GOL_Model::generateSquareOutlineGridModel(5), m_gridSize);

    m_GOLModelManager.init(m_gridSize);
    m_GOLModelPtr = m_GOLModelManager.getDefaultGOLModel();
/*
    m_GOLModelTitles.push_back("Default Square");
    m_GOLModelTitles.push_back("Square Outline");
    m_GOLModelTitles.push_back("Space Ship");

    m_GOLModelMenu.push_back(new GOL_Model(GOL_Model::generateSquareGridModel(1), m_gridSize));
    m_GOLModelMenu.push_back(new GOL_Model(GOL_Model::generateSquareOutlineGridModel(5), m_gridSize));
    m_GOLModelMenu.push_back(new GOL_Model(GOL_Model::generateSpaceShipModel(), m_gridSize));
    m_GOLModelMenu.push_back(&m_GOLSquareOutline);
*/
}


void ExplosionGenerator::initGUI()
{
    m_GUIComponentsFlags = 0;

    EG_Control::m_textEngine.initialize();

    int X_OFFSET = 600;

    int SLIDER_HEIGHT = 35;
    int BUTTON_WIDTH = 200;
    int BUTTON_HEIGHT = 35;

/*
    m_particleCountSlider.setID(m_GUIComponentsIDs);
    m_particleCountSlider.setRect(X_OFFSET, 400, BUTTON_WIDTH, SLIDER_HEIGHT);
    m_particleCountSlider.setColor(DARK_GRAY);
    m_particleCountSlider.setSliderColor(GREEN);
    m_particleCountSlider.setText("Particle Count");
    m_particleCountSlider.setValue(&m_particleCount);
    m_particleCountSlider.setMaxValue(100);
    m_particleCountSlider.setMinValue(0.5);
    m_particleCountSlider.setValueType(EG_Slider::INT_TYPE);
    m_particleCountSlider.initColoredQuad();
    m_GUIComponents.push_back(&m_particleCountSlider);
*/

/*
    m_smokeSizeSlider.setID(m_GUIComponentsIDs);
    m_smokeSizeSlider.setRect(X_OFFSET, 250, BUTTON_WIDTH, SLIDER_HEIGHT);
    m_smokeSizeSlider.setColor(DARK_GRAY);
    m_smokeSizeSlider.setSliderColor(GREEN);
    m_smokeSizeSlider.setText("Smoke Size");
    m_smokeSizeSlider.setValue(&m_smokeSize);
    m_smokeSizeSlider.setMaxValue(20);
    m_smokeSizeSlider.setMinValue(2);
    m_smokeSizeSlider.initColoredQuad();
    m_GUIComponents.push_back(&m_smokeSizeSlider);
*/
    m_resetButton = EG_Button("Reset", X_OFFSET, 200, BUTTON_WIDTH, BUTTON_HEIGHT, BLUE);
    m_resetButton.setColors(BLUE, GREEN, RED);
    m_resetButton.setID(m_GUIComponentsIDs);
    m_GUIComponents.push_back(&m_resetButton);

    m_triggerButton = EG_Button("EXPLODE!", X_OFFSET, 0, BUTTON_WIDTH, BUTTON_HEIGHT, BLUE);
    m_triggerButton.setColors(GREEN, BLUE, RED);
    m_triggerButton.setID(m_GUIComponentsIDs);
    m_GUIComponents.push_back(&m_triggerButton);

    m_GUIManager.m_GOLModelListBox.setID(m_GUIComponentsIDs);
    m_GUIComponents.push_back(&m_GUIManager.m_GOLModelListBox);
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
                    break;

                case SDL_MOUSEBUTTONUP:
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            cout << "clicking Up left" << endl;
                            m_mouseState.m_leftButtonDown = false;
                            SDL_GetMouseState(&tmpx,&tmpy);
                            break;

                        case SDL_BUTTON_RIGHT:
                            cout << "clicking Up right" << endl;
                            m_mouseState.m_rightButtonDown = false;
                            SDL_GetMouseState(&tmpx,&tmpy);
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
                            SDL_GetMouseState(&tmpx,&tmpy);
                            m_mouseState.m_leftButtonDown = true;
                            break;

                        case SDL_BUTTON_RIGHT:
                            cout << "clicking right" << endl;
                            SDL_GetMouseState(&tmpx,&tmpy);
                            m_mouseState.m_rightButtonDown = true;
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {

                    }
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            isRunning = false;
                            break;

                        case SDLK_SPACE:
                            if(m_inputMode)
                                m_switchFlag = true;
                            m_inputMode = !m_inputMode;
                            break;

                        case SDLK_r:
                            EG_Utility::debug("pressing R");



                            break;
                    }
                    break;


			}
        }
            update();
            forwardRender();
            SDL_GL_SwapBuffers();
            int a = 1;

            if(!m_inputMode)
            {
                next_game_tick += INTERVAL;
                delay_time = next_game_tick - SDL_GetTicks();

                if (next_game_tick > SDL_GetTicks())
                    SDL_Delay(next_game_tick - SDL_GetTicks());
                next_game_tick = SDL_GetTicks() + INTERVAL;
            }


    }
}


void ExplosionGenerator::update()
{
    float fDeltaTime = m_timeManager.GetElapsedTime();

    int mx, my;
    SDL_GetMouseState(&mx,&my);
    EG_Utility::debug("mouse is", glm::vec2(mx, SCREEN_HEIGHT - my));

    m_mouseState.m_pos = glm::vec2(mx, SCREEN_HEIGHT - my);

    bool sliding = false;
    bool b = false;

//    std::bitset<32> flag(m_GUIComponentsFlags);
//    cout << flag << endl;


  //  if(m_GUIComponentsFlags == 0)

//    sliding = m_particleCountSlider.update(m_mouseState, m_GUIComponentsFlags) || m_maxRadiusSlider.update(m_mouseState, m_GUIComponentsFlags);
//    sliding = m_velocitySlider.update(m_mouseState, m_GUIComponentsFlags);
//    sliding = m_smokeSizeSlider.update(m_mouseState, m_GUIComponentsFlags);
    b = m_triggerButton.update(m_mouseState, m_GUIComponentsFlags);
    b = m_resetButton.update(m_mouseState, m_GUIComponentsFlags);

    b = m_GUIManager.m_GOLModelListBox.update(m_mouseState);

    int index = m_GUIManager.m_GOLModelListBox.getIndex();
    m_GOLModelPtr = m_GOLModelManager.getModel(index);

    // m_GOLModelPtr = m_GOLModelMenu[m_GUIManager.m_GOLModelListBox.getIndex()];

    // if(m_GOLModelListBox.getIndex())

    if(m_inputMode)
    {
        r_Technique = &m_rm.r_GOLUserInputWithPattern;
        // m_GOLModelPtr = &m_GOLSquareOutline;
        m_board.initUserInput(r_Technique, m_mouseState, m_GOLModelPtr);
//        m_board.initUserInput(r_Technique, m_mouseState, m_GOLModelPtr, m_GOLModelManager.getModel(2)->getTexture());
        m_board.m_userInputBoardDoubleBuffer.swapFrontBack();
    }
    else
    {
        if(m_switchFlag)
        {
            r_Technique = &m_rm.r_GOLRenderIntermediate;
            m_board.renderInputToSimulation(r_Technique);
            m_switchFlag = false;
        }

        r_Technique = &m_rm.r_GOLUpdate;
        m_board.update(r_Technique);
        m_board.m_simulationDoubleBuffer.swapFrontBack();
    }

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
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(0.1,0.1,0.1,1.0);
//    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if(m_inputMode)
    {
        r_Technique = &m_rm.r_GOLRenderInputWithPattern;
    //    m_GOLModelPtr = &m_GOLSquareOutline;
//        m_GOLModelPtr = &m_GOLSquare;
//        m_board.initUserInput(r_Technique, m_mouseState, m_GOLModelManager.getModel(2)->getTexture());

    //    m_board.renderInput(r_Technique, m_mouseState, m_GOLModelPtr);
    //      m_board.renderInput(r_Technique, m_mouseState, m_GOLModelPtr, m_GOLModelManager.getModel(2)->getTexture());
          m_board.renderInput(r_Technique, m_mouseState, m_GOLModelPtr);
    }
    else
    {
        r_Technique = &m_rm.r_GOLRenderSimluation;
        m_board.renderSimulation(r_Technique);
    }



    renderGUI();
}

/*
void ExplosionGenerator::initGUIRenderStage()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    m_pipeline.reset();
    m_pipeline.matrixMode(PROJECTION_MATRIX);
    m_pipeline.loadIdentity();
    m_pipeline.ortho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);

    m_pipeline.matrixMode(MODEL_MATRIX);
    m_pipeline.loadIdentity();
}
*/

void ExplosionGenerator::initGUIRenderStage()
{
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    m_pipeline.reset();
    m_pipeline.matrixMode(PROJECTION_MATRIX);
    m_pipeline.loadIdentity();
    m_pipeline.ortho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);

    m_pipeline.matrixMode(MODEL_MATRIX);
    m_pipeline.loadIdentity();
}

void ExplosionGenerator::renderGUI()
{
    initGUIRenderStage();

    /// http://sdl.beuc.net/sdl.wiki/SDL_Average_FPS_Measurement
    unsigned int getTicks = SDL_GetTicks();
    m_timeManager.addTick(getTicks);
    m_fps = m_timeManager.computeAverageFPS();

    string final_str = "(" + EG_Utility::floatToStr(m_mouseState.m_pos.x) + ", " + EG_Utility::floatToStr(m_mouseState.m_pos.y) + ")";
    EG_Control::m_textEngine.render(m_pipeline, 0, 10, final_str.c_str());

    glDisable(GL_BLEND);


    m_rm.renderTextureSingle(m_GUIManager.getGUIPaletteTexture(), 0, m_GUIManager.m_paletteRect);// SCREEN_WIDTH - 200, 0, 200, SCREEN_HEIGHT);

    /// render Each GUI component
    r_Technique = &m_rm.r_RectRenderer;

    for(int i=0; i<m_GUIComponents.size(); i++)
    {
        EG_Control* control = m_GUIComponents[i];
        control->render(m_pipeline, r_Technique);
    }

/*
    m_rm.r_ButtonRenderer.enableShader(RENDER_PASS1);
    m_rm.r_ButtonRenderer.setData(RENDER_PASS1, "u_color", glm::vec3(1.0,0.0,0.0));

    m_pipeline.pushMatrix();
        m_pipeline.translate(m_triggerButton.m_rect.x, m_triggerButton.m_rect.y, 0);
        m_pipeline.scale(m_triggerButton.m_rect.w, m_triggerButton.m_rect.h, 1.0);

        m_rm.r_ButtonRenderer.loadUniformLocations(m_pipeline, RENDER_PASS1);
        m_rm.m_textureQuad.render();
    m_pipeline.popMatrix();
    m_rm.r_ButtonRenderer.disableShader(RENDER_PASS1);
*/
//    m_rm.renderTexture(m_GOLModelManager.getModel(2)->getTexture(), 0, m_GUIManager.m_paletteRect);// SCREEN_WIDTH - 200, 0, 200, SCREEN_HEIGHT);
//    m_rm.renderTexture(tempTexture, 0, m_GUIManager.m_paletteRect);// SCREEN_WIDTH - 200, 0, 200, SCREEN_HEIGHT);

 //   m_rm.renderTexture(m_GUIManager.getGUIPaletteTexture(), 0, m_GUIManager.m_paletteRect);// SCREEN_WIDTH - 200, 0, 200, SCREEN_HEIGHT);
}
