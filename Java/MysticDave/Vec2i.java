/*
========================================================================

	A 2D vector class, integers

========================================================================
*/
package MysticDave;

public class Vec2i {
    
    public int x;
    public int y;
    
    public Vec2i() {
            x = y = 0;
    }

    public Vec2i( int x, int y ) {
            this.x = x;
            this.y = y;
    }

    public void Set( int x, int y ) {
            this.x = x;
            this.y = y;
    }

    public void Set( Vec2i v ) {
            this.x = v.x;
            this.y = v.y;
    }

    public int Dot( int x, int y ) {
            return this.x * x + this.y * y;
    }

    public int Dot( Vec2i target ) {
            return (x * target.x) + (y * target.y);
    }

    public void Neg() {
            x = -x;
            y = -y;
    }

    public static void Neg( Vec2i source, Vec2i retval ) {
            retval.x = -source.x;
            retval.y = -source.y;
    }

    public void Plus( Vec2i target ) {
            this.x += target.x;
            this.y += target.y;
    }

    public void Plus( int x, int y ) {
            this.x += x;
            this.y += y;
    }

    public static void Plus( Vec2i A, Vec2i B, Vec2i retval ) {
            retval.x = A.x + B.x;
            retval.y = A.y + B.y;
    }

    public void Sub( Vec2i target ) {
            this.x -= target.x;
            this.y -= target.y;
    }

    public static void Sub( Vec2i A, Vec2i B, Vec2i retval ) {
            retval.x = A.x - B.x;
            retval.y = A.y - B.y;
    }

    public void Mult( int val ) {
            x *= val;
            y *= val;
    }

    public static void Mult( Vec2i target, int val, Vec2i retval ) {
            retval.x = target.x * val;
            retval.y = target.y * val;
    }

    public float Norm() {
            return (float)(Math.sqrt( x*x + y*y ));
    }

    public int Norm2() {
            return x*x + y*y;
    }

    public static float Dist( Vec2i A, Vec2i B ) {
            int dx = A.x - B.x;
            int dy = A.y - B.y;
            return (float)(Math.sqrt( dx*dx + dy*dy ));
    }

}
