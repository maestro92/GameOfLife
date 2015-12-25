#ifndef TEXT_ENGINE_H_
#define TEXT_ENGINE_H_

#include <unordered_map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "quad_model.h"
#include "general_renderer.h"



/// Holds all state information relevant to a character as loaded using FreeType
struct Character
{
    GLuint textureID;   // ID handle of the glyph texture
    glm::ivec2 size;    // Size of glyph
    glm::ivec2 bearing;  // Offset from baseline to left/top of glyph
    GLuint advance;    // Horizontal offset to advance to next glyph
};

class TextEngine
{
    public:
        TextEngine();

        TextEngine(string font, int size, int screenWidth, int screenHeight);


        void render(string text, float x, float y, float scale, glm::vec3 color);

        GLuint VAO, VBO;
        unordered_map<GLchar, Character> Characters;


    private:

        QuadModel m_quad;
        pipeline m_pipeline;

        int m_screenWidth;
        int m_screenHeight;

        GeneralRenderer r_textRenderer;

};


#endif
