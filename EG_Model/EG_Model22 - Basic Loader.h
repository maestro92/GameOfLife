#ifndef MESH37_H
#define	MESH37_H


#define NO_SDL_GLEXT
#include <GL/glew.h>

#include "define.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "texture.h"

using namespace std;


struct Vertex
{
    glm::vec3 m_pos;
    glm::vec3 m_normal;
    glm::vec3 m_tangent;
    glm::vec3 m_color;
    glm::vec2 m_UV;

    Vertex() {}
/*
    Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
    }
*/
    Vertex(const glm::vec3& pos,
           const glm::vec3& normal,
           const glm::vec3& tangent,
           const glm::vec3& color,
           const glm::vec2& UV)
    {
        m_pos       = pos;
        m_normal    = normal;
        m_tangent   = tangent;
        m_color     = color;
        m_UV       = UV;
    }
};


class EG_Model
{

    public:

        int VERTEX=0;
        int NORMAL=1;
        int TANGENT=2; //2
        int COLOR=3; //3
        int UV=4; //4


        EG_Model();

        ~EG_Model();

        static void genGLVertexBuffer(GLuint& id, vector<Vertex>& Vertices);
        static void genGLIndexBuffer(GLuint& id, vector<unsigned int>& Indices);

        void copyVec3(glm::vec3& v, aiVector3D& c);

        bool loadModel(string filename);
        void render();

    private:
        bool initFromAiScene(const aiScene* pScene, const std::string& Filename);
/*
        void initMesh(const aiMesh* paiMesh,
                      std::vector<glm::vec3>& Positions,
                      std::vector<glm::vec3>& Normals,
                      std::vector<glm::vec2>& TexCoords,
                      std::vector<unsigned int>& Indices);
*/


        void initMesh(unsigned int Index, const aiMesh* m, const aiScene* scene);
        bool initMaterials(const aiScene* pScene, const std::string& Filename);
        void clear();

#define INVALID_MATERIAL 0xFFFFFFFF
/*
        /// instead of having VB/IB (Vertex Buffer and Index Buffer) Objects, we
        /// have four buffers - index, position, normal and texture coordinates
        /// also a new member variable called m_VAO that stores the vertex array object
        ///
        GLuint m_VAO;
        GLuint m_Buffers[6];
*/
        struct Mesh
        {
            Mesh();

            ~Mesh();
            void init(vector<Vertex>& Vertices, vector<unsigned int>& Indices);

            GLuint VB;
            GLuint IB;
            unsigned int NumIndices;
            unsigned int MaterialIndex;

        };

        vector<Mesh> m_Entries;
        vector<Texture*>  m_Textures;
};


#endif // MESH37_H
