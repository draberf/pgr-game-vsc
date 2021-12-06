/**
*  @file Shaders used in the applications, stored as strings.
* 
* 
* 
*/ 

const auto basicVS = R".(
    #version 460

    layout(location=0)in vec3 position;
    layout(location=1)in vec3 normal;

    uniform mat4 u_view = mat4(1.f);
    uniform mat4 u_proj = mat4(1.f);

    out vec3 vColor;

    void main(){
    
        vec3 centered = vec3(position.xy-0.5, position.z+0.5);
    
        gl_Position = u_proj*u_view*vec4(centered,1);
        vColor = vec3(position.xy, -position.z);
    }
).";

const auto celVS = R".(
    #version 460

    layout(location=0)in vec3 position;
    layout(location=1)in vec3 normal;

    uniform mat4 u_view = mat4(1.f);
    uniform mat4 u_proj = mat4(1.f);

    out vec3 vColor;

    void main(){
        
        vec3 centered = vec3(position.xy-0.5, position.z+0.5);
    
        gl_Position = u_proj*u_view*vec4(centered*1.1,1);
        vColor = vec3(0,0,0);
    }
).";

const auto basicFS = R".(
    #version 460
    in vec3 vColor;
    layout(location=0)out vec4 fColor;
    void main(){
        fColor = vec4(vColor,1);
    }
).";