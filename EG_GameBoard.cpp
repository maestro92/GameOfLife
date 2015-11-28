#include "EG_GameBoard.h"


/*


*/
GameBoard::GameBoard(int w, int h, int s)
{
    if(w%s != 0 || h%s !=0)
    {
        cout << " GameBoard size is not a factor of width or height" << endl;
        exit(1);
    }

    setWidth(w);
    setHeight(h);
    setGridSize(s);

    m_numGridsX = w/s;
    m_numGridsY = h/s;

    m_inverseWidth = 1/(float)w;
    m_inverseHeight = 1/(float)h;
//    m_boardQuadModel.init(-0.5, 1, -1, 1,
//                            0.0, 0.0, 1.0);

    m_boardQuadModel.init(-1, 1, -1, 1,
                          0.0, 0.0, 1.0);

    m_userInputBoardDoubleBuffer = EG_Utility::createDoubleFrameBufferObject(w, h);
    m_userInputBoardDoubleBuffer.clear(glm::vec4(1.0,1.0,1.0,1.0));

    m_simulationDoubleBuffer = EG_Utility::createDoubleFrameBufferObject(m_numGridsX, m_numGridsY);
    m_simulationDoubleBuffer.clear();
    /*
    attachFBO(FRONT);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    attachFBO(BACK);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
*/

/*
    attachFBO(FRONT);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    attachFBO(BACK);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
*/

    m_inputToSimulationRenderInfo.set(m_numGridsX, m_numGridsY,
                                        m_userInputBoardDoubleBuffer.ping.colorTexture,
                                        m_simulationDoubleBuffer.ping.FBO, 0, 1);
 //   m_inputToScreenRenderInfo.set(m_width, m_height, RENDER_TO_SCREEN, 0, 0);

    m_simulationToInputRenderInfo.set(m_width, m_height,
                                        m_simulationDoubleBuffer.ping.colorTexture,
                                        m_userInputBoardDoubleBuffer.ping.FBO, 1, 0);
  //  m_simulationToScreenRenderInfo.set(m_width, m_height, RENDER_TO_SCREEN, 1, 0);
}

void GameBoard::setWidth(int w)
{
    m_width = w;
}

void GameBoard::setHeight(int h)
{
    m_height = h;
}

void GameBoard::setGridSize(int s)
{
    m_gridSize = s;
}

int GameBoard::getWidth()
{
    return m_width;
}

int GameBoard::getHeight()
{
    return m_height;
}

int GameBoard::getGridSize()
{
    return m_gridSize;
}

bool GameBoard::getBoard(int x, int y)
{
    return m_grids[y][x];
}


void GameBoard::initUserInput(EG_Renderer* renderer, MouseState& mouseState)
{
//    glViewport(0, 0, m_width, m_height);
//    glBindFramebuffer(GL_FRAMEBUFFER, doubleBoardBuffer.ping.colorTexture);
 //   glBindFramebuffer(GL_FRAMEBUFFER, m_doubleBoardBuffer.pong.FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_userInputBoardDoubleBuffer.pong.FBO);

    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //  attachBuffer(FRONT);
    glm::vec2 pos = mouseState.m_pos;

    float sx = floor(pos.x / m_gridSize);
    sx *= m_gridSize;

    float sy = floor(pos.y / m_gridSize);
    sy *= m_gridSize;

    float ex = sx + m_gridSize;
    float ey = sy + m_gridSize;

    renderer->enableShader(RENDER_PASS1);

//        renderer->setData(RENDER_PASS1, "u_startGridX", sx);
        renderer->setData(RENDER_PASS1, "u_boardTexture", 0, GL_TEXTURE0, m_userInputBoardDoubleBuffer.ping.colorTexture);
        renderer->setData(RENDER_PASS1, "u_startGridX", sx);
        renderer->setData(RENDER_PASS1, "u_startGridY", sy);
        renderer->setData(RENDER_PASS1, "u_endGridX", ex);
        renderer->setData(RENDER_PASS1, "u_endGridY", ey);
        renderer->setData(RENDER_PASS1, "u_invWidth", m_inverseWidth);
        renderer->setData(RENDER_PASS1, "u_invHeight", m_inverseHeight);
        renderer->setData(RENDER_PASS1, "u_mouseLeftBtnDown", mouseState.m_leftButtonDown);
//        renderer->setData(RENDER_PASS1, "u_boardTexture", 0, GL_TEXTURE0, m_board.getColorTexture(0));

        renderer->loadUniformLocations(RENDER_PASS1);
        m_boardQuadModel.render();
    renderer->disableShader(RENDER_PASS1);
}


void GameBoard::update(EG_Renderer* renderer)
{
    glViewport(0, 0, m_numGridsX, m_numGridsY);
    glBindFramebuffer(GL_FRAMEBUFFER, m_simulationDoubleBuffer.pong.FBO);

    renderer->enableShader(RENDER_PASS1);
        renderer->setData(RENDER_PASS1, "u_sourceTexture", 0, GL_TEXTURE0, m_simulationDoubleBuffer.ping.colorTexture);
        renderer->loadUniformLocations(RENDER_PASS1);
        m_boardQuadModel.render();
    renderer->disableShader(RENDER_PASS1);
}

