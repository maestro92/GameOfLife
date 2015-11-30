#ifndef EG_UTILITY_H
#define EG_UTILITY_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream> //You'll need to include this header to use 'std::stringstream'.
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>


#define NO_SDL_GLEXT
#include <GL/glew.h>

#include "EG_Shader.h"


#include "define.h"
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <iomanip>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


using namespace std;

//typedef std::<EG_NoiseBasedParticle> EG_NoiseBasedParticleList;

#define RENDER_TO_SCREEN 0

#define BLACK   glm::vec3(0.0,0.0,0.0)
#define BLUE    glm::vec3(0.0,0.0,1.0)
#define GREEN   glm::vec3(0.0,1.0,0.0)
#define TEAL    glm::vec3(0.0,1.0,1.0)
#define RED     glm::vec3(1.0,0.0,0.0)
#define PURPLE  glm::vec3(1.0,0.0,1.0)
#define YELLOW  glm::vec3(1.0,1.0,0.0)
#define DARK_GRAY    glm::vec3(0.25,0.25,0.25)
#define GRAY    glm::vec3(0.5,0.5,0.5)
#define WHITE   glm::vec3(1.0,1.0,1.0)

struct MouseState
{
    bool m_leftButtonDown;
    bool m_rightButtonDown;
    bool m_middleButtonDown;

    glm::vec2 m_pos;

    MouseState()
    {
        m_leftButtonDown = false;
        m_rightButtonDown = false;
        m_middleButtonDown = false;

        m_pos = glm::vec2(0,0);
    }

};

struct EG_TextureObject
{
    GLuint id;
    int width;
    int height;
    int depth;
};


struct EG_FrameBufferObject
{
    GLuint FBO;
    GLuint colorTexture;
    GLuint depthTexture;

    void clear()
    {
        clear(glm::vec4(0,0,0,1));
    }

    void clear(glm::vec4 v)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClearColor(v.x, v.y, v.z, v.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
};

// double buffering
struct EG_DoubleFrameBufferObject
{
    EG_FrameBufferObject ping;   // buffer 1
    EG_FrameBufferObject pong;   // buffer 2

    void swapFrontBack()
    {
        EG_FrameBufferObject temp = ping;
        ping = pong;
        pong = temp;
    }

    void clear()
    {
        ping.clear();
        pong.clear();
    }

    void clear(glm::vec4 v)
    {
        ping.clear(v);
        pong.clear(v);
    }
};

class EG_Utility
{
    public:
        EG_Utility();
        ~EG_Utility();


        template<typename T>
            static vector<T> reserveVector(int size);

        /// EG_Utility_Math.cpp
        static float DEGREE_TO_RADIAN;
        static float RADIAN_TO_DEGREE;
        static string floatToStr(float value);
        static float randFloat(float min=0, float max=1);


        /// EG_Utility_GL.cpp
      //  static SDL_Surface* m_displaySurface;
        static void initSDL(int w, int h, SDL_Surface* & m_displaySurface);
        static void exitSDL(SDL_Surface* & m_displaySurface);
        static void initGLEW();
        static void errorCheck();
        static GLuint createFBO();
        static void errorCheckFBO();
        static void bindFBO(GLuint target);
        static SDL_Surface* loadRawImage(string filename);
        static SDL_Surface* loadSDLImage(string filename);
        static GLuint loadTexture(string filename);
        static GLuint loadTexture(string filename, GLuint filteringParam);
        static GLuint loadTexture(vector<vector<vector<GLubyte>>> data, GLuint filteringParam);

        static GLuint createTexture(int w, int h);
        static GLuint create3DTexture(int w, int h, int d);

        static GLuint createDepthTexture(int, int h);
        static GLuint createCubemapTexture();
        static GLuint createCubemapTexture(string* filenames);
        static void setTextureParameters(int w, int h, int internal_format, int format);
        static void setCubemapTextureParameters();
        static EG_FrameBufferObject createFrameBufferObject(int width, int height);
        static EG_DoubleFrameBufferObject createDoubleFrameBufferObject(int width, int height);

        static void setupFrameBuffer();
        static void setupFrameBuffer(GLuint target);


        /// EG_Utility_AssimpMath.cpp
        static glm::vec3 toGlmVec(aiVector3D& v2);
        static glm::mat4 toGlmMat(aiMatrix3x3 m2);
        static glm::mat4 toGlmMat(aiMatrix4x4& m2);
        static glm::mat4 toGlmMat(const aiMatrix4x4& m2);

        static glm::vec2 scaleGlmVec(const glm::vec2 v, float s);
        static glm::vec2 scaleGlmVec(const glm::vec2 v, float s1, float s2);
        static glm::vec3 scaleGlmVec(const glm::vec3 v, float s);
        static glm::vec3 scaleGlmVec(const glm::vec3 v, float s1, float s2, float s3);


        /// EG_Utility_Debug.cpp
        static void debugLn(int l=0);
        static void debugLn(string s, int l=0);

        static void debug(string s);
        static void debug(string s, string s2);
        static void debug(string s, unsigned int i);
        static void debug(string s, int i);
        static void debug(string s, float f);
        static void debug(string s, glm::vec2 v);
        static void debug(string s, glm::vec3 v);
        static void debug(string s, glm::vec4 v);
        static void debug(string s, glm::mat3 m);
        static void debug(string s, glm::mat4 m);
        static void checkGLError();


        /// EG_Utility_UniLoc.cpp
        static void setUniLoc(GLuint location, int value);
        static void setUniLoc(GLuint location, float value);
        static void setUniLoc(GLuint location, float x, float y);
        static void setUniLoc(GLuint location, glm::vec2 value);
        static void setUniLoc(GLuint location, glm::vec3 value);
        static void setUniLoc(GLuint location, glm::vec4 value);
        static void setUniLoc(GLuint location, glm::mat3 value);
        static void setUniLoc(GLuint location, glm::mat4 value);
        static void setUniLocTranspose(GLuint location, glm::mat4 value);
};



template<typename T>
vector<T> EG_Utility::reserveVector(int size)
{
    vector<T> v;
    v.reserve(size);
    return v;
}



#endif
