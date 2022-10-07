#ifndef SHADER_H
#define SHADER_H

extern "C" {
#include "glload.h"
}

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
    // ID - идентификатор программы
    unsigned int ID;

    // Конструктор считывает данные и выполняет построение шейдера
    Shader(const char* vertexPath, const char* fragmentPath);

    // Использование/активация шейдера
    void use();

    // Полезные uniform-функции
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    //void setMat4v(const std::string& name, glm::mat4 value) const;

private:
    // Полезные функции для проверки ошибок компиляции/связывания шейдеров
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif