#include <iostream>

#define PRESS_B
#define PRESS_DOWN
#define RELEASE_DOWN
#define IMAGE_JUMP
#define JUMP_VELOCITY
#define IMAGE_DUCK
#define IMAGE_STAND
#define isJumping_
#define yVelocity_

void setGraphics();

class Heroine
{
private:
    /* data */
public:
    Heroine(/* args */);
    ~Heroine();
    void handleInput(int input);
};

Heroine::Heroine(/* args */)
{
}

Heroine::~Heroine()
{
}

// B tuşuna basıldığında zıpla
void Heroine::handleInput(int input)
{
    if (input == PRESS_B)
    {
        int yVelocity_ = JUMP_VELOCITY;
        setGraphics(IMAGE_JUMP);
    }
}

// Sürekli B'ye basıldığında sürekli zıplayacak yeni bir koşul gerekli
void Heroine::handleInput(int input)
{
    if (input == PRESS_B)
    {
        if (!isJumping_)
        {
            isJumping_ = true;
            yVelocity_ = JUMP_VELOCITY;
            setGraphics(IMAGE_JUMP);
            // Jump
        }
    }
}

// Aşağı tuşa basıldığında karakterimiz eğilsin
void Heroine::handleInput(int input)
{
    if (input == PRESS_B)
    {
        if (!isJumping_)
        {
            isJumping_ = true;
            yVelocity_ = JUMP_VELOCITY;
            setGraphics(IMAGE_JUMP);
            // Jump
        }
    }
    else if (input == PRESS_DOWN)
    {
        if (!isJumping_)
        {
            setGraphics(IMAGE_DUCK);
            // Duck
        }
    }
    else if (input == RELEASE_DOWN)
    {
        setGraphics(IMAGE_STAND);
    }
}

// Bu kod ile kullanıcı eğilerek zıplayabilir ve havadayken aşağı tuşu bıraktığında
// karakter havadayken ayakta durma pozisyonuna geçecektir. Yeni bir koşul zamanı!
void Heroine::handleInput(int input)
{
    if (input == PRESS_B)
    {
        if (!isJumping_ && !isDucking_)
        {
            isJumping_ = true;
            yVelocity_ = JUMP_VELOCITY;
            setGraphics(IMAGE_JUMP);
            // Jump
        }
    }
    else if (input == PRESS_DOWN)
    {
        if (!isJumping_)
        {
            isDucking_ = true;
            setGraphics(IMAGE_DUCK);
            // Duck
        }
    }
    else if (input == RELEASE_DOWN)
    {
        if (isDucking_)
        {
            isDucking_ = false;
            setGraphics(IMAGE_STAND);
            // Stand up
        }
    }
}

// Karakter havada iken aşağı tuşuna basıldığında karakter dive saldırısı gerçekleştirsin
void Heroine::handleInput(int input)
{
    if (input == PRESS_B)
    {
        if (!isJumping_ && !isDucking_)
        {
            isJumping_ = true;
            yVelocity_ = JUMP_VELOCITY;
            setGraphics(IMAGE_JUMP);
            // Jump
        }
    }
    else if (input == PRESS_DOWN)
    {
        if (!isJumping_)
        {
            isDucking_ = true;
            setGraphics(IMAGE_DUCK);
            // Duck
        }
        else
        {
            isJumping_ = false;
            setGraphics(IMAGE_DIVE);
        }
    }
    else if (input == RELEASE_DOWN)
    {
        if (isDucking_)
        {
            isDucking_ = false;
            setGraphics(IMAGE_STAND);
            // Stand up
        }
    }
}

// VE TEKRARDAN BUG BULMACA...