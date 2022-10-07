#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // Этап №1: Получение исходного кода вершинного/фрагментного шейдера из переменной filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Убеждаемся, что объекты ifstream могут выбросить исключение
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Открываем файлы
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // Считываем содержимое файловых буферов в потоки 
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Закрываем файлы
        vShaderFile.close();
        fShaderFile.close();

        // Конвертируем данные из потока в строковые переменные
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Этап №2: Компилируем шейдеры
    unsigned int vertex, fragment;

    // Вершинный шейдер
    vertex = bglCreateShader(GL_VERTEX_SHADER);
    bglShaderSource(vertex, 1, &vShaderCode, NULL);
    bglCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Фрагментный шейдер
    fragment = bglCreateShader(GL_FRAGMENT_SHADER);
    bglShaderSource(fragment, 1, &fShaderCode, NULL);
    bglCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Шейдерная программа
    ID = bglCreateProgram();
    bglAttachShader(ID, vertex);
    bglAttachShader(ID, fragment);
    bglLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // После того, как мы связали шейдеры с нашей программой, удаляем их, так как они нам больше не нужны
    bglDeleteShader(vertex);
    bglDeleteShader(fragment);
}

// Использование/активация шейдера
void Shader::use()
{
    bglUseProgram(ID);
}

// Полезные uniform-функции
void Shader::setBool(const std::string& name, bool value) const
{
    bglUniform1i(bglGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    bglUniform1i(bglGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    bglUniform1f(bglGetUniformLocation(ID, name.c_str()), value);
}

//void Shader::setMat4v(const std::string& name, glm::mat4 value) const
//{
//    bglUniformMatrix4fv(bglGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
//}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        bglGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            bglGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        bglGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            bglGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}