#include "utility.h"



void Utility::initGLEW()
{
    // initialize Glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      cout << "Error: %s\n" << glewGetErrorString(err) << endl;
    }
}


GLuint Utility::createFBO()
{
    GLuint FBO;
    glGenFramebuffers(1, &FBO);
    return FBO;
}


void Utility::bindFBO(GLuint target)
{


}


void Utility::errorCheckFBO()
{
    int i=glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(i!=GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "XXXXXXXXXX Error: Framebuffer is not OK, status=" << i << endl;
	}
    else
        cout << "Framebuffer Okay" << endl;
}




GLuint Utility::loadTexture(string filename)
{
    return loadTexture(filename, GL_LINEAR);
}


GLuint Utility::loadTexture(string filename, GLuint filteringParam)
{
    cout << "Loading Texture " << filename << endl;

    SDL_Surface* img2 = loadSDLImage(filename);

    unsigned int num;
    glGenTextures(1,&num);

    // tell OpenGL we want to use this texture
    glBindTexture(GL_TEXTURE_2D,num);       //and use the texture, we have just generated
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,img2->pixels);        //we make the actual texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filteringParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filteringParam);

    // if you comment these two lines out, you will see the edges of the cube
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);      //we do it for vertically and horizontally (previous line)

    //we delete the image, we don't need it anymore
    glBindTexture(GL_TEXTURE_2D,0);
    SDL_FreeSurface(img2);
    return num;
}


// http://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
GLuint Utility::loadTexture(vector<vector<vector<GLubyte>>> data, GLuint filteringParam)
{
    int h = data.size();
    int w = data[0].size();

    GLubyte temp[h][w][4];

    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            temp[y][x][0] = (data[y][x][0]);
            temp[y][x][1] = (data[y][x][1]);
            temp[y][x][2] = (data[y][x][2]);
            temp[y][x][3] = (data[y][x][3]);
        }
    }

    unsigned int num;
    glGenTextures(1,&num);

    // tell OpenGL we want to use this texture
    glBindTexture(GL_TEXTURE_2D,num);       //and use the texture, we have just generated
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, temp);        //we make the actual texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filteringParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filteringParam);

    // if you comment these two lines out, you will see the edges of the cube
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);      //we do it for vertically and horizontally (previous line)

    //we delete the image, we don't need it anymore
    glBindTexture(GL_TEXTURE_2D,0);
    return num;
}


GLuint Utility::createTexture(int w, int h)
{
    GLuint textureID;
    glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_2D,textureID);

    setTextureParameters(w, h, GL_RGBA8, GL_RGBA);
    errorCheck();

    // unbind the texture
    glBindTexture(GL_TEXTURE_2D,0);
    return textureID;
}



TextureDataBuffer Utility::createEmptyBuffer(int w, int h)
{
    TextureDataBuffer dataBuffer;
    dataBuffer.resize(h);
    for(int i=0; i<h; i++)
    {
        dataBuffer[i].resize(w);
        for(int j=0; j<w; j++)
            dataBuffer[i][j].resize(4);
    }
    return dataBuffer;
}


/*
GLuint Utility::createTexture(int w, int h)
{
    GLuint textureID;
    glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_2D,textureID);

    setTextureParameters(w, h, GL_RGBA8, GL_RGBA);
    errorCheck();

    // unbind the texture
    glBindTexture(GL_TEXTURE_2D,0);
    return textureID;
}
*/
/*
GLuint Utility::create3DTexture(int w, int h, int d)
{
    GLuint textureID;
    glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_3D, textureID);
    return textureID;
}
*/


GLuint Utility::createDepthTexture(int w, int h)
{
    GLuint textureID;

    glGenTextures(1,&textureID);
    /// glBindTexture: i'm binding this texture object as the current 2D texture
	glBindTexture(GL_TEXTURE_2D,textureID);

    setTextureParameters(w, h, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

    errorCheck();

    // unbind the texture
    glBindTexture(GL_TEXTURE_2D,0);
    return textureID;
}



void Utility::setTextureParameters(int w, int h, int internal_format, int format)
{
   	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, w, h, 0, format, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
}



GLuint Utility::createCubemapTexture()
{
    /// need to pass in the pictures in the following order
    /// left, right, top, bottom, near, far
    GLuint tex;
    glGenTextures(1,&tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

    // set textures
    /// SCREEN_WIDTH and SCREEN_HEIGHT needs to be power of two
    for (int i = 0; i < 6; i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    /// this all applies to the one cubemap
    setCubemapTextureParameters();

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return tex;
}



GLuint Utility::createCubemapTexture(string* filenames)
{
    /// need to pass in the pictures in the following order
    /// left, right, top, bottom, near, far
    GLuint tex;
    glGenTextures(1,&tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

    for(int i=0; i<6; i++)
    {
        SDL_Surface* cubemap_img = loadSDLImage(filenames[i]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,
                        GL_RGBA, cubemap_img->w, cubemap_img->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, cubemap_img->pixels);

        SDL_FreeSurface(cubemap_img);
    }

    /// this all applies to the one cubemap
    setCubemapTextureParameters();

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return tex;
}



void Utility::setCubemapTextureParameters()
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}



void Utility::errorCheck()
{
    int i;
    i = glGetError();
    if(i!=0)
    {
        std::cout << "Error happened while loading the texture: " << i << std::endl;
    }
}



FrameBufferObject Utility::createFrameBufferObject(int width, int height)
{
    FrameBufferObject pod;

    pod.depthTexture = createDepthTexture(width, height);

    // Create a FBO and attach the depth texture:
    glGenFramebuffers(1, &pod.FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, pod.FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, pod.depthTexture, 0);

    pod.colorTexture = createTexture(width, height);

    // Attach the color buffer:
    GLuint colorbuffer;
    glGenRenderbuffers(1, &colorbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorbuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pod.colorTexture, 0);

    return pod;
}


DoubleFrameBufferObject Utility::createDoubleFrameBufferObject(int width, int height)
{
    DoubleFrameBufferObject fbObj;
    fbObj.ping = createFrameBufferObject(width, height);
    fbObj.pong = createFrameBufferObject(width, height);
    return fbObj;
}


void Utility::setupFrameBuffer()
{
    setupFrameBuffer(0);
}

void Utility::setupFrameBuffer(GLuint target)
{
    glBindFramebuffer(GL_FRAMEBUFFER, target);
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
