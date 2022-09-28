#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Common.h"
#include "Math.h"
#include "Particle.h"


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 3) in mat4 instanceMatrix;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0f);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.8f, 0.8f, 1.0f);\n"
"}\n\0";

// View parameters
float theta = 0.0;
float phi = 0.0;
float camradius = 5.0;
float cameraspeed = 0.02;

float camX = camradius;
float camY = 0.0;
float camZ = 0.0;

struct RenderData
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};


// Allow window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Keyboard input: JKIL for camera motion (also escape to close window)
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    // J key will rotate left
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        theta -= cameraspeed;
        if (theta < 0.0) theta += 360.0;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
    // L key will rotate right
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        theta += cameraspeed;
        if (theta >= 360.0) theta -= 360.0;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
    // I key will rotate right
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        if (phi < 90.0-cameraspeed) phi += cameraspeed;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
    // K key will rotate right
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        if (phi > -90.0+cameraspeed) phi -= cameraspeed;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
}


// This is a really bad "ball" - just an octahedron
float br = 0.02; // ball radius
/*
float ball[] = {
    // positions   
     br,  0,  0,   // triangle 1
      0, br,  0,   
      0,  0, br, 
      0, br,  0,  // triangle 2
    -br,  0,  0,   
      0,  0, br,  
    -br,  0,  0,    // triangle 3
      0,-br,  0,   
      0,  0, br,  
      0,-br,  0,   // triangle 4
     br,  0,  0,   
      0,  0, br,  
     br,  0,  0,    // triangle 5
      0,-br,  0,  
      0,  0,-br,  
      0,-br,  0,  // triangle 6
    -br,  0,  0,   
      0,  0,-br,   
    -br,  0,  0,   // triangle 7
      0, br,  0,  
      0,  0,-br,  
      0, br,  0,    // triangle 8
     br,  0,  0,   
      0,  0,-br,   
};
float ball[] = {
    // positions         // colors
     br,  0,  0,   1.0f, 1.0f, 1.0f, // triangle 1
      0, br,  0,   1.0f, 1.0f, 1.0f,
      0,  0, br,   1.0f, 1.0f, 1.0f,
      0, br,  0,   1.0f, 1.0f, 1.0f, // triangle 2
    -br,  0,  0,   1.0f, 1.0f, 1.0f,
      0,  0, br,   1.0f, 1.0f, 1.0f,
    -br,  0,  0,   1.0f, 1.0f, 1.0f, // triangle 3
      0,-br,  0,   1.0f, 1.0f, 1.0f,
      0,  0, br,   1.0f, 1.0f, 1.0f,
      0,-br,  0,   1.0f, 1.0f, 1.0f, // triangle 4
     br,  0,  0,   1.0f, 1.0f, 1.0f,
      0,  0, br,   1.0f, 1.0f, 1.0f,
     br,  0,  0,   1.0f, 1.0f, 1.0f, // triangle 5
      0,-br,  0,   1.0f, 1.0f, 1.0f,
      0,  0,-br,   1.0f, 1.0f, 1.0f,
      0,-br,  0,   1.0f, 1.0f, 1.0f, // triangle 6
    -br,  0,  0,   1.0f, 1.0f, 1.0f,
      0,  0,-br,   1.0f, 1.0f, 1.0f,
    -br,  0,  0,   1.0f, 1.0f, 1.0f, // triangle 7
      0, br,  0,   1.0f, 1.0f, 1.0f,
      0,  0,-br,   1.0f, 1.0f, 1.0f,
      0, br,  0,   1.0f, 1.0f, 1.0f, // triangle 8
     br,  0,  0,   1.0f, 1.0f, 1.0f,
      0,  0,-br,   1.0f, 1.0f, 1.0f,
};
*/


std::vector<glm::vec3> vertices = {
    glm::vec3(br,   0.0f, 0.0f),    
    glm::vec3(0.0f, br,   0.0f),
    glm::vec3(0.0f, 0.0f, br),
    glm::vec3(-br,  0.0f, 0.0f),
    glm::vec3(0.0f, -br,  0.0f),
    glm::vec3(0.0f, 0.0f, -br),
};

std::vector<unsigned int> indices = {
    2, 0, 1, 
    2, 1, 3, 
    2, 3, 4, 
    2, 4, 0,
    5, 0, 1,
    5, 1, 3,
    5, 3, 4,
    5, 4, 0
};


class Renderer 
{
private:
    GLFWwindow* window_;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
  
    // unsigned int boxbuffer_;
    // unsigned int ballbuffer_;
    // unsigned int VAO;

    RenderData render_data_;

    unsigned int modelLoc;
    unsigned int viewLoc;
    unsigned int projectionLoc;

    unsigned int shaderProgram;
    unsigned int fragmentShader;
    unsigned int vertexShader;

    unsigned int position_buffer;
    float positions_[PARTICLE_NUMBER * 4];
    // std::vector<Particle*> particle_list_;

    glm::mat4* modelMatrices_;

    float ballposition[3] = {-1.0, -1.0, 1.0};
    

    void shut_down()
    {
        // glDeleteVertexArrays(1, &VAO);
        // glDeleteBuffers(1, &boxbuffer_);
        // glDeleteBuffers(1, &ballbuffer_);
        glDeleteBuffers(1, &render_data_.VAO);
        glDeleteBuffers(1, &render_data_.VBO);
        glDeleteBuffers(1, &render_data_.EBO);

        glDeleteProgram(shaderProgram);

        glfwTerminate();
    }


public:
    Renderer() {
        modelMatrices_ = new glm::mat4[PARTICLE_NUMBER];
    }
    ~Renderer() {}

    // void initialize(std::vector<Particle*> const &particle_list)
    void initialize()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window_ = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PARTICLE_SYSTEM", NULL, NULL);
        if (window_ == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window_);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

        glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

        // Enable depth buffering, backface culling
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // vertex shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // fragment shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glUseProgram(shaderProgram);

        // setupMesh
        glGenVertexArrays(1, &render_data_.VAO);
        glGenBuffers(1, &render_data_.VBO);
        glGenBuffers(1, &render_data_.EBO);
    
        glBindVertexArray(render_data_.VAO);
            glBindBuffer(GL_ARRAY_BUFFER, render_data_.VBO);

            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);  

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_data_.EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            // vertex positions
            glEnableVertexAttribArray(0);	
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
            // // vertex normals
            // glEnableVertexAttribArray(1);	
            // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
            // // vertex texture coords
            // glEnableVertexAttribArray(2);	
        // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        glBindVertexArray(0);

        // configure instanced array
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, PARTICLE_NUMBER * sizeof(glm::mat4), &modelMatrices_[0], GL_STATIC_DRAW);


        glBindVertexArray(render_data_.VAO);
            GLsizei vec4Size = sizeof(glm::vec4);
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(vec4Size));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(2 * vec4Size));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(3 * vec4Size));

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);
        glBindVertexArray(0);

        /*
        // Set up vertex array object (VAO) and vertex buffers for box and ball
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

            glGenBuffers(1, &boxbuffer_);
            glBindBuffer(GL_ARRAY_BUFFER, boxbuffer_);
                glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);


            glGenBuffers(1, &ballbuffer_);
            glBindBuffer(GL_ARRAY_BUFFER, ballbuffer_);
                glBufferData(GL_ARRAY_BUFFER, sizeof(ball), ball, GL_STATIC_DRAW);

            // configure instanced array for particles
            glGenBuffers(1, &position_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
                glBufferData(GL_ARRAY_BUFFER, PARTICLE_NUMBER * 4 * sizeof(float), &positions_, GL_STATIC_DRAW);
  

        // Declare model/view/projection matrices
        model = glm::mat4(1.0f);
        modelLoc = glGetUniformLocation(shaderProgram, "model");
        */
              
        view = glm::mat4(1.0f);
        viewLoc = glGetUniformLocation(shaderProgram, "view");
        projection = glm::mat4(1.0f);
        projectionLoc = glGetUniformLocation(shaderProgram, "projection");

        // Set Projection matrix
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // particle_list_ = particle_list;
        update_position(0.0);


        // for(int i = 0; i < PARTICLE_NUMBER; i++)
        // {
        //     glGenBuffers(1, &particle_vaos_[i]);
        //     glBindBuffer(GL_ARRAY_BUFFER, particle_vaos_[i]);
        //     glBufferData(GL_ARRAY_BUFFER, sizeof(ball), ball, GL_STATIC_DRAW);

        //     glBindVertexArray(particle_vaos_[i]);
        //     glEnableVertexAttribArray(0);
        //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        //     glEnableVertexAttribArray(1);
        //     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        //     glVertexAttribDivisor(0, 1);
        //     glVertexAttribDivisor(1, 1);

        //     glBindVertexArray(0);
        // }

    }

    void update_position(float n)
    {
        for(int i = 0; i < PARTICLE_NUMBER; i++)
        {
            // v = particle_list_.at(i)->get_transformed_postion_for_renderer();

            // positions_[i*4 + 0] = ballposition[0] + 0.001 * i;
            // positions_[i*4 + 1] = ballposition[1] + 0.001 * i;
            // positions_[i*4 + 2] = ballposition[2] - n * 0.001;
            // positions_[i*4 + 3] = 0;


            model = glm::mat4(1.0f);
            model = glm::translate(model, (glm::vec3(ballposition[0] + 0.001 * i,
                                                     ballposition[1] + 0.001 * i, 
                                                     ballposition[2] - n * 0.001)));
            modelMatrices_[i] = model;
        }
    }

    void start_looping() 
    {
        while (!glfwWindowShouldClose(window_)) {
            processInput(window_);
            // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Set view matrix
            view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


            glBindVertexArray(render_data_.VAO);
                glDrawElementsInstanced(
                    GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0, PARTICLE_NUMBER
                );
            glBindVertexArray(0); 
            
            /*
            for(GLuint i = 0; i < PARTICLE_NUMBER; i++)
            {
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrices_[i]));
                glDrawArrays(GL_TRIANGLES, 0, 24);
            }*/
    
            /*
            // render the box
            glBindBuffer(GL_ARRAY_BUFFER, boxbuffer_);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
                
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
                
                model = glm::mat4(1.0f);
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                glDrawArrays(GL_TRIANGLES, 0, 36);

            // update the position buffer
            glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
                glBufferSubData(GL_ARRAY_BUFFER, 0, PARTICLE_NUMBER * 4 * sizeof(float), &positions_);

            glBindBuffer(GL_ARRAY_BUFFER, ballbuffer_);
                // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);    
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));             
            
            glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
                glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
                glVertexAttribDivisor(3, 1);
                glDrawArraysInstanced(GL_TRIANGLES, 0, 6 * sizeof(float), PARTICLE_NUMBER);
                */


            // // render the ball
            // glBindBuffer(GL_ARRAY_BUFFER, ballbuffer_);
            // // position attribute
            // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            // glEnableVertexAttribArray(0);
            // // color attribute
            // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            // glEnableVertexAttribArray(1);
            // // Translate ball to its position and draw
            // model = glm::mat4(1.0f);
            // model = glm::translate(model, glm::vec3(ballposition[0], ballposition[1], ballposition[2]));
            // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            // glDrawArrays(GL_TRIANGLES, 0, 24);

            glfwSwapBuffers(window_);

            glfwPollEvents();
        }
    }

};


#endif // RENDERER_H_