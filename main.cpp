#include<iostream>
#include<raylib.h>
#include<cmath>
#include<random>

#include<algorithm>

#define Grass (Color) {76,175,80,255}
#define Sky (Color) {100, 149, 237,255}


using namespace std;
const float root=sqrt(2);

class Point{
    public: 
    float x,y;
};



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

class LineSeg{
    public:
    float l_x,l_y,r_x,r_y;
    float normal_x,normal_y;
    float len;

    float dis_from_line(float x,float y){
        return ((x-l_x)*normal_x)+((y-l_y)*normal_y);
    }
    
    float tdis1(float x,float y){
        return (x-l_x)*-normal_y+(y-l_y)*normal_x;
    }
    float tdis2(float x,float y){
        return (x-r_x)*-normal_y+(y-r_y)*normal_x;
    }
    float speed_normal(float speed_x,float speed_y){
        return speed_x*normal_x+speed_y*normal_y;
    }
    float speed_tangent(float speed_x,float speed_y){
        return speed_x*normal_y-speed_y*normal_x;
    }
};
vector<LineSeg> edge;


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
        if(dis>radius||dis<-radius) continue;
        if(dis<=radius){
            float depth = radius-abs(dis);
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
    

    for(int i=0;i<edge.size();i++){
        LineSeg seg=edge[i];
        float dis=seg.dis_from_line(x,y);
        if(abs(dis)<=radius){
            float t1=seg.tdis1(x,y),t2=seg.tdis2(x,y);
            if(t1<=0 && t2>=0){
                float depth=radius-abs(dis);
                if(dis<0) depth=-depth;
                x+=seg.normal_x*depth;
                y+=seg.normal_y*depth;
            
            float s_n=seg.speed_normal(speed_x,speed_y);
            float s_t=seg.speed_tangent(speed_x,speed_y);
            if((dis>=0 && s_n<0)||(dis<0&&s_n>0)){
                s_n=-s_n;
                speed_x=s_n*seg.normal_x+s_t*seg.normal_y;
                speed_y=s_n*seg.normal_y-s_t*seg.normal_x;
            }
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
    SetTargetFPS(30);
   
  
    ball.x=500;
    ball.y=500;
    ball.radius=10;
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

    vector<Vector2> points,points1;
    int j=0;
    float last_x=320,last_y=380;
    for(int i=0;i<50;i++){
        float pos_x,pos_y=GetRandomValue(380,440);
        
        pos_x=last_x;
        last_x+=3;
    
        Vector2 vec={pos_x,pos_y};
        points.push_back(vec);
        
    }
    for(int i=0;i<60;i++){
        float pos_x=last_x,pos_y=GetRandomValue(455,520);
        
        last_x-=2;

    
        Vector2 vec={pos_x,pos_y};
        points.push_back(vec);
        points1.push_back(vec);
        
    }
    
    points.push_back(points[0]);
    vector<LineSeg> edges;
    for(int i=0;i<points.size()-1;i++){
    
        LineSeg ls;
        ls.l_x=points[i].x;
        ls.l_y=points[i].y;
        ls.r_x=points[i+1].x;
        ls.r_y=points[i+1].y;
        ls.len=sqrt((points[i].x-points[i+1].x)*(points[i].x-points[i+1].x)+(points[i].y-points[i+1].y)*(points[i].y-points[i+1].y));


        ls.normal_x=-(points[i+1].y-points[i].y)/ls.len;
        ls.normal_y=(points[i+1].x-points[i].x)/ls.len;
        edges.push_back(ls);
        
    }
    edge=edges;
    

    
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
 
        
        
        for(int i=0;i<9;i++){
            vector<Vector2> parts;
            parts.push_back(points[i]);
            parts.push_back(points1[i]);
            parts.push_back(points[i+1]);
            DrawTriangleStrip(parts.data(),parts.size(),WHITE);
          
            parts.clear();
            parts.push_back(points[i]);
            parts.push_back(points1[i]);
            parts.push_back(points[i+1]);
            DrawTriangleStrip(parts.data(),parts.size(),WHITE);
        }
        
  
        
        ball.Draw();
        t++;
        if(t==120){
            t=0;
            Ball balls;
            balls.x=500;
            balls.y=500-250;
            balls.radius=10;
            balls.speed_x=GetRandomValue(3,4);
            balls.speed_y=GetRandomValue(3,4);
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
