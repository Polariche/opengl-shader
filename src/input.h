#pragma once

class Input {
private:
    bool up;
    bool left;
    bool right;
    bool down;

public:
    void SetUp(bool up);
    void SetLeft(bool left);
    void SetRight(bool right);
    void SetDown(bool down);

    bool GetUp();
    bool GetLeft();
    bool GetRight();
    bool GetDown();
};