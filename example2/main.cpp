#include <iostream>
#include <typeinfo>

// Context'in declaration'ı
class Context;

class State
{
    /*
    context_ pointer'ının oluşturulması. Bu sayede Context sınıfına ait değerlerin ve
    metotların State sınıfı içerisinde kullanılması sağlanır.
    Protected olarak tanımlanarak değişkenin bu sınıftan türetilen diğer sınıflar
    tarafından erişilebilmesi sağlanmaktadır.
    Değişken sınıf dışında private'a benzer olarak erişilemez.
    */
protected:
    Context *context_;

public:
    virtual ~State() {}

    void set_context(Context *context)
    {
        this->context_ = context;
    }

    /*
    Bu fonksiyonlar, state interface nesnesinden üretilmiş
    alt sınıflarda bu fonksiyonları tanımlamayı mecbur kılar.
    */
    virtual void Handle1() = 0;
    virtual void Handle2() = 0;
};

class Context
{
private:
    State *state_;

public:
    // Başlangıç durumunun tanımlanması
    Context(State *state) : state_(nullptr)
    {
        this->TransitionTo(state);
    }

    ~Context()
    {
        delete state_;
    }

    // Context'in mevcut durumunu değiştiren fonksiyon
    void TransitionTo(State *state)
    {
        std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        if (this->state_ != nullptr)
            delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }

    // Gelen isteğe göre yürütülecek fonksiyonların çağırılması
    void Request1()
    {
        this->state_->Handle1();
    }

    void Request2()
    {
        this->state_->Handle2();
    }
};

class ConcreteStateA : public State
{
public:
    void Handle1() override;

    void Handle2() override
    {
        std::cout << "ConcreteStateA durumunda bulunan Context, Request2 isteği ile Handle2 fonksiyonunu çalıştırdı.\n";
    }
};

class ConcreteStateB : public State
{
public:
    void Handle1() override
    {
        std::cout << "ConcreteStateB durumunda bulunan Context, Request1 isteği ile Handle1 fonksiyonunu çalıştırdı.\n";
    }

    void Handle2() override
    {
        std::cout << "ConcreteStateB durumunda bulunan Context, Request2 isteği ile Handle2 fonksiyonunu çalıştırdı.\n";
        std::cout << "ConcreteStateB durumunda bulunan Context, durumunu ConcreteStateA'ya değiştirmek istedi.\n";
        this->context_->TransitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::Handle1()
{
    std::cout << "ConcreteStateA durumunda bulunan Context, Request1 isteği ile Handle1 fonksiyonunu çalıştırdı.\n";
    std::cout << "ConcreteStateA durumunda bulunan Context, durumunu ConcreteStateB'ye değiştirmek istedi.\n";
    this->context_->TransitionTo(new ConcreteStateB);
}

// Ana client kodu
void ClientCode()
{
    Context *context = new Context(new ConcreteStateA);
    context->Request1();
    context->Request2();
    context->Request2();
    delete context;
}

int main()
{
    ClientCode();
    return 0;
}