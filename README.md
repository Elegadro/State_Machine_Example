# State Machine Nedir?
State machine, bir nesnenin iç durumu değiştiğinde davranışını değiştirmesini sağlayan davranışsal bir tasarım modelidir. *Finite-state machine* konsepti ile yakından ilişkildir.

Ana fikir, verilen herhangi bir anda programın bulunabileceği sonlu sayıda durumların (state) olmasıdır. Her bir benzersiz durumda program farklı çalışır ve program bir durumdan başka bir duruma geçebilir. Ancak, bulunduğu duruma bağlı olmak üzere program başka durumlara geçebilir veya geçmeyebilir. Bunlar geçiş kurallarıdır, sonlu ve önceden tanımlanmış bu geçiş kurallarına  *transition* denir.

Bu yaklaşımı nesnelere de uygulayabilirsiniz. `Document` adlı bir sınıfımızın olduğunu varsayalım. Doküman şu üç durumdan herhangi birinde olabilir: `Draft`, `Moderation` ve `Published`. Dokümanın `publish` metodu her bir durumda farklı çalışır.

- `Draft` durumunda, dokümanı moderasyona taşır.

- `Moderation` durumunda, dokümanı halka açık yapar ancak mevcut kullanıcı yönetici ise bunu yapar.

- `Published` durumunda ise hiçbir şey yapmaz.

State machines genellikle nesnenin mevcut durumuna bağlı olarak uygun davranışı seçen çok sayıda koşullu ifade (if-switch) ile uygulanır. Genellikle bu "durum" obje alanında bir değeri atar. *Finiti-state* makineleri daha önce hiç duymamış olsanız bile muhtemelen en az bir kez state machine uygulamışsınızdır.

```c++
class Document is
    field state: string
    // ...
    method publish() is
        switch (state)
            "draft":
                state = "moderation"
                break
            "moderation":
                if (currentUser.role == "admin")
                    state = "published
                break
            "published":
                // Do nothing
                break
    // ...
```

# State Machine Neden Kullanılır?

Koşullara dayalı bir state makinesinin en büyük zayıflığı `Document` sınıfına giderek daha fazla durum ve duruma bağlı davranışlar eklemeye başladığınızda ortaya çıkar [bkz. örnek](example1/main.cpp).

Çoğu yöntem, mevcut duruma göre bir yöntemin uygun davranışını seçen devasa koşullar içerecektir. Bu gibi kodların bakımı zordur çünkü geçiş mantığında ki herhangi bir değişiklik her yöntemdeki durum koşullarının değiştirilmesini gerektirebilir. 

Problem proje geliştikçe daha da büyük olabilir. Tasarım aşamasında olası tüm durumları ve geçişleri tahmin etmek oldukça zordur. Bu nedenle, sınırlı bir koşullar kümesiyle oluşturulan yalın bir state makinesi zamanla bir karmaşaya dönüşebilir.  

# State Machine Nasıl Kullanılır?

State modeli, bir nesnenin olası tüm durumlar için yeni sınıflar oluşturmanızı ve duruma özgü tüm davranışları bu sınıflara çıkarmanızı önerir.

Tüm davranışları kendi başına uygulamak yerine, *context* adı verilen orijinal nesne, mevcut durumunu temsil eden state nesnelerinden birine bir referans saklar ve durumla ilgili tüm işleri bu nesneye devreder.

1. Hangi sınıfın *context* olacağına karar verin. Bu, state bağlı koda zaten sahip olan mevcut bir sınıf olabileceği gibi state'e özgü birden fazla sınıfa dağıtılmışsa yeni bir sınıf da olabilir.

2. State interface'i belirleyin. Duruma özgü davranış içerebilecek olanları hedefleyin.

3. Her bir durum için, state interface'den üretilmiş sınıflar oluşturun. Context'in metodlarını gözden geçirin ve bu durumla ilgili tüm kodu yeni oluşturduğunuz sınıfa alın.

    Kodu state klasına alırken, context'in private üyelere bağlı olduğunu görebilirsiniz. Bunun için bir kaç çözüm vardır,

    - Bu alanların veya metodları public yapın.

    - State sınıflarını, context sınıfının içine yerleştirin. Ancak bunu yapabilmeniz için kullanılan dilin iç içe sınıfları desteklemesi gerekmektedir.

4. Context sınıfında, state interface türünde bir referans alanı ekleyin ve bu alanda bulunan değerleri değiştirebilecek public setter ekleyin.

5. Context metodunun tekrar gözden geçirin ve boş state koşullarını state nesnesinin ilgili yöntemlerine yapılan çağrılarla değiştirin.

6. Context'in durumunu değiştirmek için, state sınıflarından birinin örneğini oluşturun ve context'e aktarın. Bunu context'in içerisinde veya istemcide yapabilirsiniz.

[State Machine Örneği 1](./example2/main.cpp)

[State Machine Örneği 2](./example3/main.cpp)