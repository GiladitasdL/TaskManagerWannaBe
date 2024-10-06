#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

// struct para tasks
struct Task {
    std::string title;  // Use std::string for text
    bool isChecked;
    int id;
    int quadrant; // cuadrantes de la matriz (1-4)
    Task(const std::string& title, bool isChecked, int id) : title(title), isChecked(isChecked), id(id) {};
};

char newTaskBuffer[140] = "";  // Buffer to input tasks


// fecha
std::string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char date[20];
    sprintf(date, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return std::string(date);
}
std::vector<Task> tasks ;
std::vector<Task> tasksTomorrow;

void drawToDoList() {
    ImGui::SetNextWindowSize(ImVec2(300.0f, 450.0f));  // dimensions
    ImGui::SetNextWindowPos(ImVec2(50.0f, 50.0f));   // pos X = 200, pos Y = 100

    ImGui::Begin("To-Do List");

    ImGui::Text("Today's Date: %s", getCurrentDate().c_str());
    ImGui::Separator();
    // Display task input box 
    ImGui::InputText("New Task", newTaskBuffer, sizeof(newTaskBuffer));
    //the button or enter 
    bool addTaskPressed = ImGui::Button("Add Task");

    if (ImGui::IsKeyPressed(ImGuiKey_Enter)) {
        addTaskPressed = true; //Enter 
    }

    if (addTaskPressed) {
        if (strlen(newTaskBuffer) > 0) {
            tasks.emplace_back(newTaskBuffer, false, tasks.size()+ 1);
            newTaskBuffer[0] = '\0';  // Clear 
        }
    }
    for (size_t i = 0; i < tasks.size(); ++i) {
        ImGui::Checkbox(tasks[i].title.c_str(), &tasks[i].isChecked);
    }

    ImGui::End();
}
void drawEisenhowerMatrix() {

    ImGui::Begin("Eisenhower Matrix");

    if (ImGui::BeginTable("Matrix", 2)) {
        // Q1: Urgente  Importante
        ImGui::TableNextColumn();
        ImGui::Text("Urgent & Important (Q1)");
        for (auto& task : tasks) {
            if (task.quadrant == 1)
                ImGui::Text(task.title.c_str());
        }

        // Q2: No urgente pero Importante
        ImGui::TableNextColumn();
        ImGui::Text("Not Urgent but Important (Q2)");
        for (auto& task : tasks) {
            if (task.quadrant == 2)
                ImGui::Text(task.title.c_str());
        }

        ImGui::TableNextColumn();
        // Q3: Urgente pero No Importante
        ImGui::Text("Urgent but Not Important (Q3)");
        for (auto& task : tasks) {
            if (task.quadrant == 3)
                ImGui::Text(task.title.c_str());
        }

        ImGui::TableNextColumn();
        // Q4: Ni Urgente ni Importante
        ImGui::Text("Neither Urgent nor Important (Q4)");
        for (auto& task : tasks) {
            if (task.quadrant == 4)
                ImGui::Text(task.title.c_str());
        }
        ImGui::EndTable();
    }

    ImGui::End();
}

void drawTomorrowSection() {

    ImGui::SetNextWindowSize(ImVec2(300.0f, 450.0f));  // dimensions
    ImGui::SetNextWindowPos(ImVec2(400.0f, 50.0f));   // pos X = , pos Y = 

    ImGui::Begin("Important for tomorrow");
    static char tomorrowTask[128] = "";
    ImGui::InputText("Task", tomorrowTask, sizeof(tomorrowTask));
    //si se toca el boton o el enter
    bool addTaskPressed = ImGui::Button("Add Task");

    if (ImGui::IsKeyPressed(ImGuiKey_Enter)) {
        addTaskPressed = true; //si se presiona enter
    }

    if (addTaskPressed){
         if (strlen(tomorrowTask) > 0) {
             // agrega a la lista
                tasksTomorrow.emplace_back(tomorrowTask, false, tasksTomorrow.size()+ 1);
                tomorrowTask[0] = '\0';  // Clear buffer after adding
            }
            
    }

    for (size_t i = 0; i < tasksTomorrow.size(); ++i) {
        ImGui::Checkbox(tasksTomorrow[i].title.c_str(), &tasksTomorrow[i].isChecked);
    }
    ImGui::End();
}

void drawCatsSection() {
    ImGui::Begin("Congratulations, You Did It!");
    ImGui::Text("Every completed task earns a cat picture!");

    // imagen del gatito
    ImGui::Text("Cat Image Placeholder");  // Aca va el codigo para renderizar el cat

    ImGui::End();
}

int main() {
    // Initializar GLFW
    if (!glfwInit()) {
        std::cerr << "No pude inicializar GLFW!" << std::endl;
        return -1;
    }

    // Setup OpenGL 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // crear ventana
    GLFWwindow* window = glfwCreateWindow(920, 550, "Task Manager", NULL, NULL);

    if (!window) {
        std::cerr << "No pude construir la ventana!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    //  OpenGL funciones con GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "No pude inicializar GLAD!" << std::endl;
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Main 
    while (!glfwWindowShouldClose(window)) {
        // Poll events
        glfwPollEvents();

        // inicializar ImGui 
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glViewport(0, 0, 1280, 720); // OpenGL viewport
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);  
        glClear(GL_COLOR_BUFFER_BIT);

        // Dibuja la UI
        drawToDoList();
      //  drawEisenhowerMatrix();
        drawTomorrowSection();
       // drawCatsSection();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, 1280, 720);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
