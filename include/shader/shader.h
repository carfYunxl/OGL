#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    struct ShaderSource
    {
        std::string vertex;
        std::string fragment;
        //std::string geometry;
    };
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1/*, GEOMETRY = 2*/
    };

	//程序ID
	unsigned int ID;

	//构造器读取并构建着色器
	Shader(const std::string& filepath);

	//使用/激活程序
	void use();

	//uniforg工具函数
	void setBool(const std::string& name,bool value)const;
	void setInt(const std::string& name,int value)const;
	void setFloat4(const std::string& name,float value1, float value2, float value3, float value4)const;
    void setFloat(const std::string& name, float value)const;

    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w);
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
    ShaderSource ParserShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vShader, const std::string& fShader);
private:
	void checkCompileErrors(GLuint shader, std::string type);
};


#endif