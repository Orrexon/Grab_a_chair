/* date = August 15th 2022 3:22 pm */

#ifndef APP_MATH_H

union v2
{
    struct
    {
        float x, y;
    };
    float e[2];
};

union v2i
{
    struct
    {
        int x, y;
    };
    int e[2];
};

v2i V2i(v2 A)
{
    v2i Result = {0};
    Result.x = (int)A.x;
    Result.y = (int)A.y;
    
    return Result;
}

v2 V2(float x, float y)
{
    v2 v;
    v.x=x; 
    v.y=y;
    
    return v;
}

v2 V2Zero()
{
    return V2(0,0);
}

v2 operator+(v2 A, v2 B)
{
    v2 Result;
    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    
    return Result;
}

v2 operator+(v2 A, float B)
{
    v2 Result;
    Result.x = A.x + B;
    Result.y = A.y + B;
    
    return Result;
}

v2 operator+(float A, v2 B)
{
    v2 Result;
    Result = B + A;
    
    return Result;
}

v2 operator-(v2 A, v2 B)
{
    v2 Result;
    Result.x = A.x - B.x;
    Result.y = A.y - B.y;
    
    return Result;
}

v2 operator-(v2 A, float B)
{
    v2 Result;
    Result.x = A.x - B;
    Result.y = A.y - B;
    
    return Result;
}

v2 operator-(float A, v2 B)
{
    v2 Result;
    Result = B - A;
    
    return Result;
}

v2 operator-(v2 A)
{
    v2 Result = V2(-A.x, -A.y);
    return Result;
}

v2 operator*(v2 A, float B)
{
    v2 Result;
    Result.x = A.x * B;
    Result.y = A.y * B;
    
    return Result;
}

v2 operator*(float A, v2 B)
{
    v2 Result;
    Result = B * A;
    
    return Result;
}

void operator+=(v2& A ,v2 B)
{
    A = A + B;
}


void operator-=(v2& A ,v2 B)
{
    A = A - B;
}

bool operator==(v2 A, v2 B)
{
    return (A.x == B.x && A.y == B.y);
}

bool operator!=(v2 A, v2 B)
{
    return (A.x != B.x && A.y != B.y);
}

float Inner(v2 A, v2 B)
{
    float Result = A.x * B.x + A.y * B.y;
    return Result;
}


union v3
{
    struct
    {
        float x, y, z;
    };
    float e[3];
};


v3 V3(float x, float y, float z)
{
    v3 v;
    v.x=x; 
    v.y=y;
    v.z=z;
    
    return v;
}

v3 operator+(v3 A, v3 B)
{
    v3 Result;
    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    Result.z = A.z + B.z;
    
    return Result;
}

v3 operator+(v3 A, float B)
{
    v3 Result;
    Result.x = A.x + B;
    Result.y = A.y + B;
    Result.z = A.z + B;
    
    return Result;
}

v3 operator+(float A, v3 B)
{
    v3 Result;
    Result = B + A;
    
    return Result;
}

v3 operator-(v3 A, v3 B)
{
    v3 Result;
    Result.x = A.x - B.x;
    Result.y = A.y - B.y;
    Result.z = A.z - B.z;
    
    return Result;
}

v3 operator-(v3 A, float B)
{
    v3 Result;
    Result.x = A.x - B;
    Result.y = A.y - B;
    Result.z = A.z - B;
    
    return Result;
}

v3 operator-(float A, v3 B)
{
    v3 Result;
    Result = B - A;
    
    return Result;
}

v3 operator-(v3 A)
{
    v3 Result = V3(-A.x, -A.y, -A.z);
    return Result;
}

v3 operator*(v3 A, float B)
{
    v3 Result;
    Result.x = A.x * B;
    Result.y = A.y * B;
    Result.z = A.z * B;
    
    return Result;
}

v3 operator*(float A, v3 B)
{
    v3 Result;
    Result = B * A;
    
    return Result;
}

float Inner(v3 A, v3 B)
{
    float Result = A.x * B.x + A.y * B.y + A.z * B.z;
    return Result;
}

v3 Cross(v3 A, v3 B)
{
    v3 Result;
    Result.x = A.y*B.z - A.z*B.y;
    Result.y = A.z*B.x - A.x*B.z;
    Result.z = A.x*B.y - A.y*B.x;
    
    return Result;
}

v3 Normalize(v3 V)
{
    v3 Result = {0};
    float len = sqrt(Inner(V,V));//intrinsics
    Result.x = V.x/len;
    Result.y = V.y/len;
    Result.z = V.z/len;
    
    return Result;
}

bool operator==(v3 A, v3 B)
{
    bool Result = false;
    Result = (A.x == B.x &&
              A.y == B.y &&
              A.z == B.z);
    
    return Result;
}

#define APP_MATH_H
#endif //APP_MATH_H
