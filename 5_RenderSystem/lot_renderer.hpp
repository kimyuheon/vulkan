#pragma once 

#include "lot_device.hpp"
#include "lot_swap_chain.hpp"
#include "lot_window.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace lot {
    class LotRenderer {
        public:
            LotRenderer(LotWindow& window, LotDevice &device);
            ~LotRenderer();

            LotRenderer(const LotRenderer &) = delete;
            LotRenderer &operator=(const LotRenderer &) = delete;

            VkRenderPass getSwapChainRenderPass() const { return lotSwapChain->getRenderPass();}
            bool isFrameInProgress() const { return isFrameStarted; }

            VkCommandBuffer getCurrentCommandBuffer() const {
                //assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
                assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
                return commandBuffers[currentFrameIndex];
            }

            int getFrameIndex() const {
                assert(isFrameStarted && "Cannot get frame index when frame not in progress");
                return currentFrameIndex;
            }

            VkCommandBuffer beginFrame();
            void endFrame();
            void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
            void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

        private:
            void createCommandBuffers();
            void freeCommandBuffer();
            void recreateSwapChain();

            LotWindow &lotWindow;
            LotDevice &lotDevice;
            std::unique_ptr<LotSwapChain> lotSwapChain;
            std::vector<VkCommandBuffer> commandBuffers;

            uint32_t currentImageIndex;
            int currentFrameIndex;
            bool isFrameStarted{false};
    };
}