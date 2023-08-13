# State Machine Nedir?
State machine, bir nesnenin iç durumu değiştiğinde davranışını değiştirmesini sağlayan davranışsal bir tasarım modelidir. Sanki nesne sınıfını değiştirmiş gibi olur.

State modeli, *finite-state machine* konsepti ile yakından ilişkildir.

Ana fikir, verilen herhangi bir anda programın bulunacileceği sonlu sayıda durumların (state) olmasıdır. Her bir benzersiz durumda program farklı çalışır ve program bir durumdan başka bir duruma anına geçebilir. Ancak, mevcut duruma bağlı olmak üzere program belirli başka  durumlara geçebilir veya geçmeyebilir. Bunlar geçiş kurallarıdır, sonlu ve önceden tanımlanmış bu geçiş kurallarına  *transition* denir.

Bu yaklaşımı nesnelere de uygulayabilirsiniz. `Document` adlı bir klasımızın olduğunu varsayalım. Doküman şu üç durumdan herhangi birinde olabilir: `Draft`, `Moderation` ve `Published`. Dokümanın `publish` metodu her bir durumda farklı çalışır.

- `Draft` durumunda, dokümanı moderasyona taşır.

- `Moderation` durumunda, dokümanı halka açık yapar ancak mevcut kullanıcı yönetici ise bunu yapar.

- `Published` durumunda ise hiçbir şey yapmaz.

State machines genellikle nesnenin mevcut durumuna bağlı olarak uygun davranışı seçen çok sayıda koşullu ifade (if-switch) ile uygulanır. Genellikle bu "durum" obje alanında bir değeri atar. *finiti-state* makineleri daha önce hiç duymamış olsanız bile muhtemelen en az bir kez state machine uygulamışsınızdır.
Aşağıda ki kod tanıdık geldi mi?

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

Koşullara dayalı bir state makinesinin en büyük zayıflığı `Document` sınıfına giderek daha fazla durum ve duruma bağlı davranışlar eklemeye başladığınızda ortaya çıkar [bkz. örnek](example1/main.cpp.TEMPLATE).

Çoğu yöntem, mevcut duruma göre bir yöntemin uygun davranışını seçen devasa koşullar içerecektir. Bu gibi kodların bakımı zordur çünkü geçiş mantığında ki herhangi bir değişiklik her yöntemdeki durum koşullarının değiştirilmesini gerektirebilir. 

Problem proje geliştikçe daha da büyük olabilir. Tasarım aşamasında olası tüm durumları ve geçişleri tahmin etmek oldukça zordur. Bu nedenle, sınırlı bir koşullar kümesiyle oluşturulan yalın bir state makinesi zamanla bir karmaşaya dönüşebilir.  

# State Machine Nasıl Kullanılır?

State modeli, bir nesnenin olası tüm durumlar için yeni sınıflar oluşturmanızı ve duruma özgü tüm davranışları bu sınıflara çıkarmanızı önerir. 