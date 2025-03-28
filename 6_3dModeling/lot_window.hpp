#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace lot {
    class LotWindow{
        public:
            LotWindow(int w, int h, std::string name);
            ~LotWindow();

            LotWindow(const LotWindow &) = delete;
            LotWindow &operator=(const LotWindow &) = delete;

            bool shouldClose() {
                return glfwWindowShouldClose(window);
            }
            VkExtent2D getExtent() { 
                return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
            }
            bool wasWindowResized() { return framebufferResized; }
            void resetWindowSurfaceFlag() { framebufferResized = false; }

            void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface_);

        private:
            static void framebufferResizeCallback(GLFWwindow* window, int width, int height); 
            void initWindow();

            // 창 크기 조절 가능하도록 const 제외
            int width;
            int height;
            bool framebufferResized = false;

            std::string windowName;
            GLFWwindow *window;
    };

}