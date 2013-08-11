/*
========================================================================

	Provided standard utilites

========================================================================
*/
package MysticDave;

public class Utils {
    public static final int DIR_NORTH = 0;
    public static final int DIR_EAST  = 1;
    public static final int DIR_SOUTH = 2;
    public static final int DIR_WEST  = 3;

    /**
     * 1 is to the right (+1)
     * 3 is to the left (-1)
     * 0 or 2 are the same
     * @param dir
     * @return
     */
    public static int DirToXAdjustment( int dir ) {
        if ( dir == DIR_EAST ) {
            return 1;
        } else if ( dir == DIR_WEST ) {
            return -1;
        }
        return 0;
    }

    /**
     * 2 is down  (+1)
     * 0 is up (-1)
     * 1 and 3 are the same
     * @param dir
     * @return
     */
    public static int DirToYAdjustment(int dir) {
        if (dir == DIR_SOUTH) {
            return 1;
        } else if (dir == DIR_NORTH) {
            return -1;
        }
        return 0;
    }

    public static int PixToGrid(int pix) {
        return pix / Globals.TILE_DIM;
    }

    public static int GridToPix(int grid) {
        return grid * Globals.TILE_DIM;
    }

    /**
     * linear interpolation between start and end,
     * u = [0,1]
     * @param u
     * @param start
     * @param end
     * @return
     */
    public static float Lerp(float u, float start, float end) {
        return start + u * (end - start);
    }

    /**
     * quadratic interpolation between start and end,
     * u = [0,1]
     * @param u
     * @param start
     * @param w
     * @param end
     * @return
     */
    public static float Quadlerp(float u, float start, float w, float end) {
        return (1 - u) * (1 - u) * start + 2 * u * (1 - u) * w + u * u * end;
    }

    public static int DirFromDelta(int dx, int dy) {
        int retval = 0;
        if (dx > 0) {
            retval = DIR_EAST;
        } else if (dx < 0) {
            retval = DIR_WEST;
        } else if (dy > 0) {
            retval = DIR_SOUTH;
        } else if (dy < 0) {
            retval = DIR_NORTH;
        }
        return retval;
    }
}
