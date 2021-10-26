# Motoca infantil no parque (composição, solver, manual)

![](figura.jpg)

<!--TOC_BEGIN-->
- [Requisitos](#requisitos)
- [Shell](#shell)
- [Ajuda](#ajuda)
- [Diagrama](#diagrama)
- [Esqueleto](#esqueleto)
- [Resolução](#resolução)
<!--TOC_END-->

Você já deve ter ido em algum parque e viu crianças de 4 a 10 anos andando naquelas motocas motorizadas. Pois é, nós vamos modelar e implementar uma delas.

## Requisitos

- Você deverá implementar a classe `Pessoa` e a class `Moto`.
- Iniciar
    - A moto inicia com 1 de potência, sem minutos e sem ninguém.
- Subir
    - Só pode estar uma pessoa na moto por vez. Para subir, informe nome e idade de quem está subindo.
- Descer
    - Só pode descer se tiver alguém na moto.
- Comprar tempo
    - O tempo em minutos é comprado e enquanto houver tempo, qualquer pessoa pode dirigir.
- Dirigir tempo
    - Se houver uma pessoa com 10 anos ou menos e houver minutos, então ela pode passear de moto.
    - Se o tempo acabar no meio do passeio, informe o quanto a pessoa andou.
- Buzinar
    - Qualquer pessoa pode buzinar(honk)
    - O barulho da buzina é "Pem", porém o número de `e` é igual ao valor da potência.
    - Ex: se a potência for 5, buzinar deve gerar: Peeeeem


## Shell

```bash

#__case subindo e buzinando
$show
potencia: 1, minutos: 0, pessoa: null
$honk
fail: moto vazia
$in marcos 4
$show
potencia: 1, minutos: 0, pessoa: [marcos:4]
$honk
Pem
$in marisa 2
fail: moto ocupada
$show
potencia: 1, minutos: 0, pessoa: [marcos:4]
$end
```

```bash
#__case subindo e buzinando
$init 5
$show
potencia: 5, minutos: 0, pessoa: null
$in marcos 4
$show
potencia: 5, minutos: 0, pessoa: [marcos:4]
$honk
Peeeeem
$end
```

```bash
#__case subindo e trocando
$init 7
$in heitor 6
$show
potencia: 7, minutos: 0, pessoa: [heitor:6]
$out
$out
fail: moto vazia
$in suzana 8
$show
potencia: 7, minutos: 0, pessoa: [suzana:8]
$end
```

```bash
#__case passeando
$init 7
$in suzana 8
$drive 10
fail: tempo zerado
$buy 40
$show
potencia: 7, minutos: 40, pessoa: [suzana:8]
$drive 20
$show
potencia: 7, minutos: 20, pessoa: [suzana:8]
$end
```

```bash
#__case nem grande nem pequeno
$init 7
$buy 20
$in andreina 23
$drive 15
fail: muito grande para andar de moto
$show
potencia: 7, minutos: 20, pessoa: [andreina:23]
$end
```

```bash
#__case acabou o tempo
$init 7
$buy 20
$in andreina 6
$drive 15
$show
potencia: 7, minutos: 5, pessoa: [andreina:6]
$drive 10
fail: andou 5 min e acabou o tempo
$end
```

***
## Ajuda
    - Lembre de inicializar o objeto `Pessoa` antes de chamar o método embarcar.
    - Para buzinar, utilize o `for` gerando várias vezes o `e`. 

***
## Diagrama
![](diagrama.png)


***
## Esqueleto
<!--FILTER Solver.java java-->
```java
class Person {
    public String name;
    public int age;
    public Person(String name, int age);
    public String toString();
}
class Motorcycle {
    public Person person; //agregacao
    public int power;
    public int time;
    //Inicia o atributo power, time com zero e person com null
    public Motorcycle(int power);
    //Comprar mais tempo
    public void buy(int time);
    //Se estiver vazio, coloca a pessoa na moto e retorna true
    public boolean in(Person person);
    //Se houver uma person, retira e retorna
    //Se não, retorna null
    public Person out();
    public void drive(int time);
    //buzinar
    public void honk();
    public String toString();
}

class Solver{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Motorcycle motoca  = new Motorcycle(1);
        while(true) {
            String line = scanner.nextLine();
            String ui[] = line.split(" "); //ui user input eh um vetor de strings
            System.out.println("$" + line);
            if(ui[0].equals("end")) {
                break;
            }else if(ui[0].equals("init")) { //power
                Person person = motoca.person;
                motoca = new Motorcycle(Integer.parseInt(ui[1]));
                motoca.in(person);
            }else if(ui[0].equals("in")) { //in name age
                int age = Integer.parseInt(ui[2]);
                Person person = new Person(ui[1], age);
                motoca.in(person);
            }else if(ui[0].equals("out")) {
                motoca.out();
            }else if(ui[0].equals("show")) {
                System.out.println(motoca);
            }else if(ui[0].equals("drive")) {
                motoca.drive(Integer.parseInt(ui[1]));
            }else if(ui[0].equals("buy")) {
                motoca.buy(Integer.parseInt(ui[1]));
            }else if(ui[0].equals("honk")) {
                motoca.honk();
            }else {
                System.out.println("Comando invalido");
            }
        }
        scanner.close();
    }
}

class Manual{
    public static void main(String[] args) {
        //case subindo e buzinando
        Motorcycle moto = new Motorcycle(1);
        System.out.println(moto);
        //power: 1, minutos: 0, person: null
        moto.honk();
        //fail: moto vazia
        moto.in(new Person("marcos", 4));
        System.out.println(moto);
        //power: 1, minutos: 0, person: [marcos:4]
        moto.honk();
        //Pem
        moto.in(new Person("marisa", 2));
        //fail: moto ocupada
        System.out.println(moto);
        //power: 1, minutos: 0, person: [marcos:4]

        //case subindo e buzinando
        moto = new Motorcycle(5);
        System.out.println(moto);
        //power: 5, minutos: 0, person: null
        moto.in(new Person("marcos", 4));
        System.out.println(moto);
        //power: 5, minutos: 0, person: [marcos:4]
        moto.honk();
        //Peeeeem

        //case subindo e trocando
        moto = new Motorcycle(7);
        moto.in(new Person("heitor", 6));
        System.out.println(moto);
        //power: 7, minutos: 0, person: [heitor:6]
        Person heitor = moto.out();
        System.out.println(heitor);
        //[heitor:6]
        moto.out();
        //fail: moto vazia
        moto.in(new Person("suzana", 8));
        System.out.println(moto);
        //power: 7, minutos: 0, person: [suzana:8]

        //case passeando
        moto = new Motorcycle(7);
        moto.in(new Person("suzana", 8));
        moto.drive(10);
        //fail: time zerado
        moto.buy(40);
        System.out.println(moto);
        //power: 7, minutos: 40, person: [suzana:8]
        moto.drive(20);
        System.out.println(moto);
        //power: 7, minutos: 20, person: [suzana:8]

        //case nem grande nem pequeno
        moto = new Motorcycle(7);
        moto.buy(20);
        moto.in(new Person("andreina", 23));
        moto.drive(15);
        //fail: muito grande para andar de moto
        System.out.println(moto);
        //power: 7, minutos: 20, person: [andreina:23]

        //case acabou o time
        moto = new Motorcycle(7);
        moto.buy(20);
        moto.in(new Person("andreina", 6));
        moto.drive(15);
        System.out.println(moto);
        //power: 7, minutos: 5, person: [andreina:6]
        moto.drive(10);
        //fail: andou 5 min e acabou o time
    }
}
```

<!--FILTER_END-->