void GameBoard::renderInput(EG_Renderer* renderer, FBOTargetId target)
{
    if(target == SIMULATION)
    {
        glViewport(0, 0, m_numGridsX, m_numGridsY);
        renderInput(renderer, m_simulationDoubleBuffer.ping.FBO);
    }

    else if (target == INPUT)
    {
        cout << "invalid target in renderInput" << endl;
        exit(1);
    }

    else
    {
        glViewport(0, 0, m_width, m_height);
        renderInput(renderer, 0);
    }
}

void GameBoard::renderInput(EG_Renderer* renderer, GLuint target)
{
    glBindFramebuffer(GL_FRAMEBUFFER, target);

    /*
        the parameters of the ortho should match the dimensions of the quadModel
        if quadModel is init    left:0  right:1
                                bot:0   top:1

        then the ortho should also be
                                left:0  right:1
                                bot:0   top:1
    */
    pipeline temp_pipeline;
    temp_pipeline.loadIdentity();
    temp_pipeline.ortho(-1,1,-1,1,-1,1);

    renderer->enableShader(RENDER_PASS1);
        renderer->setData(RENDER_PASS1, "u_inputTexture", 0,
                                        GL_TEXTURE0,
                                        m_userInputBoardDoubleBuffer.ping.colorTexture);

        renderer->loadUniformLocations(temp_pipeline, RENDER_PASS1);
        m_boardQuadModel.render();

    renderer->disableShader(RENDER_PASS1);
}


void GameBoard::renderInput(EG_Renderer* renderer)
{
    renderInput(renderer, 0);
}


void GameBoard::renderInputToSimulation(EG_Renderer* renderer, RenderInfo& rInfo)
{
    glViewport(0, 0, rInfo.width, rInfo.height);
    glBindFramebuffer(GL_FRAMEBUFFER, rInfo.FBOtarget);

    pipeline temp_pipeline;
    temp_pipeline.loadIdentity();
    temp_pipeline.ortho(-1,1,-1,1,-1,1);

    renderer->enableShader(RENDER_PASS1);
        renderer->setData(RENDER_PASS1, "u_sourceTexture", 0, GL_TEXTURE0, rInfo.srcTexture);
        renderer->setData(RENDER_PASS1, "u_srcPresentValue", rInfo.srcPresentValue);
        renderer->setData(RENDER_PASS1, "u_srcEmptyValue", rInfo.srcEmptyValue);
        renderer->setData(RENDER_PASS1, "u_dstPresentValue", rInfo.dstPresentValue);
        renderer->setData(RENDER_PASS1, "u_dstEmptyValue", rInfo.dstEmptyValue);

        renderer->loadUniformLocations(temp_pipeline, RENDER_PASS1);
        m_boardQuadModel.render();

    renderer->disableShader(RENDER_PASS1);

}











void GameBoard::renderSimulation(EG_Renderer* renderer, FBOTargetId target)
{
    if(target == INPUT)
        renderSimulation(renderer, m_userInputBoardDoubleBuffer.ping.FBO);
    else
        renderSimulation(renderer, 0);
}

void GameBoard::renderSimulation(EG_Renderer* renderer, GLuint fboTarget)
{
    glViewport(0, 0, m_width, m_height);
    glBindFramebuffer(GL_FRAMEBUFFER, fboTarget);

    pipeline temp_pipeline;
    temp_pipeline.loadIdentity();
    temp_pipeline.ortho(-1,1,-1,1,-1,1);

    renderer->enableShader(RENDER_PASS1);
        renderer->setData(RENDER_PASS1, "u_simulationTexture", 0,
                                        GL_TEXTURE0,
                                        m_simulationDoubleBuffer.ping.colorTexture);

        renderer->loadUniformLocations(temp_pipeline, RENDER_PASS1);
        m_boardQuadModel.render();

    renderer->disableShader(RENDER_PASS1);
}

void GameBoard::renderSimulation(EG_Renderer* renderer)
{
    renderSimulation(renderer, 0);
}


GLuint GameBoard::getUserInputBoardColorTexture(int id)
{
    if(id == FRONT)
        return m_userInputBoardDoubleBuffer.ping.colorTexture;
    else
        return m_userInputBoardDoubleBuffer.pong.colorTexture;
}

void GameBoard::attachFBO(int id)
{
    if(id == FRONT)
        glBindFramebuffer(GL_FRAMEBUFFER, m_userInputBoardDoubleBuffer.ping.FBO);
    else
        glBindFramebuffer(GL_FRAMEBUFFER, m_userInputBoardDoubleBuffer.pong.FBO);

//    glClearColor(0, 0, 0, 1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
