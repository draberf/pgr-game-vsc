/**
*  @file Shaders used in the applications, stored as strings.
* 
* 
* 
*/ 

// VERTEX SHADERS

const auto basicVS = R".(
    #version 460

    layout(location=0)in vec3 position;
    layout(location=1)in vec3 normal;

    uniform mat4 u_view = mat4(1.f);
    uniform mat4 u_proj = mat4(1.f);
    uniform int  u_cels = 0;

    uniform vec3 a_color = (0.6f, 0.f, 0.f);

    out vec3 vColor;

    void main(){

        vec3 pos = position;

        if (u_cels == 1) {
            pos = position + normal*0.06f;
        }

        gl_Position = u_proj*u_view*vec4(pos,1);
        if (u_cels == 1) {
            vColor = vec3(0,0,0);
        } else {
            vColor = vec3(1,0,0);
        }
    }
).";

const auto skyboxVS = R".(

    #version 460

    uniform float offset = 0;
    uniform float xZoom = 2;
    uniform float yZoom = 1;

    out vec2 texCoords;

    void main() {
    
        int quad[] = int[](
            -1, -1,
             1, -1,
             1,  1,

             1,  1,
            -1,  1,
            -1, -1
        );

        if(gl_VertexID>=6){
            gl_Position = vec4(0.f,0.f,0.f,1.f);
            return;
        }

        vec2 pos;
        pos[0] = float(quad[gl_VertexID*2]);
        pos[1] = float(quad[gl_VertexID*2 + 1]);

        gl_Position = vec4(pos,0,1);

        float centerX = offset;
        float centerY = 0.01f;

        vec2 texOffset = (pos + 1) / 2;

        texCoords.x = centerX + texOffset.x * 0.5f/xZoom;
        texCoords.y = centerY + texOffset.y * 0.5f/yZoom;

    }


).";


// FRAGMENT SHADERS


const auto basicFS = R".(
    #version 460
    in vec3 vColor;
    layout(location=0)out vec4 fColor;
    void main(){
        fColor = vec4(vColor,1);
    }
).";

const auto skyboxFS = R".(
    #version 460

    in vec2 texCoords;

    uniform sampler2D sb_tex;

    layout(location=0)out vec4 fColor;
    void main(){
        fColor = texture(sb_tex, texCoords);
    }


).";