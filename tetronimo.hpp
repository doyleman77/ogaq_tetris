#pragma once

enum Shape
{
    I = 0,
    L,
    J,
    S,
    Z,
    T,
    O
};

class Tetronimo
{
    public:
        Tetronimo(Shape);
        ~Tetronimo();

        void    update();
    private:
        int x, y;
        int shape[4][4];
}
