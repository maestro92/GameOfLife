#ifndef RENDERER_H_
#define RENDERER_H_
#include "define.h"
#include "shader.h"
#include "pipeline.h"
#include "utility.h"
#include <unordered_map>
#include <stack>

using namespace std;

/*
const int RENDER_PASS1 = 0;
const int RENDER_PASS2 = 1;
*/

enum RenderPass
{
    RENDER_PASS1=0,
    RENDER_PASS2,
    RENDER_PASS3,
    RENDER_PASS4,
    RENDER_PASS5,
    RENDER_PASS6
};

const int SHADOW_RENDER = 0;
const int TWOPASS_RAYCASTING_RENDER = 1;
const int DEPTH_TEXTURE_RENDER = 2;
const int DEFERRED_SHADING_RENDER = 3;

static struct Matrices_t{
    glm::mat4 Projection;
    glm::mat4 Modelview;
    glm::mat4 Model;
    glm::mat4 View;
    glm::mat4 ViewNoRotate;
    glm::mat4 ModelviewProjection;
    glm::mat4 Normal;
} Matrices;


struct MatricesLocation
{
    GLuint ProjectionMatrix;
    GLuint ModelviewMatrix;
    GLuint ViewMatrix;
    GLuint ModelviewProjection;
    GLuint ModelMatrix;
    GLuint ViewNoRotateMatrix;
    GLuint NormalMatrix;
};



// http://blogs.msdn.com/b/oldnewthing/archive/2004/05/07/127826.aspx
// http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
/*
always make the base classes' destructors virtual when they're meant to be manipulated polymorphically
*/
struct DataPair
{
    GLuint uniLoc;
    string name;
    virtual ~DataPair(){};

    virtual void setUniLoc(){};
    virtual void printValue(){};

    void printError()
    {
        Utility::debug(name, "unmatched type");
        exit(1);
    }
    virtual void setValue(bool value){printError();};
    virtual void setValue(int value){printError();};
    virtual void setValue(float value){printError();};
    virtual void setValue(glm::vec2 value){printError();};
    virtual void setValue(glm::vec3 value){printError();};
    virtual void setValue(glm::vec4 value){printError();};
    virtual void setValue(glm::mat3 value){printError();};
    virtual void setValue(glm::mat4 value){printError();};
};


struct BoolDataPair : public DataPair
{
    bool value;

    BoolDataPair(){};
    BoolDataPair(string n)
    {
        name = n;
    };

    ~BoolDataPair(){};

    virtual void setValue(bool value)
    {
        this->value = value;
    }

    virtual void setUniLoc()
    {
        Utility::setUniLoc(uniLoc, value);
    }

    virtual void printValue()
    {
        Utility::debug("value is", value);
    }
};

struct IntDataPair : public DataPair
{
    int value;

    IntDataPair(){};
    IntDataPair(string n)
    {
        name = n;
    };

    ~IntDataPair(){};

    virtual void setValue(int value)
    {
        this->value = value;
    }

    virtual void setUniLoc()
    {
        Utility::setUniLoc(uniLoc, value);
    }

    virtual void printValue()
    {
        Utility::debug("value is", value);
    }
};

struct FloatDataPair : public DataPair
{
    float value;

    FloatDataPair(){};
    FloatDataPair(string n)
    {
        name = n;
    };

    ~FloatDataPair(){};

    void setValue(float value)
    {
        this->value = value;
    }

    void setUniLoc()
    {
        Utility::setUniLoc(uniLoc, value);
    }

    void printValue()
    {
        Utility::debug("value is", value);
    }
};

struct Vec2DataPair : public DataPair
{
    glm::vec2 value;

    Vec2DataPair(){};
    Vec2DataPair(string n)
    {
        name = n;
    };

    ~Vec2DataPair(){};

    void setValue(glm::vec2 value)
    {
        this->value = value;
    }

    void setUniLoc()
    {
        Utility::setUniLoc(uniLoc, value);
    }

    void printValue()
    {
        Utility::debug("value is", value);
    }
};

struct Vec3DataPair : public DataPair
{
    glm::vec3 value;

    Vec3DataPair(){};
    Vec3DataPair(string n)
    {
        name = n;
    };

    ~Vec3DataPair(){};

    void setValue(glm::vec3 value)
    {
        this->value = value;
    }

    void setUniLoc()
    {
        Utility::setUniLoc(uniLoc, value);
    }

    void printValue()
    {
        Utility::debug("value is", value);
    }
};

struct Vec4DataPair : public DataPair
{
    glm::vec4 value;

    Vec4DataPair(){};
    Vec4DataPair(string n)
    {
        name = n;
    };

    ~Vec4DataPair(){};


    void setValue(glm::vec4 value)
    {
        this->value = value;
    }

