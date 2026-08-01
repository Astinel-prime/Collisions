#include<iostream>
#include<raylib.h>
#include<cmath>



using namespace std;
const float root=sqrt(2);


class Line{
    public:
    float line_x,line_y;
    float normal_x,normal_y;

    float dis_from_line(float x,float y){
        return ((x-line_x)*normal_x)+((y-line_y)*normal_y);
    }
    float speed_normal(float speed_x,float speed_y){
        return speed_x*normal_x+speed_y*normal_y;
    }
    float speed_tangent(float speed_x,float speed_y){
        return speed_x*normal_y-speed_y*normal_x;
    }
};

Line l[4];
class Ball{
    public:
    float x,y;
    float speed_x=0,speed_y=0;
    int radius;

    void Draw(){
        DrawCircle(x,y,radius,YELLOW);
    }
    

    void Update(){
        
    for(int i=0;i<4;i++){
        float dis=l[i].dis_from_line(x,y);
        if(dis<=radius){
            float depth = radius-dis;
            x+=l[i].normal_x*depth;
            y+=l[i].normal_y*depth;
            if(l[i].speed_normal(speed_x,speed_y)<0){
                float s_n=l[i].speed_normal(speed_x,speed_y),s_t=l[i].speed_tangent(speed_x,speed_y);
                speed_x=-(s_n*l[i].normal_x) +
                (s_t*l[i].normal_y);

                speed_y=-(s_n*l[i].normal_y) +
                (s_t*-l[i].normal_x);
            }
        }
    }
        
        x+=speed_x;
        y+=speed_y;

    }

};
Ball ball;

int main(){
    cout<<"Start..."<<endl;
    const int screen_height=1000;
    const int screen_width=1000;

    InitWindow(screen_width,screen_height,"Collision Simulation");
    SetTargetFPS(60);

    ball.x=500;
    ball.y=500;
    ball.radius=20;
    ball.speed_x=10;
    ball.speed_y=0;
    Rectangle r={500,500+250*root,500,500};
    Vector2 v={0,0};
    
    l[0].line_x = 500-250*root;
    l[0].line_y = 500;
    l[0].normal_x=1/root;
    l[0].normal_y=1/root;

    l[1].line_x = 500;
    l[1].line_y = 500-250*root;
    l[1].normal_x=-1/root;
    l[1].normal_y=+1/root;

    l[2].line_x = 500+250*root;
    l[2].line_y = 500;
    l[2].normal_x=-1/root;
    l[2].normal_y=-1/root;

    l[3].line_x=500;
    l[3].line_y=500+250*root;
    l[3].normal_x=+1/root;
    l[3].normal_y=-1/root;

    
    

    while(WindowShouldClose()==false){
        BeginDrawing();
        
        
        ball.Update();

        ClearBackground(BLACK);
        DrawRectanglePro(r,v , 225, DARKGREEN);
        ball.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
    

    
}
