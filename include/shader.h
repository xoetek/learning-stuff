#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>

class Shader
{
    public:
    unsigned int ID, vertexShader, fragmentShader;
    int success;
    char infoLog[512];
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};