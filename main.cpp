#include<iostream>
#include<raylib.h>
#include<cmath>
#include<random>



#define Grass (Color) {76,175,80,255}
#define Sky (Color) {100, 149, 237,255}


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
        DrawCircle(x,y,radius,WHITE);
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
vector<Ball> b;

int main(){
    cout<<"Start..."<<endl;
    const int screen_height=1000;
    const int screen_width=1000;

    InitWindow(screen_width,screen_height,"Collision Simulation");
    SetTargetFPS(60);
   
  
    ball.x=500;
    ball.y=500;
    ball.radius=20;
    ball.speed_x=7;
    ball.speed_y=-5;
    Rectangle r={500,500+250*root,500,500};
    Vector2 v={0,0};
    Rectangle r1={500,500+300*root,600,600};
    
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

    
    int t=0;

    while(WindowShouldClose()==false){
        BeginDrawing();
        
        
        ball.Update();

        for(int i=0;i<b.size();i++){
            b[i].Update();
        }
        ClearBackground(Grass);
        DrawRectanglePro(r1,v,225,WHITE);
        DrawRectanglePro(r,v , 225, Sky);
        ball.Draw();
        t++;
        if(t==120){
            t=0;
            Ball balls;
            balls.x=500;
            balls.y=500-250;
            balls.radius=20;
            balls.speed_x=GetRandomValue(3,8);
            balls.speed_y=GetRandomValue(3,8);
            b.push_back(balls);

        }
        for(int i=0;i<b.size();i++){
            b[i].Draw();
        }
        

        EndDrawing();
    }
    CloseWindow();
    return 0;
    

    
}
