#ifndef PIXEL_H
#define PIXEL_H

typedef struct pixel_t{
    float r;
    float g;
    float b;
    float a;

    bool operator==(pixel_t other){
        if(     r == other.r &&
                g == other.g &&
                b == other.b &&
                a == other.a){
            return true;
        }
        return false;
    }
}pixel_t;
#define DEFAULTCOLOR {0.0f,0.0f,0.0f,1.0f}
#endif /* !PIXEL_H */
