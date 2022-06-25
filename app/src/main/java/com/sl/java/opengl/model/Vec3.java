package com.sl.java.opengl.model;

/*********************************************************************
 * Created by shenglei on 2022/6/25.
 *********************************************************************/
public class Vec3 {
    public float x = 0f;
    public float y = 0f;
    public float z = 0f;

    public Vec3() {

    }

    public Vec3(float x, float y, float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public static Vec3 add(Vec3 vec1, Vec3 vec2) {
        return new Vec3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
    }

    public static Vec3 minus(Vec3 vec1, Vec3 vec2) {
        return add(vec1, vec2.negative());
    }

    public Vec3 multiply(float value) {
        return new Vec3(x*value, y*value, z*value);
    }

    public Vec3 negative() {
        return new Vec3(-x, -y, -z);
    }
}
