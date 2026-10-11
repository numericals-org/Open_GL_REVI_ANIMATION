#include "render_system.h"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow* window) {
    
    modelLocation = glGetUniformLocation(shader, "model");
    this->window = window;

    ObjectType objectType = ObjectType::eBox;
    AnimationType animationType = AnimationType::eNone;
    MeshFactory meshFactory;
    StaticMesh mesh = meshFactory.make_cube_mesh({0.25f, 0.25f, 0.25f});
    VAOs[objectType][animationType].push_back(mesh.VAO);
    VBOs[objectType][animationType].push_back(mesh.VBO);
    std::string imagePath = std::string(PROJECT_SOURCE_DIR) + "/image/paper.jpg";
    vertexCounts[objectType] = meshFactory.make_texture(imagePath.c_str());

    objectType = ObjectType::eGirl;
    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), {1.0f, 0.0f, 0.0f});
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), {0.0f, 1.0f, 0.0f});
    std::string objPath = std::string(PROJECT_SOURCE_DIR) + "/modal/girl.obj";
    mesh = meshFactory.make_obj_mesh(objPath.c_str(), preTransform);
    VAOs[objectType][animationType].push_back(mesh.VAO);
    VBOs[objectType][animationType].push_back(mesh.VBO);
    vertexCounts[objectType] = mesh.vertexCount;
    std::string starGirlPath = std::string(PROJECT_SOURCE_DIR) + "/image/stargirl.png";
    textures[objectType] = meshFactory.make_texture(starGirlPath.c_str());

    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(
        preTransform, {0.0f, 0.0f, -1.0f}
    );
    preTransform = glm::rotate(preTransform, glm::radians(-90.0f), {0.0f, 0.0f, 1.0f});
    // preTransform = glm::rotate(preTransform, glm::radians(90.0f), {0.0f, 1.0f, 0.0f});
    objectType = ObjectType::eRevy;
    animationType = AnimationType::eRun;
    std::string ReviPath = std::string(PROJECT_SOURCE_DIR) + "/image/Revy_Final.png";
    textures[objectType] = meshFactory.make_texture(starGirlPath.c_str());
    std::stringstream filepath;
    std::string built_filepath;
    for(size_t i = 0; i<19; i++){
        filepath.str("");
        filepath<< "../../modal/Revy_run_0000";
        if(i<=9){
            filepath << "0";
        }
        filepath << i << ".obj";
        built_filepath = filepath.str();
        mesh = meshFactory.make_obj_mesh(built_filepath.c_str(), preTransform);

        VAOs[objectType][animationType].push_back(mesh.VAO);
        VBOs[objectType][animationType].push_back(mesh.VBO);
        vertexCounts[objectType] = mesh.vertexCount;
    }
}
    
void RenderSystem::update(
    std::unordered_map<unsigned int,TransformComponent> &transformComponents,
    std::unordered_map<unsigned int,RenderComponent> &renderComponents,
    std::unordered_map<unsigned int, AnimationComponent> &animationComponent
) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (auto& [entity,renderable] : renderComponents) {

        TransformComponent& transform = transformComponents[entity];
        glm::mat4 model = glm::mat4(1.0f);
	    model = glm::translate(model, transform.position);
	    model = glm::rotate(
            model, glm::radians(transform.euler.z), 
            { 0.0f, 0.0f, 1.0f });
        glUniformMatrix4fv(
		    modelLocation, 1, GL_FALSE, 
		    glm::value_ptr(model));
        
        glBindTexture(GL_TEXTURE_2D, textures[renderable.ObjectType]);
        unsigned int vertexCount = vertexCounts[renderable.ObjectType];
        size_t frame = 0;
        if (renderable.animationType != AnimationType::eNone) {
            frame = static_cast<size_t>(animationComponent[entity].frame); //TODO: change this to add animation!

        }
        glBindVertexArray(VAOs[renderable.ObjectType][renderable.animationType][frame]);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }
	glfwSwapBuffers(window);
}