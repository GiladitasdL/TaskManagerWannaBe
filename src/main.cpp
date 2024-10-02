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

// to-do lista y Eisenhower M
struct Task {
    std::string title;
    bool isChecked;
    int quadrant; // cuadrantes de la matriz (1-4)
};

// la data como string
std::string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char date[20];
    sprintf(date, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return std::string(date);
}

//  task list
std::vector<Task> tasks = {
    {"Task 1", false, 1},
    {"Task 2", false, 2},
    {"Task 3", false, 3},
    {"Task 4", false, 4}
};

void drawToDoList() {
    ImGui::Begin("To-Do List");
    ImGui::Text("Today's Date: %s", getCurrentDate().c_str());

    ImGui::Separator();
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

        // Q2: No Urgente pero Importante
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
    ImGui::Begin("Important for Tomorrow");
    static char tomorrowTask[128] = "";
    ImGui::InputText("Task", tomorrowTask, sizeof(tomorrowTask));
    if (ImGui::Button("Add Task")) {
        tasks.push_back({tomorrowTask, false, 1});  // Agregar a Q1 por ahora
        strcpy(tomorrowTask, ""); // limpiar input
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
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Task Manager", NULL, NULL);
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

        // Dibuja la UI
        drawToDoList();
        drawEisenhowerMatrix();
        drawTomorrowSection();
        drawCatsSection();

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
