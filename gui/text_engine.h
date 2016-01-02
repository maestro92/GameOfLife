#ifndef TEXT_ENGINE_H_
#define TEXT_ENGINE_H_

#include <unordered_map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "quad_model.h"
#include "renderer.h"



/// Holds all state information relevant to a character as loaded using FreeType
struct Character
{
    GLuint textureID;   // ID handle of the glyph texture
    glm::ivec2 size;    // Size of glyph
    glm::ivec2 bearing;  // Offset from baseline to left/top of glyph
    GLuint advance;    // Horizontal offset to advance to next glyph
};

struct Font
{
    glm::vec3 color;
    float size;
};

struct LineBreakInfo
{
    int lines;
    vector<int> lineBreaks;
    int maxWidth;
    int maxHeight;

    LineBreakInfo()
    {}

    LineBreakInfo(int l, vector<int> lb, int mw)
    {
        lines = l;
        lineBreaks = lb;
        maxWidth = mw;
    }
};


class TextEngine
{
    public:
        TextEngine();

        TextEngine(string font, int fontSize, int screenWidth, int screenHeight);

        float getTextWidth(string text, float fontSize);
        float getMaxDecenderHeight(float fontSize);
        float getTextHeight(string text, float fontSize);

        float getTotalTextWidth(string text, float fontSize);
        float getTotalTextHeight(string text, float fontSize);


//        vector<int> getLineBreaks(string text, float size, int linePixelWidth);
        LineBreakInfo computeLineBreakInfo(string text, float fontSize, int linePixelWidth);
        void render(string text, float x, float y, float fontSize, glm::vec3 color);
        void render(string text, float x, float y, float fontSize, glm::vec3 color, vector<int> lineBreaks);

        static vector<string> getWords(string text);
        void lineWrappedGreedyAlgo(string text);
        void lineWrappedDynamicAlgo(string text);
        void lineWrappedDynamicAlgo1(string text);


        int printSolution (int p[], int n);




        unordered_map<GLchar, Character> m_characters;
        float m_globalYMax;
        float m_globalYMin;

        int m_fontSize;

    private:
        float m_maxDescenderHeight;
        QuadModel m_quad;
        pipeline m_pipeline;

        int m_screenWidth;
        int m_screenHeight;

        Renderer r_textRenderer;

};


#endif
