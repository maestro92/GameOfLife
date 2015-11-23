#include "EG_GameBoard.h"


/*
GameBoard::GameBoard() : this(100, 100, 5)
{}
*/

/*
    w
    h
    s

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

    m_boardDisplayBuffer = EG_Utility::createDoubleFrameBufferObject(w, h);
    m_simulationDoubleBuffer = EG_Utility::createDoubleFrameBufferObject(m_numGridsX, m_numGridsY);

    attachFBO(FRONT);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    attachFBO(BACK);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


/*
GameBoard::GameBoard(int numX, int numY, int s)
{
    m_numGridsX = numX;
    m_numGridsY = numY;
    setGridSize(s);

    m_width = numX * s;
    m_height = numY * s;

    m_inverseWidth = 1/m_width;
    m_inverseHeight = 1/m_height;

    m_boardQuadModel.init(-1, 1, -1, 1,
                            0.0, 0.0, 1.0);

    m_doubleBoardBuffer = EG_Utility::createDoubleFrameBufferObject(numX, numY);


    attachFBO(FRONT);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    attachFBO(BACK);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
*/

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


void GameBoard::initUserInput(EG_GeneralRenderer& renderer, MouseState& mouseState)
{
//    glViewport(0, 0, m_width, m_height);
//    glBindFramebuffer(GL_FRAMEBUFFER, doubleBoardBuffer.ping.colorTexture);
 //   glBindFramebuffer(GL_FRAMEBUFFER, m_doubleBoardBuffer.pong.FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_boardDisplayBuffer.pong.FBO);

    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //  attachBuffer(FRONT);
    glm::vec2 pos = mouseState.m_pos;

    float sx = floor(pos.x / m_gridSize);
    sx *= m_gridSize;

    float sy = floor(pos.y / m_gridSize);
    sy *= m_gridSize;

    float ex = sx + m_gridSize;
    float ey = sy + m_gridSize;

    renderer.enableShader(RENDER_PASS1);

//        renderer.setData(RENDER_PASS1, "u_startGridX", sx);
        renderer.setData(RENDER_PASS1, "u_boardTexture", 0, GL_TEXTURE0, m_boardDisplayBuffer.ping.colorTexture);
        renderer.setData(RENDER_PASS1, "u_startGridX", sx);
        renderer.setData(RENDER_PASS1, "u_startGridY", sy);
        renderer.setData(RENDER_PASS1, "u_endGridX", ex);
        renderer.setData(RENDER_PASS1, "u_endGridY", ey);
        renderer.setData(RENDER_PASS1, "u_invWidth", m_inverseWidth);
        renderer.setData(RENDER_PASS1, "u_invHeight", m_inverseHeight);
        renderer.setData(RENDER_PASS1, "u_mouseLeftBtnDown", mouseState.m_leftButtonDown);
//        renderer.setData(RENDER_PASS1, "u_boardTexture", 0, GL_TEXTURE0, m_board.getColorTexture(0));

        renderer.loadUniformLocations(RENDER_PASS1);
        m_boardQuadModel.render();
    renderer.disableShader(RENDER_PASS1);
}

void GameBoard::displayToSimluationBoard()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_boardDisplayBuffer.pong.FBO);
}



void GameBoard::update(EG_GeneralRenderer& renderer)
{
    /*
    glViewport(0, 0, m_numGridsX, m_numGridsY);
    glBindFramebuffer(GL_FRAMEBUFFER, m_boardDisplayBuffer.pong.FBO);

    renderer.enableShader(RENDER_PASS1);
        renderer.setData(RENDER_PASS1, "u_boardTexture", 0, GL_TEXTURE0, m_boardDisplayBuffer.ping.colorTexture);
        renderer.setData(RENDER_PASS1, "u_startGridX", sx);
        renderer.setData(RENDER_PASS1, "u_startGridY", sy);
        renderer.setData(RENDER_PASS1, "u_endGridX", ex);
        renderer.setData(RENDER_PASS1, "u_endGridY", ey);
        renderer.setData(RENDER_PASS1, "u_invWidth", m_inverseWidth);
        renderer.setData(RENDER_PASS1, "u_invHeight", m_inverseHeight);
        renderer.setData(RENDER_PASS1, "u_mouseLeftBtnDown", mouseState.m_leftButtonDown);

        renderer.loadUniformLocations(RENDER_PASS1);
        m_boardQuadModel.render();
    renderer.disableShader(RENDER_PASS1);
    */
}

void GameBoard::render(EG_GeneralRenderer& renderer)
{
    renderer.enableShader(RENDER_PASS1);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_boardDisplayBuffer.ping.colorTexture);
//        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        m_boardQuadModel.render();
    renderer.disableShader(RENDER_PASS1);
}


GLuint GameBoard::getColorTexture(int id)
{
    if(id == FRONT)
        return m_boardDisplayBuffer.ping.colorTexture;
    else
        return m_boardDisplayBuffer.pong.colorTexture;
}

void GameBoard::attachFBO(int id)
{
    if(id == FRONT)
        glBindFramebuffer(GL_FRAMEBUFFER, m_boardDisplayBuffer.ping.FBO);
    else
        glBindFramebuffer(GL_FRAMEBUFFER, m_boardDisplayBuffer.pong.FBO);

//    glClearColor(0, 0, 0, 1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
