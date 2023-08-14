#include <iostream>
#include <opencv2/opencv.hpp>

class Context;

class State
{
protected:
    Context *context_;

public:
    virtual ~State() {}

    void set_context(Context *context)
    {
        this->context_ = context;
    }

    virtual void handleRequest1() = 0;
    virtual void handleRequest2() = 0;
    virtual void update() = 0;
};

class Context
{
private:
    State *state_;

public:
    cv::Mat image;

    Context(State *state, cv::Mat image) : state_(nullptr)
    {
        this->TransitionTo(state);
        this->image = image;
    }

    ~Context()
    {
        delete state_;
    }

    void TransitionTo(State *state)
    {
        if (this->state_ != nullptr)
            delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }

    void handleRequest1()
    {
        this->state_->handleRequest1();
    }

    void handleRequest2()
    {
        this->state_->handleRequest2();
    }

    void update()
    {
        this->state_->update();
    }
};

class HandleState1 : public State
{
public:
    void handleRequest1() override
    {
        std::cout << "Handle1.\n";
        
    }

    void handleRequest2() override;

    void update() override
    {
        cv::putText(this->context_->image, "Handle1", cv::Point(10, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        cv::imshow("Image", this->context_->image);
    }
};

class HandleState2 : public State
{
public:
    void handleRequest1() override
    {
        std::cout << "Transition to Handle1.\n";
        this->context_->TransitionTo(new HandleState1);
    }

    void handleRequest2() override
    {
        std::cout << "Handle2.\n";
        
    }

    void update() override
    {
        cv::putText(this->context_->image, "Handle2", cv::Point(10, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 2);
        cv::imshow("Image", this->context_->image);
    }
};

void HandleState1::handleRequest2()
{
    std::cout << "Transition to Handle2.\n";
    this->context_->TransitionTo(new HandleState2);
}

int main()
{
    cv::Mat image = cv::imread("../../example3/img/image.png");
    Context *context = new Context(new HandleState1, image);
    context->handleRequest1();
    while (true)
    {
        context->image = cv::imread("../../example3/img/image.png");
        context->update();
        char c = (char)cv::waitKey(1);
        if (c == 27)
            break;
        else if (c == '1')
            context->handleRequest1();
        else if (c == '2')
            context->handleRequest2();
    }
    return 0;
}