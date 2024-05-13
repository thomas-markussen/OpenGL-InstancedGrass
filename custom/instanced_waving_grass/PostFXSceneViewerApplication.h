#pragma once

#include <ituGL/application/Application.h>

#include <ituGL/scene/Scene.h>
#include <ituGL/texture/FramebufferObject.h>
#include <ituGL/renderer/Renderer.h>
#include <ituGL/camera/CameraController.h>
#include <ituGL/utils/DearImGui.h>
#include <array>

class Texture2DObject;
class TextureCubemapObject;
class Material;

class PostFXSceneViewerApplication : public Application
{
public:
    PostFXSceneViewerApplication();

protected:
    void Initialize() override;
    void Update() override;
    void Render() override;
    void Cleanup() override;

private:
    void InitializeCamera();
    void InitializeLights();
    void InitializeMaterials();
    void InitializeModels();
    void InitializeFramebuffers();
    void InitializeRenderer();

    /// <summary>
    /// Initializes instancing for a mesh. Remember to use SetInstancingCount in the ModelLoader of the provided mesh for this to work.
    /// Yes, the parameters should have been wrapped by a struct, and should probably be using a Builder or Factory for all this.
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="tBounds">The bounds of your translations</param>
    /// <param name="rBounds">The bounds of your rotations (min -> max)</param>
    /// <param name="sBounds">The bounds of your scale (min -> max)</param>
    /// <param name="attr">The VertexAttribute of the mat4 (4 * 4 floats)</param>
    void InitializeInstancing(Mesh& mesh, unsigned int instanceCount, glm::vec3 tBounds, glm::vec2 rBounds, glm::vec2 sBounds, VertexAttribute attr);

    std::shared_ptr<Material> CreatePostFXMaterial(const char* fragmentShaderPath, std::shared_ptr<Texture2DObject> sourceTexture = nullptr);

    Renderer::UpdateTransformsFunction GetFullscreenTransformFunction(std::shared_ptr<ShaderProgram> shaderProgramPtr) const;

    void RenderGUI();

private:
    // Helper object for debug GUI
    DearImGui m_imGui;

    // Camera controller
    CameraController m_cameraController;

    // Global scene
    Scene m_scene;

    // Renderer
    Renderer m_renderer;

    // Skybox texture
    std::shared_ptr<TextureCubemapObject> m_skyboxTexture;

    // Materials
    std::shared_ptr<Material> m_defaultMaterial;
    std::shared_ptr<Material> m_deferredMaterial;
    std::shared_ptr<Material> m_grassMaterial;
    std::shared_ptr<Material> m_composeMaterial;
    std::shared_ptr<Material> m_bloomMaterial;

    // Framebuffers
    std::shared_ptr<FramebufferObject> m_sceneFramebuffer;
    std::shared_ptr<Texture2DObject> m_depthTexture;
    std::shared_ptr<Texture2DObject> m_sceneTexture;
    std::array<std::shared_ptr<FramebufferObject>, 2> m_tempFramebuffers;
    std::array<std::shared_ptr<Texture2DObject>, 2> m_tempTextures;

    // Configuration values
    float m_exposure;
    float m_contrast;
    float m_hueShift;
    float m_saturation;
    glm::vec3 m_colorFilter;
    int m_blurIterations;
    glm::vec2 m_bloomRange;
    float m_bloomIntensity;

    // Grass configuration
    float m_windStrength;
    float m_windSwayFreq;

    glm::vec3 m_bottomColor;
    glm::vec3 m_topColor;
    float m_gradientBias;
};