    void setUniLoc()
    {
        Utility::setUniLoc(uniLoc, value);
    }

    void printValue()
    {
        Utility::debug("value is", value);
    }
};

struct Mat3DataPair : public DataPair
{
    glm::mat3 value;

    Mat3DataPair(){};
    Mat3DataPair(string n)
    {
        name = n;
    };

    ~Mat3DataPair(){};

    void setValue(glm::mat3 value)
    {
        this->value = value;
    }

    void setUniLoc()
    {
        Utility::setUniLoc(uniLoc, value);
    }

    void printValue()
    {
        Utility::debug("value is", value);
    }
};

struct Mat4DataPair : public DataPair
{
    glm::mat4 value;
    Mat4DataPair(){};
    Mat4DataPair(string n)
    {
        name = n;
    };

    ~Mat4DataPair(){};

    void setValue(glm::mat4 value)
    {
        this->value = value;
    }

    void setUniLoc()
    {
        Utility::setUniLoc(uniLoc, value);
    }

    void printValue()
    {
        Utility::debug("value is", value);
    }
};




enum DATA_PAIR_TYPE
{
    DP_BOOL = 0,
    DP_INT,
    DP_FLOAT,
    DP_VEC2,
    DP_VEC3,
    DP_VEC4,
    DP_MAT3,
    DP_MAT4,
};


class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        void addShader(Shader* s);

        void enableShader();
        void enableShader(int pass);
        void disableShader();
        void disableShader(int pass);

        GLuint GetUniformLocation(Shader* s, const char* UniformName);

        virtual void loadUniformLocations();
        virtual void loadUniformLocations(int pass);
        virtual void loadUniformLocations(pipeline& p);
        virtual void loadUniformLocations(pipeline& p, int pass);
        virtual void render();

        void initDataPairUniLoc(DataPair* p, int pass, const char* name);
        void addDataPair(const char* name, int dataType);
        void addDataPair(int pass, const char* name, int dataType);

        GLuint getUniLoc(Shader* s, const char* name);


        void setUniformLocation(GLuint location, bool value);
        void setUniformLocation(GLuint location, int value);
        void setUniformLocation(GLuint location, float value);
        void setUniformLocation(GLuint location, float x, float y);
        void setUniformLocation(GLuint location, glm::vec2 value);
        void setUniformLocation(GLuint location, glm::vec3 value);
        void setUniformLocation(GLuint location, glm::vec4 value);
        void setUniformLocation(GLuint location, glm::mat3 value);
        void setUniformLocation(GLuint location, glm::mat4 value);
        void setUniformLocationTranspose(GLuint location, glm::mat4 value);

        void setAllDataPairUniLocs(int pass);

        void setDataPairUniLoc(BoolDataPair& dp);
        void setDataPairUniLoc(IntDataPair& dp);
        void setDataPairUniLoc(FloatDataPair& dp);
        void setDataPairUniLoc(Vec2DataPair& dp);
        void setDataPairUniLoc(Vec3DataPair& dp);
        void setDataPairUniLoc(Vec4DataPair& dp);
        void setDataPairUniLoc(Mat3DataPair& dp);
        void setDataPairUniLoc(Mat4DataPair& dp);


        void printTables();
        /*
        void setData(const char* name, bool value);
        void setData(const char* name, int value);
        void setData(const char* name, int value, GLuint textureId, GLuint unit);
        void setData(const char* name, float value);
        void setData(const char* name, glm::vec2 value);
        void setData(const char* name, glm::vec3 value);
        void setData(const char* name, glm::vec4 value);
        void setData(const char* name, glm::mat3 value);
        void setData(const char* name, glm::mat4 value);
        void errorCheck(const char* name);
        */

        void setData(int pass, const char* name, bool value);
        void setData(int pass, const char* name, int value);
        void setData(int pass, const char* name, int value, GLuint textureId, GLuint unit);
        void setData(int pass, const char* name, float value);
        void setData(int pass, const char* name, glm::vec2 value);
        void setData(int pass, const char* name, glm::vec3 value);
        void setData(int pass, const char* name, glm::vec4 value);
        void setData(int pass, const char* name, glm::mat3 value);
        void setData(int pass, const char* name, glm::mat4 value);
        void errorCheck(int pass, const char* name);

        void getAllMatrixUniLocs();
        bool getMatrixUniLocs(Shader* s, MatricesLocation& Mat);

    public:
        vector<MatricesLocation> m_matricesUniLocs;
        vector<Shader*> m_shaders;
        vector< vector<DataPair*> > m_allDataPairs;

        vector< unordered_map<string, DataPair*> > m_tables;
        stack<GLuint> m_textureUnitStack;
    private:
        int m_numShaders;
        int m_curShader;

};


#endif
