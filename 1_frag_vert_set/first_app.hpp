#pragma once

#include "lot_device.hpp"
#include "lot_model.hpp"
#include "lot_pipeline.hpp"
#include "lot_swap_chain.hpp"
#include "lot_window.hpp"

#include <memory>
#include <vector>

namespace lot {
    class FirstApp {
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;

            FirstApp();
            ~FirstApp();

            FirstApp(const FirstApp &) = delete;
            FirstApp &operator=(const FirstApp &) = delete;

            void run();

        private:
            void loadModels();
            void createPipelineLayout();
            void createPipeline();
            void createCommandBuffers();
            void drawFrame();

            LotWindow lotWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
            LotDevice lotDevice{lotWindow};
            LotSwapChain lotSwapChain{lotDevice, lotWindow.getExtent()};
            /*LotPipeline lotpipeline{
                lotDevice,
                "shaders/simple_shader.vert.spv", 
                "shaders/simple_shader.frag.spv",
                LotPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};*/
            std::unique_ptr<LotPipeline> lotPipeline;
            VkPipelineLayout pipelineLayout;
            std::vector<VkCommandBuffer> commandBuffers;
            std::unique_ptr<LotModel> lotModel;
    };
}