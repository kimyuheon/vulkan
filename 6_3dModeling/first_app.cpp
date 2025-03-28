#include "first_app.hpp"

#include "simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <array>
#include <cassert>
#include <stdexcept>

namespace lot {
    /*
    struct SimplePushConstantData {
        glm::mat2 transform{1.f};
        glm::vec2 offset;
        alignas(16) glm::vec3 color;
    };
    */
    FirstApp::FirstApp() {
        //loadModels();
        loadGameObjects();
        //createPipelineLayout();
        //recreateSwapChain();
        //createPipeline();
        //createCommandBuffers();
    }

    FirstApp::~FirstApp() {}

    void FirstApp::run() {
        SimpleRenderSystem simpleRnederSystem{lotDevice, lotRenderer.getSwapChainRenderPass()};

        while (!lotWindow.shouldClose()) {
            glfwPollEvents();
            //drawFrame();
            if (auto commandBuffer = lotRenderer.beginFrame()) {
                lotRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRnederSystem.renderGameObjects(commandBuffer, gameObjects);
                lotRenderer.endSwapChainRenderPass(commandBuffer);
                lotRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(lotDevice.device());
    }

    // temporary helper function, creates a 1x1x1 cube centered at offset
std::unique_ptr<LotModel> createCubeModel(LotDevice& device, glm::vec3 offset) {
    std::vector<LotModel::Vertex> vertices{
  
        // left face (white)
        {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
        {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
        {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
        {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
        {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},
        {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
  
        // right face (yellow)
        {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
        {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
        {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
        {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
        {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},
        {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
  
        // top face (orange, remember y axis points down)
        {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
        {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
        {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
        {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
        {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
        {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
  
        // bottom face (red)
        {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
        {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
        {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
        {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
        {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},
        {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
  
        // nose face (blue)
        {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
        {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
        {{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
        {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
        {{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
        {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
  
        // tail face (green)
        {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
        {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
        {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
        {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
        {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
        {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
  
    };
    for (auto& v : vertices) {
        v.position += offset;
    }
    return std::make_unique<LotModel>(device, vertices);
  }

    //void FirstApp::loadModels() {
    void FirstApp::loadGameObjects() {
        std::shared_ptr<LotModel> lotModel =  createCubeModel(lotDevice, {.0f, .0f,.0f});

        auto cube = LotGameObject::createGameObject();
        cube.model = lotModel;
        cube.transform.translation = {.0f, .0f, .5f};
        cube.transform.scale = {.5f, .5f, .5f};

        gameObjects.push_back(std::move(cube));
    }

    /*
    void FirstApp::createPipelineLayout() {
        VkPushConstantRange pushconstantRange{};
        pushconstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushconstantRange.offset = 0;
        pushconstantRange.size  = sizeof(SimplePushConstantData);

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushconstantRange;
        if (vkCreatePipelineLayout(lotDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout");
        }
    }

    void FirstApp::createPipeline() {
        //auto pipelineConfig = LotPipeline::defaultPipelineConfigInfo(lotSwapChain.width(), lotSwapChain.height());
        PipelineConfigInfo pipelineConfig{};
        LotPipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = lotSwapChain->getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        lotPipeline = std::make_unique<LotPipeline>(
            lotDevice,
            "shaders/simple_shader.vert.spv", 
            "shaders/simple_shader.frag.spv",
            pipelineConfig
        );
    }

    void FirstApp::recreateSwapChain() {
        auto extent = lotWindow.getExtent();
        while (extent.width == 0 || extent.height == 0) {
            extent = lotWindow.getExtent();
            glfwWaitEvents();
        }
        // 대기
        vkDeviceWaitIdle(lotDevice.device());
        
        if (lotSwapChain == nullptr) {
            lotSwapChain = std::make_unique<LotSwapChain>(lotDevice, extent);
        } else {
            lotSwapChain = std::make_unique<LotSwapChain>(lotDevice, extent, std::move(lotSwapChain));
            if (lotSwapChain->imageCount() != commandBuffers.size()) {
                createCommandBuffers();
                freeCommandBuffers();
            }
        }
        
        createPipeline();
    }

    void FirstApp::createCommandBuffers() {
        commandBuffers.resize(lotSwapChain->imageCount());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = lotDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(lotDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command, buffer");
        }
    }

    void FirstApp::freeCommandBuffers() {
        vkFreeCommandBuffers(
            lotDevice.device(),
            lotDevice.getCommandPool(),
            static_cast<uint32_t>(commandBuffers.size()),
            commandBuffers.data());
        commandBuffers.clear();
    }

    void FirstApp::recordCommandBuffer(int imageIndex) {
        //static int frame = 30;
        //frame = (frame + 1) % 100;

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        
        if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = lotSwapChain->getRenderPass();
        renderPassInfo.framebuffer = lotSwapChain->getFrameBuffer(imageIndex);

        renderPassInfo.renderArea.offset = {0,0};
        renderPassInfo.renderArea.extent = lotSwapChain->getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {0.01f, 0.01f, 0.01f, 1.0f};
        clearValues[1].depthStencil = {1.0f, 0};
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(lotSwapChain->getSwapChainExtent().width);
        viewport.height = static_cast<float>(lotSwapChain->getSwapChainExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        VkRect2D scissor{{0, 0}, lotSwapChain->getSwapChainExtent()};
        vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
        vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

        //lotPipeline->bind(commandBuffers[imageIndex]);
        //lotModel->bind(commandBuffers[imageIndex]);
        //lotModel->draw(commandBuffers[imageIndex]);

        renderGameObjects(commandBuffers[imageIndex]);

        vkCmdEndRenderPass(commandBuffers[imageIndex]);
        if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS) {
            throw std::runtime_error("failed to recoed command buffer!");
        }
    }

    void FirstApp::renderGameObjects(VkCommandBuffer commandBuffer) {          
        lotPipeline->bind(commandBuffer);

        for (auto& obj : gameObjects) {
            obj.transform2d.rotation = glm::mod(obj.transform2d.rotation + 0.01f, glm::two_pi<float>());
            
            SimplePushConstantData push{};
            //push.offset = {-0.5f + frame * 0.01f, -0.4f + j * 0.25f};
            //push.color = {0.0f, 0.0f, 0.2f + 0.2f * j};
            push.offset = obj.transform2d.translation;
            push.color = obj.color;
            push.transform = obj.transform2d.mat2();

            vkCmdPushConstants(
                            //commandBuffers[imageIndex], 
                            commandBuffer,
                            pipelineLayout, 
                            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                            0,
                            sizeof(SimplePushConstantData),
                            &push);
            //lotModel->draw(commandBuffers[imageIndex]);
            obj.model->bind(commandBuffer);
            obj.model->draw(commandBuffer);
        }
    }

    void FirstApp::drawFrame() {
        uint32_t imageIndex;
        auto result = lotSwapChain->acquireNextImage(&imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        }
        
        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
            throw std::runtime_error("failed to acquire swap chain image!");

        recordCommandBuffer(imageIndex);
        result = lotSwapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || lotWindow.wasWindowResized()) {
            lotWindow.resetWindowSurfaceFlag();
            recreateSwapChain();
            return;
        }
        if (result != VK_SUCCESS)
            throw std::runtime_error("failed to present swap chain image!");
    }
    */
}