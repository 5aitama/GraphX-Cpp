#ifndef GRAPHX_FACTORY_HPP
#define GRAPHX_FACTORY_HPP

namespace j2l 
{
    namespace GraphX 
    {
        class I2DRenderer;

        namespace Factory
        {
            /**
             * @brief Create a 2D view for rendering visual effects. The user must handle the life cycle of 
             *        the variable returned and call DeleteRenderer once finished to free allocated memory. 
             *        Once created, pass it to CreateArena function for starting robot synchronising.
             * 
             * @param width The window width.
             * @param height The window height.
             * @param title The window title.
             */
            I2DRenderer* create2DRenderer(const int width, const int height, const char* title);
        }
    }
}

#endif