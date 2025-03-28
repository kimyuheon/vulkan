#pragma once

#include "lot_device.hpp"
#include "lot_game_object.hpp"
#include "lot_pipeline.hpp"

#include <memory>
#include <vector>

namespace lot {
    class SimpleRenderSystem {
        public:
            SimpleRenderSystem(LotDevice &device, VkRenderPass renderPass);
            ~SimpleRenderSystem();

            SimpleRenderSystem(const SimpleRenderSystem &) = delete;
            SimpleRenderSystem &operator=(const SimpleRenderSystem &) = delete;

            void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<LotGameObject> &gameObject);

        private:
            void createPipelineLayout();
            void createPipeLine(VkRenderPass renderPass);

            LotDevice &lotDevice;

            std::unique_ptr<LotPipeline> lotPipeline;
            VkPipelineLayout pipelineLayout;
    };

}