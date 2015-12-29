#include "text_engine.h"


TextEngine::TextEngine()
{

}

TextEngine::TextEngine(string font, int size, int screenWidth, int screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    // set m_GUIPipeline
    m_pipeline.matrixMode(PROJECTION_MATRIX);
    m_pipeline.loadIdentity();
    m_pipeline.ortho(0, m_screenWidth, 0, m_screenHeight, -1, 1);

    m_pipeline.matrixMode(MODEL_MATRIX);
    m_pipeline.loadIdentity();

    m_quad.init(1,1);


    /// init freetype font
    string fontPath = "Assets/Fronts/" + font;

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        Utility::debug("ERROR::FREETYPE: Could not init FreeType Library");

    FT_Face face;
    if (FT_New_Face(ft, "Assets/Fonts/arial.ttf", 0, &face))
        Utility::debug("ERROR::FREETYPE: Failed to load font");

    FT_Set_Pixel_Sizes(face, 0, size);
    if(FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        Utility::debug("Could not load character 'X'\n");
    }

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use

        int height = face->glyph->bitmap.rows;
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, height),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        m_characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    /// set shader
    Shader* s;

    /// r_TextRenderer
    s = new Shader("/EG_GUIShaders/text.vs", "/EG_GUIShaders/text.fs");
    r_textRenderer.addShader(s);
    r_textRenderer.addDataPair(RENDER_PASS1, "u_texture",   DP_INT);
    r_textRenderer.addDataPair(RENDER_PASS1, "u_color",     DP_VEC3);
}



vector<int> TextEngine::getWordWraps(string text, float size)
{

}


float TextEngine::getTextWidth(string text, float size)
{
    float width = 0;
    for (int i=0; i<text.size(); i++)
    {
        char c = text[i];
        Character ch = m_characters[c];

        float xpos = width + ch.bearing.x * size;
        float w = ch.size.x * size;

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        width += (ch.advance >> 6) * size; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
    return width;
}


float TextEngine::getTextBotY(string text, float size)
{
    float minYPos = 0;

    for (int i=0; i<text.size(); i++)
    {
        char c = text[i];
        Character ch = m_characters[c];

        float yBotPos = (ch.size.y - ch.bearing.y) * size;

        minYPos = max(yBotPos, minYPos);
    }
    return minYPos;
}


float TextEngine::getTextHeight(string text, float size)
{
    float minYPos = 100;
    float maxYPos = 0;

    for (int i=0; i<text.size(); i++)
    {
        char c = text[i];
        Character ch = m_characters[c];

        float yBotPos = -(ch.size.y - ch.bearing.y) * size;
        float yTopPos = ch.bearing.y * size;

        Utility::debug("char is", c);
        Utility::debug("ch.size.y", ch.size.y);
        Utility::debug("ch.bearing.y", ch.bearing.y);
        Utility::debug("yBotPos", yBotPos);
        Utility::debug("yTopPos", yTopPos);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        minYPos = min(yBotPos, minYPos);
        maxYPos = max(yTopPos, maxYPos);
    }
    return maxYPos - minYPos;
}



void TextEngine::render(string text, float x, float y, float size, glm::vec3 color)
{
    if(text == "AgHy")
        int a = 1;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    r_textRenderer.enableShader();
        r_textRenderer.setData(RENDER_PASS1, "u_color", color);

        for (int i=0; i<text.size(); i++)
        {
            char c = text[i];
            Character ch = m_characters[c];

            float xpos = x + ch.bearing.x * size;
            float ypos = y - (ch.size.y - ch.bearing.y) * size;

        //    Utility::debug("xpos, ypos", c);
        //    Utility::debug("xpos, ypos", glm::vec2(xpos, ypos));
            float w = ch.size.x * size;
            float h = ch.size.y * size;

            m_pipeline.pushMatrix();

                m_pipeline.translate(xpos, ypos, 0);
                m_pipeline.scale(w, h, 0);

                r_textRenderer.setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, ch.textureID);
                r_textRenderer.loadUniformLocations(m_pipeline, RENDER_PASS1);

                m_quad.render();

            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * size; // Bitshift by 6 to get value in pixels (2^6 = 64)
            m_pipeline.popMatrix();
        }

    r_textRenderer.disableShader();
    glDisable(GL_BLEND);
}









/*
void TextEngine::render(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
 //   glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    r_textRenderer.enableShader();
        r_textRenderer.setData(RENDER_PASS1, "u_color", color);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        // Iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = m_characters[*c];

            GLfloat xpos = x + ch.bearing.x * scale;
            GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

            GLfloat w = ch.size.x * scale;
            GLfloat h = ch.size.y * scale;
            // Update VBO for each character
            GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            };

            r_textRenderer.setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, ch.textureID);
            r_textRenderer.loadUniformLocations(m_pipeline, RENDER_PASS1);



            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

    r_textRenderer.disableShader();

    glDisable(GL_BLEND);
}
*/
